
#include "AnsiTerminal.h"
#include <iostream>
#include <string>
#include "SpreadSheet.h"
#include <vector>
using namespace std;


int main() {
   
    // Initialize terminal and clear the screen
    AnsiTerminal terminal;
    terminal.clearScreen(); // Clear the screen at the beginning

    // Grid dimensions
    int rows = 10;                // Initial number of rows
    int cols = 10;                // Initial number of columns
    const int cellWidth = 10;     // Width of each cell
    const int cellHeight = 2;     // Height of each cell
    const int maxCellDisplayLength = 7; // Maximum characters displayed in a cell
    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight); // Draw the grid

    // Initialize the spreadsheet
    SpreadSheet spread_sheet(rows, cols);

    int row = 1, col = 0;         // Initial cursor position
    char key;                     // User input
    string inputValue = "";       // Stores user input for the current cell
    bool isFormula = false;       // Tracks whether the current input is a formula

    while (true) {

        // Retrieve the grid of cells and the current cell
        auto& cells = spread_sheet.getAllCels();
        auto& cell = cells[row][col];
        FormulaParser formulaParser(cells);
        FileManager fileManager(cells);
        string fileName = "output.csv";

        // Calculate cursor position for terminal output
        int cursorRow = row * cellHeight + cellHeight / 2 + 1;
        int cursorCol = col * cellWidth + cellWidth / 2 + 1;

        // Display the value of the current cell
        string cellValue = cell.getString_Value();
        if (cellValue.size() > maxCellDisplayLength) {
            cellValue = cellValue.substr(0, maxCellDisplayLength);
        }
        terminal.printAt(cursorRow, cursorCol - cellValue.size() / 2, cellValue);
      
         // Get user input
        key = terminal.getSpecialKey();

        // Clear the previous position
        string limitedInput = (inputValue.size() > maxCellDisplayLength) ? inputValue.substr(0, maxCellDisplayLength) : inputValue;
        terminal.printAt(cursorRow, cursorCol - limitedInput.size() / 2, string(limitedInput.size(), ' '));

       
        // Handle special keys for navigation and input
        switch (key) {
            case 'U': // Move up
                row = (row > 1) ? row - 1 : row;
                break;
            case 'D': // Move down
                if (row < rows - 1) {
                    row++;
                } else {
                    spread_sheet.addRow(cols); // Add a new row
                    rows++;
                    terminal.clearScreen();
                    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight);

                    // Reprint all data after resizing
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            string cellValue = cells[i][j].getString_Value();
                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength);
                            }
                            int cellRow = i * cellHeight + cellHeight / 2 + 1;
                            int cellCol = j * cellWidth + cellWidth / 2 + 1;
                            terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue);
                        }
                    }
                }
                break;
            case 'L': // Move left
                col = (col > 0) ? col - 1 : col;
                break;
            case 'R': // Move right
                if (col < cols - 1) {
                    col++;
                } else {
                    spread_sheet.addColumn(); // Add a new column
                    cols++;
                    terminal.clearScreen();
                    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight);

                    // Reprint all data after resizing
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            string cellValue = cells[i][j].getString_Value();
                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength);
                            }
                            int cellRow = i * cellHeight + cellHeight / 2 + 1;
                            int cellCol = j * cellWidth + cellWidth / 2 + 1;
                            terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue);
                        }
                    }
                }
                break;
            case 'I': // Save to file
                fileManager.saveToFile(fileName);
                break;
            case 'P': // load from file
                fileManager.loadFromFile("test_spreadsheet.csv");
                
                // reprint data to table
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            string cellValue = cells[i][j].getString_Value();
                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength); 
                            }
                            int cellRow = i * cellHeight + cellHeight / 2 + 1;
                            int cellCol = j * cellWidth + cellWidth / 2 + 1;
                            terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue);
                        }
                    }
                break;
            case 'q': // Quit the program
                return 0;
            
            case 'J': // USER CLICK THE ENTER

             //check isFormula
             if(inputValue.size() > 0 && inputValue[0] == '='){
                
                string formula = inputValue.substr(1);

                 // check if contains functions keyword 
                if(formula.find("SUM") != string::npos){
                    formula = formulaParser.formulaConverterForSum(formula);
                }
                if(formula.find("AVER") != string::npos){
                    formula = formulaParser.formulaConverterForAver(formula);
                }
                if(formula.find("MAX") != string::npos){
                    formula = formulaParser.formulaConverterForMax(formula);
                }
                if(formula.find("MIN") != string::npos){
                    formula = formulaParser.formulaConverterForMin(formula);
                }
                if(formula.find("STDDEV") != string::npos){
                    formula = formulaParser.formulaConverterForSDTDEV(formula);
                }
                formulaParser.applyFormula(formula , row,col);

             }else{

                if(cell.getString_Value().size() > 0){ // check if cell has a value
                   
                    cell.setString_Value(""); // if it has then delete the value
                    terminal.printAt(cursorRow, cursorCol - (cellWidth / 2) + 1, string(cellWidth - 1, ' '));

                }else{
                    //save input value to cell
                    cell.setString_Value(inputValue);
                    
                    // check cell has a dependency
                    if(cell.isCellHasDependent()){
                        vector<string>appliedFormulas = cell.getAppliedFormulas();

                        int size_of_formulas = appliedFormulas.size();
                        for(int i = 0; i < size_of_formulas; i++){
                            vector<vector<int>>dependentCells = cell.getDependentCells();
                            formulaParser.applyFormula(appliedFormulas[i] , dependentCells[i][0],dependentCells[i][1]);
                       
                            // reprint data to table
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < cols; j++) {
                                    string cellValue = cells[i][j].getString_Value();
                                    if (cellValue.size() > maxCellDisplayLength) {
                                        cellValue = cellValue.substr(0, maxCellDisplayLength); 
                                    }
                                    int cellRow = i * cellHeight + cellHeight / 2 + 1;
                                    int cellCol = j * cellWidth + cellWidth / 2 + 1;
                                    terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue);
                                }
                            }
                        }
                    }

                    terminal.printAt(0, 15, string(80, ' ')); // Clear previous status row
                    terminal.printAt(0, 15, "Cell [" + string(1, 'A' + col) + to_string(row + 1) + "]: " + inputValue);
                }
             }
                inputValue.clear();
            break;

            case 127: //backspace
                if (inputValue.size() > 0) { 
                    inputValue.pop_back();
                }
            break;

            default: // user is entering a value
        
            if (key >= ' ' && key <= '~') { // onyl pritable chars
                if(inputValue.empty()){ // save first char
                    inputValue += key;
                }else{
                    if(inputValue[0] == '='){ // check if is a formula

                        if (key >= 'a' && key <= 'z') {
                            char upperKey = key - ('a' - 'A'); // write lowercase letters in uppercase
                            inputValue += upperKey;
                        }else{
                            inputValue += key;
                        }

                    }else{
                        inputValue += key;
                    }
                }
                
            }
        }
        
        string visibleInput = (inputValue.size() > maxCellDisplayLength)? inputValue.substr(0, maxCellDisplayLength): inputValue;

        terminal.printAt(0, 15, string(80, ' ')); // Clear previous value in the status row
        terminal.printAt(0, 15, "Cell [" + string(1, 'A' + col) + to_string(row ) + "]: " + inputValue);

        // cell i temizle ve yeni inputu yazdir
        if(inputValue.size() < maxCellDisplayLength - 2){
            terminal.printAt(cursorRow, cursorCol - inputValue.size() / 2, (inputValue[0] == '=' ? "" : inputValue));
            
        }else{
            string terminatedVal = inputValue.substr(0, maxCellDisplayLength);
            terminal.printAt(cursorRow, cursorCol - terminatedVal.size() / 2, (terminatedVal[0] == '=' ? "" : terminatedVal));
        }
    }
    terminal.clearScreen(); // Clear the screen on exit
    return 0;
}
