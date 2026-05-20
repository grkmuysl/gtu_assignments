package Main;
import HWSystem.EmbeddedSystem.SystemManager;

/**
 * Main application class that serves as the entry point for the embedded system application.
 * Handles command-line arguments and initializes the SystemManager.
 */
public class Main {
   
    /**
     * Main method that starts the application
     * 
     * @param args Command-line arguments:
     *             args[0] - Input file path containing system configuration or commands
     *             args[1] - Log file path where system logs will be written
     */
    public static void main(String[] args) {

        // Check if the required command-line arguments are provided
        if (args.length < 1) {
            System.out.println("Usage: java FileToArrayList <filename>");
            return;
        }
        
        // Extract file paths from command-line arguments
        String filePath = args[0];
        String logFilePath = args[1];
        
        // Create and initialize the system manager
        SystemManager systemManager = new SystemManager();
        
        // Start the system with the provided file paths
        systemManager.RunSystem(filePath, logFilePath);
    }
}
