package HWSystem.Devices.WirelessIO;

import HWSystem.Protocols.Protocol;

/**
 * Concrete implementation of WirelessIO for Bluetooth communication.
 * Provides specific functionality for sending and receiving data via Bluetooth.
 */
public class Bluetooth extends WirelessIO{
    
    /**
     * Constructor for Bluetooth wireless I/O device
     * 
     * @param protocol Communication protocol used by this device
     * @param DevID Unique device identifier
     */
    public Bluetooth(Protocol protocol, int DevID){
        super(protocol, DevID);
    }

    /**
     * Current state of the device (ON/OFF)
     */
    protected DeviceState state = DeviceState.OFF;

    /**
     * Sends data through the Bluetooth connection
     * Uses the underlying protocol to write data and prints a confirmation message
     * 
     * @param data The string data to be sent
     */
    @Override
    public void sendData(String data){
        super.protocol.write(data);
        System.out.printf("%s Sending: \" %s\" \n" , getName() , data);
    }

    /**
     * Receives data through the Bluetooth connection
     * Uses the underlying protocol to read incoming data
     * 
     * @return String containing the received data
     */
    @Override
    public String recvData(){
        String recvData = super.protocol.read();
        return recvData;
    }

    /**
     * Turns on the Bluetooth device
     * Sets the device state to ON
     */
    @Override
    public void turnOn(){
        state = DeviceState.ON;
    }
    
    /**
     * Turns off the Bluetooth device
     * Sets the device state to OFF
     */
    @Override
    public void turnOff(){
        state = DeviceState.OFF;
    }
    
    /**
     * Returns the name of this device type
     * 
     * @return String "Bluetooth" as the device name
     */
    @Override
    public String getName(){
        return "Bluetooth";
    }

    /**
     * Returns the current state of the device
     * 
     * @return Current DeviceState (ON/OFF)
     */
    @Override
    public DeviceState getState(){
        return state;
    }
}
