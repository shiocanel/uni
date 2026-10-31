package validation;

import domain.model.Friendship;
import exception.EntityNotFoundException;
import exception.ValidationException;
import repository.FriendshipRepository;
import repository.UserRepository;

public final class FriendshipValidationStrategy implements ValidationStrategy<Friendship> {
    private final UserRepository userRepository;
    private final FriendshipRepository friendshipRepository;

    /**
     * Initializes the friendship validation strategy with the specified user and friendship repositories.
     *
     * @param userRepository     the repository used to verify user existence
     * @param friendshipRepository the repository used to verify existing friendships
     */
    public FriendshipValidationStrategy(UserRepository userRepository, FriendshipRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * Validates the specified friendship, ensuring it is not null, connects different users who both exist, and is not a duplicate.
     *
     * @param friendship the friendship entity to validate
     */
    @Override
    public void validate(Friendship friendship) {
        if (friendship == null)
            throw new ValidationException("Prietenia nu poate fi null");

        if (friendship.getFirstUserId() == friendship.getSecondUserId()) {
            throw new ValidationException("Un utilizator nu se poate adauga pe sine ca prieten");
        }
        if (!userRepository.findById(friendship.getFirstUserId()).isPresent()) {
            throw new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + friendship.getFirstUserId());
        }
        if (!userRepository.findById(friendship.getSecondUserId()).isPresent()) {
            throw new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + friendship.getSecondUserId());
        }
        if (friendshipRepository.findByUsers(friendship.getFirstUserId(), friendship.getSecondUserId()).isPresent()) {
            throw new ValidationException("Cei doi utilizatori sunt deja prieteni");
        }
    }
}