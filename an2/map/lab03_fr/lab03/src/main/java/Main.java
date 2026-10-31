import domain.model.Friendship;
import domain.model.User;
import exception.RepositoryException;
import repository.FriendshipRepository;
import repository.RepositoryFactory;
import repository.UserRepository;
import service.SocialNetworkService;
import ui.ConsoleUI;
import validation.FriendshipValidationStrategy;
import validation.UserValidationStrategy;

import java.util.Scanner;

/** Application entry point. */
public final class Main {
    private Main() {
    }

    /**
     * Loads configuration, creates repositories and starts the console interface.
     *
     * @param args command-line arguments (not used; configuration is read from config.properties)
     */
    public static void main(String[] args) {
        try {
            UserValidationStrategy userValidator = new UserValidationStrategy();
            RepositoryFactory factory = new RepositoryFactory();
            UserRepository userRepository = factory.createUtilizatorRepository(userValidator);

            FriendshipValidationStrategy friendshipValidator = new FriendshipValidationStrategy(userRepository);
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
