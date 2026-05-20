package Entry;

public class Entry<K, V> {
    public K key;
    public V value;
    public boolean isDeleted;
    
    // An Entry class to use in hashmap and hashset
    public Entry(K key, V value) {
        this.key = key;
        this.value = value;
        this.isDeleted = false;
    }
}
