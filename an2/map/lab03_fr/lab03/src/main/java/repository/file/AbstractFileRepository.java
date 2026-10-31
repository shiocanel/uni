package repository.file;

import domain.model.Entity;
import exception.RepositoryException;
import exception.SocialNetworkException;
import repository.InMemoryRepository;
import validation.ValidationStrategy;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.Optional;

/**
 * File-backed repository. The inherited in-memory map holds the current state;
 * this class handles loading and rewriting the text file.
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
        if (file == null) throw new IllegalArgumentException("Calea fisierului nu poate fi null.");
        this.file = file;
    }

    /** Converts one text line to an entity. */
    protected abstract E extractEntity(String line);

    /** Converts one entity to a single text line. */
    protected abstract String createEntityAsString(E entity);

    /** Loads existing data; a missing file is treated as an empty repository. */
    protected final void loadExistingData() {
        if (!Files.exists(file)) return;
        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(Files.newInputStream(file), StandardCharsets.UTF_8))) {
            String line;
            int lineNumber = 0;
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                if (line.trim().isEmpty()) continue;
                try {
                    E entity = extractEntity(line);
                    super.save(entity);
                } catch (IllegalArgumentException exception) {
                    reportInvalidLine(lineNumber, exception.getMessage());
                } catch (DateTimeParseException exception) {
                    reportInvalidLine(lineNumber, exception.getMessage());
                } catch (SocialNetworkException exception) {
                    reportInvalidLine(lineNumber, exception.getMessage());
                }
            }
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot citi fisierul " + file + ".", exception);
        }
    }

    @Override
    public void save(E entity) {
        super.save(entity);
        try {
            writeCurrentState();
        } catch (RepositoryException exception) {
            super.deleteById(entity.getId());
            throw exception;
        }
    }

    @Override
    public void update(E entity) {
        if (entity == null || entity.getId() == null)
            throw new IllegalArgumentException("Entitatea si ID-ul ei nu pot fi null.");
        Optional<E> previous = super.findById(entity.getId());
        super.update(entity);
        try {
            writeCurrentState();
        } catch (RepositoryException exception) {
            if (previous.isPresent()) super.update(previous.get());
            throw exception;
        }
    }

    @Override
    public void deleteById(ID id) {
        if (id == null) throw new IllegalArgumentException("ID-ul nu poate fi null.");
        Optional<E> previous = super.findById(id);
        super.deleteById(id);
        try {
            writeCurrentState();
        } catch (RepositoryException exception) {
            if (previous.isPresent()) super.save(previous.get());
            throw exception;
        }
    }

    /** @return the path used by this repository */
    protected final Path getFile() {
        return file;
    }

    /** Writes the in-memory contents, one entity per line, without a header. */
    protected final void writeCurrentState() {
        Path parent = file.getParent();
        try {
            if (parent != null) Files.createDirectories(parent);
            try (BufferedWriter writer = new BufferedWriter(
                    new OutputStreamWriter(Files.newOutputStream(file, StandardOpenOption.CREATE,
                            StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.WRITE), StandardCharsets.UTF_8))) {
                List<E> entities = super.findAll();
                for (int index = 0; index < entities.size(); index++) {
                    writer.write(createEntityAsString(entities.get(index)));
                    writer.newLine();
                }
            }
        } catch (IOException exception) {
            throw new RepositoryException("Nu pot salva fisierul " + file + ".", exception);
        }
    }

    private void reportInvalidLine(int lineNumber, String reason) {
        System.err.println("Fisierul " + file + ", linia " + lineNumber
                + " a fost ignorata. Motiv: " + (reason == null ? "date invalide" : reason));
    }
}
