package ui;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.User;
import exception.SocialNetworkException;
import service.SocialNetworkService;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public final class ConsoleUI {
    private final SocialNetworkService service;
    private final Scanner scanner;

    /**
     * Initializes the console user interface with the given social network service and scanner.
     *
     * @param service the social network service to interact with
     * @param scanner the scanner used for reading console input
     */
    public ConsoleUI(SocialNetworkService service, Scanner scanner) {
        this.service = service;
        this.scanner = scanner;
    }

    /**
     * Starts the main interactive command-line loop, displaying the menu and processing user choices until exit.
     */
    public void run() {
        boolean running = true;
        while (running) {
            printMenu();
            String choice = readLine("Alege o optiune: ");
            if (choice == null)
                break;

            try {
                switch (choice.trim()) {
                    case "1": showUsers(); break;
                    case "2": addUser(); break;
                    case "3": removeUser(); break;
                    case "4": addFriendship(); break;
                    case "5": removeFriendship(); break;
                    case "6": showFriendships(); break;
                    case "7": showCommunityCount(); break;
                    case "8": showMostSociableCommunity(); break;
                    case "0":
                        running = false;
                        System.out.println("Datele au fost salvate. Sa fie cu sanatate!");
                        break;
                    default:
                        System.out.println("Optiune invalida!!!! Alege un numar din meniu");
                }
            }
            catch (SocialNetworkException exception) {
                System.out.println("Eroare: " + exception.getMessage());
            }
            catch (RuntimeException exception) {
                System.out.println("A aparut o eroare neasteptata: " + exception.getMessage());
            }

            if (running)
                System.out.println();
        }
    }

    /**
     * Prints the main menu options to the console.
     */
    private void printMenu() {
        System.out.println("===MENU===");
        System.out.println("1. Afiseaza utilizatorii");
        System.out.println("2. Adauga utilizator");
        System.out.println("3. Sterge utilizator");
        System.out.println("4. Adauga prietenie");
        System.out.println("5. Sterge prietenie");
        System.out.println("6. Afiseaza prieteniile");
        System.out.println("7. Afiseaza numarul de comunitati");
        System.out.println("8. Afiseaza cea mai sociabila comunitate");
        System.out.println("0. Iesire");
    }

    /**
     * Displays all registered users in the network along with the total count.
     */
    private void showUsers() {
        List<User> users = service.getAllUsers();
        if (users.isEmpty()) {
            System.out.println("Nu exista utilizatori in retea!");
            return;
        }
        System.out.println("Utilizatori: ");
        for (User user : users)
            System.out.println("  " + user);

        System.out.println("Total: " + users.size());
    }

    /**
     * Prompts the user for a first and last name, creates a new user via the service, and displays confirmation.
     */
    private void addUser() {
        String firstName = readLine("Prenume: ");
        if (firstName == null)
            return;

        String lastName = readLine("Nume: ");
        if (lastName == null)
            return;

        User user = service.addUser(firstName, lastName);
        System.out.println("Utilizator adaugat: " + user);
    }

    /**
     * Prompts for a user ID and removes that user along with their associated friendships from the network.
     */
    private void removeUser() {
        Long userId = readLong("ID-ul utilizatorului de sters: ");
        if (userId == null)
            return;

        service.removeUser(userId);
        System.out.println("Utilizatorul " + userId + " si prieteniile sale au fost sterse!!!");
    }

    /**
     * Prompts for two user IDs and creates a new friendship between them.
     */
    private void addFriendship() {
        Long firstId = readLong("ID-ul primului utilizator: ");
        if (firstId == null)
            return;

        Long secondId = readLong("ID-ul celui de-al doilea utilizator: ");
        if (secondId == null)
            return;

        service.addFriendship(firstId, secondId);
        System.out.println("Prietenia a fost adaugata!");
    }

    /**
     * Prompts for two user IDs and removes the friendship between them.
     */
    private void removeFriendship() {
        Long firstId = readLong("ID-ul primului utilizator: ");
        if (firstId == null)
            return;

        Long secondId = readLong("ID-ul celui de-al doilea utilizator: ");
        if (secondId == null)
            return;

        service.removeFriendship(firstId, secondId);
        System.out.println("Prietenia a fost stearsa!!");
    }

    /**
     * Displays all friendships in the network with user names and IDs, along with the total count.
     */
    private void showFriendships() {
        List<Friendship> friendships = service.getAllFriendships();
        if (friendships.isEmpty()) {
            System.out.println("Nu exista prietenii in retea.");
            return;
        }
        Map<Long, User> usersById = new HashMap<Long, User>();
        for (User user : service.getAllUsers())
            usersById.put(user.getId(), user);

        System.out.println("Prietenii:");
        for (Friendship friendship : friendships) {
            User first = usersById.get(friendship.getFirstUserId());
            User second = usersById.get(friendship.getSecondUserId());

            String firstLabel = first == null ? String.valueOf(friendship.getFirstUserId()) : first.getFullName();
            String secondLabel = second == null ? String.valueOf(friendship.getSecondUserId()) : second.getFullName();
            System.out.println("  " + firstLabel + " (ID " + friendship.getFirstUserId() + ") -- "
                    + secondLabel + " (ID " + friendship.getSecondUserId() + ")");
        }
        System.out.println("Total: " + friendships.size());
    }

    /**
     * Computes and prints the total number of communities present in the social network.
     */
    private void showCommunityCount() {
        int count = service.getCommunityCount();
        System.out.println("Numar de comunitati: " + count);
    }

    /**
     * Finds and displays details of the most sociable community, including its size, diameter, and member list.
     */
    private void showMostSociableCommunity() {
        java.util.Optional<Community> result = service.getMostSociableCommunity();
        if (!result.isPresent()) {
            System.out.println("Nu exista utilizatori, deci nu exista comunitati.");
            return;
        }

        Community community = result.get();
        System.out.println("Cea mai sociabila comunitate:");
        System.out.println("  Numar membri: " + community.getSize());
        System.out.println("  Diametru (distanta minima maxima): " + community.getDiameter());

        for (User user : community.getMembers())
            System.out.println("  " + user);
    }

    /**
     * Prints a prompt to the console and reads a line of text input from the user.
     *
     * @param prompt the text prompt to display
     * @return the entered line of text, or null if no input is available
     */
    private String readLine(String prompt) {
        System.out.print(prompt);
        System.out.flush();

        if (scanner.hasNextLine()) {
            return scanner.nextLine();
        }

        return null;
    }

    /**
     * Repeatedly prompts the user until a valid numeric Long value is entered.
     *
     * @param prompt the text prompt to display
     * @return the parsed Long value, or null if input reading fails
     */
    private Long readLong(String prompt) {
        while (true) {
            String value = readLine(prompt);

            if (value == null) {
                return null;
            }

            try {
                return Long.parseLong(value.trim());
            } catch (NumberFormatException exception) {
                System.out.println("Introdu un ID numeric valid.");
            }
        }
    }
}