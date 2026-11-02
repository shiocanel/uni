package repository;

import domain.model.Entity;
import exception.EntityNotFoundException;
import exception.RepositoryException;
import validation.ValidationStrategy;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

/** Generic in-memory repository used directly for MEMORY and as the parent of file repositories. */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final Map<ID, E> entities = new LinkedHashMap<ID, E>();
    private final ValidationStrategy<E> validator;

    /** @param validator strategy used before entities are stored */
    public InMemoryRepository(ValidationStrategy<E> validator) {
        if (validator == null) throw new IllegalArgumentException("Validatorul este obligatoriu.");
        this.validator = validator;
    }

    @Override
    public List<E> findAll() {
        return new ArrayList<E>(entities.values());
    }

    @Override
    public Optional<E> findById(ID id) {
        if (id == null) return Optional.empty();
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public void save(E entity) {
        validateAndCheckId(entity);
        ID id = entity.getId();
        if (entities.containsKey(id))
            throw new RepositoryException("Exista deja o entitate cu ID-ul " + id + ".");
        entities.put(id, entity);
    }

    @Override
    public void update(E entity) {
        validateAndCheckId(entity);
        ID id = entity.getId();
        if (!entities.containsKey(id))
            throw new EntityNotFoundException("Nu exista o entitate cu ID-ul " + id + " pentru actualizare.");
        entities.put(id, entity);
    }

    @Override
    public void deleteById(ID id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null.");
        if (!entities.containsKey(id)) throw new EntityNotFoundException("Nu exista o entitate cu ID-ul " + id + ".");
        entities.remove(id);
    }

    /** @return the validator used by this repository */
    protected final ValidationStrategy<E> getValidator() {
        return validator;
    }

    private void validateAndCheckId(E entity) {
        if (entity == null) throw new IllegalArgumentException("Entitatea nu poate fi null.");
        validator.validate(entity);
        if (entity.getId() == null) throw new IllegalArgumentException("ID-ul entitatii nu poate fi null.");
    }
}
