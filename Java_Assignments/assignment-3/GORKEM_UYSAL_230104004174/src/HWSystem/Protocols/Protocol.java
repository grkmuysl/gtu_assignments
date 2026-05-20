package HWSystem.Protocols;

/**
 * Interface defining the standard communication protocol methods.
 * All concrete protocol implementations must implement these methods
 * to provide consistent communication functionality.
 */
public interface Protocol {
    /**
     * Reads data using the protocol
     * 
     * @return A string containing the data read
     */
    String read();
    
    /**
     * Writes data using the protocol
     * 
     * @param data The string data to be written
     */
    void write(String data);
    
    /**
     * Returns the name of the protocol
     * 
     * @return String containing the protocol name
     */
    String getProtocolName();
}
