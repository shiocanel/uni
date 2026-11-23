package repository;

import domain.model.Friendship;
import domain.model.User;
import exception.RepositoryException;
import repository.database.FriendshipDbRepository;
import repository.database.UserDbRepository;
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

/** Creates repository implementations based on config.properties. */
public final class RepositoryFactory {
    private final Properties properties;
    private final RepositoryType repositoryType;
    private final int pageSize;
    private final Map<RepositoryType, Function<ValidationStrategy<User>, UserRepository>> userCreators;
    private final Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>> friendshipCreators;

    /**
     * Loads configuration and prepares the repository creators.
     *
     * @throws RepositoryException when configuration is missing or invalid
     */
    public RepositoryFactory() {
        this.properties = loadProperties();
        String configuredType = requireProperty("repository.type");
        try {
            this.repositoryType = RepositoryType.valueOf(configuredType.toUpperCase(Locale.ROOT));
        } catch (IllegalArgumentException exception) {
            throw new RepositoryException("Unknown repository.type: " + configuredType
                    + ". Accepted values are MEMORY, FILE and DATABASE.", exception);
        }
        this.pageSize = repositoryType == RepositoryType.DATABASE ? loadPageSize() : 0;
        this.userCreators = createUserCreators();
        this.friendshipCreators = createFriendshipCreators();
    }

    /**
     * Creates a user repository using the function registered for the active type.
     *
     * @param validator validation strategy for users
     * @return repository for users
     * @throws IllegalArgumentException when validator is null
     * @throws RepositoryException when no creator is registered
     */
    public UserRepository createUserRepository(ValidationStrategy<User> validator) {
        if (validator == null) {
            throw new IllegalArgumentException("User validator is required.");
        }
        Function<ValidationStrategy<User>, UserRepository> creator = userCreators.get(repositoryType);
        if (creator == null) {
            throw new RepositoryException("No user repository creator for " + repositoryType + ".");
        }
        return creator.apply(validator);
    }

    /**
     * Creates a friendship repository using the function registered for the active type.
     *
     * @param validator validation strategy for friendships
     * @return repository for friendships
     * @throws IllegalArgumentException when validator is null
     * @throws RepositoryException when no creator is registered
     */
    public FriendshipRepository createFriendshipRepository(ValidationStrategy<Friendship> validator) {
        if (validator == null) {
            throw new IllegalArgumentException("Friendship validator is required.");
        }
        Function<ValidationStrategy<Friendship>, FriendshipRepository> creator =
                friendshipCreators.get(repositoryType);
        if (creator == null) {
            throw new RepositoryException("No friendship repository creator for " + repositoryType + ".");
        }
        return creator.apply(validator);
    }

    /**
     * Returns the page size configured for DATABASE storage.
     *
     * @return configured number of elements per page, or zero when paging is not enabled
     */
    public int getPageSize() {
        return pageSize;
    }

    private int loadPageSize() {
        String configuredSize = requireProperty("paging.page-size");
        try {
            int parsedSize = Integer.parseInt(configuredSize);
            if (parsedSize <= 0) {
                throw new NumberFormatException("value must be positive");
            }
            return parsedSize;
        } catch (NumberFormatException exception) {
            throw new RepositoryException(
                    "Property 'paging.page-size' must be a positive integer in config.properties.", exception);
        }
    }

    /**
     * Returns the active persistence type.
     *
     * @return active persistence type
     */
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
                validator -> new UserDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password")));
        return Collections.unmodifiableMap(creators);
    }

    private Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>>
    createFriendshipCreators() {
        Map<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>> creators =
                new EnumMap<RepositoryType, Function<ValidationStrategy<Friendship>, FriendshipRepository>>(
                        RepositoryType.class);
        creators.put(RepositoryType.MEMORY, InMemoryFriendshipRepository::new);
        creators.put(RepositoryType.FILE,
                validator -> new FriendshipFileRepository(Paths.get(requireProperty("file.friendships")), validator));
        creators.put(RepositoryType.DATABASE,
                validator -> new FriendshipDbRepository(validator, requireProperty("db.url"),
                        requireProperty("db.user"), requireProperty("db.password")));
        return Collections.unmodifiableMap(creators);
    }

    private Properties loadProperties() {
        Properties loaded = new Properties();
        InputStream resource = RepositoryFactory.class.getResourceAsStream("/config.properties");
        if (resource == null) {
            throw new RepositoryException(
                    "config.properties was not found in src/main/resources. Copy config.example.properties first.");
        }
        try (InputStream input = resource) {
            loaded.load(input);
        } catch (IOException exception) {
            throw new RepositoryException("Could not read config.properties.", exception);
        }
        return loaded;
    }

    private String requireProperty(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.trim().isEmpty()) {
            throw new RepositoryException("Missing required property '" + key + "' in config.properties.");
        }
        return value.trim();
    }
}
