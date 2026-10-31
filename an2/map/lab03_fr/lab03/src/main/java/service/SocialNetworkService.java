package service;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.FriendshipId;
import domain.model.User;
import exception.EntityNotFoundException;
import exception.ValidationException;
import repository.FriendshipRepository;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

/** Application service for managing users, friendships and connected communities. */
public final class SocialNetworkService {
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;
    private final ValidationStrategy<User> userValidator;
    private final ValidationStrategy<Friendship> friendshipValidator;

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
        if (userRepository == null || friendshipRepository == null || userValidator == null || friendshipValidator == null)
            throw new IllegalArgumentException("Service-ul are nevoie de repository-uri si validatoare.");
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
     * @throws exception.ValidationException when a name is invalid
     * @throws exception.RepositoryException when the user cannot be saved
     */
    public User addUser(String firstName, String lastName) {
        return addUser(firstName, lastName, "", "", "");
    }

    /** Creates a user with contact and profile details. */
    public User addUser(String firstName, String lastName, String email, String birthDate, String description) {
        long nextId = 1;
        for (User existing : userRepository.findAll()) {
            if (existing.getId() >= nextId) nextId = existing.getId() + 1;
        }
        User user = new User(nextId, firstName, lastName, email, birthDate, description);
        userValidator.validate(user);
        userRepository.save(user);
        return user;
    }

    /**
     * Removes the user and all friendships associated with that user.
     *
     * @param userId ID of the user to remove
     * @throws EntityNotFoundException when no user has this ID
     * @throws exception.RepositoryException when a repository operation fails
     */
    public void removeUser(long userId) {
        requireUser(userId);
        friendshipRepository.deleteByUserId(userId);
        userRepository.deleteById(userId);
    }

    /**
     * Finds a user by first name, last name or complete name, ignoring letter case.
     *
     * @param name first name, last name or complete name to search for
     * @return the unique matching user
     * @throws EntityNotFoundException when no user matches
     * @throws ValidationException when the name matches more than one user or is blank
     */
    public User findUserByName(String name) {
        String soughtName = normalizeName(name);
        if (soughtName.isEmpty()) {
            throw new ValidationException("Numele nu poate fi gol.");
        }

        List<User> fullNameMatches = new ArrayList<User>();
        List<User> firstNameMatches = new ArrayList<User>();
        List<User> lastNameMatches = new ArrayList<User>();

        for (User user : userRepository.findAll()) {
            if (soughtName.equalsIgnoreCase(normalizeName(user.getFullName()))) {
                fullNameMatches.add(user);
            }
            if (soughtName.equalsIgnoreCase(normalizeName(user.getFirstName()))) {
                firstNameMatches.add(user);
            }
            if (soughtName.equalsIgnoreCase(normalizeName(user.getLastName()))) {
                lastNameMatches.add(user);
            }
        }

        // A complete name is the most specific match.
        if (fullNameMatches.size() == 1) return fullNameMatches.get(0);
        if (fullNameMatches.size() > 1) {
            throw ambiguousName(soughtName);
        }

        // Prefer a first name so a person can enter names such as "Antonio" or "Alexandra".
        if (firstNameMatches.size() == 1) return firstNameMatches.get(0);
        if (firstNameMatches.size() > 1) {
            throw ambiguousName(soughtName);
        }

        if (lastNameMatches.size() == 1) return lastNameMatches.get(0);
        if (lastNameMatches.size() > 1) {
            throw ambiguousName(soughtName);
        }

        throw new EntityNotFoundException("Nu am gasit utilizatorul cu numele '" + soughtName + "'. "
                + "Alege un nume din lista utilizatorilor.");
    }

    private ValidationException ambiguousName(String name) {
        return new ValidationException("Numele '" + name + "' nu identifica un singur utilizator. "
                + "Introdu numele complet, asa cum apare in lista utilizatorilor.");
    }

    /**
     * Removes a user using their name rather than asking for an ID.
     *
     * @param name first name or complete name of the user
     * @throws EntityNotFoundException when no user matches
     * @throws ValidationException when the name is ambiguous
     */
    public void removeUserByName(String name) {
        User user = findUserByName(name);
        removeUser(user.getId());
    }

    /** @return a read-only list of registered users */
    public List<User> getAllUsers() {
        return Collections.unmodifiableList(new ArrayList<User>(userRepository.findAll()));
    }

    /**
     * Creates a friendship between two existing user IDs.
     *
     * @param firstUserId first user's ID
     * @param secondUserId second user's ID
     * @throws exception.ValidationException when the friendship is invalid or already exists
     * @throws EntityNotFoundException when either user does not exist
     */
    public void addFriendship(long firstUserId, long secondUserId) {
        Friendship friendship = new Friendship(firstUserId, secondUserId);
        friendshipValidator.validate(friendship);
        if (friendshipRepository.findByUsers(firstUserId, secondUserId).isPresent())
            throw new ValidationException("Cei doi utilizatori sunt deja prieteni.");
        friendshipRepository.save(friendship);
    }

