package repository.file;

import domain.model.User;
import exception.RepositoryException;
import repository.UserRepository;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

public final class CsvUserRepository implements UserRepository {
    private static final String HEADER = "id,firstName,lastName";
    private final Path file;

    /**
     * Initializes the CSV user repository with the specified file path and ensures the file exists with the required header.
     *
     * @param file the path to the CSV file
     */
    public CsvUserRepository(Path file) {
        this.file = file;
        CsvSupport.ensureFile(file, HEADER);
    }

    @Override
    /**
     * Retrieves all users from the CSV file, parses and validates each row, sorts the results by ID, and returns them as a list.
     *
     * @return a list of all stored users
     */
    public List<User> findAll() {
        List<String> lines = CsvSupport.readLines(file);
        List<User> users = new ArrayList<User>();
        for (int index = 1; index < lines.size(); index++) {
            String line = lines.get(index).trim();
            if (line.isEmpty()) continue;
            List<String> fields = CsvSupport.parseRow(line);
            if (fields.size() != 3) {
                throw new RepositoryException("Rand invalid in " + file + ", linia " + (index + 1) + ".");
            }
            try {
                users.add(new User(Long.parseLong(fields.get(0)), fields.get(1), fields.get(2)));
            } catch (NumberFormatException exception) {
                throw new RepositoryException("ID invalid in " + file + ", linia " + (index + 1) + ".", exception);
            }
        }
        Collections.sort(users, new Comparator<User>() {
            @Override public int compare(User first, User second) {
                return Long.compare(first.getId(), second.getId());
            }
        });
        return users;
    }

    @Override
    /**
     * Finds and returns a user by their unique ID if the provided ID is not null.
     *
     * @param id the unique ID of the user to find
     * @return an Optional containing the user if found, or empty otherwise
     */
    public Optional<User> findById(Long id) {
        if (id == null) return Optional.empty();
        for (User user : findAll()) if (user.getId().equals(id)) return Optional.of(user);
        return Optional.empty();
    }

    @Override
    /**
     * Saves a new user to the repository after verifying that a user with the same ID does not already exist.
     *
     * @param user the user object to save
     */
    public void save(User user) {
        List<User> users = findAll();
        for (User existing : users) {
            if (existing.getId().equals(user.getId())) {
                throw new RepositoryException("Exista deja un utilizator cu ID-ul " + user.getId() + ".");
            }
        }
        users.add(user);
        writeAll(users);
    }

    @Override
    /**
     * Deletes the user matching the specified ID from the repository if found.
     *
     * @param id the unique ID of the user to delete
     */
    public void deleteById(Long id) {
        if (id == null) return;
        List<User> users = findAll();
        boolean removed = false;
        for (int index = users.size() - 1; index >= 0; index--) {
            if (users.get(index).getId().equals(id)) {
                users.remove(index);
                removed = true;
            }
        }
        if (removed) writeAll(users);
    }

    /**
     * Sorts the list of users by their ID and writes all records along with the CSV header back to the file.
     *
     * @param users the list of users to write
     */
    private void writeAll(List<User> users) {
        Collections.sort(users, new Comparator<User>() {
            @Override public int compare(User first, User second) {
                return Long.compare(first.getId(), second.getId());
            }
        });
        List<String> lines = new ArrayList<String>();
        lines.add(HEADER);
        for (User user : users) {
            lines.add(user.getId() + "," + CsvSupport.formatField(user.getFirstName()) + ","
                    + CsvSupport.formatField(user.getLastName()));
        }
        CsvSupport.writeLines(file, lines);
    }
}