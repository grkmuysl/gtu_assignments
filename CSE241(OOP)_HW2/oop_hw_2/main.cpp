
#include "AnsiTerminal.h" // Class for terminal operations
#include <iostream>       // Library for input/output operations
#include <string>         // Library for string manipulations
#include "SpreadSheet.h"  // Class for spreadsheet operations
#include <vector>         // Library for vector data structure
#include "FormulaParser.h" // Class for formula parsing
#include "FileManager.h"   // Class for file management

// Using standard namespace and custom namespaces
using namespace std;
using namespace spread_sheet;
using namespace file_manager;
using namespace formula_parser;


int main() {
   
    // Initialize terminal and clear the screen
    AnsiTerminal terminal;
    terminal.clearScreen(); // Clear the screen at the beginning

    // Grid dimensions
    int rows = 10;                // Initial number of rows
    int cols = 10;                // Initial number of columns
    int initial_row = 0;
    int initial_col = 0;
    const int cellWidth = 10;     // Width of each cell
    const int cellHeight = 2;     // Height of each cell
    const int maxCellDisplayLength = 7; // Maximum characters displayed in a cell
    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight, initial_row, initial_col); // Draw the grid

    // Initialize the spreadsheet
    SpreadSheet spread_sheet2(rows, cols);

    int row = 1, col = 0;         // Initial cursor position
    char key;                     // User input
    string inputValue = "";       // Stores user input for the current cell
    bool isFormula = false;       // Tracks whether the current input is a formula

    while (true) {

        // Retrieve the grid of cells and the current cell
        auto& cells = spread_sheet2.getAllCells();
        auto& cell = cells[row][col];
        
        FormulaParser formulaParser(cells);
        
        FileManager fileManager(cells, rows, cols);
        string fileName = "output.csv";

        // Calculate cursor position for terminal output
        int cursorRow = (row - initial_row) * cellHeight + cellHeight / 2 + 1;
        int cursorCol = (col - initial_col) * cellWidth + cellWidth / 2 + 1;


        string cellValue; // Variable to store the value of the current cell

        // Check if the cell is null (empty)
        if (cell == nullptr) {
            cellValue = ""; // If the cell is empty, assign an empty string to cellValue
        } else {
            cellValue = cell->getData(); // If the cell is not empty, get its data and assign it to cellValue
        }

        // Check if the cell value exceeds the maximum display length
        if (cellValue.size() > maxCellDisplayLength) {
            cellValue = cellValue.substr(0, maxCellDisplayLength); // Truncate the cell value to the maximum display length
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
                // Check if the current row is greater than 1 (to ensure we don't go out of bounds)
                if (row > 1) {
                    // If the current row is at the top of the visible grid, adjust the grid view
                    if (row == initial_row + 1 && row > 1) {
                        row--; // Move the cursor up
                        rows--; // Decrease the total visible rows
                        initial_row--; // Adjust the initial row to shift the grid up
                        terminal.clearScreen(); // Clear the screen
                        terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight, initial_row, initial_col); // Redraw the grid

                        // Reprint all data in the visible grid after resizing
                        for (int i = initial_row; i < rows; i++) {
                            for (int j = initial_col; j < cols; j++) {
                                string cellValue = cells[i][j]->getData(); // Get cell data
                                if (cellValue.size() > maxCellDisplayLength) { 
                                    cellValue = cellValue.substr(0, maxCellDisplayLength); // Truncate if it exceeds the max length
                                }
                                // Calculate the row and column position for printing
                                int cellRow = (i - initial_row) * cellHeight + cellHeight / 2 + 1;
                                int cellCol = j * cellWidth + cellWidth / 2 + 1;
                                terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue); // Print cell value
                            }
                        }
                    } else {
                        row = row - 1; // Simply move the cursor up
                    }
                } else {
                    row = row; // If already at the top, do nothing
                }
                break;

            case 'D': // Move down
                // Check if the current row is within bounds
                if (row < rows - 1) {
                    row++; // Move the cursor down
                } else {
                    spread_sheet2.addRow(); // Add a new row to the spreadsheet
                    rows++; // Increase the total number of rows
                    initial_row++; // Adjust the initial row to shift the grid down
                    terminal.clearScreen(); // Clear the screen
                    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight, initial_row, initial_col); // Redraw the grid

                    // Reprint all data in the visible grid after resizing
                    for (int i = initial_row; i < rows; i++) {
                        for (int j = initial_col; j < cols; j++) {
                            string cellValue = cells[i][j]->getData(); // Get cell data
                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength); // Truncate if it exceeds the max length
                            }
                            // Calculate the row and column position for printing
                            int cellRow = (i - initial_row) * cellHeight + cellHeight / 2 + 1;
                            int cellCol = j * cellWidth + cellWidth / 2 + 1;
                            if (i - initial_row > 0) { // Ensure the row is within the visible range
                                terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue); // Print cell value
                            }
                        }
                    }
                }
                break;

            case 'L': // Move left
                // Check if the current column is within bounds
                if (col > 0) {
                    // If the current column is at the left edge of the visible grid, adjust the grid view
                    if (col == initial_col && cols > 10) {
                        col--; // Move the cursor left
                        cols--; // Decrease the total visible columns
                        initial_col--; // Adjust the initial column to shift the grid left
                        terminal.clearScreen(); // Clear the screen
                        terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight, initial_row, initial_col); // Redraw the grid

                        // Reprint all data in the visible grid after resizing
                        for (int i = initial_row; i < rows; i++) {
                            for (int j = initial_col; j < cols; j++) {
                                string cellValue = cells[i][j]->getData(); // Get cell data
                                if (cellValue.size() > maxCellDisplayLength) {
                                    cellValue = cellValue.substr(0, maxCellDisplayLength); // Truncate if it exceeds the max length
                                }
                                // Calculate the row and column position for printing
                                int cellRow = i * cellHeight + cellHeight / 2 + 1;
                                int cellCol = (j - initial_col) * cellWidth + cellWidth / 2 + 1;
                                terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue); // Print cell value
                            }
                        }
                    } else {
                        col = col - 1; // Simply move the cursor left
                    }
                } else {
                    col = col; // If already at the leftmost column, do nothing
                }
                break;

            case 'R': // Move right
                // Check if the current column is within bounds
                if (col < cols - 1) {
                    col++; // Move the cursor right
                } else {
                    spread_sheet2.addColumn(); // Add a new column to the spreadsheet
                    cols++; // Increase the total number of columns
                    initial_col++; // Adjust the initial column to shift the grid right
                    terminal.clearScreen(); // Clear the screen
                    terminal.drawGrid(rows - 1, cols, cellWidth, cellHeight, initial_row, initial_col); // Redraw the grid

                    // Reprint all data in the visible grid after resizing
                    for (int i = initial_row; i < rows; i++) {
                        for (int j = initial_col; j < cols; j++) {
                            string cellValue = cells[i][j]->getData(); // Get cell data
                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength); // Truncate if it exceeds the max length
                            }
                            // Calculate the row and column position for printing
                            int cellRow = i * cellHeight + cellHeight / 2 + 1;
                            int cellCol = (j - initial_col) * cellWidth + cellWidth / 2 + 1;
                            terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue); // Print cell value
                        }
                    }
                }
                break;

            case 'I': // Save to file
                fileManager.saveToFile(fileName);
                break;
            case 'P': // load from file
                fileManager.loadFromFile("output.csv");
                
                // reprint data to table
                    for (int i = initial_row; i < rows; i++) {
                        for (int j = initial_col; j < cols; j++) {
                            string cellValue = cells[i][j]->getData();

                            if (cellValue.size() > maxCellDisplayLength) {
                                cellValue = cellValue.substr(0, maxCellDisplayLength);
                            }
                            int cellRow = i * cellHeight + cellHeight / 2 + 1;
                            int cellCol = (j-initial_col) * cellWidth + cellWidth / 2 + 1 ;
                           
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

                // Check if the formula contains specific function keywords and convert them as needed
                if (formula.find("SUM") != string::npos) { 
                    // If the formula contains "SUM", convert it using the appropriate converter
                    formula = formulaParser.formulaConverterForSum(formula);
                }
                if (formula.find("AVER") != string::npos) { 
                    // If the formula contains "AVER", convert it using the appropriate converter
                    formula = formulaParser.formulaConverterForAver(formula);
                }
                if (formula.find("MAX") != string::npos) { 
                    // If the formula contains "MAX", convert it using the appropriate converter
                    formula = formulaParser.formulaConverterForMax(formula);
                }
                if (formula.find("MIN") != string::npos) { 
                    // If the formula contains "MIN", convert it using the appropriate converter
                    formula = formulaParser.formulaConverterForMin(formula);
                }
                if (formula.find("STDDEV") != string::npos) { 
                    // If the formula contains "STDDEV", convert it using the appropriate converter
                    formula = formulaParser.formulaConverterForSDTDEV(formula);
                }

                // Apply the converted formula to the specified cell (row, col)
                formulaParser.applyFormula(formula, row, col);

             }else{

                if (cell->getData().size() > 0) { // Check if the cell already has a value
                    // Create a new StringValueCell to clear the current cell's data
                    unique_ptr<Cell> newStrCell = make_unique<StringValueCell>();
                    // Retrieve the dependent cells of the current cell
                    vector<vector<int>> dependentCells = cell->getDependentCells();
                    // Retrieve the applied formulas of the current cell
                    vector<string> appliedFormulas = cell->getAppliedFormulas();

                    // Set the dependent cells for the new empty StringValueCell
                    for (int i = 0; i < dependentCells.size(); i++) {
                        newStrCell->setDependentCells(dependentCells[i]);
                    }
                    // Set the applied formulas for the new empty StringValueCell
                    newStrCell->setAppliedFormulas(appliedFormulas);

                    // Clear the data in the new StringValueCell
                    newStrCell->setData("");
                    // Replace the current cell with the new empty StringValueCell
                    cell = move(newStrCell);
                    // Clear the cell display in the terminal
                    terminal.printAt(cursorRow, cursorCol - (cellWidth / 2) + 1, string(cellWidth - 1, ' '));
                } else {
                    // Save the input value to the cell

                    if (formulaParser.isInteger(inputValue)) { // Check if the input value is an integer
                        // Create a new IntValueCell to store the integer value
                        unique_ptr<IntValueCell> intCell = make_unique<IntValueCell>();

                        // Retrieve the dependent cells and applied formulas from the current cell
                        vector<vector<int>> dependentCells = cells[row][col]->getDependentCells();
                        vector<string> appliedFormulas = cells[row][col]->getAppliedFormulas();

                        // Set the dependent cells for the new IntValueCell
                        for (int i = 0; i < dependentCells.size(); i++) {
                            intCell->setDependentCells(dependentCells[i]);
                        }
                        // Set the applied formulas for the new IntValueCell
                        intCell->setAppliedFormulas(appliedFormulas);
                        // Set the integer data for the new IntValueCell
                        intCell->setData(inputValue);
                        // Replace the current cell with the new IntValueCell
                        cells[row][col] = move(intCell);
                    } else if (formulaParser.isDouble(inputValue)) { // Check if the input value is a double
                        // Create a new DoubleValueCell to store the double value
                        unique_ptr<DoubleValueCell> doubleCell = make_unique<DoubleValueCell>();

                        // Retrieve the dependent cells and applied formulas from the current cell
                        vector<vector<int>> dependentCells = cells[row][col]->getDependentCells();
                        vector<string> appliedFormulas = cells[row][col]->getAppliedFormulas();

                        // Set the dependent cells for the new DoubleValueCell
                        for (int i = 0; i < dependentCells.size(); i++) {
                            doubleCell->setDependentCells(dependentCells[i]);
                        }
                        // Set the applied formulas for the new DoubleValueCell
                        doubleCell->setAppliedFormulas(appliedFormulas);
                        // Set the double data for the new DoubleValueCell
                        doubleCell->setData(inputValue);
                        // Replace the current cell with the new DoubleValueCell
                        cells[row][col] = move(doubleCell);
                    } else {
                        // If the input value is neither integer nor double, save it as a string
                        cell->setData(inputValue);
                    }

                    // Check if the cell has dependencies
                    if (cell->isCellHasDependent()) {
                        // Retrieve the applied formulas of the current cell
                        vector<string> appliedFormulas = cell->getAppliedFormulas();
                        int size_of_formulas = appliedFormulas.size();

                        // Loop through each applied formula
                        for (int i = 0; i < size_of_formulas; i++) {
                            // Retrieve the dependent cells for the current formula
                            vector<vector<int>> dependentCells = cell->getDependentCells();
                            // Apply the formula to the dependent cells
                            formulaParser.applyFormula(appliedFormulas[i], dependentCells[i][0], dependentCells[i][1]);

                            // Reprint all data in the table to update the display
                            for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < cols; j++) {
                                    // Get the data from each cell
                                    string cellValue = cells[i][j]->getData();
                                    // Truncate the cell value if it exceeds the maximum display length
                                    if (cellValue.size() > maxCellDisplayLength) {
                                        cellValue = cellValue.substr(0, maxCellDisplayLength);
                                    }
                                    // Calculate the row and column position for printing
                                    int cellRow = i * cellHeight + cellHeight / 2 + 1;
                                    int cellCol = j * cellWidth + cellWidth / 2 + 1;
                                    // Print the cell value in the terminal
                                    terminal.printAt(cellRow, cellCol - cellValue.size() / 2, cellValue);
                                }
                            }
                        }
                    }

                    // Convert the column number to a column name (e.g., 0 -> A, 1 -> B)
                    string colName = "";
                    int temp = col; // Store the column number in a temporary variable
                    while (temp >= 0) {
                        colName = char('A' + (temp % 26)) + colName; // Add the corresponding letter to the column name
                        temp = temp / 26 - 1; // Move to the next "digit" in the column name
                    }

                    // Clear the previous status row in the terminal
                    terminal.printAt(0, 15, string(80, ' '));
                    // Print the updated status row with the cell's coordinates and value
                    terminal.printAt(0, 15, "Cell [" + colName + to_string(row) + "]: " + inputValue);
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
        string colName = ""; 
        int temp = col; // Store the column number in a temporary variable
        while (temp >= 0) {
            // Convert the column number to a column name (e.g., 0 -> A, 1 -> B)
            colName = char('A' + (temp % 26)) + colName; // Add the corresponding letter to the column name
            temp = temp / 26 - 1; // Move to the next "digit" in the column name
        }

        // Check if the input value is not empty
        if (inputValue.length() > 0) {
            // Print the cell's coordinates (column name and row number) and the input value
            terminal.printAt(0, 15, "Cell [" + colName + to_string(row) + "]: " + inputValue);
        } else {
            // If the input value is empty, retrieve the current data from the cell
            string cellData = cells[row][col]->getData();
            // Print the cell's coordinates (column name and row number) and the cell's data
            terminal.printAt(0, 15, "Cell [" + colName + to_string(row) + "]: " + cellData);
        }


        // clear the cell then print new value
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
