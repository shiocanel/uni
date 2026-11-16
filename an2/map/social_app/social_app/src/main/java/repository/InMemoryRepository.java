package repository;

import domain.model.Entity;
import exception.RepositoryException;
import validation.ValidationStrategy;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

/**
 * Generic in-memory repository used directly for MEMORY and as the parent
 * of file repositories.
 *
 * @param <ID> identifier type
 * @param <E> entity type
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final Map<ID, E> entities = new LinkedHashMap<ID, E>();
    private final ValidationStrategy<E> validator;

    /**
     * Creates an in-memory repository.
     *
     * @param validator strategy used before entities are stored
     */
    public InMemoryRepository(ValidationStrategy<E> validator) {
        if (validator == null) {
            throw new IllegalArgumentException("Validator is required.");
        }
        this.validator = validator;
    }

    @Override
    public List<E> findAll() {
        return new ArrayList<E>(entities.values());
    }

    @Override
    public Optional<E> findById(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null.");
        }
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public E save(E entity) {
        validateEntity(entity, false);
        ID id = entity.getId();
        if (entities.containsKey(id)) {
            throw new RepositoryException("An entity with ID " + id + " already exists.");
        }
        entities.put(id, entity);
        return entity;
    }

    @Override
    public Optional<E> update(E entity) {
        validateEntity(entity, true);
        ID id = entity.getId();
        if (!entities.containsKey(id)) {
            return Optional.empty();
        }
        entities.put(id, entity);
        return Optional.of(entity);
    }

    @Override
    public Optional<E> deleteById(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null.");
        }
        return Optional.ofNullable(entities.remove(id));
    }

    /**
     * Returns the validator used by this repository.
     *
     * @return the entity validator
     */
    protected final ValidationStrategy<E> getValidator() {
        return validator;
    }

    private void validateEntity(E entity, boolean requireId) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null.");
        }
        if (requireId && entity.getId() == null) {
            throw new IllegalArgumentException("Entity ID cannot be null for update.");
        }
        validator.validate(entity);
        if (entity.getId() == null) {
            throw new IllegalArgumentException("Entity ID cannot be null.");
        }
    }
}
