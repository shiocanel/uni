package service;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.User;
import domain.service.CommunityAnalyzer;
import exception.EntityNotFoundException;
import repository.FriendshipRepository;
import repository.UserRepository;
import validation.ValidationStrategy;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Optional;

public final class SocialNetworkService {
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;
    private final ValidationStrategy<User> userValidator;
    private final ValidationStrategy<Friendship> friendshipValidator;
    private final CommunityAnalyzer communityAnalyzer;

    /**
     * Initializes the social network service with the required repositories, validation strategies, and community analyzer.
     *
     * @param userRepository      the repository for managing users
     * @param friendshipRepository the repository for managing friendships
     * @param userValidator       the validation strategy for user entities
     * @param friendshipValidator the validation strategy for friendship entities
     * @param communityAnalyzer   the analyzer used for community detection
     */
    public SocialNetworkService(UserRepository userRepository,
                                FriendshipRepository friendshipRepository,
                                ValidationStrategy<User> userValidator,
                                ValidationStrategy<Friendship> friendshipValidator,
                                CommunityAnalyzer communityAnalyzer) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
        this.userValidator = userValidator;
        this.friendshipValidator = friendshipValidator;
        this.communityAnalyzer = communityAnalyzer;
    }

    /**
     * Generates a new unique ID, creates and validates a new user with the specified first and last name, saves them, and returns the created user.
     *
     * @param firstName the first name of the user
     * @param lastName  the last name of the user
     * @return the newly created and saved user
     */
    public User addUser(String firstName, String lastName) {
        long nextId = 1;
        for (User user : userRepository.findAll()) {
            if (user.getId() >= nextId) nextId = user.getId() + 1;
        }
        User user = new User(nextId, firstName, lastName);
        userValidator.validate(user);
        userRepository.save(user);
        return user;
    }

    /**
     * Deletes a user by their ID along with all associated friendships after verifying the user exists.
     *
     * @param userId the unique ID of the user to remove
     */
    public void removeUser(long userId) {
        requireUser(userId);
        friendshipRepository.deleteByUserId(userId);
        userRepository.deleteById(userId);
    }

    /**
     * Retrieves an unmodifiable list of all registered users in the network.
     *
     * @return an unmodifiable list of all users
     */
    public List<User> getAllUsers() {
        return Collections.unmodifiableList(userRepository.findAll());
    }

    /**
     * Creates, validates, and saves a new friendship between two users identified by their IDs.
     *
     * @param firstUserId  the ID of the first user
     * @param secondUserId the ID of the second user
     */
    public void addFriendship(long firstUserId, long secondUserId) {
        Friendship friendship = new Friendship(firstUserId, secondUserId);
        friendshipValidator.validate(friendship);
        friendshipRepository.save(friendship);
    }

    /**
     * Removes the friendship between two specified users if it exists.
     *
     * @param firstUserId  the ID of the first user
     * @param secondUserId the ID of the second user
     */
    public void removeFriendship(long firstUserId, long secondUserId) {
        Friendship friendship = friendshipRepository.findByUsers(firstUserId, secondUserId)
                .orElseThrow(() -> new EntityNotFoundException("Prietenia dintre utilizatorii "
                        + firstUserId + " si " + secondUserId + " nu exista"));
        friendshipRepository.deleteById(friendship.getId());
    }

    /**
     * Retrieves an unmodifiable list of all friendships in the network.
     *
     * @return an unmodifiable list of all friendships
     */
    public List<Friendship> getAllFriendships() {
        return Collections.unmodifiableList(friendshipRepository.findAll());
    }

    /**
     * Analyzes the network's users and friendships to determine and return all distinct communities.
     *
     * @return a list of communities found in the social network
     */
    public List<Community> getCommunities() {
        return communityAnalyzer.analyze(userRepository.findAll(), friendshipRepository.findAll());
    }

    /**
     * Returns the total count of distinct communities present in the network.
     *
     * @return the number of communities
     */
    public int getCommunityCount() {
        return getCommunities().size();
    }

    /**
     * Finds and returns the most sociable community based on community diameter and size.
     *
     * @return an Optional containing the most sociable community, or empty if no communities exist
     */
    public Optional<Community> getMostSociableCommunity() {
        List<Community> communities = new ArrayList<Community>(getCommunities());
        if (communities.isEmpty()) return Optional.empty();
        Collections.sort(communities, new Comparator<Community>() {
            @Override public int compare(Community first, Community second) {
                int byDiameter = Integer.compare(second.getDiameter(), first.getDiameter());
                if (byDiameter != 0) return byDiameter;
                return Integer.compare(second.getSize(), first.getSize());
            }
        });
        return Optional.of(communities.get(0));
    }

    /**
     * Verifies and retrieves a user by their ID, throwing an exception if the user does not exist.
     *
     * @param userId the ID of the user to look up
     * @return the found user
     */
    private User requireUser(long userId) {
        return userRepository.findById(userId)
                .orElseThrow(() -> new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + userId));
    }
}