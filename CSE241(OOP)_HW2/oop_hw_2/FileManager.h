#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Cell.h"
#include <fstream>
#include <memory>

namespace file_manager {
    // The FileManager class is responsible for saving and loading spreadsheet data to/from files.
    // It operates on a 2D array of unique_ptr<Cell> objects, representing the spreadsheet.
    class FileManager {
    private:
        // Reference to a 2D array of unique_ptr<Cell>, representing the spreadsheet cells.
        unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& cells;

        int maxRow; // Maximum number of rows in the spreadsheet
        int maxCol; // Maximum number of columns in the spreadsheet

    public:
        // Constructor: Initializes the FileManager with the spreadsheet cells and their dimensions.
        FileManager(unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& sheetCells, int row, int col);

        // Saves the spreadsheet data to a CSV file.
        // Each row of the spreadsheet is written as a line in the file, with cell values separated by commas.
        void saveToFile(const string& fileName);

        // Loads spreadsheet data from a CSV file.
        // Each line in the file corresponds to a row, with cell values separated by commas.
        void loadFromFile(const string& fileName);
    };
}

#endif
