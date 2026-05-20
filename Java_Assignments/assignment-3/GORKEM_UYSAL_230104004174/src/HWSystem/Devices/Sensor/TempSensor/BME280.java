package HWSystem.Devices.Sensor.TempSensor;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of TempSensor for the BME280 temperature sensor.
 * Provides specific functionality for reading temperature data.
 */
public class BME280 extends TempSensor{

    /**
     * Constructor for BME280 temperature sensor
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public BME280(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the sensor (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;
    
    /**
     * Current temperature value in degrees Celsius
     */
    private float temp = 35.5f;

    /**
     * Gets the current temperature reading from the sensor
     * Performs a protocol read operation before returning the value
     * 
     * @return Current temperature value in degrees Celsius
     * @note This implementation returns 0.0f instead of the temp field value,
     *       which appears to be a bug in the original code
     */
    @Override
    float getTemp(){
        super.protocol.read();
        return 0.0f;  // Note: This should probably return temp instead of 0.0f
    }

    /**
     * Returns the sensor type
     * 
     * @return String indicating the sensor type as "TempSensor"
     */
    @Override
    public String getSensType(){
        return "TempSensor";
    }

    /**
     * Converts sensor data to a formatted string representation
     * 
     * @return String containing temperature value in Celsius
     */
    @Override
    public String data2String() {
        String data = String.format("Temperature: %.2fC", temp);
        return data;
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
     * @return String "BME280" as the device name
     */
    @Override
    public String getName(){
        return "BME280";
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
