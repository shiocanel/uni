package domain.model;

import java.io.Serializable;
import java.util.Objects;

/**
 * Base class for entities identified by a unique ID.
 *
 * @param <ID> the identifier type
 */
public class Entity<ID> implements Serializable {
    private static final long serialVersionUID = 1L;

    protected ID id;

    /**
     * Returns the entity identifier.
     *
     * @return the entity ID
     */
    public ID getId() {
        return id;
    }

    /**
     * Sets the entity identifier.
     *
     * @param id the identifier to set
     */
    public void setId(ID id) {
        this.id = id;
    }

    /**
     * Compares entities by identifier.
     *
     * @param other the object to compare with
     * @return true when the identifiers are equal
     */
    @Override
    public boolean equals(Object other) {
        if (this == other) return true;
        if (!(other instanceof Entity<?>)) return false;
        Entity<?> entity = (Entity<?>) other;
        return Objects.equals(id, entity.id);
    }

    /**
     * Creates a hash code based on the identifier.
     *
     * @return the entity hash code
     */
    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    /**
     * Returns a short representation of the entity.
     *
     * @return a string containing the ID
     */
    @Override
    public String toString() {
        return "Entity{id=" + id + '}';
    }
}
