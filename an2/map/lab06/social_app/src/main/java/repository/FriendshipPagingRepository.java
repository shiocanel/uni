package repository;

import domain.model.Friendship;
import domain.model.User;
import util.paging.Page;
import util.paging.Pageable;

/** Database-capable friendship repository that can page a user's friends. */
public interface FriendshipPagingRepository extends FriendshipRepository {
    /**
     * Retrieves one page of a user's friends, together with the total number of friends.
     *
     * @param userId ID of the user whose friends are requested
     * @param pageable zero-based page request
     * @return page of friend users and the total number of friends
     * @throws IllegalArgumentException when userId or pageable is null or invalid
     * @throws exception.RepositoryException when the database query fails
     */
    Page<User> findFriendsOnPage(Long userId, Pageable pageable);
}
