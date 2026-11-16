package repository.file;

import domain.model.Entity;
import exception.RepositoryException;
import exception.SocialNetworkException;
import repository.InMemoryRepository;
import validation.ValidationStrategy;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

/**
 * Template Method base for file-backed repositories. It keeps the loaded state in the
 * inherited in-memory map and delegates line/entity conversion to concrete subclasses.
 *
 * @param <ID> entity identifier type
 * @param <E> entity type
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    private final Path file;

    /**
     * Sets up the path and validator. Subclasses call loadExistingData() in their constructor
     * body, after their own initialization has completed.
     *
     * @param file path to the text file
     * @param validator entity validation strategy
     */
    protected AbstractFileRepository(Path file, ValidationStrategy<E> validator) {
        super(validator);
        if (file == null) {
            throw new IllegalArgumentException("Calea fisierului nu poate fi null.");
        }
        this.file = file;
    }

    /**
     * Converts one text line to an entity.
     *
     * @param line source line, without the line separator
     * @return parsed entity
     * @throws IllegalArgumentException when the line has an invalid format
     * @throws SocialNetworkException when the parsed entity fails validation
     */
    protected abstract E extractEntity(String line);

    /**
     * Converts one entity to a single text line.
     *
     * @param entity entity to serialize
     * @return serialized entity, without a line separator
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Loads existing data; a missing file is treated as an empty repository.
     * Invalid lines are reported with their original line number and ignored.
     *
     * @throws RepositoryException when the file cannot be read
     */
    protected final void loadExistingData() {
        if (!Files.exists(file)) {
            return;
        }
        final List<String> lines;
        try (Stream<String> fileLines = Files.lines(file, StandardCharsets.UTF_8)) {
            lines = fileLines.collect(Collectors.toList());
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot citi fisierul " + file + ".", exception);
        }

        IntStream.range(0, lines.size())
                .filter(index -> !lines.get(index).trim().isEmpty())
                .forEach(index -> loadLine(lines.get(index), index + 1));
    }

    private void loadLine(String line, int lineNumber) {
        try {
            E entity = extractEntity(line);
            super.save(entity);
        } catch (DateTimeParseException | IllegalArgumentException | SocialNetworkException exception) {
            reportInvalidLine(lineNumber, exception.getMessage());
        }
    }

    /**
     * Saves an entity and persists the new repository state.
     * The in-memory insertion is rolled back when writing fails.
     *
     * @param entity entity to store
     * @return stored entity
     * @throws IllegalArgumentException when the entity is null or invalid
     * @throws RepositoryException when the file cannot be written
     */
    @Override
    public E save(E entity) {
        E stored = super.save(entity);
        try {
            writeCurrentState();
            return stored;
        } catch (RepositoryException exception) {
            super.deleteById(entity.getId());
            throw exception;
        }
    }

    /**
     * Updates an entity and persists the new repository state.
     * The previous value is restored when writing fails.
     *
     * @param entity entity containing updated data
     * @return updated entity, or empty when the ID does not exist
     * @throws IllegalArgumentException when entity or its ID is null
     * @throws RepositoryException when the file cannot be written
     */
    @Override
    public Optional<E> update(E entity) {
        if (entity == null || entity.getId() == null) {
            throw new IllegalArgumentException("Entity and ID cannot be null.");
        }
        Optional<E> previous = super.findById(entity.getId());
        Optional<E> updated = super.update(entity);
        if (!updated.isPresent()) {
            return Optional.empty();
        }
        try {
            writeCurrentState();
            return updated;
        } catch (RepositoryException exception) {
            previous.ifPresent(this::restoreUpdatedEntity);
            throw exception;
        }
    }

    /**
     * Deletes an entity and persists the new repository state.
     * The deleted value is restored when writing fails.
     *
     * @param id ID of the entity to delete
     * @return deleted entity, or empty when the ID does not exist
     * @throws IllegalArgumentException when id is null
     * @throws RepositoryException when the file cannot be written
     */
    @Override
    public Optional<E> deleteById(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("ID cannot be null.");
        }
        Optional<E> removed = super.deleteById(id);
        if (!removed.isPresent()) {
            return Optional.empty();
        }
        try {
            writeCurrentState();
            return removed;
        } catch (RepositoryException exception) {
            removed.ifPresent(this::restoreEntity);
            throw exception;
        }
    }

    private void restoreUpdatedEntity(E entity) {
        super.update(entity);
    }

    private void restoreEntity(E entity) {
        super.save(entity);
    }

    /**
     * Returns the path used by this repository.
     *
     * @return file path
     */
    protected final Path getFile() {
        return file;
    }

    /** Writes the in-memory contents as UTF-8 lines, without a header. */
    protected final void writeCurrentState() {
        Path parent = file.getParent();
        try {
            if (parent != null) {
                Files.createDirectories(parent);
            }
            List<String> lines = super.findAll().stream()
                    .map(this::createEntityAsString)
                    .collect(Collectors.toList());
            Files.write(file, lines, StandardCharsets.UTF_8,
                    StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.WRITE);
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot salva fisierul " + file + ".", exception);
        }
    }

    private void reportInvalidLine(int lineNumber, String reason) {
        System.err.println("Fisierul " + file + ", linia " + lineNumber
                + " a fost ignorata. Motiv: " + (reason == null ? "date invalide" : reason));
    }
}
