package HWSystem.Devices.Sensor.IMUSensor;

import HWSystem.Devices.Sensor.Sensor;
import HWSystem.Protocols.Protocol;

/**
 * Abstract base class for Inertial Measurement Unit (IMU) sensors.
 * Extends the generic Sensor class with IMU-specific functionality.
 */
public abstract class IMUSensor extends Sensor {
    /**
     * Constructor for IMU sensors
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public IMUSensor(Protocol protocol, int DevID){
        super(protocol, DevID);
    }
    
    /**
     * Gets the acceleration reading from the IMU sensor.
     * 
     * @return Current acceleration value, typically in m/s²
     */
    abstract float getAccel();
    
    /**
     * Gets the rotation/angular velocity reading from the IMU sensor.
     * 
     * @return Current rotation value, typically in degrees/s
     */
    abstract float getRot();
}
