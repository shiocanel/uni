package exception;

public class EntityNotFoundException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /**
     * Initializes the entity not found exception with the specified detail message.
     *
     * @param message the detail message explaining which entity could not be found
     */
    public EntityNotFoundException(String message) { super(message); }
}