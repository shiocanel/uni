package repository.file;

import domain.model.Friendship;
import domain.model.FriendshipId;
import repository.FriendshipRepository;
import validation.ValidationStrategy;

import java.nio.file.Path;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/** File-backed friendship repository; each line has the format idUtilizator1;idUtilizator2;dataPrieteniei. */
public final class FriendshipFileRepository extends AbstractFileRepository<FriendshipId, Friendship>
        implements FriendshipRepository {
    private static final DateTimeFormatter OUTPUT_FORMAT = DateTimeFormatter.ofPattern("yyyy-MM-dd'T'HH:mm");

    /** @param file path to users.txt @param validator friendship validation strategy */
    public FriendshipFileRepository(Path file, ValidationStrategy<Friendship> validator) {
        super(file, validator);
        loadExistingData();
    }

    @Override
    protected Friendship extractEntity(String line) {
        String[] fields = line.split(";", -1);
        if (fields.length != 3)
            throw new IllegalArgumentException("Se asteptau 3 campuri: idUtilizator1;idUtilizator2;dataPrieteniei.");
        long firstId = Long.parseLong(fields[0].trim());
        long secondId = Long.parseLong(fields[1].trim());
        LocalDateTime date = LocalDateTime.parse(fields[2].trim(), DateTimeFormatter.ISO_LOCAL_DATE_TIME);
        return new Friendship(firstId, secondId, date);
    }

    @Override
    protected String createEntityAsString(Friendship friendship) {
        return friendship.getFirstUserId() + ";" + friendship.getSecondUserId() + ";"
                + friendship.getDate().format(OUTPUT_FORMAT);
    }

}
