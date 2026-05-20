package HWSystem.Protocols;

/**
 * Concrete implementation of the Protocol interface for SPI communication.
 * SPI (Serial Peripheral Interface) is a synchronous serial communication
 * interface specification used for short-distance communication, primarily
 * in embedded systems.
 */
public class SPI implements Protocol{
    
    /**
     * Reads data using the SPI protocol
     * 
     * @return A string indicating that data is being read via SPI
     */
    @Override
    public String read(){
        return getProtocolName() +" Reading";
    }
    
    /**
     * Writes data using the SPI protocol
     * Prints a message indicating the data being written
     * 
     * @param data The string data to be written
     */
    @Override
    public void write(String data){
        System.out.printf("%s : Writing \"%s\" \n", getProtocolName(), data);
    }

    /**
     * Returns the name of this protocol
     * 
     * @return String "SPI" as the protocol name
     */
    @Override
    public String getProtocolName(){
        return "SPI";
    }
}
