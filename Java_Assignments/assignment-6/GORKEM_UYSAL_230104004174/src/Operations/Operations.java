package Operations;

import GTUHashSet.GTUHashSet;
import MyList.MyList;


/**
 * Operations class contains functions to generetate suggestions by applying various operations.
 * 
 */

public class Operations {

    /** Set to store all generated suggestions */
    GTUHashSet<String> allSuggestions;

    /** Maximum number of operation to execute */
    int OPERATIONS_LIMIT = 10000;

    /** initial count of operations */
    int operationCount = 0;

    /** Default constructor */
    public Operations(){
        allSuggestions = new GTUHashSet<>();
    }


    /** English alphabet characters used for replacements and insertions */
    char[] alphabet = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    /**
     * Replaces a character at a specific index with a new string.
     * 
     * @param str The original string
     * @param index index The index at which to replace
     * @param newChar newChar The new string to insert
     * @return A new string with the character at index replaced by newChar
     * @throws IndexOutOfBoundsException if the index is out of bounds
     */
    private String replaceAt(String str, int index, String newChar) {
        if (index < 0 || index >= str.length()) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        operationCount++;
        return str.substring(0, index) + newChar + str.substring(index + 1);
    }

     /**
     * Replaces a character at a specific index with a another char.
     * 
     * @param str The original string
     * @param index index The index at which to replace
     * @param newChar newChar The new string to insert
     * @return A new string with the character at index replaced by newChar
     * @throws IndexOutOfBoundsException if the index is out of bounds
     */
    private String replaceAt(String str, int index, char newChar) {
        if (index < 0 || index >= str.length()) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        operationCount++;
        return str.substring(0, index) + newChar + str.substring(index + 1);
    }


    /**
    * Inserts a character at a specific index in a string.
    * 
    * @param input The original string
    * @param index The index at which to insert
    * @param newChar The character to insert
    * @return A new string with the character inserted at index
    */
    private String insertCharToString(String input, int index, char newChar) {
        operationCount++;
        return input.substring(0, index) + newChar + input.substring(index);
    }

    /**
    * Checks if the suggestion limit has been reached.
    * 
    * @return true if the number of suggestions has reached the limit
    */
    private boolean reachedLimit() {
        return operationCount >= OPERATIONS_LIMIT;
    }

    /* Resets operation count */
    public void resetOperationCount() {
        operationCount = 0;
    }


     /**
     * Generates suggestions by deleting one character from the input string.
     * 
     * @param input The input string
     * @return A list of generated suggestions
     */
    private MyList<String> delete_1_char(String input){
        MyList<String> suggestionsList = new MyList<>();
        int inputLen = input.length();

            for(int i = 0; i < inputLen; i++){
            if(reachedLimit()){
                break;
            }
                operationCount++;
                String generatedStr = replaceAt(input, i, "");
                allSuggestions.add(generatedStr);
            }
        return suggestionsList;
    }


     /**
     * Generates suggestions by deleting two characters from the input string.
     * 
     * @param input The input string
     * @return A list of generated suggestions
     */
    private MyList<String> delete_2_char(String input){
        MyList<String> suggestionsList = new MyList<>();
        int inputLen = input.length();

             for(int i = 0; i < inputLen; i++){
                for(int j = i; j < inputLen - 1; j++){

                    if(reachedLimit()) return suggestionsList;
                    operationCount++;

                    String delete_1_char = replaceAt(input, i, "");
                    String generatedString = replaceAt(delete_1_char, j, "");
                    allSuggestions.add(generatedString);
                }
            }

       return suggestionsList;
    }


    /**
     * Generates suggestions by replacing one character in the input string.
     * 
     * @param input The input string
     * @return A list of generated suggestions
     */
    private MyList<String> replace_1_char(String input){
        MyList<String> suggestionsList = new MyList<>();
        int inputLen = input.length();
        
        for(int i = 0; i < inputLen; i++){
            for(int j = 0; j < alphabet.length; j++){
                
                if(reachedLimit()) return suggestionsList;
                
                operationCount++;
                String generatedString = replaceAt(input, i, alphabet[j]);
                allSuggestions.add(generatedString);
            }
        }
        
        return suggestionsList;
    }

     /**
     * Generates suggestions by replacing two characters in the input string.
     * 
     * @param input The input string
     * @return A list of generated suggestions
     */
    private MyList<String> replace_2_char(String input){
        MyList<String> replace_first_char_list = new MyList<>();
        MyList<String> replace_second_char_list = new MyList<>();
        int inputLen = input.length();

        for(int i = 0; i < inputLen; i++){
            for(int j = 0; j < alphabet.length; j++){

                if(reachedLimit()) return replace_second_char_list;

                operationCount++;
                String replace_1_char =  replaceAt(input, i, alphabet[j]);
                replace_first_char_list.add(replace_1_char);
            }
        }

        for(int k = 0; k < replace_first_char_list.size(); k++){
            for(int l = 0 ; l < inputLen; l++){
                for(int m = 0; m < alphabet.length; m++){
                    
                    if(reachedLimit()) return replace_second_char_list;

                    operationCount++;
                    String replace_second_char =  replaceAt(replace_first_char_list.get(k), l, alphabet[m]);
                    allSuggestions.add(replace_second_char);
                }
            }
        }

        return replace_second_char_list;
    }
    

