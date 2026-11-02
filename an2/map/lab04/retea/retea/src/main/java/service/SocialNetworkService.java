package service;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.User;
import exception.EntityNotFoundException;
import exception.ValidationException;
import repository.FriendshipRepository;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.TreeSet;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/** Application service for managing users, friendships and connected communities. */
public final class SocialNetworkService {
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;
    private final ValidationStrategy<User> userValidator;
    private final ValidationStrategy<Friendship> friendshipValidator;

    /** Functional interface matching the six-argument User constructor. */
    @FunctionalInterface
    private interface UserCreator {
        User create(long id, String firstName, String lastName, String email, String birthDate, String description);
    }

    /**
     * Creates the service using repository interfaces, not concrete implementations.
     *
     * @param userRepository repository for users
     * @param friendshipRepository repository for friendships
     * @param userValidator user validation strategy
     * @param friendshipValidator friendship validation strategy
     */
    public SocialNetworkService(UserRepository userRepository,
                                FriendshipRepository friendshipRepository,
                                ValidationStrategy<User> userValidator,
                                ValidationStrategy<Friendship> friendshipValidator) {
        if (userRepository == null || friendshipRepository == null || userValidator == null || friendshipValidator == null) {
            throw new IllegalArgumentException("Service-ul are nevoie de repository-uri si validatoare.");
        }
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.userValidator = userValidator;
        this.friendshipValidator = friendshipValidator;
    }

    /**
     * Creates, validates and stores a new user with an automatically generated ID.
     *
     * @param firstName user's first name
     * @param lastName user's last name
     * @return the created user
     */
    public User addUser(String firstName, String lastName) {
        return addUser(firstName, lastName, "", "", "");
    }

    /**
     * Creates a user with contact and profile details.
     *
     * @param firstName user's first name
     * @param lastName user's last name
     * @param email user's email address, or an empty string
     * @param birthDate user's birth date in YYYY-MM-DD format, or an empty string
     * @param description short profile description
     * @return the created user
     */
    public User addUser(String firstName, String lastName, String email, String birthDate, String description) {
        long nextId = userRepository.findAll().stream()
                .map(User::getId)
                .reduce(0L, Math::max) + 1L;
        UserCreator creator = User::new;
        User user = creator.create(nextId, firstName, lastName, email, birthDate, description);
        userValidator.validate(user);
        userRepository.save(user);
        return user;
    }

    /**
     * Finds a user by ID.
     *
     * @param userId ID to search for
     * @return an Optional containing the user when present
     */
    public Optional<User> findUserById(long userId) {
        return userRepository.findById(userId);
    }

    /**
     * Removes the user and all friendships associated with that user.
     *
     * @param userId ID of the user to remove
     * @throws EntityNotFoundException when no user has this ID
     */
    public void removeUser(long userId) {
        requireUser(userId);
        friendshipRepository.deleteByUserId(userId);
        userRepository.deleteById(userId);
    }

    /**
     * Finds a user by first name, last name or complete name, ignoring letter case.
     * A complete-name match has priority over first-name and last-name matches.
     *
     * @param name first name, last name or complete name to search for
     * @return the unique matching user
     * @throws EntityNotFoundException when no user matches
     * @throws ValidationException when the name is blank or ambiguous
     */
    public User findUserByName(String name) {
        String soughtName = normalizeName(name);
        if (soughtName.isEmpty()) {
            throw new ValidationException("Numele nu poate fi gol.");
        }

        List<User> users = userRepository.findAll();
        User fullNameMatch = resolveMatches(users.stream()
                .filter(user -> soughtName.equalsIgnoreCase(normalizeName(user.getFullName())))
                .collect(Collectors.toList()), soughtName);
        if (fullNameMatch != null) {
            return fullNameMatch;
        }

        User firstNameMatch = resolveMatches(users.stream()
                .filter(user -> soughtName.equalsIgnoreCase(normalizeName(user.getFirstName())))
                .collect(Collectors.toList()), soughtName);
        if (firstNameMatch != null) {
            return firstNameMatch;
        }

        User lastNameMatch = resolveMatches(users.stream()
                .filter(user -> soughtName.equalsIgnoreCase(normalizeName(user.getLastName())))
                .collect(Collectors.toList()), soughtName);
        if (lastNameMatch != null) {
            return lastNameMatch;
        }

        throw new EntityNotFoundException("Nu am gasit utilizatorul cu numele '" + soughtName + "'. "
                + "Alege un nume din lista utilizatorilor.");
    }

