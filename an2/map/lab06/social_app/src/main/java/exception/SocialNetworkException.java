package exception;

/** Base unchecked exception for errors that can be presented by the application. */
public class SocialNetworkException extends RuntimeException {
    private static final long serialVersionUID = 1L;

    /** @param message explanation of the error */
    public SocialNetworkException(String message) {
        super(message);
    }

    /**
     * @param message explanation of the error
     * @param cause original cause
     */
    public SocialNetworkException(String message, Throwable cause) {
        super(message, cause);
    }
}
