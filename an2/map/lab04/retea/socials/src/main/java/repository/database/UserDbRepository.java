package repository.database;

import domain.model.User;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.util.List;
import java.util.Optional;

/** Database repository skeleton. JDBC implementation belongs to Lab 5. */
public final class UserDbRepository implements UserRepository {
    private final ValidationStrategy<User> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates the repository skeleton with the configuration needed for the next lab.
     *
     * @param validator user validator
     * @param url JDBC URL
     * @param user database user
     * @param password database password
     */
    public UserDbRepository(ValidationStrategy<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    private UnsupportedOperationException notImplemented() {
        return new UnsupportedOperationException(
                "Repository-ul JDBC pentru utilizatori se implementeaza la Laboratorul 5.");
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 5
     */
    @Override
    public List<User> findAll() {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 5
     */
    @Override
    public Optional<User> findById(Long id) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 5
     */
    @Override
    public void save(User entity) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 5
     */
    @Override
    public void update(User entity) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 5
     */
    @Override
    public void deleteById(Long id) {
        throw notImplemented();
    }
}
