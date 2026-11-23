package exception;

/** Thrown when repository configuration or persistence fails. */
public class RepositoryException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /** @param message explanation of the repository error */
    public RepositoryException(String message) {
        super(message);
    }

    /**
     * @param message explanation of the repository error
     * @param cause original low-level exception
     */
    public RepositoryException(String message, Throwable cause) {
        super(message, cause);
    }
}
