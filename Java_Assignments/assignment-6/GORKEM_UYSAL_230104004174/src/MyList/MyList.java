package MyList;


/**
 * MyList is a generic resizable array implementation
 * It provides methods for adding annd getting elements, and checking the size 
 * 
 * @param <E> The type of elements in this list
 */

public class MyList<E> {

    /* Array to store elements */
    private E[] data;

    /* current number of elements in the list */
    private int size;

    /* capacity of the list */
    private int capacity;

    /* Constructs an empty list with an inital capacity of 1 */

    public MyList(){
        size = 0;
        capacity = 1;
        data = (E[]) new Object[capacity];
    }


    /* Increase the capacity of the list 
    *  Copies all existing elements on the new array.   
    */
    private void reSize(){
        capacity = capacity*2;
        E[] newData = (E[]) new Object[capacity];

        for(int i = 0; i < size ; i++){
            newData[i] = data[i];
        }

        data = newData;
    }

    /** Adding an element to the list
    * Resize the element if the capacity is full.
    * @param item The element to be added to list
    */
    public void add(E item){
        if(size >= capacity){
            reSize();
        }
        data[size] = item;
        size++;
    }

    /** Adding an other list  to the this list
    * 
    * @param list The list to be added to this list
    */
    public void addList(MyList<E> list){
        int size_of_list = list.size();
        for(int i = 0; i < size_of_list; i++){
            this.add(list.get(i));
        }

    }

    /**
    * Returns the element at the specified position in this list.
    * @param index The index of the element to return
    * @return The element at the specified position in this list
    * @throws IndexOutOfBoundsException if the index is out of range
    */
    public E get(int index){
        if(index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }

        return data[index];
    }

    /**
    * Returns true if this list contains no elements.
    * 
    * @return true if this list contains no elements
    */
    public boolean isEmpty(){
        return size == 0;
    }

    /**
    * Returns the number of elements in this list.
    * 
    * @return The number of elements in this list
    */
    public int size(){
        return size;
    }

}