    /**
     * Creates a friendship using first names or complete names typed by the user.
     *
     * @param firstName first user's first name or complete name
     * @param secondName second user's first name or complete name
     * @throws EntityNotFoundException when either name does not match a user
     * @throws ValidationException when a name is ambiguous or the friendship is invalid
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
        Optional<Friendship> friendship = friendshipRepository.findByUsers(firstUserId, secondUserId);
        if (!friendship.isPresent()) {
            throw new EntityNotFoundException("Nu exista prietenia dintre utilizatorii "
                    + firstUserId + " si " + secondUserId + ".");
        }
        friendshipRepository.deleteById(friendship.get().getId());
    }

    /**
     * Removes a friendship using first names or complete names.
     *
     * @param firstName first user's first name or complete name
     * @param secondName second user's first name or complete name
     * @throws EntityNotFoundException when a user or the friendship does not exist
     * @throws ValidationException when either name is ambiguous
     */
    public void removeFriendshipByName(String firstName, String secondName) {
        User first = findUserByName(firstName);
        User second = findUserByName(secondName);
        removeFriendship(first.getId(), second.getId());
    }

    /** @return a read-only list of all friendships */
    public List<Friendship> getAllFriendships() {
        return Collections.unmodifiableList(new ArrayList<Friendship>(friendshipRepository.findAll()));
    }

    /**
     * Finds all connected components, including users who have no friends.
     *
     * @return a read-only list of communities sorted by their first member ID
     */
    public List<Community> getCommunities() {
        List<User> users = userRepository.findAll();
        List<Friendship> friendships = friendshipRepository.findAll();
        Map<Long, User> usersById = new HashMap<Long, User>();
        Map<Long, Set<Long>> adjacency = new HashMap<Long, Set<Long>>();

        for (User user : users) {
            usersById.put(user.getId(), user);
            adjacency.put(user.getId(), new TreeSet<Long>());
        }
        for (Friendship friendship : friendships) {
            Set<Long> firstNeighbors = adjacency.get(friendship.getFirstUserId());
            Set<Long> secondNeighbors = adjacency.get(friendship.getSecondUserId());
            if (firstNeighbors != null && secondNeighbors != null
                    && friendship.getFirstUserId() != friendship.getSecondUserId()) {
                firstNeighbors.add(friendship.getSecondUserId());
                secondNeighbors.add(friendship.getFirstUserId());
            }
        }

        List<Long> allIds = new ArrayList<Long>(adjacency.keySet());
        Collections.sort(allIds);
        Set<Long> visited = new HashSet<Long>();
        List<Community> communities = new ArrayList<Community>();

        for (Long startId : allIds) {
            if (visited.contains(startId)) continue;
            List<Long> componentIds = collectComponent(startId, adjacency, visited);
            List<User> members = new ArrayList<User>();
            for (Long id : componentIds) members.add(usersById.get(id));
            Collections.sort(members, new Comparator<User>() {
                @Override
                public int compare(User first, User second) {
                    return Long.compare(first.getId(), second.getId());
                }
            });
            communities.add(new Community(members, calculateDiameter(componentIds, adjacency)));
        }
        return Collections.unmodifiableList(communities);
    }

    /**
     * Counts the connected components in the network.
     *
     * @return the number of communities
     */
    public int getCommunityCount() {
        return getCommunities().size();
    }

    /**
     * Returns the community with greatest diameter, then greatest size, preserving the previous lab's rule.
     *
     * @return the selected community, or empty when the network has no users
     */
    public Optional<Community> getMostSociableCommunity() {
        List<Community> communities = new ArrayList<Community>(getCommunities());
        if (communities.isEmpty()) return Optional.empty();
        Collections.sort(communities, new Comparator<Community>() {
            @Override
            public int compare(Community first, Community second) {
                int byDiameter = Integer.compare(second.getDiameter(), first.getDiameter());
                if (byDiameter != 0) return byDiameter;
                int bySize = Integer.compare(second.getSize(), first.getSize());
                if (bySize != 0) return bySize;
                long firstId = first.getMembers().get(0).getId();
                long secondId = second.getMembers().get(0).getId();
                return Long.compare(firstId, secondId);
            }
        });
        return Optional.of(communities.get(0));
    }

    private User requireUser(long userId) {
        Optional<User> user = userRepository.findById(userId);
        if (!user.isPresent()) throw new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + userId + ".");
        return user.get();
    }

    private List<Long> collectComponent(Long startId, Map<Long, Set<Long>> adjacency, Set<Long> visited) {
        List<Long> component = new ArrayList<Long>();
        Queue<Long> queue = new ArrayDeque<Long>();
        queue.add(startId);
        visited.add(startId);
        while (!queue.isEmpty()) {
            Long current = queue.remove();
            component.add(current);
            for (Long neighbor : adjacency.get(current)) {
                if (visited.add(neighbor)) queue.add(neighbor);
            }
        }
        Collections.sort(component);
        return component;
    }

    private int calculateDiameter(List<Long> component, Map<Long, Set<Long>> adjacency) {
        int diameter = 0;
        for (Long source : component) {
            Map<Long, Integer> distances = breadthFirstDistances(source, adjacency);
            for (Long target : component) {
                Integer distance = distances.get(target);
                if (distance != null && distance > diameter) diameter = distance;
            }
        }
        return diameter;
    }

    private Map<Long, Integer> breadthFirstDistances(Long source, Map<Long, Set<Long>> adjacency) {
        Map<Long, Integer> distances = new HashMap<Long, Integer>();
        Queue<Long> queue = new ArrayDeque<Long>();
        distances.put(source, 0);
        queue.add(source);
        while (!queue.isEmpty()) {
            Long current = queue.remove();
            for (Long neighbor : adjacency.get(current)) {
                if (!distances.containsKey(neighbor)) {
                    distances.put(neighbor, distances.get(current) + 1);
                    queue.add(neighbor);
                }
            }
        }
        return distances;
    }

    private String normalizeName(String name) {
        if (name == null) return "";
        return name.trim().replaceAll("\\s+", " ");
    }
}
