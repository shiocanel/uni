package domain.model;

import java.time.LocalDateTime;

/** Represents an undirected friendship and the time it was created. */
public final class Friendship extends Entity<FriendshipId> {
    private static final long serialVersionUID = 1L;

    private final LocalDateTime date;

    /**
     * Creates a friendship timestamped with the current local date and time.
     *
     * @param firstUserId one user's ID
     * @param secondUserId the other user's ID
     */
    public Friendship(long firstUserId, long secondUserId) {
        this(firstUserId, secondUserId, LocalDateTime.now().withSecond(0).withNano(0));
    }

    /**
     * Creates a friendship with a supplied timestamp, for example when loading a file.
     *
     * @param firstUserId one user's ID
     * @param secondUserId the other user's ID
     * @param date time when the friendship was created
     */
    public Friendship(long firstUserId, long secondUserId, LocalDateTime date) {
        if (date == null) throw new IllegalArgumentException("Data prieteniei nu poate fi null.");
        this.id = new FriendshipId(firstUserId, secondUserId);
        this.date = date;
    }

    /** @return the first (smaller) user ID */
    public long getFirstUserId() {
        return getId().getFirstUserId();
    }

    /** @return the second (larger) user ID */
    public long getSecondUserId() {
        return getId().getSecondUserId();
    }

    /** @return the friendship creation date and time */
    public LocalDateTime getDate() {
        return date;
    }

    /** @return true if this friendship involves the supplied user ID */
    public boolean involves(long userId) {
        return getFirstUserId() == userId || getSecondUserId() == userId;
    }

    @Override
    public String toString() {
        return getFirstUserId() + " <-> " + getSecondUserId() + " (" + date + ")";
    }
}
