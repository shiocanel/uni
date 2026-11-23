package exception;

/** Thrown when an entity or an operation does not satisfy validation rules. */
public class ValidationException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /** @param message explanation of the validation error */
    public ValidationException(String message) {
        super(message);
    }
}
