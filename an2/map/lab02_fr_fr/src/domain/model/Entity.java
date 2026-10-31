package domain.model;

import java.io.Serializable;
import java.util.Objects;

public class Entity<ID> implements Serializable {
    private static final long serialVersionUID = 7331115341259248461L;

    protected ID id;

    /**
     * Returns the unique identifier of this entity.
     *
     * @return the entity's ID
     */
    public ID getId() {
        return id;
    }

    /**
     * Sets or updates the unique identifier of this entity.
     *
     * @param id the new ID to set for the entity
     */
    public void setId(ID id) {
        this.id = id;
    }

    /**
     * Compares this entity to another object for equality based on their IDs.
     *
     * @param other the reference object with which to compare
     * @return true if this entity is equal to the other object, false otherwise
     */
    @Override
    public boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof Entity<?>)) return false;
        Entity<?> entity = (Entity<?>) other;
        return Objects.equals(id, entity.id);
    }

    /**
     * Returns a hash code value for the entity based on its ID.
     *
     * @return a hash code value for this entity
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /**
     * Returns a string representation of the entity containing its ID.
     *
     * @return a string representation of the entity
     */
    @Override
    public String toString() {
        return "Entity{id=" + id + '}';
    }
}