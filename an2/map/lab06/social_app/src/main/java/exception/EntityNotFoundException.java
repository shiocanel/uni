package exception;

/** Thrown when an entity cannot be found in a repository. */
public class EntityNotFoundException extends SocialNetworkException {
    private static final long serialVersionUID = 1L;

    /** @param message explanation of the missing entity */
    public EntityNotFoundException(String message) {
        super(message);
    }
}
