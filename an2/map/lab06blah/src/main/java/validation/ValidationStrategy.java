package validation;

/**
 * Functional contract for validating domain entities.
 *
 * @param <T> type of the value being validated
 */
@FunctionalInterface
public interface ValidationStrategy<T> {
    /**
     * Validates a value.
     *
     * @param value value to validate
     * @throws exception.ValidationException when the value is invalid
     */
    void validate(T value);

    /**
     * Returns a validator that applies this validation and then the supplied validation.
     *
     * @param other validation to execute after this one
     * @return a composed validation strategy
     * @throws NullPointerException when {@code other} is null
     */
    default ValidationStrategy<T> andThen(ValidationStrategy<T> other) {
        if (other == null) {
            throw new NullPointerException("Validatorul compus nu poate fi null.");
        }
        return value -> {
            this.validate(value);
            other.validate(value);
        };
    }
}
