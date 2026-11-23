import domain.service.CommunityAnalyzer;
import repository.FriendshipRepository;
import repository.UserRepository;
import repository.file.CsvFriendshipRepository;
import repository.file.CsvUserRepository;
import service.SocialNetworkService;
import ui.ConsoleUI;
import validation.FriendshipValidationStrategy;
import validation.UserValidationStrategy;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

public final class Main {
    private Main() { }

    public static void main(String[] args) {
        Path dataDirectory = Paths.get(args.length > 0 ? args[0] : "data");
        UserRepository userRepository = new CsvUserRepository(dataDirectory.resolve("users.csv"));
        FriendshipRepository friendshipRepository = new CsvFriendshipRepository(dataDirectory.resolve("friendships.csv"));

        SocialNetworkService service = new SocialNetworkService(
                userRepository,
                friendshipRepository,
                new UserValidationStrategy(),
                new FriendshipValidationStrategy(userRepository, friendshipRepository),
                new CommunityAnalyzer());

        new ConsoleUI(service, new Scanner(System.in)).run();
    }
}
