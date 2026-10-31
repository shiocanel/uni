package exception;

public class ValidationException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /**
     * Initializes the validation exception with the specified detail message.
     *
     * @param message the detail message describing the validation error
     */
    public ValidationException(String message) { super(message); }

    /**
     * Initializes the validation exception with the specified detail message and cause.
     *
     * @param message the detail message describing the validation error
     * @param cause   the underlying cause of the exception
     */
    public ValidationException(String message, Throwable cause) { super(message, cause); }
}