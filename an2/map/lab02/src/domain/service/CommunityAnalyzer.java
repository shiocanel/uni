package domain.service;

import domain.model.Community;
import domain.model.Friendship;
import domain.model.User;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

public final class CommunityAnalyzer {
    /**
     * Analyzes the given users and friendships to discover all connected components (communities), computing their member lists and network diameters.
     *
     * @param users       the list of all users in the network
     * @param friendships the list of all friendships connecting the users
     * @return an unmodifiable list of detected communities
     */
    public List<Community> analyze(List<User> users, List<Friendship> friendships) {
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
            for (Long id : componentIds)
                members.add(usersById.get(id));

            Collections.sort(members, new Comparator<User>() {
                @Override public int compare(User first, User second) {
                    return Long.compare(first.getId(), second.getId());
                }
            });
            int diameter = calculateDiameter(componentIds, adjacency);
            communities.add(new Community(members, diameter));
        }
        return Collections.unmodifiableList(communities);
    }

    /**
     * Collects all user IDs belonging to the same connected component starting from a given user ID using breadth-first search.
     *
     * @param startId   the starting user ID for component collection
     * @param adjacency the adjacency list representing network connections
     * @param visited   a set tracking already visited user IDs
     * @return a sorted list of user IDs belonging to the connected component
     */
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

    /**
     * Calculates the diameter of a connected component by finding the maximum shortest path between any pair of nodes.
     *
     * @param component the list of user IDs representing the component
     * @param adjacency the adjacency list representing network connections
     * @return the calculated community diameter
     */
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

    /**
     * Computes the shortest path distances from a given source user ID to all reachable nodes in the component using breadth-first search.
     *
     * @param source    the source user ID
     * @param adjacency the adjacency list representing network connections
     * @return a map containing user IDs and their corresponding shortest distances from the source
     */
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
}