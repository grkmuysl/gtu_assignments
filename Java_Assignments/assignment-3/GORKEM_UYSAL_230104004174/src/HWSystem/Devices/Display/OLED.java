package HWSystem.Devices.Display;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of Display class for OLED displays.
 * Provides specific functionality for OLED type displays.
 */
public class OLED extends Display{

    /**
     * Constructor for OLED display
     * @param protocol Communication protocol used by this OLED display
     * @param DevID Unique device identifier
     */
    public OLED(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the OLED display (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;

    /**
     * Implements the printData method for OLED displays
     * Prints the provided data to the system output
     * @param data The string data to be displayed on the OLED
     */
    @Override
    public void printData(String data){
        System.out.printf("%s: Printing \"%s\".\n", getName() , data);
    }
    
    /**
     * Turns on the OLED display
     * Sets the device state to ON
     */
    @Override
    public void turnOn(){
        state = DeviceState.ON;
    }
    
    /**
     * Turns off the OLED display
     * Sets the device state to OFF
     */
    @Override
    public void turnOff(){
        state = DeviceState.OFF;
    }
    
    /**
     * Returns the name of this device type
     * @return String "OLED" as the device name
     */
    @Override
    public String getName(){
        return "OLED";
    }
    
    /**
     * Returns the current state of the OLED display
     * @return Current DeviceState (ON/OFF)
     */
    @Override
    public DeviceState getState(){
        return state;
    }
}
