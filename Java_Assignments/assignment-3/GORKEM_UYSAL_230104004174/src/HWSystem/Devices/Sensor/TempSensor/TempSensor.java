package HWSystem.Devices.Sensor.TempSensor;

import HWSystem.Devices.Sensor.Sensor;
import HWSystem.Protocols.Protocol;

/**
 * Abstract base class for temperature sensors.
 * Extends the generic Sensor class and provides temperature-specific functionality.
 */
public abstract class TempSensor extends Sensor{
    
    /**
     * Constructor for temperature sensor
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public TempSensor(Protocol protocol, int DevID){
        super(protocol, DevID);
    }
    
    /**
     * Abstract method to get the current temperature reading
     * Must be implemented by concrete temperature sensor classes
     * 
     * @return Current temperature value in degrees Celsius
     */
    abstract float getTemp();
}
