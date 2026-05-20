package HWSystem.EmbeddedSystem;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

import HWSystem.Devices.Device;
import HWSystem.Devices.Device.DeviceState;
import HWSystem.Devices.Display.LCD;
import HWSystem.Devices.Display.OLED;
import HWSystem.Devices.MotorDriver.PCA9685;
import HWSystem.Devices.MotorDriver.SparkFunMD;
import HWSystem.Devices.Ports.Port;
import HWSystem.Devices.Sensor.IMUSensor.GY_951;
import HWSystem.Devices.Sensor.IMUSensor.MPU6050;
import HWSystem.Devices.Sensor.TempSensor.BME280;
import HWSystem.Devices.Sensor.TempSensor.DHT11;
import HWSystem.Devices.WirelessIO.Bluetooth;
import HWSystem.Devices.WirelessIO.Wifi;
import HWSystem.Protocols.I2C;
import HWSystem.Protocols.OneWire;
import HWSystem.Protocols.Protocol;
import HWSystem.Protocols.SPI;
import HWSystem.Protocols.UART;

/**
 * The SystemManager class is responsible for managing an embedded system.
 * It handles device connections, communication protocols, and user commands.
 * This class serves as the central control point for the entire embedded system.
 */
public class SystemManager {
    /** Queue to track motor driver device IDs */
    private static Queue<Integer> motorDriversIDs = new LinkedList<>();
    
    /** Queue to track display device IDs */
    private static Queue<Integer> DisplaysIDs = new LinkedList<>();
    
    /** Queue to track sensor device IDs */
    private static Queue<Integer> SensorsIDs = new LinkedList<>();
    
    /** Queue to track wireless I/O device IDs */
    private static Queue<Integer> WirelessIOIDs = new LinkedList<>();

    // Collections for specific device types to avoid using instanceof:
    
    /** Collection of LCD display devices */
    private static ArrayList<LCD> lcdsDevices = new ArrayList<>();
    
    /** Collection of OLED display devices */
    private static ArrayList<OLED> oledsDevices = new ArrayList<>();

    /** Collection of PCA9685 motor driver devices */
    private static ArrayList<PCA9685> pca9685sDevices = new ArrayList<>();
    
    /** Collection of SparkFun motor driver devices */
    private static ArrayList<SparkFunMD> sparkFunMDsDevices = new ArrayList<>();

    /** Collection of GY-951 IMU sensor devices */
    private static ArrayList<GY_951> gy_951sDevices = new ArrayList<>();
    
    /** Collection of MPU6050 IMU sensor devices */
    private static ArrayList<MPU6050> mpu6050sDevices = new ArrayList<>();
    
    /** Collection of BME280 temperature sensor devices */
    private static ArrayList<BME280> bme280sDevices = new ArrayList<>();
    
    /** Collection of DHT11 temperature sensor devices */
    private static ArrayList<DHT11> dht11sDevices = new ArrayList<>();
        
    /** Collection of Bluetooth wireless devices */
    private static ArrayList<Bluetooth> bluetoothsDevices = new ArrayList<>();
    
    /** Collection of WiFi wireless devices */
    private static ArrayList<Wifi> wifisDevices = new ArrayList<>();
        
