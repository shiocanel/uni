package repository;

import domain.model.Entity;

import java.util.List;
import java.util.Optional;

/** Generic contract for storing and retrieving domain entities. */
public interface Repository<ID, E extends Entity<ID>> {
    /** @return all stored entities; the returned list can be modified without changing the repository */
    List<E> findAll();

    /**
     * Finds an entity by ID.
     *
     * @param id identifier to search for
     * @return an Optional containing the entity, or empty when the ID is absent or null
     */
    Optional<E> findById(ID id);

    /**
     * Stores a new entity.
     *
     * @param entity entity to store
     * @throws IllegalArgumentException when entity or its ID is null
     */
    void save(E entity);

    /**
     * Replaces an existing entity with the same ID.
     *
     * @param entity entity containing updated data
     * @throws IllegalArgumentException when entity or its ID is null
     * @throws exception.EntityNotFoundException when its ID is not stored
     */
    void update(E entity);

    /**
     * Deletes an entity by ID.
     *
     * @param id identifier to delete
     * @throws IllegalArgumentException when id is null
     * @throws exception.EntityNotFoundException when the ID is not stored
     */
    void deleteById(ID id);
}
