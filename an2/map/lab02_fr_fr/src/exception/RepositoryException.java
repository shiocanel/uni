package exception;

public class RepositoryException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /**
     * Initializes the repository exception with the specified detail message.
     *
     * @param message the detail message describing the repository error
     */
    public RepositoryException(String message) { super(message); }

    /**
     * Initializes the repository exception with the specified detail message and cause.
     *
     * @param message the detail message describing the repository error
     * @param cause   the underlying cause of the exception
     */
    public RepositoryException(String message, Throwable cause) { super(message, cause); }
}