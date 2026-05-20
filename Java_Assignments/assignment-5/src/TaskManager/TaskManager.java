package TaskManager;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

import PriorityQueue.MyMinHeap;
import Tasks.MyTask;
import Users.MyUser;

/**
 * Manages users and tasks using a min-heap priority queue.
 */
public class TaskManager {
    /** List of users in the system. */
    ArrayList<MyUser> usersList = new ArrayList<>();

    /** Min-heap for storing tasks by priority. */
    MyMinHeap<MyTask> taskList = new MyMinHeap<>();

    /** Path to the configuration file. */
    String configPath;

    /**
     * Constructs a TaskManager with the given configuration file path.
     * Time Complexity: O(1)
     *
     * @param configPath Path to the user configuration file.
     */
    public TaskManager(String configPath){
        this.configPath = configPath;
    }

    /**
     * Runs the main system: loads users and processes tasks.
     * Time Complexity: O(n + m log m), where n = number of users, m = number of tasks.
     */
    public void runTheSystem(){
        getUsers();
        getTasks();
    }

    /**
     * Reads users from the configuration file and adds them to the users list.
     * Time Complexity: O(n), where n = number of users.
     */
    private void getUsers(){
        try (Scanner scanner = new Scanner(new File(configPath))) {
            String line;
            int user_id = 0;
            int user_priority;

            while(scanner.hasNext()){
                line = scanner.nextLine();
                user_priority = Integer.parseInt(line);
                if(user_priority < 0){
                    System.err.println("Priority cannot be negative.");
                } else {
                    MyUser user = new MyUser(user_id, user_priority);
                    usersList.add(user);
                    user_id++;
                }
            }
        } catch (Exception e) {
            System.err.println("Couldn't find file: " + e.getMessage());
        }
    }

    /**
     * Reads tasks from standard input and adds them to the task heap.
     * Accepts user IDs, creates tasks, and adds them to the heap.
     * Typing 'execute' will process all tasks.
     * Time Complexity: O(m log m), where m = number of tasks.
     */
    private void getTasks(){
        Scanner scanner = new Scanner(System.in);
        int taskId = 0;

        while (true) {
            String input = scanner.nextLine().trim();

            if (input.equals("execute")) {
                executeTasks(taskList);
                scanner.close();
                break;
            }

            try {
                int userID = Integer.parseInt(input);
                if(userID < 0){
                    System.err.println("UserID cannot be negative.");
                } else {
                    if(userID >= usersList.size()){
                        System.err.println("There is no user with this userID.");
                    }else{
                        for(int i = 0; i < usersList.size(); i++){
                            MyUser user = usersList.get(i);
                            if(user.getId() == userID){
                                MyTask task = new MyTask(user, taskId);
                                taskList.add(task);
                            }
                        }
                        taskId++;
                    }
                  
                }
            } catch (NumberFormatException e) {
                System.err.println("Invalid format of userID: " + input);
            }
        }
    }

    /**
     * Executes all tasks in the min-heap and prints their details.
     * Time Complexity: O(m log m), where m = number of tasks.
     *
     * @param taskListMinHeap The min-heap containing tasks to execute.
     */
    private void executeTasks(MyMinHeap<MyTask> taskListMinHeap){
        while(!taskListMinHeap.isEmpty()){
            MyTask tempTask = taskListMinHeap.poll();
            String taskToStr = tempTask.toString();
            System.out.println(taskToStr);
        }
    }
}
