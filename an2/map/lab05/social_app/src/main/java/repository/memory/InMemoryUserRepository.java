package repository.memory;

import domain.model.User;
import repository.InMemoryRepository;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.util.Comparator;

/** In-memory user repository. IDs are assigned by this storage implementation. */
public final class InMemoryUserRepository extends InMemoryRepository<Long, User> implements UserRepository {
    /**
     * Creates an in-memory user repository.
     *
     * @param validator user validation strategy
     */
    public InMemoryUserRepository(ValidationStrategy<User> validator) {
        super(validator);
    }

    /**
     * Assigns the next ID and stores the user.
     *
     * @param user user to save
     * @return saved user with its assigned ID
     * @throws IllegalArgumentException when user is null
     * @throws exception.RepositoryException when the ID already exists
     */
    @Override
    public User save(User user) {
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
        return super.save(user);
    }
}