    /**
     * Processes user commands for managing embedded system devices.
     * This method handles various commands like listing devices, adding/removing devices,
     * turning devices on/off, and interacting with specific device types.
     * 
     * @param command The command string to be processed
     * @param protocolsList List of available communication protocols
     * @param portList List of available ports in the system
     * @param sensors_count Maximum number of sensors allowed
     * @param displays_count Maximum number of displays allowed
     * @param wireless_adapters_count Maximum number of wireless adapters allowed
     * @param motor_drivers_count Maximum number of motor drivers allowed
     * @param ports_count Total number of ports in the system
     */
    private static void processCommand(String command, ArrayList<Protocol> protocolsList, ArrayList<Port> portList, 
    int sensors_count, int displays_count, int wireless_adapters_count, int motor_drivers_count, int ports_count){

        if(command.equals("list ports")){
            // List all ports and their status (empty or occupied with device details)
            System.out.println("list of Ports:");
            Iterator<Port> portIterator = portList.iterator();
            int i = 0;
            
            while (portIterator.hasNext()) {
                Port port = portIterator.next();
                
                //check is empty or not 
                if (port.getEmptyStatus()) {
                    System.out.printf("%d %s empty\n", i, port.protocol.getProtocolName());
                } else {
                    Device dev = port.device;
                    if ("Sensor".equals(dev.getDevType())) {
                        if("GY_951".equals(dev.getName())){
                            GY_951 gy_951 = gy_951sDevices.get(dev.getDevID());
                            System.out.printf("%d %s occupied %s %s %s %d %s\n", i, port.protocol.getProtocolName(), 
                            dev.getName(), gy_951.getSensType(), dev.getDevType(), dev.getDevID(), dev.getState());

                        }else if("MPU6050".equals(dev.getName())){
                            MPU6050 mpu6050 = mpu6050sDevices.get(dev.getDevID());
                            System.out.printf("%d %s occupied %s %s %s %d %s\n", i, port.protocol.getProtocolName(), 
                            dev.getName(), mpu6050.getSensType(), dev.getDevType(), dev.getDevID(), dev.getState());

                        }else if("BME280".equals(dev.getName())){
                            BME280 bme280 = bme280sDevices.get(dev.getDevID());
                            System.out.printf("%d %s occupied %s %s %s %d %s\n", i, port.protocol.getProtocolName(), 
                            dev.getName(), bme280.getSensType(), dev.getDevType(), dev.getDevID(), dev.getState());

                        }else if("DHT11".equals(dev.getName())){

                            DHT11 dht11 = dht11sDevices.get(dev.getDevID());
                            System.out.printf("%d %s occupied %s %s %s %d %s\n", i, port.protocol.getProtocolName(), 
                            dev.getName(), dht11.getSensType(), dev.getDevType(), dev.getDevID(), dev.getState());
                        }
                    } else {
                       
                        System.out.printf("%d %s occupied %s %s %d %s\n", i, port.protocol.getProtocolName(), 
                            dev.getName(), dev.getDevType(), dev.getDevID(), dev.getState());
                    }
                }
                i++;
            }

        }else if(command.contains("addDev")){ 
            // Add a new device to a port
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
           
            if(splitCommand.get(0).equals("addDev")){
                
                if(splitCommand.size() == 4){
                    String devType = splitCommand.get(1);
                   
                    // try catch for parseInt
                    try{
                        int portId = Integer.parseInt(splitCommand.get(2));
                        int devId = Integer.parseInt(splitCommand.get(3));
                        
                        if(portId < 0 || portId >= ports_count){
                            
                            System.err.printf("Invalid port ID.\n");
                        }else{
                            if(devType.equals("DHT11")){
                                if(portId == 2){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < sensors_count){
                                            // check if there is a device with same ids
                                            if(!SensorsIDs.contains(devId)){
                                                Device newDevice = new DHT11(protocolsList.get(portId) , devId);
                                                DHT11 dht11 = new DHT11(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                SensorsIDs.add(devId);
                                                dht11sDevices.add(dht11);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("MPU6050")){
                                if(portId == 0){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < sensors_count){
                                            if(!SensorsIDs.contains(devId)){
                                                Device newDevice = new MPU6050(protocolsList.get(portId) , devId);
                                                MPU6050 mpu6050 = new MPU6050(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                SensorsIDs.add(devId);
                                                mpu6050sDevices.add(mpu6050);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("LCD")){
                                if(portId == 0){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < displays_count){
                                            if(!DisplaysIDs.contains(devId)){
                                                Device newDevice = new LCD(protocolsList.get(portId) , devId);
                                                LCD lcd = new LCD(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                DisplaysIDs.add(devId);
                                                lcdsDevices.add(lcd);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("OLED")){
                                if(portId == 1){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < displays_count){
                                            if(!DisplaysIDs.contains(devId)){
                                                Device newDevice = new OLED(protocolsList.get(portId) , devId);
                                                OLED oled = new OLED(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                DisplaysIDs.add(devId);
                                                oledsDevices.add(oled);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("Bluetooth")){
                                if(portId == 3){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < wireless_adapters_count){
                                            if(!WirelessIOIDs.contains(devId)){
                                                Device newDevice = new Bluetooth(protocolsList.get(portId) , devId);
                                                Bluetooth bluetooth = new Bluetooth(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                WirelessIOIDs.add(devId);
                                                bluetoothsDevices.add(bluetooth);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                    
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("PCA9685")){
                                if(portId == 0){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < motor_drivers_count){
                                            if(!motorDriversIDs.contains(devId)){
                                                Device newDevice = new PCA9685(protocolsList.get(portId) , devId);
                                                PCA9685 pca9685 = new PCA9685(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                motorDriversIDs.add(devId);
                                                pca9685sDevices.add(pca9685);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                        
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("SparkFunMD")){
                                if(portId == 1){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < motor_drivers_count){
                                            if(!motorDriversIDs.contains(devId)){
                                                Device newDevice = new SparkFunMD(protocolsList.get(portId) , devId);
                                                SparkFunMD sparkFunMD = new SparkFunMD(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                motorDriversIDs.add(devId);
                                                sparkFunMDsDevices.add(sparkFunMD);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                        
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("BME280")){
                                if(portId == 0 || portId == 1 ){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < sensors_count){
                                            if(!SensorsIDs.contains(devId)){
                                                Device newDevice = new BME280(protocolsList.get(portId) , devId);
                                                BME280 bme280 = new BME280(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                SensorsIDs.add(devId);
                                                bme280sDevices.add(bme280);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                        
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("GY951")){
                                if(portId == 1 || portId == 3 ){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < sensors_count){
                                            if(!SensorsIDs.contains(devId)){
                                                Device newDevice = new GY_951(protocolsList.get(portId) , devId);
                                                GY_951 gy_951 = new GY_951(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                SensorsIDs.add(devId);
                                                gy_951sDevices.add(gy_951);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                        
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else if(devType.equals("Wifi")){
                                if(portId == 1 || portId == 3 ){
                                    // check if is empty
                                    if(portList.get(portId).getEmptyStatus()){
                                        if(devId >= 0 && devId < wireless_adapters_count){
                                            if(!WirelessIOIDs.contains(devId)){
                                                Device newDevice = new Wifi(protocolsList.get(portId) , devId);
                                                Wifi wifi = new Wifi(protocolsList.get(portId) , devId);
                                                portList.get(portId).setDevice(newDevice);
                                                portList.get(portId).setEmptyStatus(false);
                                                WirelessIOIDs.add(devId);
                                                wifisDevices.add(wifi);
                                                System.out.println("Device added.");
                                            }else{
                                                System.err.printf("There is a device with the same ID.\n");
                                            }
                                        }else{
                                            System.err.printf("Invalid device ID.\n");
                                        }
                                        
                                    }else{
                                        System.err.printf("The port is full.\n");
                                    }
                                    
                                }else{
                                    System.err.printf("The device's protocol is not compatible with this port.\n");
                                }
                            }else{
                                System.err.printf("Invalid device name.\n");
                            }
                        }
                    }catch(Exception e){
                        System.err.println("Ids must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                
                System.err.printf("Undefined command.\n");
            }
            
        }else if(command.contains("turnON")){
            // Turn on a device connected to a specific port
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
            
            if(splitCommand.get(0).equals("turnON")){
                if(splitCommand.size() == 2){
                    try{
                        int portID = Integer.parseInt(splitCommand.get(1));
                        if(portID < portList.size() && portID >= 0){
                            if(!portList.get(portID).getEmptyStatus()){
                                if(portList.get(portID).device.getState() == DeviceState.OFF){
                                    
                                    portList.get(portID).device.turnOn();
                                    System.out.printf("%s: Turning ON. \n" ,portList.get(portID).device.getName());
                                    portList.get(portID).writeLogToStack("Writing \"turnON\".");

                                    int devID = portList.get(portID).device.getDevID();
                                    // update both arrayList
                                    int deviceNum = determineDevice(portList.get(portID).device.getName());
                                    switch(deviceNum){
                                        case 0:
                                        lcdsDevices.get(devID).turnOn();
                                        break;

                                        case 1:
                                        oledsDevices.get(devID).turnOn();
                                        break;

                                        case 2:
                                        pca9685sDevices.get(devID).turnOn();
                                        break;

                                        case 3:
                                        sparkFunMDsDevices.get(devID).turnOn();
                                        break;

                                        case 4:
                                        gy_951sDevices.get(devID).turnOn();
                                        break;

                                        case 5:
                                        mpu6050sDevices.get(devID).turnOn();
                                        break;

                                        case 6:
                                        bme280sDevices.get(devID).turnOn();
                                        break;

                                        case 7:
                                        dht11sDevices.get(devID).turnOn();
                                        break;

                                        case 8:
                                        bluetoothsDevices.get(devID).turnOn();
                                        break;

                                        case 9:
                                        wifisDevices.get(devID).turnOn();
                                        break;
                                    }
                                    
                                }else{
                                    System.err.printf("The device is already turned on!\n");
                                }
                                
                            }else{
                                System.err.printf("The port is empty!\n");
                            }
                        }else{
                            System.err.printf("The port not found!\n");
                        }
                    }catch(Exception e){
                        System.err.printf("Port ID must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
            
        }else if(command.contains("turnOFF")){
            // Turn off a device connected to a specific port
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
            
            if(splitCommand.get(0).equals("turnOFF")){
                if(splitCommand.size() == 2){
                    try{
                        int portID = Integer.parseInt(splitCommand.get(1));
    
                        if(portID < portList.size() && portID >= 0){
                            if(!portList.get(portID).getEmptyStatus()){
                                if(portList.get(portID).device.getState() == DeviceState.ON){
                                    portList.get(portID).device.turnOff();
                                    System.out.printf("%s: Turning OFF. \n" ,portList.get(portID).device.getName());
                                    portList.get(portID).writeLogToStack("Writing \"turnOFF\"");
                                    
                                    int devID = portList.get(portID).device.getDevID();
                                    // update both arrayList
                                    int deviceNum = determineDevice(portList.get(portID).device.getName());
                                    switch(deviceNum){
                                        case 0:
                                        lcdsDevices.get(devID).turnOff();
                                        break;

                                        case 1:
                                        oledsDevices.get(devID).turnOff();
                                        break;

                                        case 2:
                                        pca9685sDevices.get(devID).turnOff();
                                        break;

                                        case 3:
                                        sparkFunMDsDevices.get(devID).turnOff();
                                        break;

                                        case 4:
                                        gy_951sDevices.get(devID).turnOff();
                                        break;

                                        case 5:
                                        mpu6050sDevices.get(devID).turnOff();
                                        break;

                                        case 6:
                                        bme280sDevices.get(devID).turnOff();
                                        break;

                                        case 7:
                                        dht11sDevices.get(devID).turnOff();
                                        break;

                                        case 8:
                                        bluetoothsDevices.get(devID).turnOff();
                                        break;

                                        case 9:
                                        wifisDevices.get(devID).turnOff();
                                        break;
                                    }

                                }else{
                                    System.err.printf("The device is already turned off!\n");
                                }
                                
                            }else{
                                System.err.printf("The port is empty!\n");
                            }
                        }else{
                            System.err.printf("The port not found!\n");
                        }
                    }catch(Exception e){
                        System.err.printf("Port ID must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
           
        }else if(command.contains("rmDev")){
            // Remove a device from a port
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));

            if(splitCommand.get(0).equals("rmDev")){
                if(splitCommand.size() == 2){
                    int portID = Integer.parseInt(splitCommand.get(1));
                    try{
                        if(portID < portList.size() && portID >= 0){
                            // if port is not empty
                            if(!portList.get(portID).getEmptyStatus()){
                             
                                if(portList.get(portID).device.getState() == DeviceState.OFF){
                                    
                                    int deviceNum = determineDevice(portList.get(portID).device.getName());
                                    int indOfDev = portList.get(portID).device.getDevID();

                                    portList.get(portID).deleteDevice();
                                    System.out.println("Device removed.");
                                   
                                    // update both arrayList
                                    switch(deviceNum){
                                        case 0:
                                        lcdsDevices.remove(indOfDev);
                                        break;

                                        case 1:
                                        oledsDevices.remove(indOfDev);
                                        break;

                                        case 2:
                                        pca9685sDevices.remove(indOfDev);
                                        break;

                                        case 3:
                                        sparkFunMDsDevices.remove(indOfDev);
                                        break;

                                        case 4:
                                        gy_951sDevices.remove(indOfDev);
                                        break;

                                        case 5:
                                        mpu6050sDevices.remove(indOfDev);
                                        break;

                                        case 6:
                                        bme280sDevices.remove(indOfDev);
                                        break;

                                        case 7:
                                        dht11sDevices.remove(indOfDev);                                        break;

                                        case 8:
                                        bluetoothsDevices.remove(indOfDev);
                                        break;

                                        case 9:
                                        wifisDevices.remove(indOfDev);
                                        break;
                                    }
                                    
                                }else{
                                    System.err.printf("Device is active.\n");
                                }
                                
                            }else{
                                System.err.printf("The port is empty!\n");
                            }
                        }else{
                            System.err.printf("The port not found!\n");
                        }
                    }catch(Exception e){
                        System.err.printf("Port ID must be integers.\n");
                    }
                    
                }else{

                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
                
        }else if(command.equals("list Sensor")){
            // List all connected sensor devices
            // flag for empty states
            boolean isEmpty = true; 
            System.out.println("list of Sensors:");
            Iterator<Port> portIterator = portList.iterator();

            int portId = 0;
            while(portIterator.hasNext()){
                Port tempPort = portIterator.next();
                Device dev = tempPort.device;
                if (dev != null) {
                    int deviceNum = determineDevice(dev.getName());

                    if(deviceNum == 4 || deviceNum == 5 || deviceNum == 6 || deviceNum == 7){
                        isEmpty = false;
                        System.out.printf("%s %d %d %s\n" , dev.getName(), dev.getDevID(), portId, portList.get(portId).protocol.getProtocolName());
                    }
                }
                portId++;

            }
            if(isEmpty){
                System.out.println("Sensor list is empty.");
            }

        }else if(command.equals("list Display")){
            // List all connected display devices
            // flag for empty states
            boolean isEmpty = true; 
            System.out.println("list of Displays:");

            Iterator<Port> portIterator = portList.iterator();

            int portId = 0;
            while(portIterator.hasNext()){
                Port tempPort = portIterator.next();
                Device dev = tempPort.device;
                if (dev != null) {
                    int deviceNum = determineDevice(dev.getName());

                    if(deviceNum == 0 || deviceNum == 1){
                        isEmpty = false;
                        System.out.printf("%s %d %d %s\n" , dev.getName(), dev.getDevID(), portId, portList.get(portId).protocol.getProtocolName());
                    }
                }
                portId++;
            }

            if(isEmpty){
                System.out.println("Display list is empty.");
            }

        }else if(command.equals("list WirelessIO")){
            // List all connected wireless I/O devices
            boolean isEmpty = true; 
            System.out.println("list of WirelessIO's:");

            Iterator<Port> portIterator = portList.iterator();

            int portId = 0;
            while(portIterator.hasNext()){
                Port tempPort = portIterator.next();
                Device dev = tempPort.device;
                if (dev != null) {
                    int deviceNum = determineDevice(dev.getName());

                    if(deviceNum == 8 || deviceNum == 9){
                        isEmpty = false;
                        System.out.printf("%s %d %d %s\n" , dev.getName(), dev.getDevID(), portId, portList.get(portId).protocol.getProtocolName());
                    }
                }
                portId++;

            }

            if(isEmpty){
                System.out.println("WirelessIO list is empty.");
            }
        }else if(command.equals("list MotorDriver")){
            // List all connected motor driver devices
            boolean isEmpty = true; 
            System.out.println("list of MotorDrivers:");

            Iterator<Port> portIterator = portList.iterator();

            int portId = 0;
            while(portIterator.hasNext()){
                Port tempPort = portIterator.next();
                Device dev = tempPort.device;
                if (dev != null) {
                    int deviceNum = determineDevice(dev.getName());

                    if(deviceNum == 2 || deviceNum == 3){
                        isEmpty = false;
                        System.out.printf("%s %d %d %s\n" , dev.getName(), dev.getDevID(), portId, portList.get(portId).protocol.getProtocolName());
                    }
                }
                portId++;
            }
        
            if(isEmpty){
                System.out.println("MotorDriver list is empty.");
            }

        }else if(command.contains("readSensor")){
            // Read data from a sensor device
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));

            if(splitCommand.get(0).equals("readSensor")){
                if(splitCommand.size() == 2){
                    int devID = Integer.parseInt(splitCommand.get(1));
                    boolean isFound = false;
                    try{
                        Iterator<Port> portIterator = portList.iterator();

                        while(portIterator.hasNext()){
                            Port tempPort = portIterator.next();
                            Device dev = tempPort.device;
                            
                            if(dev != null){
                                // if they are equal then device  found
                                if(dev.getDevID() == devID){
                                    isFound = true;

                                    if("Sensor".equals(dev.getDevType())){
                                          // check device state ON/OFF
                                        if(dev.getState() == DeviceState.ON){
                                            if("GY_951".equals(dev.getName())){
                                                GY_951 gy_951 = gy_951sDevices.get(dev.getDevID());
                                                String data = gy_951.data2String();
                                                System.out.printf("%s %s %s: %s \n" , gy_951.getName() ,gy_951.getSensType() ,gy_951.getDevType(), data);
                                                tempPort.writeLogToStack("Reading");
                    
                                            }else if("MPU6050".equals(dev.getName())){
                                                MPU6050 mpu6050 = mpu6050sDevices.get(dev.getDevID());
                                                String data = mpu6050.data2String();
                                                System.out.printf("%s %s %s: %s \n" , mpu6050.getName() ,mpu6050.getSensType() ,mpu6050.getDevType(), data);
                                                tempPort.writeLogToStack("Reading");
                    
                                            }else if("BME280".equals(dev.getName())){
                                                BME280 bme280 = bme280sDevices.get(dev.getDevID());
                                                String data = bme280.data2String();
                                                System.out.printf("%s %s %s: %s \n" , bme280.getName() ,bme280.getSensType() ,bme280.getDevType(), data);
                                                tempPort.writeLogToStack("Reading");
                    
                    
                                            }else if("DHT11".equals(dev.getName())){
                    
                                                DHT11 dht11 = dht11sDevices.get(dev.getDevID());
                                                String data = dht11.data2String();
                                                System.out.printf("%s %s %s: %s \n" , dht11.getName() ,dht11.getSensType() ,dht11.getDevType(), data);
                                                tempPort.writeLogToStack("Reading");
                                            }
                                        }else{
                                            System.err.printf("Device is not active.\n");
                                        }
                                    }   
                                }
                            }

                        }
                        // if device not found
                        if(!isFound){
                            System.err.printf("Device not found.\n");
                        }
                    }catch(Exception e){
                        System.err.println("Device ID must be integers.\n");
                    }
                    
                }else{

                    System.err.printf("Undefined command.\n");
                }
            }else{

                System.err.printf("Undefined command.\n");
            }
            
        }else if(command.contains("printDisplay")){
            // Print data to a display device
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));

            if(splitCommand.get(0).equals("printDisplay")){
                if(splitCommand.size() == 3){
                    String inputData = splitCommand.get(2);
                    int devID = Integer.parseInt(splitCommand.get(1));
                    boolean isFound = false;
                    
                    try{
                        Iterator<Port> portIterator = portList.iterator();

                        while(portIterator.hasNext()){
                            Port tempPort = portIterator.next();
                            Device dev = tempPort.device;
                            
                            if(dev != null){
                                // if they are equal then device  found
                                if(dev.getDevID() == devID){
                                    isFound = true;
                                    // check device state ON/OFF
                                    if("Display".equals(dev.getDevType())){
                                        if(dev.getState() == DeviceState.ON){
                                            if("LCD".equals(dev.getName())){
                                                LCD lcd = lcdsDevices.get(dev.getDevID());
                                                lcd.printData(inputData);
                                                
                                                tempPort.writeLogToStack("Writing " + inputData + ".");
                                            }else if("OLED".equals(dev.getName())){
                                                OLED oled = oledsDevices.get(dev.getDevID());
                                                 oled.printData(inputData);
                                                tempPort.writeLogToStack("Writing " + inputData + ".");
                                            }
                                        }else{
                                            System.err.printf("Device is not active.\n");
                                        }
                                    }
                                }
                            }
                        }
                      
                        // if device not found
                        if(!isFound){
                            System.err.printf("Device not found.\n");
                        }
                    }catch(Exception e){
                        System.err.println("Device ID must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
            
        }else if(command.contains("readWireless")){
            // Read data from a wireless device
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
            if(splitCommand.get(0).equals("readWireless")){
                if(splitCommand.size() == 2){
                    try{
                        int devID = Integer.parseInt(splitCommand.get(1));
                        boolean isFound = false;
                        // find device with devID
                        Iterator<Port> portIterator = portList.iterator();

                        while(portIterator.hasNext()){
                            Port tempPort = portIterator.next();
                            Device dev = tempPort.device;
                            if(dev != null){
                                // if they are equal then device  found
                                if(dev.getDevID() == devID){
                                    isFound = true;
                                    // check device state ON/OFF
                                        if(dev.getState() == DeviceState.ON){
                                            if("WirelessIO".equals(dev.getDevType())){
                                                if("Bluetooth".equals(dev.getName())){
                                                    Bluetooth bluetooth = bluetoothsDevices.get(dev.getDevID());
                                                    System.out.printf("%s: Received \"%s\" \n" ,dev.getName() ,bluetooth.recvData());
                                                    tempPort.writeLogToStack("Reading");
                                                }else if("Wifi".equals(dev.getName())){
                                                    Wifi wifi = wifisDevices.get(dev.getDevID());
                                                   
                                                    System.out.printf("%s: Received \"%s\" \n" ,dev.getName() ,wifi.recvData());
                                                    tempPort.writeLogToStack("Reading");
                                                }
                                            }
                                        }else{
                                            System.err.printf("Device is not active.\n");
                                            break;
                                        }
                                }
                            }
                        }
                        // if device not found
                        if(!isFound){
                            System.err.printf("Device not found.\n");
                        }
                    }catch(Exception e){
                        System.err.println("Device ID must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
        }else if(command.contains("writeWireless")){
            // Send data through a wireless device
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
            if(splitCommand.get(0).equals("writeWireless")){
                if(splitCommand.size() == 3){
                    try{
                        int devID = Integer.parseInt(splitCommand.get(1));
                        String inputData = splitCommand.get(2);
                        boolean isFound = false;
        
                        Iterator<Port> portIterator = portList.iterator();

                        while(portIterator.hasNext()){
                            Port tempPort = portIterator.next();
                            Device dev = tempPort.device;
                            
                            if(dev != null){
                                // if they are equal then device  found
                                if(dev.getDevID() == devID){
                                    isFound = true;
                                    if("WirelessIO".equals(dev.getDevType())){
                                        if(dev.getState() == DeviceState.ON){
                                            if("Bluetooth".equals(dev.getName())){
                                                Bluetooth bluetooth = bluetoothsDevices.get(dev.getDevID());
                                                bluetooth.sendData(inputData);
                                                tempPort.writeLogToStack("Writing " + inputData + ".");
                                            }else if("Wifi".equals(dev.getName())){
                                                Wifi wifi = wifisDevices.get(dev.getDevID());
                                                wifi.sendData(inputData);
                                                tempPort.writeLogToStack("Writing " + inputData + ".");
                                            }
                                        }else{
                                            System.err.printf("Device is not active.\n");
                                            break;
                                        }
                                    }
                                }
                            }
                        
                        }
                        // if device not found
                        if(!isFound){
                            System.err.printf("Device not found.\n");
                        }
                    }catch(Exception e){
                        System.err.println("Device ID must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
        }else if(command.contains("setMotorSpeed")){
            // Set the speed of a motor driver
            ArrayList<String> splitCommand = new ArrayList<>(Arrays.asList(command.split(" ")));
            if(splitCommand.get(0).equals("setMotorSpeed")){
                if(splitCommand.size() == 3){
                    try{
                        int devID = Integer.parseInt(splitCommand.get(1));
                        int motorSpeed = Integer.parseInt(splitCommand.get(2));
                        boolean isFound = false;
        
                        Iterator<Port> portIterator = portList.iterator();

                        while(portIterator.hasNext()){
                            Port tempPort = portIterator.next();
                            Device dev = tempPort.device;

                            if(dev != null){
                                // if they are equal then device  found
                                if(dev.getDevID() == devID){
                                    isFound = true;
                                    // check device state ON/OFF
                                    if("MotorDriver".equals(dev.getDevType())){
                                        if(dev.getState() == DeviceState.ON){
                                            if("PCA9685".equals(dev.getName())){
                                                PCA9685 pca9685 = pca9685sDevices.get(dev.getDevID());
                                                pca9685.setMotorSpeed(motorSpeed);
                                                tempPort.writeLogToStack("Writing " + motorSpeed + ".");
                                            }{ 
                                                SparkFunMD sparkFunMD = sparkFunMDsDevices.get(dev.getDevID());
                                                sparkFunMD.setMotorSpeed(motorSpeed);
                                                tempPort.writeLogToStack("Writing " + motorSpeed + ".");
                                            }
                                        }
                                        else{
                                            System.err.printf("Device is not active.\n");
                                            break;
                                        }
                                    }
                                }
                            }
                        }
        
                        // if device not found
                        if(!isFound){
                            System.err.printf("Device not found.\n");
                        }
                    }catch(Exception e){
                        System.err.println("Device ID and motor speed value must be integers.\n");
                    }
                    
                }else{
                    System.err.printf("Undefined command.\n");
                }
            }else{
                System.err.printf("Undefined command.\n");
            }
            
        }else{
            if(!command.endsWith("exit")){
                System.err.printf("Undefined command.\n");
            }
        }
    }
    
    /**
     * Initializes and runs the embedded system based on configuration file.
     * This method reads system configuration, initializes ports and protocols,
     * and processes user commands from standard input.
     * 
     * @param filePath Path to the configuration file
     * @param logFilePath Path where log files will be stored
     */
    public void RunSystem(String filePath , String logFilePath ){
        int[] ports_initial_values = {0,0,0,0};
        int ind_for_initial_values = 0;
        LinkedList<String> commandList = new LinkedList<String>();        

        int ports_count = 0;
        int sensors_count = 0;
        int displays_count = 0;
        int wireless_adapters_count = 0;
        int motor_drivers_count = 0;

        ArrayList<Protocol> protocolsList = new ArrayList<>();
        ArrayList<Port> portsList = new ArrayList<>();

        // file reading
        try (Scanner scanner = new Scanner(new File(filePath))) {
            
            //first line
            String line = scanner.nextLine();
            ArrayList<String> first_line = new ArrayList<>(Arrays.asList(line.split(":", 2)));
            ArrayList<String> protocols = new ArrayList<>(Arrays.asList(first_line.get(1).split(",")));
            
            ports_count = protocols.size();

            Iterator<String> iterator = protocols.iterator();
            while(iterator.hasNext()){
                String tempProtocol = iterator.next();
                if(tempProtocol.trim().equals("I2C")){
                    protocolsList.add(new I2C());

                }else if(tempProtocol.trim().equals("SPI")){
                    protocolsList.add(new SPI());

                }else if(tempProtocol.trim().equals("OneWire")){
                    protocolsList.add(new OneWire());

                }else if(tempProtocol.trim().equals("UART")){
                    protocolsList.add(new UART());
                }
            }

            Iterator<Protocol> protocolIterator = protocolsList.iterator();
            int port_ind = 0;
            while(protocolIterator.hasNext()){
                Protocol protocol = protocolIterator.next();
                portsList.add(new Port(protocol, null, true, port_ind, logFilePath));
                port_ind++;


            }
            while (scanner.hasNextLine()) {
                line = scanner.nextLine();
                ArrayList<String> valuesList = new ArrayList<>(Arrays.asList(line.split(":")));

                ports_initial_values[ind_for_initial_values] = Integer.parseInt(valuesList.get(1));
                ind_for_initial_values+=1;
            }
            
        } catch (Exception e) {
            System.err.println("Couldn't find file: " + e.getMessage());
        }

        for(int i = 0; i < ports_count; i++){
            switch(i){
                case 0:
                sensors_count = ports_initial_values[i];
                break;

                case 1:
                displays_count = ports_initial_values[i];
                break;

                case 2:
                wireless_adapters_count = ports_initial_values[i];
                break;

                case 3:
                motor_drivers_count = ports_initial_values[i];
                break;
            }
        }
        
        // Try to read the file
        // I got help from GPT to write this function
        try (Scanner scanner = new Scanner(System.in)) {
            // Read each line and add it to the ArrayList
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (line.equals("exit")) {
                    commandList.add(line);
                    break; // Exit the loop if "exit" is encountered
                }
                commandList.add(line);
            }
        } catch (Exception e) {
            System.out.println("Error reading from standard input: " + e.getMessage());
            return;
        }

        for (String command : commandList) {
            if (command.equals("exit")) {
                Iterator<String> iterator = commandList.iterator();
                while (iterator.hasNext()) {
                    String commandInList = iterator.next();
                    processCommand(commandInList, protocolsList, portsList, sensors_count, displays_count, wireless_adapters_count, motor_drivers_count, ports_count);
                }
                Iterator<Port> portIterator = portsList.iterator();
                while (portIterator.hasNext()) {
                    Port tempPort = portIterator.next();
                    tempPort.createLogFile();
                    tempPort.writeLogsToFile();
                }
                System.out.println("Exitting...");
                break; 
            } 
        }
    }
    
    /**
     * Determines the device type based on its name.
     * Maps device name strings to integer codes for internal use.
     * 
     * @param name The name of the device
     * @return An integer code representing the device type (0-9) or -1 if not found
     */
    private static int determineDevice(String name){
        if("LCD".equals(name)){
            return 0;
        }else if("OLED".equals(name)){
            return 1;
        }else if("PCA9685".equals(name)){
            return 2;
        }else if("SparkFunMD".equals(name)){
            return 3;
        }else if("GY_951".equals(name)){
            return 4;
        }else if("MPU6050".equals(name)){
            return 5;
        }else if("BME280".equals(name)){
            return 6;
        }else if("DHT11".equals(name)){
            return 7;
        }else if("Bluetooth".equals(name)){
            return 8;
        }else if("Wifi".equals(name)){
            return 9;
        }
        return -1;
    }
}

                                
