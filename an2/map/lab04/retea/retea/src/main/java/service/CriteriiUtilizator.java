package service;

import domain.model.User;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;
import java.util.function.Predicate;

/** Static search criteria that can be combined with Predicate.and, or and negate. */
public final class CriteriiUtilizator {
    private CriteriiUtilizator() {
    }

    /**
     * Builds a criterion selecting users whose IDs are not in the supplied set.
     *
     * @param usersWithFriends IDs of users who have at least one friendship
     * @return predicate matching users without friends
     */
    public static Predicate<User> faraPrieteni(Set<Long> usersWithFriends) {
        Set<Long> connectedIds = usersWithFriends == null
                ? Collections.<Long>emptySet() : new HashSet<Long>(usersWithFriends);
        return user -> !connectedIds.contains(user.getId());
    }

    /**
     * Builds a criterion selecting users whose first name contains the supplied text.
     *
     * @param text text to search for, ignoring letter case
     * @return predicate matching first names
     */
    public static Predicate<User> prenumeContine(String text) {
        String sought = normalize(text);
        return user -> normalize(user.getFirstName()).contains(sought);
    }

    /**
     * Builds a criterion selecting users who have an email address.
     *
     * @return predicate matching users with non-empty email addresses
     */
    public static Predicate<User> areEmail() {
        return user -> !user.getEmail().isEmpty();
    }

    /**
     * Builds a criterion selecting users whose last name begins with a prefix.
     *
     * @param prefix prefix to search for, ignoring letter case
     * @return predicate matching last names
     */
    public static Predicate<User> numeIncepeCu(String prefix) {
        String sought = normalize(prefix);
        return user -> normalize(user.getLastName()).startsWith(sought);
    }

    private static String normalize(String value) {
        return value == null ? "" : value.trim().toLowerCase(java.util.Locale.ROOT);
    }
}
