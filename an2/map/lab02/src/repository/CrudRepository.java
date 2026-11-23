package repository;

import domain.model.Entity;

import java.util.List;
import java.util.Optional;

public interface CrudRepository<ID, E extends Entity<ID>> {
    /**
     * Retrieves all entities from the repository.
     *
     * @return a list of all entities
     */
    List<E> findAll();

    /**
     * Finds and returns an entity by its unique identifier.
     *
     * @param id the unique identifier of the entity to find
     * @return an Optional containing the entity if found, or empty otherwise
     */
    Optional<E> findById(ID id);

    /**
     * Saves a new entity to the repository.
     *
     * @param entity the entity to save
     */
    void save(E entity);

    /**
     * Deletes an entity by its unique identifier from the repository.
     *
     * @param id the unique identifier of the entity to delete
     */
    void deleteById(ID id);
}