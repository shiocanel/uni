package repository;

import domain.model.Entity;

import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/**
 * Generic contract for storing and retrieving domain entities.
 *
 * @param <ID> type of the entity identifier
 * @param <E> entity type
 */
public interface Repository<ID, E extends Entity<ID>> {
    /**
     * Returns all stored entities.
     *
     * @return all stored entities
     */
    List<E> findAll();

    /**
     * Returns the entities accepted by the supplied criterion.
     *
     * @param filter predicate used to select entities; it must not be null
     * @return a new list containing only matching entities
     * @throws NullPointerException when filter is null
     */
    default List<E> findAll(Predicate<E> filter) {
        if (filter == null) {
            throw new NullPointerException("Search criterion cannot be null.");
        }
        return findAll().stream()
                .filter(filter)
                .collect(Collectors.toList());
    }

    /**
     * Finds an entity by ID.
     *
     * @param id identifier to search for
     * @return an Optional containing the entity, or empty when the ID is absent
     * @throws IllegalArgumentException when id is null
     */
    Optional<E> findById(ID id);

    /**
     * Stores a new entity.
     *
     * @param entity entity to store
     * @return the stored entity; a repository may assign its ID before returning it
     * @throws IllegalArgumentException when entity is null or invalid
     * @throws exception.RepositoryException when storage fails or the ID already exists
     */
    E save(E entity);

    /**
     * Updates an existing entity.
     *
     * @param entity entity containing updated data
     * @return the updated entity, or empty when no entity with that ID exists
     * @throws IllegalArgumentException when entity or its ID is null
     * @throws exception.RepositoryException when storage fails
     */
    Optional<E> update(E entity);

    /**
     * Deletes an entity by ID.
     *
     * @param id identifier to delete
     * @return the deleted entity, or empty when the ID does not exist
     * @throws IllegalArgumentException when id is null
     * @throws exception.RepositoryException when storage fails
     */
    Optional<E> deleteById(ID id);
}
