package validation;

public interface ValidationStrategy<T> {
    void validate(T value);
}
