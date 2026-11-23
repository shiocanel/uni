package repository.file;

import domain.model.Friendship;
import domain.model.FriendshipId;
import exception.RepositoryException;
import repository.FriendshipRepository;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

public final class CsvFriendshipRepository implements FriendshipRepository {
    private static final String HEADER = "userId1,userId2";
    private final Path file;

    /**
     * Initializes the CSV friendship repository with the specified file path and ensures the file exists with the required header.
     */
    public CsvFriendshipRepository(Path file) {
        this.file = file;
        CsvSupport.ensureFile(file, HEADER);
    }

    @Override
    /**
     * Retrieves all friendships from the CSV file, parses and validates each row, sorts the results, and returns them as a list.
     */
    public List<Friendship> findAll() {
        List<String> lines = CsvSupport.readLines(file);
        List<Friendship> friendships = new ArrayList<Friendship>();
        for (int index = 1; index < lines.size(); index++) {
            String line = lines.get(index).trim();
            if (line.isEmpty())
                continue;

            List<String> fields = CsvSupport.parseRow(line);
            if (fields.size() != 2) {
                throw new RepositoryException("Rand invalid in " + file + ", linia " + (index + 1) + ".");
            }

            try {
                friendships.add(new Friendship(Long.parseLong(fields.get(0)), Long.parseLong(fields.get(1))));
            }
            catch (NumberFormatException exception) {
                throw new RepositoryException("ID invalid in " + file + ", linia " + (index + 1) + ".", exception);
            }
        }
        sortFriendships(friendships);
        return friendships;
    }

    @Override
    /**
     * Finds and returns a friendship by its compound FriendshipId if the provided ID is not null.
     */
    public Optional<Friendship> findById(FriendshipId id) {
        if (id == null)
            return Optional.empty();

        return findByUsers(id.getFirstUserId(), id.getSecondUserId());
    }

    @Override
    /**
     * Searches for and returns a friendship involving the two specified user IDs.
     */
    public Optional<Friendship> findByUsers(long firstUserId, long secondUserId) {
        FriendshipId requestedId = new FriendshipId(firstUserId, secondUserId);
        for (Friendship friendship : findAll()) {
            if (friendship.getId().equals(requestedId))
                return Optional.of(friendship);
        }

        return Optional.empty();
    }

    @Override
    /**
     * Saves a new friendship to the repository after verifying it does not already exist.
     */
    public void save(Friendship friendship) {
        if (findByUsers(friendship.getFirstUserId(), friendship.getSecondUserId()).isPresent()) {
            throw new RepositoryException("Prietenia exista deja.");
        }
        List<Friendship> friendships = findAll();
        friendships.add(friendship);
        writeAll(friendships);
    }

    @Override
    /**
     * Deletes a friendship matching the specified FriendshipId from the repository if found.
     */
    public void deleteById(FriendshipId id) {
        if (id == null)
            return;

        List<Friendship> friendships = findAll();

        boolean removed = false;
        for (int index = friendships.size() - 1; index >= 0; index--) {
            if (friendships.get(index).getId().equals(id)) {
                friendships.remove(index);
                removed = true;
            }
        }

        if (removed)
            writeAll(friendships);
    }

    @Override
    /**
     * Deletes all friendships associated with the specified user ID from the repository.
     */
    public void deleteByUserId(long userId) {
        List<Friendship> friendships = findAll();
        boolean changed = false;

        for (int index = friendships.size() - 1; index >= 0; index--) {
            if (friendships.get(index).involves(userId)) {
                friendships.remove(index);
                changed = true;
            }
        }
        if (changed)
            writeAll(friendships);
    }

    /**
     * Sorts the list of friendships and writes all records along with the CSV header back to the file.
     */
    private void writeAll(List<Friendship> friendships) {
        sortFriendships(friendships);
        List<String> lines = new ArrayList<String>();
        lines.add(HEADER);

        for (Friendship friendship : friendships) {
            lines.add(friendship.getFirstUserId() + "," + friendship.getSecondUserId());
        }
        CsvSupport.writeLines(file, lines);
    }

    /**
     * Sorts a list of friendships in ascending order primarily by the first user ID, and secondarily by the second user ID.
     */
    private void sortFriendships(List<Friendship> friendships) {
        Collections.sort(friendships, new Comparator<Friendship>() {
            @Override
            public int compare(Friendship first, Friendship second) {
                int byFirst = Long.compare(first.getFirstUserId(), second.getFirstUserId());
                return byFirst != 0 ? byFirst
                        : Long.compare(first.getSecondUserId(), second.getSecondUserId());
            }
        });
    }
}