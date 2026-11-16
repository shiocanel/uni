package ui;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.User;
import exception.RepositoryException;
import exception.SocialNetworkException;
import service.SocialNetworkService;

import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Scanner;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/** Console-based interface for the social network application. */
public final class ConsoleUI {
    private final SocialNetworkService service;
    private final Scanner scanner;
    private final DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    /**
     * Creates the console interface.
     *
     * @param service application service
     * @param scanner source of console input
     */
    public ConsoleUI(SocialNetworkService service, Scanner scanner) {
        if (service == null || scanner == null) {
            throw new IllegalArgumentException("Service-ul si scanner-ul sunt obligatorii.");
        }
        this.service = service;
        this.scanner = scanner;
    }

    /** Runs the interactive menu until the user chooses exit or input ends. */
    public void run() {
        boolean running = true;
        // This is an interaction loop, not a collection traversal; the menu must remain active.
        while (running) {
            printMenu();
            String option = readLine("Optiunea: ");
            if (option == null) {
                break;
            }

            try {
                switch (option.trim()) {
                    case "1":
                        showUsers();
                        break;
                    case "2":
                        addUser();
                        break;
                    case "3":
                        removeUser();
                        break;
                    case "4":
                        addFriendship();
                        break;
                    case "5":
                        removeFriendship();
                        break;
                    case "6":
                        showFriendships();
                        break;
                    case "7":
                        System.out.println("Numar comunitati: " + service.getCommunityCount());
                        break;
                    case "8":
                        showMostSociableCommunity();
                        break;
                    case "9":
                        showCommunities();
                        break;
                    case "0":
                        running = false;
                        System.out.println("La revedere!");
                        break;
                    default:
                        System.out.println("Optiune invalida.");
                }
            } catch (RepositoryException exception) {
                System.out.println("Storage error: " + exception.getMessage());
            } catch (SocialNetworkException exception) {
                System.out.println("Error: " + exception.getMessage());
            } catch (UnsupportedOperationException exception) {
                System.out.println("Operatie indisponibila: " + exception.getMessage());
            }
            System.out.println();
        }
    }

    private void printMenu() {
        System.out.println("--- RETEA DE SOCIALIZARE ---");
        System.out.println("1. Afiseaza utilizatorii");
        System.out.println("2. Adauga utilizator");
        System.out.println("3. Sterge utilizator");
        System.out.println("4. Adauga prietenie");
        System.out.println("5. Sterge prietenie");
        System.out.println("6. Afiseaza prieteniile");
        System.out.println("7. Numarul de comunitati");
        System.out.println("8. Cea mai sociabila comunitate");
        System.out.println("9. Afiseaza toate comunitatile");
        System.out.println("0. Iesire");
    }

    private void showUsers() {
        List<User> users = service.getAllUsers();
        if (users.isEmpty()) {
            System.out.println("Nu exista utilizatori.");
            return;
        }
        users.stream().map(user -> {
            String email = Optional.of(user.getEmail()).filter(value -> !value.isEmpty())
                    .map(value -> " | Email: " + value).orElse("");
            String birthDate = Optional.of(user.getBirthDate()).filter(value -> !value.isEmpty())
                    .map(value -> " | Nastere: " + value).orElse("");
            String description = Optional.of(user.getDescription()).filter(value -> !value.isEmpty())
                    .map(value -> " | Despre: " + value).orElse("");
            return user.getId() + ". " + user.getFullName() + email + birthDate + description;
        }).forEach(System.out::println);
        System.out.println("----------------------------------------");
        System.out.println("Total: " + users.size());
    }

    private void addUser() {
        String firstName = readLine("Prenume: ");
        if (firstName == null) return;
        String lastName = readLine("Nume: ");
        if (lastName == null) return;
        String email = readLine("Email (optional): ");
        if (email == null) return;
        String birthDate = readLine("Data nasterii YYYY-MM-DD (optional): ");
        if (birthDate == null) return;
        String description = readLine("Descriere scurta (optional, fara ;): ");
        if (description == null) return;

        User user = service.addUser(firstName, lastName, email, birthDate, description);
        System.out.println("Adaugat: " + user.getFullName() + " (ID " + user.getId() + ")");
    }

    private void removeUser() {
        String name = readLine("Numele utilizatorului: ");
        if (name == null) return;
        User user = service.findUserByName(name);
        service.removeUserByName(name);
        System.out.println("A fost sters " + user.getFullName() + " si prieteniile lui.");
    }

    private void addFriendship() {
        System.out.println("Poti scrie prenumele sau numele complet.");
        String firstName = readLine("Primul utilizator: ");
        if (firstName == null) return;
        String secondName = readLine("Al doilea utilizator: ");
        if (secondName == null) return;

        User first = service.findUserByName(firstName);
        User second = service.findUserByName(secondName);
        service.addFriendshipByName(firstName, secondName);
        System.out.println("Prietenie adaugata: " + first.getFullName() + " - " + second.getFullName());
    }

    private void removeFriendship() {
        System.out.println("Poti scrie prenumele sau numele complet.");
        String firstName = readLine("Primul utilizator: ");
        if (firstName == null) return;
        String secondName = readLine("Al doilea utilizator: ");
        if (secondName == null) return;

        User first = service.findUserByName(firstName);
        User second = service.findUserByName(secondName);
        service.removeFriendshipByName(firstName, secondName);
        System.out.println("Prietenie stearsa: " + first.getFullName() + " - " + second.getFullName());
    }

    private void showFriendships() {
        List<Friendship> friendships = service.getAllFriendships();
        if (friendships.isEmpty()) {
            System.out.println("Nu exista prietenii.");
            return;
        }
        Map<Long, User> usersById = service.getAllUsers().stream()
                .collect(Collectors.toMap(User::getId, Function.identity()));
        friendships.stream().map(friendship -> {
            User first = usersById.get(friendship.getFirstUserId());
            User second = usersById.get(friendship.getSecondUserId());
            String firstName = first == null ? "ID " + friendship.getFirstUserId() : first.getFullName();
            String secondName = second == null ? "ID " + friendship.getSecondUserId() : second.getFullName();
            return firstName + " - " + secondName + " (" + friendship.getDate().format(dateFormat) + ")";
        }).forEach(System.out::println);
        System.out.println("Total prietenii: " + friendships.size());
    }

    private void showMostSociableCommunity() {
        Optional<Community> result = service.getMostSociableCommunity();
        if (!result.isPresent()) {
            System.out.println("Nu exista comunitati.");
            return;
        }
        result.ifPresent(community -> {
            System.out.println("Cea mai sociabila comunitate:");
            System.out.println("Membri: " + community.getSize());
            System.out.println("Diametru: " + community.getDiameter());
            community.getMembers().stream().map(User::getFullName).forEach(name -> System.out.println("- " + name));
        });
    }

    private void showCommunities() {
        List<Community> communities = service.getCommunities();
        if (communities.isEmpty()) {
            System.out.println("Nu exista comunitati.");
            return;
        }
        IntStream.range(0, communities.size()).mapToObj(index -> {
            Community community = communities.get(index);
            String members = community.getMembers().stream()
                    .map(User::getFullName)
                    .collect(Collectors.joining(", "));
            return "Comunitatea " + (index + 1) + " (membri: " + community.getSize()
                    + ", diametru: " + community.getDiameter() + "): " + members;
        }).forEach(System.out::println);
    }

    private String readLine(String prompt) {
        System.out.print(prompt);
        return scanner.hasNextLine() ? scanner.nextLine() : null;
    }
}
