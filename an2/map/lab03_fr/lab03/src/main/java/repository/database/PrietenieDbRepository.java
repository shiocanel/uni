package repository.database;

import domain.model.Friendship;
import domain.model.FriendshipId;
import repository.FriendshipRepository;
import validation.ValidationStrategy;

import java.util.List;
import java.util.Optional;

/** Database friendship repository skeleton. JDBC implementation belongs to Lab 4. */
public final class PrietenieDbRepository implements FriendshipRepository {
    private final ValidationStrategy<Friendship> validator;
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates the repository skeleton with the configuration needed for the next lab.
     *
     * @param validator friendship validator
     * @param url JDBC URL
     * @param user database user
     * @param password database password
     */
    public PrietenieDbRepository(ValidationStrategy<Friendship> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    private UnsupportedOperationException notImplemented() {
        return new UnsupportedOperationException(
                "Repository-ul JDBC pentru prietenii se implementeaza la Laboratorul 4.");
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public List<Friendship> findAll() {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public Optional<Friendship> findById(FriendshipId id) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public void save(Friendship entity) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public void update(Friendship entity) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public void deleteById(FriendshipId id) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public Optional<Friendship> findByUsers(long firstUserId, long secondUserId) {
        throw notImplemented();
    }

    /**
     * {@inheritDoc}
     * @throws UnsupportedOperationException database storage is implemented in Lab 4
     */
    @Override
    public void deleteByUserId(long userId) {
        throw notImplemented();
    }
}
