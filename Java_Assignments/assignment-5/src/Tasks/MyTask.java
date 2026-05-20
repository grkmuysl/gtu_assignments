package Tasks;

import Users.MyUser;

/**
 * Represents a task assigned to a user.
 */
public class MyTask implements Comparable<MyTask> {
    /** The user associated with this task. */
    MyUser user;

    /** Unique identifier for this task. */
    Integer id;

    /**
     * Constructs a task for the given user with a specific ID.
     * Time Complexity: O(1)
     *
     * @param user The user assigned to the task.
     * @param id   The unique task ID.
     */
    public MyTask(MyUser user, Integer id){
        this.user = user;
        this.id = id;
    }

    /**
     * Returns a string representation of the task.
     * Time Complexity: O(1)
     *
     * @return String describing the task and user.
     */
    public String toString(){
        String str = "Task " + id + " User " + user.getId();
        return str;
    }

    /**
     * Compares this task to another task.
     * Tasks are first compared by user priority, then by task ID.
     * Time Complexity: O(1)
     *
     * @param other The other task to compare to.
     * @return Negative if this task has higher priority, positive if lower, zero if equal.
     */
    @Override
    public int compareTo(MyTask other) {
        int userPriorityCompare = this.user.getPriority().compareTo(other.user.getPriority());
        if (userPriorityCompare != 0) {
            return userPriorityCompare; 
        }
        return this.id.compareTo(other.id); 
    }

}
