package domain.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public final class Community {
    private final List<User> members;
    private final int diameter;

    /**
     * Initializes a community with a list of member users and its computed network diameter.
     *
     * @param members  the list of users belonging to the community
     * @param diameter the diameter of the community graph
     */
    public Community(List<User> members, int diameter) {
        this.members = Collections.unmodifiableList(new ArrayList<User>(members));
        this.diameter = diameter;
    }

    /**
     * Returns an unmodifiable list of all members belonging to this community.
     *
     * @return an unmodifiable list of community members
     */
    public List<User> getMembers() { return members; }

    /**
     * Returns the network diameter of this community.
     *
     * @return the community diameter
     */
    public int getDiameter() { return diameter; }

    /**
     * Returns the total number of members in this community.
     *
     * @return the size of the community
     */
    public int getSize() { return members.size(); }
}