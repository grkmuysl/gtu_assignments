package PriorityQueue;

/**
 * Interface for a priority queue data structure.
 *
 * @param <T> Type of elements, must be Comparable.
 */
public interface MyPriorityQueue<T extends Comparable<T>> {

    /**
     * Adds an element to the priority queue.
     * Time Complexity: O(log n)
     *
     * @param t The element to add.
     */
    void add(T t);

    /**
     * Removes and returns the element with the highest priority (minimum for min-heap).
     * Time Complexity: O(log n)
     *
     * @return The element with the highest priority, or null if the queue is empty.
     */
    T poll();

    /**
     * Checks if the priority queue is empty.
     * Time Complexity: O(1)
     *
     * @return true if the queue is empty, false otherwise.
     */
    boolean isEmpty();
}