     /**
     * Generates suggestions by inserting one character into the input string.
     * 
     * @param input The input string
     * @return A list of generated suggestions
     */
    private MyList<String> insert_1_char(String input){
        MyList<String> suggestionsList = new MyList<>();
        int inputLen = input.length();

        for(int i = 0; i < inputLen; i++){
            for(int j = 0; j < alphabet.length; j++){

                if(reachedLimit()) return suggestionsList;

                operationCount++;
                String generatedString = insertCharToString(input, i, alphabet[j]);
                allSuggestions.add(generatedString);
            }
        }

        return suggestionsList;
    }


    /**
     * Generates suggestions by inserting two characters into the input string.
     * 
     * @param input The input string
     */
    public void insert_2_char(String input){
        MyList<String> insert_first_char_list = new MyList<>();
        MyList<String> insert_second_char_list = new MyList<>();
        int inputLen = input.length();

        for(int i = 0; i < inputLen; i++){
            for(int j = 0; j < alphabet.length; j++){

                if(reachedLimit()) return;

                operationCount++;
                String generatedString = insertCharToString(input, i, alphabet[j]);
                insert_first_char_list.add(generatedString);
            }
        }

        for(int k = 0; k < insert_first_char_list.size() ; k++){
            for(int l = 0; l < inputLen + 1 ; l++){
                for(int m = 0; m < alphabet.length; m++){

                    if(reachedLimit()) return;

                    operationCount++;
                    String generatedString = insertCharToString(insert_first_char_list.get(k), l, alphabet[m]);
                    insert_second_char_list.add(generatedString);
                }
            }
        }

        for(int n = 0; n < insert_second_char_list.size() ; n++){

            if(reachedLimit()) return;

            operationCount++;
            allSuggestions.add(insert_second_char_list.get(n));
        }

    }


     /**
     * Generates suggestions by first replacing and then inserting a character.
     * 
     * @param input The input string
     */
    private void replace_and_insert(String input){
        MyList<String> replaceList = new MyList<>();
        MyList<String> replace_and_insert_List = new MyList<>();

        if(reachedLimit()) return;
        replaceList = replace_1_char(input);
        operationCount++;
      

        for(int i = 0; i < replaceList.size(); i++){
            if(reachedLimit()) return;
            replace_and_insert_List = insert_1_char(replaceList.get(i));
            operationCount++;
        }

        for(int j = 0; j < replace_and_insert_List.size() ; j++){
            if(reachedLimit()) return;
            allSuggestions.add(replace_and_insert_List.get(j));
            operationCount++;
        }
    }

     /**
     * Generates suggestions by first removing and then replacing a character.
     * 
     * @param input The input string
     */
    private void remove_and_replace(String input){
        MyList<String> removeList = new MyList<>();
        MyList<String> remove_and_replace_list = new MyList<>();
        
        if(reachedLimit()) return;
        removeList = replace_1_char(input);
        operationCount++;

        for(int i = 0; i < removeList.size(); i++){
            if(reachedLimit()) return;
            remove_and_replace_list = replace_1_char(removeList.get(i));
            operationCount++;
        }

        for(int j = 0; j < remove_and_replace_list.size() ; j++){
            if(reachedLimit()) return;
            allSuggestions.add(remove_and_replace_list.get(j));
            operationCount++;
        }

        
    }

     /**
     * Applies all operations to generate suggestions for the input string.
     * 
     * @param input The input string
     */
    public void allOperations(String input){
        delete_1_char(input);
        if (reachedLimit()) return;

        delete_2_char(input);
        if (reachedLimit()) return;

        replace_1_char(input);
        if (reachedLimit()) return;

        replace_2_char(input);
        if (reachedLimit()) return;

        insert_1_char(input);
        if (reachedLimit()) return;

        insert_2_char(input);
        if (reachedLimit()) return;
        
        replace_and_insert(input);
        if (reachedLimit()) return;
        
        remove_and_replace(input);
    }


     /**
     * Generates all suggestions for the input string and returns them as a set.
     * 
     * @param input The input string
     * @return A set of all generated suggestions
     */
    public GTUHashSet<String> getAllSuggestions(String input){
        allOperations(input);
        return allSuggestions;
    }

}
