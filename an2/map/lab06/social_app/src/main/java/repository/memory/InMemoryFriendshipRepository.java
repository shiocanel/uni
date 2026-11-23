package repository.memory;

import domain.model.Friendship;
import domain.model.FriendshipId;
import repository.FriendshipRepository;
import repository.InMemoryRepository;
import validation.ValidationStrategy;

/** In-memory repository for undirected friendships. */
public final class InMemoryFriendshipRepository extends InMemoryRepository<FriendshipId, Friendship>
        implements FriendshipRepository {
    /** @param validator validation strategy for friendships */
    public InMemoryFriendshipRepository(ValidationStrategy<Friendship> validator) {
        super(validator);
    }
}
