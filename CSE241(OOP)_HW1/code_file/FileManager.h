#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Cell.h"
#include <fstream>

// The FileManager class handles file operations, including saving and loading
// a spreadsheet represented by a 2D vector of Cell objects.
class FileManager {
private:
    vector<vector<Cell>>& cells; // Reference to the spreadsheet cells

public:
    // Constructor initializes the FileManager with a reference to the spreadsheet cells
    FileManager(vector<vector<Cell>>& sheetCells);

    // Saves the current state of the spreadsheet to a CSV file
    void saveToFile(const string& fileName);

    // Loads spreadsheet data from a CSV file into the cells
    void loadFromFile(const string& fileName);
};

#endif
