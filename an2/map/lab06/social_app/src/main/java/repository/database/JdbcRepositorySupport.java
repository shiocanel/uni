package repository.database;

import exception.RepositoryException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * Common JDBC connection and SQL exception handling for database repositories.
 */
public abstract class JdbcRepositorySupport {
    private final String url;
    private final String user;
    private final String password;

    /**
     * Creates the JDBC support object.
     *
     * @param url PostgreSQL JDBC URL
     * @param user database username
     * @param password database password
     * @throws IllegalArgumentException when a connection parameter is null or blank
     */
    protected JdbcRepositorySupport(String url, String user, String password) {
        if (isBlank(url) || isBlank(user) || password == null) {
            throw new IllegalArgumentException("Database connection settings are required.");
        }
        this.url = url.trim();
        this.user = user.trim();
        this.password = password;
    }

    /**
     * Opens a new JDBC connection.
     *
     * @return open database connection
     * @throws SQLException when PostgreSQL cannot be reached or authentication fails
     */
    protected Connection openConnection() throws SQLException {
        return DriverManager.getConnection(url, user, password);
    }

    /**
     * Converts an SQLException into an application-level repository exception.
     *
     * @param exception original SQL exception
     * @param operation short description of the attempted operation
     * @return repository exception with a user-friendly message
     */
    protected RepositoryException translate(SQLException exception, String operation) {
        String state = exception.getSQLState();
        if (state != null && state.startsWith("08")) {
            return new RepositoryException(
                    "PostgreSQL error: " + exception.getMessage()
                            + " | SQLState: " + exception.getSQLState(),
                    exception
            );
        }
        if (state != null && state.startsWith("28")) {
            return new RepositoryException(
                    "PostgreSQL rejected the credentials. Check db.user and db.password in config.properties.");
        }
        if (state != null && state.startsWith("23")) {
            return new RepositoryException(
                    "The database rejected the operation because a constraint was violated. Check the IDs and entered values.");
        }
        return new RepositoryException(
                "Database operation failed while trying to " + operation
                        + (state == null ? "." : " (SQL state " + state + ")."));
    }

    private boolean isBlank(String value) {
        return value == null || value.trim().isEmpty();
    }
}
