package HWSystem.Devices;

import HWSystem.Protocols.Protocol;

/**
 * Abstract base class for all hardware devices in the system.
 * Provides common functionality and defines the interface that all devices must implement.
 * <p>
 * This class serves as the foundation for the device hierarchy, ensuring all devices
 * share common behavior and attributes such as protocol communication, state management,
 * and identification.
 * </p>
 * 
 * @author System Designer
 * @version 1.0
 * @since 1.0
 */
public abstract class Device {
    /**
     * Enumeration representing the possible states of a device.
     * Devices can be either ON (active) or OFF (inactive).
     */
    public enum DeviceState {
        /** Device is powered on and operational */
        ON, 
        /** Device is powered off and not operational */
        OFF
    }
    
    /**
     * The communication protocol used by this device.
     * This determines how the device communicates with the system.
     * 
     * @see HWSystem.Protocols.Protocol
     */
    protected Protocol protocol;
    
    /**
     * Unique identifier for this device.
     * Used to distinguish between multiple devices of the same type.
     */
    private int deviceId;
    
    /**
     * Constructor for device objects.
     * Initializes a new device with the specified protocol and ID.
     * 
     * @param protocol Communication protocol used by this device
     * @param DevID Unique device identifier
     * @throws IllegalArgumentException if the device ID is negative
     */
    public Device(Protocol protocol, int DevID) {
        this.protocol = protocol;
        this.deviceId = DevID;
    }

    /**
     * Returns the unique device identifier.
     * 
     * @return The device ID as an integer
     */
    public int getDevID(){
        return deviceId;
    }
    
    /**
     * Abstract method to turn on the device.
     * Must be implemented by concrete device classes to define
     * device-specific startup behavior.
     * 
     * @throws RuntimeException if the device cannot be turned on
     */
    public abstract void turnOn();
    
    /**
     * Abstract method to turn off the device.
     * Must be implemented by concrete device classes to define
     * device-specific shutdown behavior.
     * 
     * @throws RuntimeException if the device cannot be turned off
     */
    public abstract void turnOff();
    
    /**
     * Abstract method to get the specific name of the device.
     * Must be implemented by concrete device classes.
     * 
     * @return String representing the device name
     */
    public abstract String getName();
    
    /**
     * Abstract method to get the type of the device.
     * Must be implemented by concrete device classes.
     * Device types might include "Sensor", "Display", "MotorDriver", etc.
     * 
     * @return String representing the device type
     */
    public abstract String getDevType();
    
    /**
     * Abstract method to get the current state of the device.
     * Must be implemented by concrete device classes to report
     * whether the device is currently on or off.
     * 
     * @return Current DeviceState (ON/OFF)
     * @see DeviceState
     */
    public abstract DeviceState getState();
}
