package HWSystem.Devices.MotorDriver;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of MotorDriver class for SparkFun Motor Driver.
 * Provides specific functionality for SparkFun motor driver hardware.
 */
public class SparkFunMD extends MotorDriver{
    /**
     * Constructor for SparkFun Motor Driver
     * @param protocol Communication protocol used by this motor driver
     * @param DevID Unique device identifier
     */
    public SparkFunMD(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current speed setting of the motor (0-100 or other range)
     */
    private int motorSpeed = 0;
    
    /**
     * Current state of the motor driver (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;

    /**
     * Sets the speed of the motor controlled by this driver
     * @param speed The speed value to set for the motor
     */
    @Override
    public void setMotorSpeed(int speed){
        // turn int speed value to string
        String speed_str = String.valueOf(speed);
        
        // protocol write method
        //super.protocol.write(speed_str);
        
        System.out.printf("%s: Setting speed to %d\n" , getName() , speed);
        motorSpeed = speed;
    }

    /**
     * Turns on the motor driver
     * Sets the device state to ON
     */
    @Override
    public void turnOn(){
        state = DeviceState.ON;
    }
    
    /**
     * Turns off the motor driver
     * Sets the device state to OFF
     */
    @Override
    public void turnOff(){
        state = DeviceState.OFF;
    }
    
    /**
     * Returns the name of this device type
     * @return String "SparkFunMD" as the device name
     */
    @Override
    public String getName(){
        return "SparkFunMD";
    }
    
    /**
     * Returns the current state of the motor driver
     * @return Current DeviceState (ON/OFF)
     */
    @Override
    public DeviceState getState(){
        return state;
    }
}
