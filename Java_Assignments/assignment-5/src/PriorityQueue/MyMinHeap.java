package PriorityQueue;

import java.util.ArrayList;

/**
 * Min-heap based priority queue implementation.
 *
 * @param <T> Type of elements, must be Comparable.
 */
public class MyMinHeap<T extends Comparable<T>> implements MyPriorityQueue<T> {

    /** Internal list to store heap elements. */
    private ArrayList<T> heap;

    /**
     * Constructs an empty min-heap.
     * Time Complexity: O(1)
     */
    public MyMinHeap(){
        heap = new ArrayList<>();
    }

    /**
     * Adds a new element to the heap.
     * Time Complexity: O(log n)
     *
     * @param item Element to add.
     */
    @Override
    public void add(T item){
        heap.add(item);
        int addedItem = heap.size() - 1;
        siftUp(addedItem);
    }

    /**
     * Removes and returns the minimum element from the heap.
     * Time Complexity: O(log n)
     *
     * @return The minimum element, or null if the heap is empty.
     */
    @Override
    public T poll(){
        if(!heap.isEmpty()){
            int firstInd = 0;
            int lastInd = heap.size() - 1;
            T minItem = heap.get(firstInd);
            swap(firstInd, lastInd);
            heap.remove(lastInd);
            siftDown(firstInd);
            return minItem;
        } else {
            return null;
        }
    }

    /**
     * Restores heap property by moving the element at the given index up.
     * Time Complexity: O(log n)
     *
     * @param idx Index of the element to sift up.
     */
    private void siftUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap.get(idx).compareTo(heap.get(parent)) < 0) {
                swap(idx, parent);
                idx = parent;
            } else{
                break;
            }
        }
    }

    /**
     * Restores heap property by moving the element at the given index down.
     * Time Complexity: O(log n)
     *
     * @param idx Index of the element to sift down.
     */
    private void siftDown(int idx){
        int size = heap.size();

        while ((2 * idx) + 1 < size) {
            int leftChild = (2 * idx) + 1;
            int rightChild = (2 * idx) + 2;
            int smallest = leftChild;

            if (rightChild < size && heap.get(rightChild).compareTo(heap.get(leftChild)) < 0) {
                smallest = rightChild;
            }
            if (heap.get(idx).compareTo(heap.get(smallest)) > 0) {
                swap(idx, smallest);
                idx = smallest;
            } else break;
        }
    }

    /**
     * Swaps two elements in the heap.
     * Time Complexity: O(1)
     *
     * @param i Index of the first element.
     * @param j Index of the second element.
     */
    private void swap(int i, int j) {
        T first = heap.get(i);
        T second = heap.get(j);
        heap.set(i, second);
        heap.set(j, first);
    }

    /**
     * Checks if the heap is empty.
     * Time Complexity: O(1)
     *
     * @return true if the heap is empty, false otherwise.
     */
    @Override
    public boolean isEmpty(){
        return heap.isEmpty();
    }

    /**
     * Returns the internal ArrayList representing the heap.
     * Time Complexity: O(1)
     *
     * @return The internal ArrayList of the heap.
     */
    public ArrayList<T> getArrayList(){
        return heap;
    }
}
