package repository.database;

import domain.model.User;
import repository.PagingRepository;
import repository.UserRepository;
import validation.ValidationStrategy;
import util.paging.Page;
import util.paging.Pageable;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

/**
 * PostgreSQL repository for users.
 *
 * @see UserRepository
 */
public final class UserDbRepository extends JdbcRepositorySupport implements UserRepository, PagingRepository<Long, User> {
    private static final String SELECT_ALL =
            "SELECT id, first_name, last_name, email, birth_date, description FROM users ORDER BY id";
    private static final String SELECT_PAGE =
            "SELECT id, first_name, last_name, email, birth_date, description FROM users ORDER BY id LIMIT ? OFFSET ?";
    private static final String COUNT_ALL = "SELECT COUNT(*) FROM users";
    private static final String SELECT_BY_ID =
            "SELECT id, first_name, last_name, email, birth_date, description FROM users WHERE id = ?";
    private static final String INSERT =
            "INSERT INTO users (first_name, last_name, email, birth_date, description) VALUES (?, ?, ?, ?, ?) RETURNING id";
    private static final String UPDATE =
            "UPDATE users SET first_name = ?, last_name = ?, email = ?, birth_date = ?, description = ? WHERE id = ?";
    private static final String DELETE =
            "DELETE FROM users WHERE id = ? RETURNING id, first_name, last_name, email, birth_date, description";

    private final ValidationStrategy<User> validator;

    /**
     * Creates the database repository.
     *
     * @param validator strategy used before save and update
     * @param url PostgreSQL JDBC URL
     * @param user database username
     * @param password database password
     */
    public UserDbRepository(ValidationStrategy<User> validator, String url, String user, String password) {
        super(url, user, password);
        if (validator == null) {
            throw new IllegalArgumentException("User validator is required.");
        }
        this.validator = validator;
    }

    /**
     * {@inheritDoc}
     *
     * @return all users stored in PostgreSQL
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public List<User> findAll() {
        List<User> users = new ArrayList<User>();

        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(SELECT_ALL);
             ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                users.add(readUser(resultSet));
            }
            return users;
        } catch (SQLException exception) {
            throw translate(exception, "load users");
        }
    }

    /**
     * Retrieves one page of users and obtains the total count on the same JDBC connection.
     *
     * @param pageable zero-based page request
     * @return requested users and the total number of users
     * @throws IllegalArgumentException when pageable is null
     * @throws exception.RepositoryException when either SQL query fails
     */
    @Override
    public Page<User> findAllOnPage(Pageable pageable) {
        if (pageable == null) {
            throw new IllegalArgumentException("Pageable cannot be null.");
        }

        try (Connection connection = openConnection()) {
            long totalNumberOfUsers;
            try (PreparedStatement countStatement = connection.prepareStatement(COUNT_ALL);
                 ResultSet countResult = countStatement.executeQuery()) {
                if (!countResult.next()) {
                    throw new SQLException("COUNT(*) did not return a result.");
                }
                totalNumberOfUsers = countResult.getLong(1);
            }

            List<User> users = new ArrayList<User>();
            try (PreparedStatement pageStatement = connection.prepareStatement(SELECT_PAGE)) {
                pageStatement.setInt(1, pageable.getPageSize());
                pageStatement.setLong(2, pageable.getOffset());
                try (ResultSet pageResult = pageStatement.executeQuery()) {
                    while (pageResult.next()) {
                        users.add(readUser(pageResult));
                    }
                }
            }
            return new Page<User>(users, totalNumberOfUsers);
        } catch (SQLException exception) {
            throw translate(exception, "load a page of users");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param id user ID to find
     * @return the user when it exists, otherwise an empty Optional
     * @throws IllegalArgumentException when id is null
     * @throws exception.RepositoryException when the database query fails
     */
    @Override
    public Optional<User> findById(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("User ID cannot be null.");
        }
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(SELECT_BY_ID)) {
            statement.setLong(1, id);
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next() ? Optional.of(readUser(resultSet)) : Optional.<User>empty();
            }
        } catch (SQLException exception) {
            throw translate(exception, "find a user");
        }
    }

    /**
     * Inserts a user and reads the ID generated by PostgreSQL.
     *
     * @param user user to insert; its ID must be null
     * @return user populated with the generated ID
     * @throws IllegalArgumentException when user is null or already has an ID
     * @throws exception.RepositoryException when the insert fails
     */
    @Override
    public User save(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User cannot be null.");
        }
        if (user.getId() != null) {
            throw new IllegalArgumentException("A new database user must not have an ID.");
        }
        validator.validate(user);

        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(INSERT)) {
            bindUserFields(statement, user);
            try (ResultSet resultSet = statement.executeQuery()) {
                if (!resultSet.next()) {
                    throw new SQLException("PostgreSQL did not return the generated user ID.");
                }
                return new User(resultSet.getLong(1), user.getFirstName(), user.getLastName(),
                        user.getEmail(), user.getBirthDate(), user.getDescription());
            }
        } catch (SQLException exception) {
            throw translate(exception, "save a user");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param user user with updated values and an existing ID
     * @return the updated user, or empty when the ID does not exist
     * @throws IllegalArgumentException when user or its ID is null
     * @throws exception.RepositoryException when the database update fails
     */
    @Override
    public Optional<User> update(User user) {
        if (user == null || user.getId() == null) {
            throw new IllegalArgumentException("User and user ID cannot be null for update.");
        }
        validator.validate(user);

        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(UPDATE)) {
            bindUserFields(statement, user);
            statement.setLong(6, user.getId());
            int affectedRows = statement.executeUpdate();
            return affectedRows == 1 ? Optional.of(user) : Optional.<User>empty();
        } catch (SQLException exception) {
            throw translate(exception, "update a user");
        }
    }

    /**
     * {@inheritDoc}
     *
     * @param id ID of the user to delete
     * @return the deleted user, or empty when the ID does not exist
     * @throws IllegalArgumentException when id is null
     * @throws exception.RepositoryException when the database delete fails
     */
    @Override
    public Optional<User> deleteById(Long id) {
        if (id == null) {
            throw new IllegalArgumentException("User ID cannot be null.");
        }
        try (Connection connection = openConnection();
             PreparedStatement statement = connection.prepareStatement(DELETE)) {
            statement.setLong(1, id);
            try (ResultSet resultSet = statement.executeQuery()) {
                return resultSet.next() ? Optional.of(readUser(resultSet)) : Optional.<User>empty();
            }
        } catch (SQLException exception) {
            throw translate(exception, "delete a user");
        }
    }

    private void bindUserFields(PreparedStatement statement, User user) throws SQLException {
        statement.setString(1, user.getFirstName());
        statement.setString(2, user.getLastName());
        statement.setString(3, user.getEmail());
        statement.setString(4, user.getBirthDate());
        statement.setString(5, user.getDescription());
    }

    private User readUser(ResultSet resultSet) throws SQLException {
        return new User(resultSet.getLong("id"),
                resultSet.getString("first_name"),
                resultSet.getString("last_name"),
                resultSet.getString("email"),
                resultSet.getString("birth_date"),
                resultSet.getString("description"));
    }
}
