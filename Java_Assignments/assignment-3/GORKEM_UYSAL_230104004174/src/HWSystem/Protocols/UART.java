package HWSystem.Protocols;

/**
 * Concrete implementation of the Protocol interface for UART communication.
 * UART (Universal Asynchronous Receiver-Transmitter) is a hardware communication
 * protocol that uses asynchronous serial communication with configurable speed.
 */
public class UART implements Protocol{
    
    /**
     * Reads data using the UART protocol
     * 
     * @return A string indicating that data is being read via UART
     */
    @Override
    public String read(){
        return getProtocolName() +" Reading";
    }

    /**
     * Writes data using the UART protocol
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
     * @return String "UART" as the protocol name
     */
    @Override
    public String getProtocolName(){
        return "UART";
    }
}
