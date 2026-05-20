#include "SpreadSheet.h"

// Constructor initializes the spreadsheet with the specified rows and columns,
// and sets up FormulaParser and FileManager with the cells grid
SpreadSheet::SpreadSheet(int initial_row, int initial_col)
    : cells(initial_row, vector<Cell>(initial_col)),
      formulaParser(cells), fileManager(cells) {}

// Checks if the given string input contains only numeric digits
bool SpreadSheet::isDigit(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) return false; // Return false if any character is not a digit
    }
    return true; // Return true if all characters are digits
}

// Returns the Cell object at the specified row and column
Cell SpreadSheet::getCell(int row, int col) {
    return cells[row][col];
}

// Returns a reference to the entire grid of cells
vector<vector<Cell>>& SpreadSheet::getAllCels() {
    return cells;
}

// Adds a new column to the spreadsheet by appending a new Cell to each row
void SpreadSheet::addColumn() {
    for (auto& row : cells) {
        row.push_back(Cell()); // Add a new Cell to the end of the row
    }
}

// Adds a new row to the spreadsheet, initializing it with a specified number of columns
void SpreadSheet::addRow(const int cols) {
    vector<Cell> newRow(cols, Cell()); // Create a new row filled with empty Cells
    cells.push_back(newRow);          // Append the new row to the spreadsheet
}
