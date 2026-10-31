package repository.factory;

import domain.validators.Validator;

import java.util.Locale;
import java.util.Properties;

public class RepositoryFactory {
    private Properties properties;
    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    public Repository<Long, User> createUserRepository(Validator<User> validator) {
        String property = properties.getProperty("repository.type");
        RepositoryType type = RepositoryType.valuOf(property.trim().toUpperCase());

        switch (type){
            case MEMORY:
                return new InMemoryRepository<>(validator);
            case FILE:
                return new UserFileRepository<>(validator);
            case DATABASE:
                return new DatabaseRepository<>(validator, properties.getProperty("url"),
                        properties.getProperty("username"),
                        properties.getProperty("password"));
            default:
                throw new UnsupportedOperationException("Invalid repository type");
        }

    }
}
