package HWSystem.Devices.Display;

import HWSystem.Devices.Device;
import HWSystem.Protocols.Protocol;

/**
 * Abstract class representing a display device in the hardware system.
 * Extends the base Device class and provides display-specific functionality.
 */
public abstract class Display extends Device {
    /**
     * Constructor for Display device
     * @param protocol Communication protocol used by this display
     * @param DevID Unique device identifier
     */
    public Display(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Abstract method to print data on the display
     * Must be implemented by concrete display classes
     * @param data The string data to be displayed
     */
    public abstract void printData(String data);
    
    /**
     * Returns the device type
     * Overrides the getDevType method from the Device class
     * @return String indicating this is a "Display" device
     */
    @Override
    public String getDevType(){
        return "Display";
    }
}
