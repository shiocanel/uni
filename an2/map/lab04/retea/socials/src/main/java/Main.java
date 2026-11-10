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

    /*
        1. ValidationStrategy
        2. Predicate, lambda, used -> Repository, UserCriteria, SocialNetworkService
        3. Function -> RepositoryFactory
        4.

     */

    /**
     * Loads configuration, creates repositories and starts the console interface.
     * A second validation rule is composed as a lambda with the existing validator.
     *
     * @param args command-line arguments (not used; configuration is read from config.properties)
     */
    public static void main(String[] args) {
        try {
            ValidationStrategy<User> userValidator = new UserValidationStrategy().andThen(user -> {
                if (!user.getBirthDate().isEmpty()) {
                    try {
                        LocalDate birthDate = LocalDate.parse(user.getBirthDate());
                        if (birthDate.isAfter(LocalDate.now())) {
                            throw new ValidationException("Data nasterii nu poate fi in viitor.");
                        }
                    }
                    catch (DateTimeParseException exception) {
                        throw new ValidationException("Data nasterii nu reprezinta o data calendaristica valida.");
                    }
                }
            });

            RepositoryFactory factory = new RepositoryFactory();
            UserRepository userRepository = factory.createUtilizatorRepository(userValidator);
            ValidationStrategy<Friendship> friendshipValidator = new FriendshipValidationStrategy(userRepository);
            FriendshipRepository friendshipRepository = factory.createPrietenieRepository(friendshipValidator);

            SocialNetworkService service = new SocialNetworkService(
                    userRepository, friendshipRepository, userValidator, friendshipValidator);
            System.out.println("Mod de stocare activ: " + factory.getRepositoryType());
            new ConsoleUI(service, new Scanner(System.in)).run();
        }
        catch (RepositoryException exception) {
            System.err.println("Aplicatia nu poate porni: " + exception.getMessage());
        }
    }
}
