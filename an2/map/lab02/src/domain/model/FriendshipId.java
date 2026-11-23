package domain.model;

import java.io.Serializable;
import java.util.Objects;

public final class FriendshipId implements Serializable {
    private static final long serialVersionUID = 1L;

    private final long firstUserId;
    private final long secondUserId;

    /**
     * Initializes a normalized friendship identifier, automatically ordering the user IDs so that the smaller ID comes first.
     *
     * @param firstUserId  the ID of the first user
     * @param secondUserId the ID of the second user
     */
    public FriendshipId(long firstUserId, long secondUserId) {
        this.firstUserId = Math.min(firstUserId, secondUserId);
        this.secondUserId = Math.max(firstUserId, secondUserId);
    }

    /**
     * Returns the first (smaller) user ID in the friendship identifier.
     *
     * @return the first user ID
     */
    public long getFirstUserId() {
        return firstUserId;
    }

    /**
     * Returns the second (larger) user ID in the friendship identifier.
     *
     * @return the second user ID
     */
    public long getSecondUserId() {
        return secondUserId;
    }

    /**
     * Compares this friendship ID to another object for equality based on both user IDs.
     *
     * @param other the reference object with which to compare
     * @return true if this object is equal to the other object, false otherwise
     */
    @Override
    public boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof FriendshipId)) return false;
        FriendshipId that = (FriendshipId) other;
        return firstUserId == that.firstUserId && secondUserId == that.secondUserId;
    }

    /**
     * Returns a hash code value for the friendship ID based on both user IDs.
     *
     * @return a hash code value for this friendship ID
     */
    @Override
    public int hashCode() {
        return Objects.hash(firstUserId, secondUserId);
    }

    /**
     * Returns a string representation of the friendship ID formatted as a hyphen-separated pair of user IDs.
     *
     * @return a string representation of the friendship ID
     */
    @Override
    public String toString() {
        return firstUserId + "-" + secondUserId;
    }
}