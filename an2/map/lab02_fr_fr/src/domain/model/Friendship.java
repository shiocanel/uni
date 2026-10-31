package domain.model;

public final class Friendship extends Entity<FriendshipId> {
    private static final long serialVersionUID = 1L;

    /**
     * Initializes a friendship between two users with the specified user IDs.
     *
     * @param firstUserId  the ID of the first user
     * @param secondUserId the ID of the second user
     */
    public Friendship(long firstUserId, long secondUserId) {
        this.id = new FriendshipId(firstUserId, secondUserId);
    }

    /**
     * Returns the ID of the first user in the friendship.
     *
     * @return the first user's ID
     */
    public long getFirstUserId() { return getId().getFirstUserId(); }

    /**
     * Returns the ID of the second user in the friendship.
     *
     * @return the second user's ID
     */
    public long getSecondUserId() { return getId().getSecondUserId(); }

    /**
     * Checks whether the friendship involves the specified user ID.
     *
     * @param userId the user ID to check
     * @return true if the friendship involves the user, false otherwise
     */
    public boolean involves(long userId) {
        return getFirstUserId() == userId || getSecondUserId() == userId;
    }

    /**
     * Returns a string representation of the friendship showing both connected user IDs.
     *
     * @return a string representation of the friendship
     */
    @Override
    public String toString() {
        return getFirstUserId() + " <-> " + getSecondUserId();
    }
}