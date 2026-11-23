package repository.database;

import domain.model.Friendship;
import domain.model.FriendshipId;
import domain.model.User;
import repository.FriendshipPagingRepository;
import validation.ValidationStrategy;
import util.paging.Page;
import util.paging.Pageable;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/** PostgreSQL repository for undirected friendships. */
public final class FriendshipDbRepository extends JdbcRepositorySupport implements FriendshipPagingRepository {
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
    /* One SQL statement: join friends to users, count all matches, and page in PostgreSQL. */
    private static final String SELECT_FRIENDS_PAGE =
            "WITH friends AS ("
                    + " SELECT u.id, u.first_name, u.last_name, u.email, u.birth_date, u.description"
                    + " FROM friendships f JOIN users u"
                    + " ON u.id = CASE WHEN f.id1 = ? THEN f.id2 ELSE f.id1 END"
                    + " WHERE f.id1 = ? OR f.id2 = ?"
                    + "), total AS ("
                    + " SELECT COUNT(*) AS total_number FROM friends"
                    + "), paged AS ("
                    + " SELECT id, first_name, last_name, email, birth_date, description"
                    + " FROM friends ORDER BY id LIMIT ? OFFSET ?"
                    + ")"
                    + " SELECT paged.id, paged.first_name, paged.last_name, paged.email,"
                    + " paged.birth_date, paged.description, total.total_number"
                    + " FROM total LEFT JOIN paged ON TRUE ORDER BY paged.id";

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
     * Retrieves one page of a user's friends using a single joined SQL statement.
     * The CTE also returns the total count when the requested page is empty or out of range.
     *
     * @param userId ID of the user whose friends are requested
     * @param pageable zero-based page request
     * @return requested friend users and the total number of friends
     * @throws IllegalArgumentException when userId is null/non-positive or pageable is null
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public Page<User> findFriendsOnPage(Long userId, Pageable pageable) {
        if (userId == null || userId.longValue() <= 0) {
            throw new IllegalArgumentException("User ID must be a positive value.");
        }
        if (pageable == null) {
            throw new IllegalArgumentException("Pageable cannot be null.");
        }

        List<User> friends = new ArrayList<User>();
        long totalNumberOfFriends = 0;
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(SELECT_FRIENDS_PAGE)) {
            statement.setLong(1, userId);
            statement.setLong(2, userId);
            statement.setLong(3, userId);
            statement.setInt(4, pageable.getPageSize());
            statement.setLong(5, pageable.getOffset());

            try (ResultSet resultSet = statement.executeQuery()) {
                while (resultSet.next()) {
                    totalNumberOfFriends = resultSet.getLong("total_number");
                    Object friendId = resultSet.getObject("id");
                    // The LEFT JOIN returns one count row with null user columns for an empty page.
                    if (friendId != null) {
                        friends.add(new User(((Number) friendId).longValue(),
                                resultSet.getString("first_name"),
                                resultSet.getString("last_name"),
                                resultSet.getString("email"),
                                resultSet.getString("birth_date"),
                                resultSet.getString("description")));
                    }
                }
            }
            return new Page<User>(friends, totalNumberOfFriends);
        } catch (SQLException exception) {
            throw translate(exception, "load a page of a user's friends");
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
