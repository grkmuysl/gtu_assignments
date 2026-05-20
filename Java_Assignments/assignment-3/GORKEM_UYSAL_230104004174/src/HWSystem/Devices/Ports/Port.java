package HWSystem.Devices.Ports;

import java.io.File;
import java.io.FileWriter;
import java.util.Stack;

import HWSystem.Devices.Device;
import HWSystem.Protocols.Protocol;

/**
 * Represents a hardware port that connects devices using specific protocols
 * and maintains a log of port activities.
 */
public class Port {
    
    /**
     * Protocol used by this port for communication
     */
    public Protocol protocol;
    
    /**
     * Device currently connected to this port
     */
    public Device device;
    
    /**
     * Flag indicating whether the port is empty (no device connected)
     */
    private boolean isEmpty;
    
    /**
     * Unique identifier for this port
     */
    int portId;
    
    /**
     * Path where log files will be stored
     */
    private String logFilePath;
    
    /**
     * Stack to store log records before writing to file
     */
    private Stack<String> logRecords;
    
    /**
     * Constructor for creating a new port
     * 
     * @param protocol Communication protocol used by this port
     * @param device Device connected to this port (null if empty)
     * @param isEmpty Flag indicating if port has no device connected
     * @param portId Unique identifier for this port
     * @param logFilePath Directory path where log files will be stored
     */
    public Port(Protocol protocol, Device device, boolean isEmpty, int portId, String logFilePath){
        this.protocol = protocol;
        this.device = device;
        this.isEmpty = isEmpty;
        this.portId = portId;
        this.logFilePath = logFilePath;
        this.logRecords = new Stack<>();
        logRecords.push("Port Opened.");
    }

    /**
     * Connects a device to this port
     * 
     * @param device The device to connect to this port
     */
    public void setDevice(Device device){
        this.device = device;
    }
    
    /**
     * Sets the empty status of the port
     * 
     * @param isEmpty True if port has no device connected, false otherwise
     */
    public void setEmptyStatus(boolean isEmpty){
        this.isEmpty = isEmpty;
    }

    /**
     * Gets the empty status of the port
     * 
     * @return True if port has no device connected, false otherwise
     */
    public boolean getEmptyStatus(){
        return isEmpty;
    }
    
    /**
     * Removes the device from this port
     */
    public void deleteDevice(){
        this.device = null;
        this.isEmpty = true;
    }

    /**
     * Creates a new log file for this port
     */
    public void createLogFile(){
        String fileName = protocol.getProtocolName() + "_" + portId + ".log";
        try{
            File logFile = new File(logFilePath, fileName);
            logFile.createNewFile();
        }catch(Exception e){
            System.out.println("File couldn't create.");
        }
    }

    /**
     * Adds a new log entry to the log records stack
     * 
     * @param log The log message to record
     */
    public void writeLogToStack(String log){
        logRecords.push(log);
    }

    /**
     * Writes all accumulated log records to the log file
     * and clears the log records stack
     */
    // I got help from GPT to write this function
    public void writeLogsToFile(){
        String fileName = protocol.getProtocolName() + "_" + portId + ".log";
        File logFile = new File(logFilePath, fileName);
        
        try {
            FileWriter writer = new FileWriter(logFile);

            // Write and remove logs from the stack
            while (!logRecords.isEmpty()) {
                String log = logRecords.pop() + "\n";
                writer.write(log);
            }
            writer.close();
            
        } catch (Exception e) {
            System.err.println("Error writing logs to file: " + e.getMessage());
        }
    }
}
