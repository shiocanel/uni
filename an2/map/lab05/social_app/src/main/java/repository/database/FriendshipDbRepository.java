package repository.database;

import domain.model.Friendship;
import domain.model.FriendshipId;
import repository.FriendshipRepository;
import validation.ValidationStrategy;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/** PostgreSQL repository for undirected friendships. */
public final class FriendshipDbRepository extends JdbcRepositorySupport implements FriendshipRepository {
    private static final String SELECT_ALL =
            "SELECT id1, id2, friends_from FROM friendships ORDER BY id1, id2";
    private static final String SELECT_BY_ID =
            "SELECT id1, id2, friends_from FROM friendships WHERE id1 = ? AND id2 = ?";
    private static final String INSERT =
            "INSERT INTO friendships (id1, id2, friends_from) VALUES (?, ?, ?)";
    private static final String UPDATE =
            "UPDATE friendships SET friends_from = ? WHERE id1 = ? AND id2 = ?";
    private static final String DELETE =
            "DELETE FROM friendships WHERE id1 = ? AND id2 = ? RETURNING id1, id2, friends_from";
    private static final String DELETE_BY_USER =
            "DELETE FROM friendships WHERE id1 = ? OR id2 = ?";

    private final ValidationStrategy<Friendship> validator;

    /**
     * Creates the database repository.
     *
     * @param validator strategy used before save and update
     * @param url PostgreSQL JDBC URL
     * @param user database username
     * @param password database password
     */
    public FriendshipDbRepository(ValidationStrategy<Friendship> validator,
                                  String url, String user, String password) {
        super(url, user, password);
        if (validator == null) {
            throw new IllegalArgumentException("Friendship validator is required.");
        }
        this.validator = validator;
    }

    /**
     * {@inheritDoc}
     *
     * @return all friendships stored in PostgreSQL
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public List<Friendship> findAll() {
        List<Friendship> friendships = new ArrayList<Friendship>();
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(SELECT_ALL);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                friendships.add(readFriendship(resultSet));
            }
            return friendships;
        } catch (SQLException exception) {
            throw translate(exception, "load friendships");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param id normalized friendship ID
     * @return the friendship when present, otherwise an empty Optional
     * @throws IllegalArgumentException when id is null
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public Optional<Friendship> findById(FriendshipId id) {
        if (id == null) {
            throw new IllegalArgumentException("Friendship ID cannot be null.");
        }
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(SELECT_BY_ID)) {
            statement.setLong(1, id.getFirstUserId());
            statement.setLong(2, id.getSecondUserId());
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next()
                        ? Optional.of(readFriendship(resultSet))
                        : Optional.<Friendship>empty();
            }
        } catch (SQLException exception) {
            throw translate(exception, "find a friendship");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param friendship friendship to insert
     * @return the inserted friendship
     * @throws IllegalArgumentException when friendship is null
     * @throws exception.RepositoryException when the insert fails
     */
    @Override
    public Friendship save(Friendship friendship) {
        if (friendship == null) {
            throw new IllegalArgumentException("Friendship cannot be null.");
        }
        validator.validate(friendship);

        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(INSERT)) {
            statement.setLong(1, friendship.getFirstUserId());
            statement.setLong(2, friendship.getSecondUserId());
            statement.setTimestamp(3, Timestamp.valueOf(friendship.getDate()));
            statement.executeUpdate();
            return friendship;
        } catch (SQLException exception) {
            throw translate(exception, "save a friendship");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param friendship friendship containing the updated timestamp
     * @return the updated friendship, or empty when it does not exist
     * @throws IllegalArgumentException when friendship or its ID is null
     * @throws exception.RepositoryException when the update fails
     */
    @Override
    public Optional<Friendship> update(Friendship friendship) {
        if (friendship == null || friendship.getId() == null) {
            throw new IllegalArgumentException("Friendship and its ID cannot be null for update.");
        }
        validator.validate(friendship);

        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(UPDATE)) {
            statement.setTimestamp(1, Timestamp.valueOf(friendship.getDate()));
            statement.setLong(2, friendship.getFirstUserId());
            statement.setLong(3, friendship.getSecondUserId());
            int affectedRows = statement.executeUpdate();
            return affectedRows == 1 ? Optional.of(friendship) : Optional.<Friendship>empty();
        } catch (SQLException exception) {
            throw translate(exception, "update a friendship");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param id ID of the friendship to delete
     * @return the deleted friendship, or empty when it does not exist
     * @throws IllegalArgumentException when id is null
     * @throws exception.RepositoryException when the delete fails
     */
    @Override
    public Optional<Friendship> deleteById(FriendshipId id) {
        if (id == null) {
            throw new IllegalArgumentException("Friendship ID cannot be null.");
        }
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(DELETE)) {
            statement.setLong(1, id.getFirstUserId());
            statement.setLong(2, id.getSecondUserId());
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next()
                        ? Optional.of(readFriendship(resultSet))
                        : Optional.<Friendship>empty();
            }
        } catch (SQLException exception) {
            throw translate(exception, "delete a friendship");
        }
    }

    /**
     * Finds a friendship between two users regardless of the argument order.
     *
     * @param firstUserId first user ID
     * @param secondUserId second user ID
     * @return the friendship when present
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public Optional<Friendship> findByUsers(long firstUserId, long secondUserId) {
        return findById(new FriendshipId(firstUserId, secondUserId));
    }

    /**
     * Deletes all friendships involving one user.
     *
     * @param userId ID of the user
     * @throws IllegalArgumentException when userId is not positive
     * @throws exception.RepositoryException when the database delete fails
     */
    @Override
    public void deleteByUserId(long userId) {
        if (userId <= 0) {
            throw new IllegalArgumentException("User ID must be positive.");
        }
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(DELETE_BY_USER)) {
            statement.setLong(1, userId);
            statement.setLong(2, userId);
            statement.executeUpdate();
        } catch (SQLException exception) {
            throw translate(exception, "delete a user's friendships");
        }
    }

    private Friendship readFriendship(ResultSet resultSet) throws SQLException {
        return new Friendship(resultSet.getLong("id1"), resultSet.getLong("id2"),
                resultSet.getTimestamp("friends_from").toLocalDateTime());
    }
}
