package domain.model;

public final class User extends Entity<Long> {
    private static final long serialVersionUID = 1L;

    private final String firstName;
    private final String lastName;

    /**
     * Initializes a user entity with the specified ID, first name, and last name, trimming any surrounding whitespace from the names.
     *
     * @param id        the unique identifier of the user
     * @param firstName the first name of the user
     * @param lastName  the last name of the user
     */
    public User(long id, String firstName, String lastName) {
        this.id = id;
        this.firstName = firstName == null ? null : firstName.trim();
        this.lastName = lastName == null ? null : lastName.trim();
    }

    /**
     * Returns the first name of the user.
     *
     * @return the user's first name
     */
    public String getFirstName() { return firstName; }

    /**
     * Returns the last name of the user.
     *
     * @return the user's last name
     */
    public String getLastName() { return lastName; }

    /**
     * Returns the full name of the user by combining their first and last names with a space.
     *
     * @return the user's full name
     */
    public String getFullName() {
        return firstName + " " + lastName;
    }

    /**
     * Returns a string representation of the user containing their ID and full name.
     *
     * @return a string representation of the user
     */
    @Override
    public String toString() {
        return "ID: " + getId() + " | " + getFullName();
    }
}