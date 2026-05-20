package GTUHashSet;


import java.util.Iterator;
import java.util.NoSuchElementException;

import GTUHashMap.GTUHashMap;

public class GTUHashSet<E> implements Iterable<E>{
    private static final Object WORD = new Object();
    private GTUHashMap<E, Object> map;

    /** Constructor */
    public GTUHashSet() { map = new GTUHashMap<>(); }

    /**
    * Adds the specified element to this set if it is not already present.
    * 
    * @param element the element to be added to this set
    */
    public void add(E element) { map.put(element, WORD); }

    /**
    * Removes the specified element from this set if it is present.
    * 
    * @param element the element to be removed from this set
    */
    public void remove(E element) { map.remove(element); }

    /**
    * Returns true if this set contains the specified element.
    * 
    * @param element the element whose presence in this set is to be tested
    * @return true if this set contains the specified element
    */
    public boolean contains(E element) { return map.containsKey(element); }


    /**
    * Returns the number of elements in this set.
    * 
    * @return the number of elements in this set
    */
    public int size() { return map.size(); }

    /**
    * Returns an iterator over the elements in this set.
    * 
    * @return An iterator over the elements in this set
    */
    @Override
    public Iterator<E> iterator() {
        return new GTUHashSetIterator();
    }

    public int getCollisionCount() {
        return map.getCollisionCount();
    }

    public void resetCollisionCount() {
        map.resetCollisionCount();
    }

    /**
    * Iterator implementation for GTUHashSet.
    * Provides methods for iterating through the elements of the set.
    */

    private class GTUHashSetIterator implements Iterator<E> {
        /** Array containing all keys from the map */
        private Object[] keys;

        /** Current position in the keys array */
        private int currentIndex = 0;

        /** Number of elements returned so far */
        private int count = 0;
        
        /**
        * Constructs a new iterator for the set.
        * Initializes the keys array with all elements from the map.
        */
        public GTUHashSetIterator() {
            keys = new Object[map.size()];
            keys = map.getKeys();
        }
        

        /**
         * Returns true if the iteration has more elements.
         * 
         * @return true if the iteration has more elements
         */
        @Override
        public boolean hasNext() {
            return count < keys.length;
        }
        
        /**
         * Returns the next element in the iteration.
         * 
         * @return The next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public E next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            E key = (E) keys[currentIndex];
            currentIndex++;
            count++;
            return key;
        }


       
    }
}
