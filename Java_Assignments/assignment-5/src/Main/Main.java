package Main;

import TaskManager.TaskManager;

/**
 * Main class for starting the Task Manager system.
 */
public class Main {
   
    /**
     * Entry point of the program.
     * Time Complexity: O(1)
     * 
     * @param args Command line arguments, expects the configuration file path as the first argument.
     */
    public static void main(String[] args) {
        String configPath = args[0];
        TaskManager taskManager = new TaskManager(configPath);
        taskManager.runTheSystem();
    }
}
