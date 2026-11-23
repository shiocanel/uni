package validation;

import domain.model.User;
import exception.ValidationException;

public final class UserValidationStrategy implements ValidationStrategy<User> {
    /**
     * Validates the specified user entity, ensuring it is not null, has a positive ID, and contains valid first and last names.
     *
     * @param user the user entity to validate
     */
    @Override
    public void validate(User user) {
        if (user == null)
            throw new ValidationException("Utilizatorul nu poate fi null");
        if (user.getId() <= 0)
            throw new ValidationException("ID-ul utilizatorului trebuie sa fie pozitiv");

        validateName(user.getFirstName(), "prenumele");
        validateName(user.getLastName(), "numele");
    }

    /**
     * Validates a given name string (first or last name) to ensure it is not empty, does not exceed 50 characters, and contains only allowed characters.
     *
     * @param name      the name string to validate
     * @param fieldName the description of the field being validated (e.g., first or last name)
     */
    private void validateName(String name, String fieldName) {
        if (name == null || name.trim().isEmpty()) {
            throw new ValidationException("Campul pentru " + fieldName + " nu poate fi gol");
        }
        if (name.length() > 50) {
            throw new ValidationException("Campul pentru " + fieldName + " poate avea cel mult 50 de charss");
        }
        for (int index = 0; index < name.length(); index++) {
            char character = name.charAt(index);
            if (!Character.isLetter(character) && character != ' ' && character != '-' && character != '\'' && character != '.') {
                throw new ValidationException("Campul pentru " + fieldName
                        + " poate contine litere, spatii, cratime, apostrof sau punct");
            }
        }
    }
}