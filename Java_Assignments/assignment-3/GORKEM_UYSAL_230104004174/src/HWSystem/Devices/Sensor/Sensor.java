package HWSystem.Devices.Sensor;

import HWSystem.Devices.Device;
import HWSystem.Protocols.Protocol;

/**
 * Abstract base class for all sensor devices.
 * Extends the generic Device class and provides sensor-specific functionality.
 */
public abstract class Sensor extends Device{
    
    /**
     * Constructor for sensor devices
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public Sensor(Protocol protocol, int DevID){
        super(protocol, DevID);
    }
    
    /**
     * Abstract method to get the specific sensor type
     * Must be implemented by concrete sensor classes
     * 
     * @return String representing the specific sensor type
     */
    public abstract String getSensType();
    
    /**
     * Abstract method to convert sensor data to a string representation
     * Must be implemented by concrete sensor classes
     * 
     * @return String representation of the sensor data
     */
    public abstract String data2String();
    
    /**
     * Returns the device type as "Sensor"
     * 
     * @return String "Sensor" as the device type
     */
    @Override
    public String getDevType(){
        return "Sensor";
    }
}
