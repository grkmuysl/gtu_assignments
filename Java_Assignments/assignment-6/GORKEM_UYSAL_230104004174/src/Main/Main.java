package Main;

import java.io.IOException;
import SpellChecker.SpellChecker;

public class Main {
   
   
    public static void main(String[] args) {
        
        try {
            SpellChecker.main(args);
        } catch (IOException e) {
            System.err.println("Error running SpellChecker: " + e.getMessage());
        }
    }

    
}
