package HWSystem.Devices.MotorDriver;

import HWSystem.Devices.Device;
import HWSystem.Protocols.Protocol;

/**
 * Abstract class representing a motor driver device in the hardware system.
 * Extends the base Device class and provides motor-specific functionality.
 */
public abstract class MotorDriver extends Device{
    /**
     * Constructor for MotorDriver device
     * @param protocol Communication protocol used by this motor driver
     * @param DevID Unique device identifier
     */
    public MotorDriver(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Abstract method to set the motor speed
     * Must be implemented by concrete motor driver classes
     * @param speed The speed value to set for the motor
     */
    public abstract void setMotorSpeed(int speed);
    
    /**
     * Returns the device type
     * Overrides the getDevType method from the Device class
     * @return String indicating this is a "MotorDriver" device
     */
    @Override
    public String getDevType(){
        return "MotorDriver";
    }
    
}
