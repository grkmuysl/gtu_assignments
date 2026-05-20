package HWSystem.Devices.Display;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of Display class for LCD displays.
 * Provides specific functionality for LCD type displays.
 */
public class LCD extends Display{
    /**
     * Constructor for LCD display
     * @param protocol Communication protocol used by this LCD display
     * @param DevID Unique device identifier
     */
    public LCD(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the LCD display (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;

    /**
     * Implements the printData method for LCD displays
     * Prints the provided data to the system output
     * @param data The string data to be displayed on the LCD
     */
    @Override
    public void printData(String data){
        System.out.printf("%s: Printing \"%s\". \n", getName() , data);
    }

    /**
     * Turns on the LCD display
     * Sets the device state to ON
     */
    @Override
    public void turnOn(){
        state = DeviceState.ON;
    }
    
    /**
     * Turns off the LCD display
     * Sets the device state to OFF
     */
    @Override
    public void turnOff(){
        state = DeviceState.OFF;
    }
    
    /**
     * Returns the name of this device type
     * @return String "LCD" as the device name
     */
    @Override
    public String getName(){
        return "LCD";
    }

    /**
     * Returns the current state of the LCD display
     * @return Current DeviceState (ON/OFF)
     */
    @Override
    public DeviceState getState(){
        return state;
    }
}
