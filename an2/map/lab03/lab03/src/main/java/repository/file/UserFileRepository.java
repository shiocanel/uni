package repository.file;

import domain.model.User;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.nio.file.Path;

/** File-backed user repository; each line has the format id;prenume;nume. */
public final class UserFileRepository extends AbstractFileRepository<Long, User> implements UserRepository {
    /** @param file path to users.txt @param validator user validation strategy */
    public UserFileRepository(Path file, ValidationStrategy<User> validator) {
        super(file, validator);
        loadExistingData();
    }

    @Override
    protected User extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length == 3) {
            return new User(Long.parseLong(fields[0].trim()), fields[1], fields[2]);
        }
        if (fields.length != 6)
            throw new IllegalArgumentException("Format asteptat: id;prenume;nume;email;dataNasterii;descriere.");
        return new User(Long.parseLong(fields[0].trim()), fields[1], fields[2], fields[3], fields[4], fields[5]);
    }

    @Override
    protected String createEntityAsString(User user) {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName() + ";"
                + user.getEmail() + ";" + user.getBirthDate() + ";" + user.getDescription();
    }
}
