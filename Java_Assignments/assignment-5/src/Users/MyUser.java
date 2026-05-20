package Users;

/**
 * Represents a user with an ID and a priority.
 */
public class MyUser {
    /** Unique identifier for the user. */
    Integer id;

    /** Priority value for the user. Lower values mean higher priority. */
    Integer priority;

    /**
     * Constructs a user with the given ID and priority.
     * Time Complexity: O(1)
     *
     * @param id       The user's unique identifier.
     * @param priority The user's priority value.
     */
    public MyUser(Integer id, Integer priority) {
        this.id = id;
        this.priority = priority;
    }

    /**
     * Returns the user's ID.
     * Time Complexity: O(1)
     *
     * @return The user's ID.
     */
    public Integer getId() {
        return this.id;
    }

    /**
     * Returns the user's priority.
     * Time Complexity: O(1)
     *
     * @return The user's priority.
     */
    public Integer getPriority() {
        return this.priority;
    }
}
