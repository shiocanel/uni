package validation;

import domain.model.User;
import exception.ValidationException;

/** Validation rules for users. */
public final class UserValidationStrategy implements ValidationStrategy<User> {
    /**
     * Checks the ID and names of a user.
     *
     * @param user user entity to validate
     * @throws ValidationException when the user or any of its fields is invalid
     */
    @Override
    public void validate(User user) {
        if (user == null) throw new ValidationException("Utilizatorul nu poate fi null.");
        if (user.getId() == null || user.getId().longValue() <= 0)
            throw new ValidationException("ID-ul utilizatorului trebuie sa fie pozitiv.");
        validateName(user.getFirstName(), "prenumele");
        validateName(user.getLastName(), "numele");
        if (!user.getEmail().isEmpty() && !user.getEmail().matches("^[^\\s@]+@[^\\s@]+\\.[^\\s@]+$"))
            throw new ValidationException("Adresa de email nu este valida.");
        if (!user.getBirthDate().isEmpty() && !user.getBirthDate().matches("\\d{4}-\\d{2}-\\d{2}"))
            throw new ValidationException("Data nasterii trebuie sa aiba formatul YYYY-MM-DD.");
        if (user.getDescription().contains(";"))
            throw new ValidationException("Descrierea nu poate contine caracterul ;.");
    }

    private void validateName(String name, String fieldName) {
        if (name == null || name.trim().isEmpty())
            throw new ValidationException("Campul pentru " + fieldName + " nu poate fi gol.");
        if (name.length() > 50)
            throw new ValidationException("Campul pentru " + fieldName + " poate avea cel mult 50 de caractere.");
        for (int index = 0; index < name.length(); index++) {
            char character = name.charAt(index);
            if (!Character.isLetter(character) && character != ' ' && character != '-'
                    && character != '\'' && character != '.') {
                throw new ValidationException("Campul pentru " + fieldName
                        + " poate contine litere, spatii, cratime, apostrof sau punct.");
            }
        }
    }
}
