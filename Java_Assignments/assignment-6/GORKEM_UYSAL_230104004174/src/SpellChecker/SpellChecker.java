package SpellChecker;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.Scanner;

import GTUHashMap.GTUHashMap;
import GTUHashSet.GTUHashSet;
import Operations.Operations;

public class SpellChecker {

    /**
    * Generates all possible suggestions for a given input word.
    * 
    * @param input The word to generate suggestions for
    * @return A set of generated suggestions
    */

    private static GTUHashSet<String> generateAllSuggestions(String input){
        GTUHashSet<String> suggestions = new GTUHashSet<>();
        Operations myOp = new Operations();
        suggestions = myOp.getAllSuggestions(input);
        return suggestions;
    }

    public static void main(String[] args) throws IOException {
        // Create a set and BufferedReader for the dictionary
        GTUHashSet<String> dictionary = new GTUHashSet<>();        
        BufferedReader reader = new BufferedReader(new
        FileReader("dictionary.txt"));

        dictionary.resetCollisionCount();

        // Create a map to group words by their length
        GTUHashMap<Integer, GTUHashSet<String>> lengthMap = new GTUHashMap<>();

        String word;

        while ((word = reader.readLine()) != null) {
            int wordLen = word.trim().length();

            // If there's no word group for this length, create a new set
            if(!lengthMap.containsKey(wordLen)){
                lengthMap.put(wordLen, new GTUHashSet<>());
            }

            // Add the word to its legth group and the main dictionary
            lengthMap.get(wordLen).add(word);
            dictionary.add(word.trim());
            
        }

        reader.close();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.print("Enter a word: ");
            String input = scanner.nextLine().trim();
            long startTime = System.nanoTime();

            // reset collision count before getting input
            dictionary.resetCollisionCount();

            // If the word is in the dictionary, it's correct
            if (dictionary.contains(input)) {
                System.out.println("Correct.");
            } else {
                // If the word is not in the dictionary, it's incorrect and suggestions are provided
                System.out.println("Incorrect.");
                

                // Generate all possible suggestions
                GTUHashSet<String> allSuggestions = new GTUHashSet<>();
                allSuggestions = generateAllSuggestions(input);

                // Create a new set for valid suggestions
                GTUHashSet<String> validSuggestions = new GTUHashSet<String>();

                int minLen;
                if(input.length() > 2){
                    minLen = input.length() - 2;
                }else if(input.length() == 2){
                    minLen = input.length() - 1;
                }else{
                    minLen = 1;
                }

                // Check map groups between 2 characters less and 2 characters more (legth of input) .
                for(int len = minLen ; len < input.length() + 2; len++){
                    GTUHashSet<String> lengthSet = lengthMap.get(len);
          
                    // create a Iterator to travers on the hashset
                    Iterator<String> suggestionIterator = allSuggestions.iterator();
                    while(suggestionIterator.hasNext()){
                        String suggestion = suggestionIterator.next();
                        if(lengthSet.contains(suggestion)){
                            validSuggestions.add(suggestion);
                        }
                    }
                }

                System.out.printf("All suggestions : %d \n" , allSuggestions.size());
                System.out.printf("Valid suggestions : %d \n" , validSuggestions.size());
                System.out.printf("Count of collisions : %d \n" , dictionary.getCollisionCount());

                // Print all valid suggestions
                Iterator<String> validSuggestionIterator = validSuggestions.iterator();
                System.out.println("Suggestions: ");
                System.out.printf("[");
                while(validSuggestionIterator.hasNext()){
                    String validSuggestion = validSuggestionIterator.next();
                    System.out.printf("%s, " , validSuggestion);
                }
                System.out.println("]");

            }
                long endTime = System.nanoTime();
                System.out.printf("Lookup and suggestion took %.2f ms\n", (endTime -
                startTime) / 1e6);
            }
    }
}