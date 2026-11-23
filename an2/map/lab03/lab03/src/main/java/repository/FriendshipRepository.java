package repository;

import domain.model.Friendship;
import domain.model.FriendshipId;

import java.util.List;
import java.util.Optional;

/** Repository contract for undirected friendships. */
public interface FriendshipRepository extends Repository<FriendshipId, Friendship> {
    /**
     * Finds a friendship without depending on the order in which the two IDs are provided.
     *
     * @param firstUserId one user's ID
     * @param secondUserId the other user's ID
     * @return the friendship, if present
     */
    default Optional<Friendship> findByUsers(long firstUserId, long secondUserId) {
        return findById(new FriendshipId(firstUserId, secondUserId));
    }

    /**
     * Deletes every friendship involving the supplied user.
     *
     * @param userId ID of the user whose friendships are to be deleted
     */
    default void deleteByUserId(long userId) {
        List<Friendship> friendships = findAll();
        for (Friendship friendship : friendships) {
            if (friendship.involves(userId)) deleteById(friendship.getId());
        }
    }
}
