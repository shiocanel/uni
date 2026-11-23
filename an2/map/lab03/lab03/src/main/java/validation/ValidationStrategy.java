package validation;

/** Strategy interface for validating domain entities. */
public interface ValidationStrategy<T> {
    /**
     * Validates an entity.
     *
     * @param value entity to validate
     * @throws exception.ValidationException when the entity is invalid
     */
    void validate(T value);
}
