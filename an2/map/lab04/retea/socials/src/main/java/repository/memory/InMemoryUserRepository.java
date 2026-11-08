package repository.memory;

import domain.model.User;
import repository.InMemoryRepository;
import repository.UserRepository;
import validation.ValidationStrategy;

/** In-memory user repository. */
public final class InMemoryUserRepository extends InMemoryRepository<Long, User> implements UserRepository {
    /** @param validator validation strategy for users */
    public InMemoryUserRepository(ValidationStrategy<User> validator) {
        super(validator);
    }
}
