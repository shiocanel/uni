package domain.model;

/** Represents a person registered in the social network. */
public final class User extends Entity<Long> {
    private static final long serialVersionUID = 1L;

    private final String firstName;
    private final String lastName;
    private final String email;
    private final String birthDate;
    private final String description;

    public User(long id, String firstName, String lastName) {
        this(id, firstName, lastName, "", "", "");
    }

    public User(long id, String firstName, String lastName, String email, String birthDate, String description) {
        this.id = id;
        this.firstName = firstName == null ? null : firstName.trim();
        this.lastName = lastName == null ? null : lastName.trim();
        this.email = email == null ? "" : email.trim();
        this.birthDate = birthDate == null ? "" : birthDate.trim();
        this.description = description == null ? "" : description.trim();
    }

    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }
    public String getEmail() { return email; }
    public String getBirthDate() { return birthDate; }
    public String getDescription() { return description; }
    public String getFullName() { return firstName + " " + lastName; }

    @Override
    public String toString() { return getFullName() + " (ID: " + getId() + ")"; }
}
