package HWSystem.Devices.WirelessIO;

import HWSystem.Devices.Device;
import HWSystem.Protocols.Protocol;

/**
 * Abstract base class for all wireless input/output devices.
 * Extends the generic Device class and provides wireless communication functionality.
 */
public abstract class WirelessIO extends Device{
    
    /**
     * Constructor for wireless I/O devices
     * 
     * @param protocol Communication protocol used by this device
     * @param DevID Unique device identifier
     */
    public WirelessIO(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Abstract method to send data through the wireless connection
     * Must be implemented by concrete wireless I/O classes
     * 
     * @param data The string data to be sent
     */
    public abstract void sendData(String data);
    
    /**
     * Abstract method to receive data through the wireless connection
     * Must be implemented by concrete wireless I/O classes
     * 
     * @return String containing the received data
     */
    public abstract String recvData();
    
    /**
     * Returns the device type as "WirelessIO"
     * 
     * @return String "WirelessIO" as the device type
     */
    @Override
    public String getDevType(){
        return "WirelessIO";
    }
}
