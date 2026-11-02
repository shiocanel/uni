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
import java.util.Collections;
import java.util.EnumMap;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.function.Function;

/**
 * Factory that is the only class selecting concrete repository implementations.
 * Repository construction is delegated to functions indexed by persistence type.
 */
public final class RepositoryFactory {
    private final Properties properties;
    private final RepositoryType repositoryType;
    private final Map<RepositoryType, Function<ValidationStrategy<User>, UserRepository>> userCreators;
    private final Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>> friendshipCreators;

    /** Loads configuration and prepares the repository constructor maps. */
    public RepositoryFactory() {
        this.properties = loadProperties();
        String configuredType = requireProperty("repository.type");
        try {
            this.repositoryType = RepositoryType.valueOf(configuredType.toUpperCase(Locale.ROOT));
        } catch (IllegalArgumentException exception) {
            throw new RepositoryException("Valoare necunoscuta pentru repository.type: " + configuredType
                    + ". Valorile acceptate sunt MEMORY, FILE si DATABASE.", exception);
        }
        this.userCreators = createUserCreators();
        this.friendshipCreators = createFriendshipCreators();
    }

    /**
     * Creates a user repository using the function registered for the active type.
     *
     * @param validator validation strategy for users
     * @return a repository interface backed by the selected storage type
     * @throws IllegalArgumentException when validator is null
     * @throws RepositoryException when no constructor is registered for the active type
     */
    public UserRepository createUtilizatorRepository(ValidationStrategy<User> validator) {
        if (validator == null) {
            throw new IllegalArgumentException("Validatorul pentru utilizatori este obligatoriu.");
        }
        Function<ValidationStrategy<User>, UserRepository> creator = userCreators.get(repositoryType);
        if (creator == null) {
            throw new RepositoryException("Nu exista un factory pentru utilizatori de tipul " + repositoryType + ".");
        }
        return creator.apply(validator);
    }

    /**
     * Creates a friendship repository using the function registered for the active type.
     *
     * @param validator validation strategy for friendships
     * @return a repository interface backed by the selected storage type
     * @throws IllegalArgumentException when validator is null
     * @throws RepositoryException when no constructor is registered for the active type
     */
    public FriendshipRepository createPrietenieRepository(ValidationStrategy<Friendship> validator) {
        if (validator == null) {
            throw new IllegalArgumentException("Validatorul pentru prietenii este obligatoriu.");
        }
        Function<ValidationStrategy<Friendship>, FriendshipRepository> creator = friendshipCreators.get(repositoryType);
        if (creator == null) {
            throw new RepositoryException("Nu exista un factory pentru prietenii de tipul " + repositoryType + ".");
        }
        return creator.apply(validator);
    }

    /** @return active persistence type */
    public RepositoryType getRepositoryType() {
        return repositoryType;
    }

    private Map<RepositoryType, Function<ValidationStrategy<User>, UserRepository>> createUserCreators() {
        Map<RepositoryType, Function<ValidationStrategy<User>, UserRepository>> creators =
                new EnumMap<RepositoryType, Function<ValidationStrategy<User>, UserRepository>>(RepositoryType.class);
        creators.put(RepositoryType.MEMORY, InMemoryUserRepository::new);
        creators.put(RepositoryType.FILE,
                validator -> new UserFileRepository(Paths.get(requireProperty("file.users")), validator));
        creators.put(RepositoryType.DATABASE,
                validator -> new UtilizatorDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password")));
        return Collections.unmodifiableMap(creators);
    }

    private Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>> createFriendshipCreators() {
        Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>> creators =
                new EnumMap<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>>(RepositoryType.class);
        creators.put(RepositoryType.MEMORY, InMemoryFriendshipRepository::new);
        creators.put(RepositoryType.FILE,
                validator -> new FriendshipFileRepository(Paths.get(requireProperty("file.friendships")), validator));
        creators.put(RepositoryType.DATABASE,
                validator -> new PrietenieDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password")));
        return Collections.unmodifiableMap(creators);
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
