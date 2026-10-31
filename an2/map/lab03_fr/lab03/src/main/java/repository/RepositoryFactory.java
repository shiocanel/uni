package repository;

import domain.model.Friendship;
import domain.model.User;
import exception.RepositoryException;
import repository.database.PrietenieDbRepository;
import repository.database.UtilizatorDbRepository;
import repository.file.FriendshipFileRepository;
import repository.file.UserFileRepository;
import repository.memory.InMemoryFriendshipRepository;
import repository.memory.InMemoryUserRepository;
import validation.ValidationStrategy;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Paths;
import java.util.Properties;
import java.util.Locale;

/**
 * Simple Factory that is the only class selecting concrete repository implementations.
 * Settings are read from src/main/resources/config.properties via the classpath.
 */
public final class RepositoryFactory {
    private final Properties properties;
    private final RepositoryType repositoryType;

    /** Loads and validates the repository configuration. */
    public RepositoryFactory() {
        this.properties = loadProperties();
        String configuredType = requireProperty("repository.type");
        try {
            this.repositoryType = RepositoryType.valueOf(configuredType.toUpperCase(Locale.ROOT));
        } catch (IllegalArgumentException exception) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + configuredType
                    + ". Valorile acceptate sunt MEMORY, FILE si DATABASE.", exception);
        }
    }

    /**
     * Creates a user repository according to the selected persistence type.
     *
     * @param validator validation strategy for users
     * @return a repository interface backed by the selected storage type
     */
    public UserRepository createUtilizatorRepository(ValidationStrategy<User> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul pentru utilizatori este obligatoriu.");
        switch (repositoryType) {
            case MEMORY:
                return new InMemoryUserRepository(validator);
            case FILE:
                return new UserFileRepository(Paths.get(requireProperty("file.users")), validator);
            case DATABASE:
                return new UtilizatorDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password"));
            default:
                throw new RepositoryException("Tip de repository nesuportat: " + repositoryType);
        }
    }

    /**
     * Creates a friendship repository according to the selected persistence type.
     *
     * @param validator validation strategy for friendships
     * @return a repository interface backed by the selected storage type
     */
    public FriendshipRepository createPrietenieRepository(ValidationStrategy<Friendship> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul pentru prietenii este obligatoriu.");
        switch (repositoryType) {
            case MEMORY:
                return new InMemoryFriendshipRepository(validator);
            case FILE:
                return new FriendshipFileRepository(Paths.get(requireProperty("file.friendships")), validator);
            case DATABASE:
                return new PrietenieDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password"));
            default:
                throw new RepositoryException("Tip de repository nesuportat: " + repositoryType);
        }
    }

    /** @return active persistence type */
    public RepositoryType getRepositoryType() {
        return repositoryType;
    }

    private Properties loadProperties() {
        Properties loaded = new Properties();
        InputStream resource = RepositoryFactory.class.getResourceAsStream("/config.properties");
        if (resource == null) {
            throw new RepositoryException("Nu gasesc config.properties in src/main/resources.");
        }
        try (InputStream input = resource) {
            loaded.load(input);
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot citi config.properties.", exception);
        }
        return loaded;
    }

    private String requireProperty(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.trim().isEmpty()) {
            throw new RepositoryException("Lipseste proprietatea obligatorie '" + key + "' din config.properties.");
        }
        return value.trim();
    }
}
