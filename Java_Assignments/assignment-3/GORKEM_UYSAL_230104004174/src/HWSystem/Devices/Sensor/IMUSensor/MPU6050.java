package HWSystem.Devices.Sensor.IMUSensor;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of IMUSensor for the MPU6050 IMU sensor.
 * Provides specific functionality for reading acceleration and rotation data.
 */
public class MPU6050 extends IMUSensor{

    /**
     * Constructor for MPU6050 IMU sensor
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public MPU6050(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the sensor (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;
    
    /**
     * Current acceleration value in m/s²
     */
    private float acceleration = 1.5f;
    
    /**
     * Current rotation value in degrees/s
     */
    private float rotation = 2.5f;

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
     * Uses the getter methods to ensure protocol.read() is called
     * 
     * @return String containing acceleration and rotation values
     */
    @Override
    public String data2String() {
        String data = String.format("Acceleration: %.2f, Rotation: %.2f", getAccel(), getRot());
        return data;
    }

    /**
     * Gets the current acceleration reading from the sensor
     * Performs a protocol read operation before returning the value
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
     * Performs a protocol read operation before returning the value
     * 
     * @return Current rotation value in degrees/s
     */
    @Override
    float getRot(){
        super.protocol.read();
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
     * @return String "MPU6050" as the device name
     */
    @Override
    public String getName(){
        return "MPU6050";
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