    private User resolveMatches(List<User> matches, String soughtName) {
        if (matches.size() > 1) {
            throw ambiguousName(soughtName);
        }
        return matches.stream().findFirst().orElse(null);
    }

    private ValidationException ambiguousName(String name) {
        return new ValidationException("Numele '" + name + "' nu identifica un singur utilizator. "
                + "Introdu numele complet, asa cum apare in lista utilizatorilor.");
    }

    /**
     * Removes a user using their name rather than asking for an ID.
     *
     * @param name first name or complete name of the user
     */
    public void removeUserByName(String name) {
        User user = findUserByName(name);
        removeUser(user.getId());
    }

    /** @return an unmodifiable list of registered users */
    public List<User> getAllUsers() {
        List<User> users = userRepository.findAll().stream()
                .collect(Collectors.toCollection(ArrayList::new));
        return Collections.unmodifiableList(users);
    }

    /**
     * Searches users using a composable predicate and sorts matches by last name, then first name.
     *
     * @param criterion predicate used to select users
     * @return matching users in alphabetical order
     */
    public List<User> findUsers(Predicate<User> criterion) {
        return userRepository.findAll(criterion).stream()
                .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                .collect(Collectors.toList());
    }

    /**
     * Returns the registered users who do not participate in any friendship.
     *
     * @return users without friends
     */
    public List<User> getUsersWithoutFriends() {
        Set<Long> usersWithFriends = friendshipRepository.findAll().stream()
                .flatMap(friendship -> Stream.of(friendship.getFirstUserId(), friendship.getSecondUserId()))
                .distinct()
                .collect(Collectors.toSet());
        Function<Set<Long>, Predicate<User>> criterionFactory = CriteriiUtilizator::faraPrieteni;
        return findUsers(criterionFactory.apply(usersWithFriends));
    }

    /**
     * Creates a friendship between two existing user IDs.
     *
     * @param firstUserId first user's ID
     * @param secondUserId second user's ID
     * @throws ValidationException when the friendship is invalid or already exists
     * @throws EntityNotFoundException when either user does not exist
     */
    public void addFriendship(long firstUserId, long secondUserId) {
        Friendship friendship = new Friendship(firstUserId, secondUserId);
        friendshipValidator.validate(friendship);
        boolean alreadyExists = friendshipRepository.findAll().stream()
                .anyMatch(existing -> existing.getId().equals(friendship.getId()));
        if (alreadyExists) {
            throw new ValidationException("Cei doi utilizatori sunt deja prieteni.");
        }
        friendshipRepository.save(friendship);
    }

    /**
     * Creates a friendship using first names or complete names typed by the user.
     *
     * @param firstName first user's first name or complete name
     * @param secondName second user's first name or complete name
     */
    public void addFriendshipByName(String firstName, String secondName) {
        User first = findUserByName(firstName);
        User second = findUserByName(secondName);
        addFriendship(first.getId(), second.getId());
    }

    /**
     * Removes the friendship between two existing user IDs.
     *
     * @param firstUserId first user's ID
     * @param secondUserId second user's ID
     * @throws EntityNotFoundException when the friendship does not exist
     */
    public void removeFriendship(long firstUserId, long secondUserId) {
        Friendship friendship = friendshipRepository.findByUsers(firstUserId, secondUserId)
                .orElseThrow(() -> new EntityNotFoundException("Nu exista prietenia dintre utilizatorii "
                        + firstUserId + " si " + secondUserId + "."));
        friendshipRepository.deleteById(friendship.getId());
    }

