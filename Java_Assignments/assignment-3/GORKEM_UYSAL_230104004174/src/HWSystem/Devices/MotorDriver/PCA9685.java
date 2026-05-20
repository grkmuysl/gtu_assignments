package HWSystem.Devices.MotorDriver;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of MotorDriver class for PCA9685 motor driver.
 * PCA9685 is a 16-channel PWM controller commonly used for motor control.
 */
public class PCA9685 extends MotorDriver{

    /**
     * Constructor for PCA9685 motor driver
     * @param protocol Communication protocol used by this motor driver
     * @param DevID Unique device identifier
     */
    public PCA9685(Protocol protocol, int DevID){
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
     * @return String "PCA9685" as the device name
     */
    @Override
    public String getName(){
        return "PCA9685";
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
