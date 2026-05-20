package GTUHashMap;


import Entry.Entry;

public class GTUHashMap<K, V> {
    
    private Entry<K, V>[] table;
    private int size;
    private int capacity;
    private static int collisionCount = 0;

    // Default constructor
    public GTUHashMap() { 
        this.size = 0;
        this.capacity = 2;
        this.table = new Entry[capacity];
    }

    //  Resizes the hash table with next prime number method
    private void resize(){
        int oldCapacity = capacity;
        Entry<K, V>[] oldTable = table;

        // increase the capacity to next prime number
        capacity = nextPrime(oldCapacity * 2);
        size = 0;
        table = (Entry<K, V>[]) new Entry[capacity];

        // insert old table to new table
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] != null && !oldTable[i].isDeleted) {
                put(oldTable[i].key, oldTable[i].value);
            }
        }
    }

    /**
    * Checks if a number is prime.
    * 
    * @param number The number to check
    * @return true if the number is prime, false otherwise
    */
     private boolean isPrime(int number){
        if (number <= 1) {
            return false;
        }

        // number equals to 2 or 3
         if (number <= 3) {
            return true;
        }

        // number is even
        if (number % 2 == 0 || number % 3 == 0) {
            return false;
        }

        // for larger numbers
        for (int i = 5; i * i <= number; i += 6) {
            if (number % i == 0 || number % (i + 2) == 0) {
                return false;
            }
        }
        
        return true;
    }

    /**
    * return the next prime number
    * 
    * @param number The initial number
    * @return The next prime number
    */
    private int nextPrime(int number) {
        
        if (number <= 2) {
            return 2;
        }
        
        // if number is even turn to odd.
        if(number % 2 == 0){
            number = number + 1;
        }
        

        // find first prime number
        while (!isPrime(number)) {
            number += 2;  // check only odd numbers
        }
        
        return number;
    }

    /**
    * calculates the hash index
    * 
    * @param key The key to hash
    * @return The index in the hash table
    */

    private int tableInd(K key){
        return  Math.abs(key.hashCode() % capacity);
    }

    /**
    * Inserts a key-value pair into the hash table.
    * If the key already exists, the value is updated.
    * If the table is full, it is resized before insertion.
    * 
    * @param key The key to insert
    * @param value The value to associate with the key
    */

    public void put(K key, V value) {

        // check the capacity
        if(size >= capacity){
            resize();
        }

        int index = tableInd(key);
        int originalIndex = index;

        // if there is a collision then increase collisionCount
        if(table[index] != null && !table[index].isDeleted && !table[index].key.equals(key)) {
            collisionCount++;
        }

        while(table[index] != null && !table[index].isDeleted){
            if (table[index].key.equals(key)) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity;

            

            // if we travers the entire table break.
            if (index == originalIndex) {
                break;
            }
        } 

        table[index] = new Entry<>(key, value);
        size++;

    }

    /**
    * Returns the value with the specified key.
    * 
    * @param key The key which associated value is to be returned
    * @return The value associated with the key, or null if the key is not found
    */

    public V get(K key) { 
        int index = tableInd(key);
        int originalIndex = index;

        while(table[index] != null){
            if (table[index].key.equals(key) && !table[index].isDeleted) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
            
            
            if (index == originalIndex) {
                break;
            }
        }

        return null;
    }

    /**
    * Removes the mapping for the specified key from this map if present.
    * Uses tombstone method to removing
    * 
    *  @param key The key whose mapping is to be removed
    */

    public void remove(K key) { 
        int index = tableInd(key);

        while(table[index] != null){
            if(!table[index].isDeleted && table[index].key.equals(key)){
                table[index].isDeleted = true;
                size--;
                return;
            }
            index = (index + 1) % capacity;

            if (index == tableInd(key)) {
                break;
            }
        }

    } 
   
    /**
    * Returns true if this map contains a mapping for the specified key.
    * 
    * @param key The key which to be tested
    * @return true if this map contains a mapping for the specified key
    */

   public boolean containsKey(K key) { 
    int index = tableInd(key);
    int originalIndex = index;
    
    while(table[index] != null){
        if (table[index].key.equals(key) && !table[index].isDeleted) {
            return true;
        }
        index = (index + 1) % capacity;
        
        
        if (index == originalIndex) {
            break;
        }
    }

        return false;
    }

    /**
    * Returns the number of key-value mappings in this map.
    * 
    * @return The number of key-value mappings in this map
    */

    public int size() { 
        return size;
    }

    /**
    * Returns an array of all the keys in this map.
    * 
    * @return An array of all the keys in this map
    */
    public Object[] getKeys(){
        Object[] keys = new Object[size];
        int index = 0;
        for (int i = 0; i < capacity; i++) {
            if (table[i] != null && !table[i].isDeleted) {
                keys[index] = table[i].key;
                index++;
            }
        }
        return keys;
    }

    /**
     * Function to get collisions count
     * @return collisionCount count of collisions
     */
    public int getCollisionCount() {
        return collisionCount;
    }

    /**
     * Reset collisionCount
     */
    public void resetCollisionCount() {
        collisionCount = 0;
    }
}