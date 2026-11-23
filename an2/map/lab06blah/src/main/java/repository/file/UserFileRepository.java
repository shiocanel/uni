package repository.file;

import domain.model.User;
import exception.ValidationException;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.nio.file.Path;
import java.util.Comparator;
import java.util.Optional;

/** File-backed user repository; each line has six fields when written. */
public final class UserFileRepository extends AbstractFileRepository<Long, User> implements UserRepository {
    /**
     * Creates a file repository for users and loads existing data.
     *
     * @param file path to the users file
     * @param validator user validation strategy
     */
    public UserFileRepository(Path file, ValidationStrategy<User> validator) {
        super(file, validator);
        loadExistingData();
    }

    /**
     * Assigns an ID when needed and saves the user to the file.
     *
     * @param user user to save
     * @return saved user with its ID
     * @throws IllegalArgumentException when user is null
     * @throws ValidationException when a field cannot be represented in the file format
     * @throws exception.RepositoryException when the file cannot be written
     */
    @Override
    public User save(User user) {
        assignIdIfNeeded(user);
        ensureFileCompatible(user);
        return super.save(user);
    }

    /**
     * Updates a user already stored in the file.
     *
     * @param user user containing updated values and its ID
     * @return updated user, or empty when the ID does not exist
     * @throws IllegalArgumentException when user or its ID is null
     * @throws exception.RepositoryException when the file cannot be written
     */
    @Override
    public Optional<User> update(User user) {
        ensureFileCompatible(user);
        return super.update(user);
    }

    private void assignIdIfNeeded(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User cannot be null.");
        }
        if (user.getId() == null) {
            long nextId = findAll().stream()
                    .map(User::getId)
                    .max(Comparator.naturalOrder())
                    .orElse(0L) + 1L;
            user.setId(nextId);
        }
    }

    private void ensureFileCompatible(User user) {
        if (user == null) {
            throw new IllegalArgumentException("User cannot be null.");
        }
        if (containsFileSeparator(user.getFirstName()) || containsFileSeparator(user.getLastName())
                || containsFileSeparator(user.getEmail()) || containsFileSeparator(user.getBirthDate())
                || containsFileSeparator(user.getDescription())) {
            throw new ValidationException("The FILE storage format does not allow semicolons or line breaks in user fields.");
        }
    }

    private boolean containsFileSeparator(String value) {
        return value != null && (value.contains(";") || value.contains("\n") || value.contains("\r"));
    }

    @Override
    protected User extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length == 3) {
            return new User(Long.parseLong(fields[0].trim()), fields[1], fields[2]);
        }
        if (fields.length != 6) {
            throw new IllegalArgumentException(
                    "Expected format: id;firstName;lastName;email;birthDate;description.");
        }
        return new User(Long.parseLong(fields[0].trim()),
                fields[1], fields[2], fields[3], fields[4], fields[5]);
    }

    @Override
    protected String createEntityAsString(User user) {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName() + ";"
                + user.getEmail() + ";" + user.getBirthDate() + ";" + user.getDescription();
    }
}
