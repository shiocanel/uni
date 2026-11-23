package domain.model;

/** Represents a person registered in the social network. */
public final class User extends Entity<Long> {
    private static final long serialVersionUID = 1L;

    private final String firstName;
    private final String lastName;
    private final String email;
    private final String birthDate;
    private final String description;

    /**
     * Creates a user without an ID. The selected repository assigns the ID when saving.
     *
     * @param firstName user's first name
     * @param lastName user's last name
     */
    public User(String firstName, String lastName) {
        this(null, firstName, lastName, "", "", "");
    }

    /**
     * Creates a user without an ID and with optional profile information.
     *
     * @param firstName user's first name
     * @param lastName user's last name
     * @param email user's email address
     * @param birthDate user's birth date
     * @param description user's profile description
     */
    public User(String firstName, String lastName, String email, String birthDate, String description) {
        this(null, firstName, lastName, email, birthDate, description);
    }

    /**
     * Creates a user with a known ID, for example when reading from storage.
     *
     * @param id user ID
     * @param firstName user's first name
     * @param lastName user's last name
     */
    public User(Long id, String firstName, String lastName) {
        this(id, firstName, lastName, "", "", "");
    }

    /**
     * Creates a user with all fields. A null ID is allowed before the first save.
     *
     * @param id user ID, or null before saving
     * @param firstName user's first name
     * @param lastName user's last name
     * @param email user's email address
     * @param birthDate user's birth date
     * @param description user's profile description
     */
    public User(Long id, String firstName, String lastName, String email, String birthDate, String description) {
        this.id = id;
        this.firstName = firstName == null ? null : firstName.trim();
        this.lastName = lastName == null ? null : lastName.trim();
        this.email = email == null ? "" : email.trim();
        this.birthDate = birthDate == null ? "" : birthDate.trim();
        this.description = description == null ? "" : description.trim();
    }

    /** @return user's first name */
    public String getFirstName() { return firstName; }

    /** @return user's last name */
    public String getLastName() { return lastName; }

    /** @return user's email address */
    public String getEmail() { return email; }

    /** @return user's birth date */
    public String getBirthDate() { return birthDate; }

    /** @return user's profile description */
    public String getDescription() { return description; }

    /** @return user's full name */
    public String getFullName() { return firstName + " " + lastName; }

    @Override
    public String toString() { return getFullName() + " (ID: " + getId() + ")"; }
}
