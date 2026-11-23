package validation;

import domain.model.User;
import exception.ValidationException;

/**
 * Validation rules for users. A null ID is accepted before save because
 * the selected repository assigns the ID.
 */
public final class UserValidationStrategy implements ValidationStrategy<User> {
    /**
     * Checks the names and optional profile fields of a user.
     * A null ID is accepted before saving because the repository assigns it.
     *
     * @param user user entity to validate
     * @throws ValidationException when the user or any of its fields is invalid
     */
    @Override
    public void validate(User user) {
        if (user == null) {
            throw new ValidationException("User cannot be null.");
        }
        if (user.getId() != null && user.getId().longValue() <= 0) {
            throw new ValidationException("User ID must be positive.");
        }

        validateName(user.getFirstName(), "first name");
        validateName(user.getLastName(), "last name");

        if (!user.getEmail().isEmpty()
                && !user.getEmail().matches("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$")) {
            throw new ValidationException("Email address is not valid.");
        }
        if (!user.getBirthDate().isEmpty()
                && !user.getBirthDate().matches("\\d{4}-\\d{2}-\\d{2}")) {
            throw new ValidationException("Birth date must use the YYYY-MM-DD format.");
        }
        if (user.getDescription().contains(";")) {
            throw new ValidationException("Description cannot contain the ; character.");
        }
    }

    private void validateName(String name, String fieldName) {
        if (name == null || name.trim().isEmpty()) {
            throw new ValidationException(fieldName + " cannot be empty.");
        }
        if (name.length() > 50) {
            throw new ValidationException(fieldName + " can contain at most 50 characters.");
        }
        for (int index = 0; index < name.length(); index++) {
            char character = name.charAt(index);
            if (Character.isISOControl(character)) {
                throw new ValidationException(fieldName + " cannot contain control characters.");
            }
        }
    }
}
