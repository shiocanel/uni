package validation;

import domain.model.Friendship;
import exception.EntityNotFoundException;
import exception.ValidationException;
import repository.UserRepository;

/** Validation rules for friendships. */
public final class FriendshipValidationStrategy implements ValidationStrategy<Friendship> {
    private final UserRepository userRepository;

    /**
     * @param userRepository repository used to check that both users exist
     */
    public FriendshipValidationStrategy(UserRepository userRepository) {
        if (userRepository == null) throw new IllegalArgumentException("Repository-ul de utilizatori este obligatoriu.");
        this.userRepository = userRepository;
    }

    /**
     * Checks that a friendship connects two distinct users that both exist.
     *
     * @param friendship friendship entity to validate
     * @throws ValidationException when the friendship is null or connects a user to themselves
     * @throws EntityNotFoundException when either user does not exist
     */
    @Override
    public void validate(Friendship friendship) {
        if (friendship == null) throw new ValidationException("Prietenia nu poate fi null.");
        if (friendship.getFirstUserId() == friendship.getSecondUserId())
            throw new ValidationException("Un utilizator nu se poate adauga pe sine ca prieten.");
        if (!userRepository.findById(friendship.getFirstUserId()).isPresent())
            throw new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + friendship.getFirstUserId() + ".");
        if (!userRepository.findById(friendship.getSecondUserId()).isPresent())
            throw new EntityNotFoundException("Nu exista utilizatorul cu ID-ul " + friendship.getSecondUserId() + ".");
    }
}
