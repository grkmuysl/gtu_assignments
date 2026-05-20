package HWSystem.Devices.Sensor.TempSensor;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of TempSensor for the DHT11 temperature sensor.
 * Provides specific functionality for reading temperature data.
 */
public class DHT11 extends TempSensor{
    
    /**
     * Constructor for DHT11 temperature sensor
     * 
     * @param protocol Communication protocol used by this sensor
     * @param DevID Unique device identifier
     */
    public DHT11(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the sensor (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;
    
    /**
     * Current temperature value in degrees Celsius
     */
    private float temp = 30.5f;

    /**
     * Gets the current temperature reading from the sensor
     * Performs a protocol read operation before returning the value
     * 
     * @return Current temperature value in degrees Celsius
     */
    @Override
    float getTemp(){
        super.protocol.read();
        return temp;
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
     * @return String "DHT11" as the device name
     */
    @Override
    public String getName(){
        return "DHT11";
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
