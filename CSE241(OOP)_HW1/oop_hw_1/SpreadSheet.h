#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <iostream>
#include <string>
#include "Cell.h"
#include <vector>
#include "FormulaParser.h"
#include "FileManager.h"
#include <fstream>

using namespace std;

// The SpreadSheet class manages a 2D grid of cells, allowing operations like adding rows,
// adding columns, retrieving cells, and interacting with the FormulaParser and FileManager.
class SpreadSheet {
private:
    vector<vector<Cell>> cells;      // 2D grid of Cell objects representing the spreadsheet
    FormulaParser formulaParser;    // FormulaParser instance for handling formulas
    FileManager fileManager;        // FileManager instance for saving/loading files

public:
    // Constructor initializes the spreadsheet with the given rows and columns
    SpreadSheet(int initial_row, int initial_col);

    // Returns the Cell at the specified row and column
    Cell getCell(int row, int col);

    // Checks if the given string input contains only digits
    bool isDigit(const string& input);

    // Returns a reference to the entire grid of cells
    vector<vector<Cell>>& getAllCels();

    // Adds a new column to the spreadsheet
    void addColumn();

    // Adds a new row with a specified number of columns
    void addRow(const int cols);
};

#endif
