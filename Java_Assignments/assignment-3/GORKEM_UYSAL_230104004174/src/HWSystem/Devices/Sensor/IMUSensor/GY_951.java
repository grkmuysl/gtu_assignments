package HWSystem.Devices.Sensor.IMUSensor;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of IMUSensor for the GY-951 IMU sensor.
 * Provides specific functionality for reading acceleration and rotation data.
 */
public class GY_951 extends IMUSensor{
    /**
     * Constructor for GY-951 IMU sensor
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public GY_951(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the sensor (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;
    
    /**
     * Current acceleration value in m/s²
     */
    private float acceleration = 7.2f;
    
    /**
     * Current rotation value in degrees/s
     */
    private float rotation = 4.2f;
    
    /**
     * Returns the sensor type
     * 
     * @return String indicating the sensor type as "IMUSensor"
     */
    @Override
    public String getSensType(){
        return "IMUSensor";
    }

    /**
     * Converts sensor data to a formatted string representation
     * 
     * @return String containing acceleration and rotation values
     */
    @Override
    public String data2String() {
        String data = String.format("Acceleration: %.2f, Rotation: %.2f", acceleration, rotation);
        return data;
    }

    /**
     * Gets the current acceleration reading from the sensor
     * 
     * @return Current acceleration value in m/s²
     */
    @Override
    float getAccel(){
        super.protocol.read();
        return acceleration;
    }
    
    /**
     * Gets the current rotation reading from the sensor
     * 
     * @return Current rotation value in degrees/s
     */
    @Override
    float getRot(){
        return rotation;
    }

    /**
     * Turns on the sensor
     * Sets the device state to ON
     */
    @Override
    public void turnOn(){
        state = DeviceState.ON;
    }
    
    /**
     * Turns off the sensor
     * Sets the device state to OFF
     */
    @Override
    public void turnOff(){
        state = DeviceState.OFF;
    }
    
    /**
     * Returns the name of this device type
     * 
     * @return String "GY_951" as the device name
     */
    @Override
    public String getName(){
        return "GY_951";
    }
    
    /**
     * Returns the current state of the sensor
     * 
     * @return Current DeviceState (ON/OFF)
     */
    @Override
    public DeviceState getState(){
        return state;
    }
}
