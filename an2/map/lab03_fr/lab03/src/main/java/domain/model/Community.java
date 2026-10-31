package domain.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/** A connected component of users in the social network. */
public final class Community {
    private final List<User> members;
    private final int diameter;

    /**
     * Creates a community with its members and graph diameter.
     *
     * @param members community members
     * @param diameter largest shortest-path distance in this component
     */
    public Community(List<User> members, int diameter) {
        this.members = Collections.unmodifiableList(new ArrayList<User>(members));
        this.diameter = diameter;
    }

    /** @return an unmodifiable list of community members */
    public List<User> getMembers() {
        return members;
    }

    /** @return the community graph diameter */
    public int getDiameter() {
        return diameter;
    }

    /** @return number of users in the community */
    public int getSize() {
        return members.size();
    }
}
