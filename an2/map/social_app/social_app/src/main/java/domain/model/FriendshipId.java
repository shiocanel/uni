package domain.model;

import java.io.Serializable;
import java.util.Objects;

/** Identifier for an undirected friendship between two users. */
public final class FriendshipId implements Serializable {
    private static final long serialVersionUID = 1L;

    private final long firstUserId;
    private final long secondUserId;

    /**
     * Creates a normalized ID: the smaller user ID is always first.
     *
     * @param firstUserId one user's ID
     * @param secondUserId the other user's ID
     */
    public FriendshipId(long firstUserId, long secondUserId) {
        this.firstUserId = Math.min(firstUserId, secondUserId);
        this.secondUserId = Math.max(firstUserId, secondUserId);
    }

    /** @return the smaller user ID */
    public long getFirstUserId() {
        return firstUserId;
    }

    /** @return the larger user ID */
    public long getSecondUserId() {
        return secondUserId;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof FriendshipId)) return false;
        FriendshipId that = (FriendshipId) other;
        return firstUserId == that.firstUserId && secondUserId == that.secondUserId;
    }

    @Override
    public int hashCode() {
        return Objects.hash(firstUserId, secondUserId);
    }

    @Override
    public String toString() {
        return firstUserId + "-" + secondUserId;
    }
}
