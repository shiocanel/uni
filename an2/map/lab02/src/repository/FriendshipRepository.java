package repository;

import domain.model.Friendship;
import domain.model.FriendshipId;

import java.util.Optional;

public interface FriendshipRepository extends CrudRepository<FriendshipId, Friendship> {
    /**
     * Finds and returns a friendship between two users specified by their user IDs.
     *
     * @param firstUserId  the ID of the first user
     * @param secondUserId the ID of the second user
     * @return an Optional containing the friendship if found, or empty otherwise
     */
    Optional<Friendship> findByUsers(long firstUserId, long secondUserId);

    /**
     * Deletes all friendships involving the specified user ID from the repository.
     *
     * @param userId the ID of the user whose friendships should be deleted
     */
    void deleteByUserId(long userId);
}