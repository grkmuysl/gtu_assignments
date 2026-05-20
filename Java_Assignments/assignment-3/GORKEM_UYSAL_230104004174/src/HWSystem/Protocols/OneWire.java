package HWSystem.Protocols;

/**
 * Concrete implementation of the Protocol interface for OneWire communication.
 * OneWire is a device communications bus system that provides low-speed data,
 * signaling, and power over a single conductor.
 */
public class OneWire implements Protocol{
    
    /**
     * Reads data using the OneWire protocol
     * 
     * @return A string indicating that data is being read via OneWire
     */
    @Override
    public String read(){
        return getProtocolName() +" Reading";
    }
    
    /**
     * Writes data using the OneWire protocol
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
     * @return String "OneWire" as the protocol name
     */
    @Override
    public String getProtocolName(){
        return "OneWire";
    }
}
