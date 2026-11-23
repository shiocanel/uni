import domain.model.Friendship;
import domain.model.User;
import exception.RepositoryException;
import exception.ValidationException;
import repository.FriendshipRepository;
import repository.RepositoryFactory;
import repository.UserRepository;
import service.SocialNetworkService;
import ui.ConsoleUI;
import validation.FriendshipValidationStrategy;
import validation.UserValidationStrategy;
import validation.ValidationStrategy;

import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

/** Application entry point. */
public final class Main {
    private Main() {
    }

    /**
     * Loads configuration, creates repositories and starts the console interface.
     * The repository assigns the ID of each new user.
     *
     * @param args command-line arguments (not used)
     */
    public static void main(String[] args) {
        try {
            ValidationStrategy<User> userValidator = new UserValidationStrategy().andThen(user -> {
                if (!user.getBirthDate().isEmpty()) {
                    try {
                        LocalDate birthDate = LocalDate.parse(user.getBirthDate());
                        if (birthDate.isAfter(LocalDate.now())) {
                            throw new ValidationException("Birth date cannot be in the future.");
                        }
                    } catch (DateTimeParseException exception) {
                        throw new ValidationException("Birth date is not a valid calendar date.");
                    }
                }
            });

            RepositoryFactory factory = new RepositoryFactory();
            UserRepository userRepository = factory.createUserRepository(userValidator);
            ValidationStrategy<Friendship> friendshipValidator =
                    new FriendshipValidationStrategy(userRepository);
            FriendshipRepository friendshipRepository =
                    factory.createFriendshipRepository(friendshipValidator);

            SocialNetworkService service = new SocialNetworkService(
                    userRepository, friendshipRepository, userValidator, friendshipValidator);
            System.out.println("Active storage: " + factory.getRepositoryType());
            new ConsoleUI(service, new Scanner(System.in), factory.getPageSize()).run();
        } catch (RepositoryException exception) {
            System.err.println("Application could not start: " + exception.getMessage());
        }
    }
}