    /**
     * Removes a friendship using first names or complete names.
     *
     * @param firstName first user's first name or complete name
     * @param secondName second user's first name or complete name
     */
    public void removeFriendshipByName(String firstName, String secondName) {
        User first = findUserByName(firstName);
        User second = findUserByName(secondName);
        removeFriendship(first.getId(), second.getId());
    }

    /** @return an unmodifiable list of all friendships */
    public List<Friendship> getAllFriendships() {
        return Collections.unmodifiableList(new ArrayList<Friendship>(friendshipRepository.findAll()));
    }

    /**
     * Returns a count of direct friends for each user ID.
     *
     * @return map from user ID to number of direct friends; users without friends are omitted
     */
    public Map<Long, Long> getFriendCountsByUser() {
        return friendshipRepository.findAll().stream()
                .flatMap(friendship -> Stream.of(friendship.getFirstUserId(), friendship.getSecondUserId()))
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }

    /**
     * Finds all connected components, including users who have no friends. Component IDs are
     * assigned with disjoint sets and the final groups are built with Collectors.groupingBy.
     *
     * @return communities ordered by the smallest user ID in each community
     */
    public List<Community> getCommunities() {
        List<User> users = userRepository.findAll().stream()
                .sorted(Comparator.comparing(User::getId))
                .collect(Collectors.toList());
        Map<Long, Set<Long>> adjacency = users.stream().collect(Collectors.toMap(
                User::getId, user -> new TreeSet<Long>(), (first, ignored) -> first, LinkedHashMap::new));
        Map<Long, Long> parents = users.stream()
                .collect(Collectors.toMap(User::getId, User::getId));
        Map<Long, Integer> treeSizes = users.stream()
                .collect(Collectors.toMap(User::getId, user -> 1));

        friendshipRepository.findAll().stream()
                .filter(friendship -> parents.containsKey(friendship.getFirstUserId())
                        && parents.containsKey(friendship.getSecondUserId())
                        && friendship.getFirstUserId() != friendship.getSecondUserId())
                .forEach(friendship -> {
                    adjacency.get(friendship.getFirstUserId()).add(friendship.getSecondUserId());
                    adjacency.get(friendship.getSecondUserId()).add(friendship.getFirstUserId());
                    union(parents, treeSizes, friendship.getFirstUserId(), friendship.getSecondUserId());
                });

        Map<Long, List<User>> usersByComponent = users.stream()
                .collect(Collectors.groupingBy(user -> findRoot(parents, user.getId())));
        return usersByComponent.values().stream()
                .map(members -> {
                    List<User> sortedMembers = members.stream()
                            .sorted(Comparator.comparing(User::getId))
                            .collect(Collectors.toList());
                    Set<Long> componentIds = sortedMembers.stream()
                            .map(User::getId).collect(Collectors.toCollection(TreeSet::new));
                    return new Community(sortedMembers, calculateDiameter(componentIds, adjacency));
                })
                .sorted(Comparator.comparingLong(community -> community.getMembers().stream()
                        .map(User::getId).min(Long::compareTo).orElse(Long.MAX_VALUE)))
                .collect(Collectors.toList());
    }

    private void union(Map<Long, Long> parents,
                       Map<Long, Integer> treeSizes,
                       Long firstId,
                       Long secondId) {
        Long firstRoot = findRoot(parents, firstId);
        Long secondRoot = findRoot(parents, secondId);
        if (firstRoot.equals(secondRoot)) {
            return;
        }
        if (treeSizes.get(firstRoot) < treeSizes.get(secondRoot)) {
            Long temporary = firstRoot;
            firstRoot = secondRoot;
            secondRoot = temporary;
        }
        parents.put(secondRoot, firstRoot);
        treeSizes.put(firstRoot, treeSizes.get(firstRoot) + treeSizes.get(secondRoot));
    }

