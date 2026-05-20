package HWSystem.Protocols;

/**
 * Concrete implementation of the Protocol interface for I2C communication.
 * I2C (Inter-Integrated Circuit) is a synchronous, multi-master, multi-slave, packet switched,
 * single-ended, serial communication bus.
 */
public class I2C implements Protocol{
    
    /**
     * Reads data using the I2C protocol
     * 
     * @return A string indicating that data is being read via I2C
     */
    @Override
    public String read(){
        return getProtocolName() +" Reading";
    }
    
    /**
     * Writes data using the I2C protocol
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
     * @return String "I2C" as the protocol name
     */
    @Override
    public String getProtocolName(){
        return "I2C";
    }
}
