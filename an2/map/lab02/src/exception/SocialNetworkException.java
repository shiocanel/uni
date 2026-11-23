package exception;

public class SocialNetworkException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    /**
     * Initializes the social network exception with the specified detail message.
     *
     * @param message the detail message describing the exception
     */
    public SocialNetworkException(String message) { super(message); }

    /**
     * Initializes the social network exception with the specified detail message and cause.
     *
     * @param message the detail message describing the exception
     * @param cause   the underlying cause of the exception
     */
    public SocialNetworkException(String message, Throwable cause) { super(message, cause); }
}