    private Long findRoot(Map<Long, Long> parents, Long userId) {
        Long parent = parents.get(userId);
        return parent.equals(userId) ? userId : findRoot(parents, parent);
    }

    /**
     * Counts connected components in the network.
     *
     * @return number of communities
     */
    public int getCommunityCount() {
        return Math.toIntExact(getCommunities().stream().count());
    }

    /**
     * Returns the community with greatest diameter, then greatest size; ties keep the
     * community whose smallest user ID is lowest, as in the previous implementation.
     *
     * @return the selected community, or empty when the network has no users
     */
    public Optional<Community> getMostSociableCommunity() {
        Comparator<Community> ranking = Comparator.comparingInt(Community::getDiameter)
                .thenComparingInt(Community::getSize)
                .thenComparing(Comparator.comparingLong(
                        (Community community) -> community.getMembers().stream()
                                .map(User::getId).min(Long::compareTo).orElse(Long.MAX_VALUE)).reversed());
        return getCommunities().stream().max(ranking);
    }

    /**
     * Checks whether every registered user has at least one friend.
     *
     * @return true for an empty network or when every user has a friend
     */
    public boolean allUsersHaveFriends() {
        Set<Long> usersWithFriends = getFriendCountsByUser().keySet();
        return userRepository.findAll().stream().allMatch(user -> usersWithFriends.contains(user.getId()));
    }

    /**
     * Checks whether at least one registered user has no friends.
     *
     * @return true when an isolated user exists
     */
    public boolean hasUsersWithoutFriends() {
        Set<Long> usersWithFriends = getFriendCountsByUser().keySet();
        return userRepository.findAll().stream().anyMatch(user -> !usersWithFriends.contains(user.getId()));
    }

    /**
     * Checks whether every community consists of a single isolated user.
     *
     * @return true when no community contains a friendship edge
     */
    public boolean hasOnlyIsolatedUsers() {
        return getCommunities().stream().noneMatch(community -> community.getSize() > 1);
    }

    private User requireUser(long userId) {
        return userRepository.findById(userId)
                .orElseThrow(() -> new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + userId + "."));
    }

    /**
     * Calculates the diameter by finding shortest-path distances from every vertex.
     *
     * @param component IDs belonging to one connected component
     * @param adjacency graph adjacency map
     * @return maximum shortest-path distance in the component
     */
    private int calculateDiameter(Set<Long> component, Map<Long, Set<Long>> adjacency) {
        return component.stream()
                .mapToInt(source -> breadthFirstDistances(source, adjacency).values().stream()
                        .mapToInt(Integer::intValue).max().orElse(0))
                .max().orElse(0);
    }

    private Map<Long, Integer> breadthFirstDistances(Long source, Map<Long, Set<Long>> adjacency) {
        Map<Long, Integer> distances = new HashMap<Long, Integer>();
        distances.put(source, 0);
        expandFrontier(Collections.singleton(source), 1, distances, adjacency);
        return distances;
    }

    private void expandFrontier(Set<Long> frontier,
                                int nextDistance,
                                Map<Long, Integer> distances,
                                Map<Long, Set<Long>> adjacency) {
        Set<Long> nextFrontier = frontier.stream()
                .filter(adjacency::containsKey)
                .flatMap(userId -> adjacency.get(userId).stream())
                .filter(neighbor -> !distances.containsKey(neighbor))
                .collect(Collectors.toSet());
        nextFrontier.forEach(userId -> distances.put(userId, nextDistance));
        if (!nextFrontier.isEmpty()) {
            expandFrontier(nextFrontier, nextDistance + 1, distances, adjacency);
        }
    }

    private String normalizeName(String name) {
        return name == null ? "" : name.trim().replaceAll("\\s+", " ");
    }
}
