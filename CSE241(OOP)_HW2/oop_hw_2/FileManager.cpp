#include "FileManager.h"

namespace file_manager {
    // Constructor initializes the FileManager with the provided spreadsheet cells
    // Takes a reference to a 2D array of unique_ptr<Cell>, along with the number of rows and columns.
    FileManager::FileManager(unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& sheetCells, int row, int col) 
                : cells(sheetCells), maxRow(row), maxCol(col) {}

    // Saves the spreadsheet data to a CSV file.
    // Each cell's data is written to the file, separated by commas, with rows on separate lines.
    void FileManager::saveToFile(const string& fileName) {
        ofstream outputFile(fileName); // Open the file for writing
        if (!outputFile.is_open()) { // Check if the file was opened successfully
            cerr << "File could not open." << endl;
            return; // Exit the function if the file cannot be opened
        }

        int maxRows = maxRow; // Total number of rows
        int maxCols = maxCol; // Total number of columns

        // Iterate through each row and column of the spreadsheet
        for (int row = 0; row < maxRows; ++row) {
            for (int col = 0; col < maxCols; ++col) {
                if (col > 0) {
                    outputFile << ","; // Add a comma as a separator between columns
                }

                // Retrieve the data from the cell and write it to the file
                string value = cells[row][col]->getData();
                if (!value.empty()) { // Only write non-empty values
                    outputFile << value;
                }
            }
            outputFile << endl; // Move to the next row in the file
        }

        outputFile.close(); // Close the file after writing
    }

    // Loads spreadsheet data from a CSV file.
    // Each line in the file corresponds to a row, with cell values separated by commas.
    void FileManager::loadFromFile(const string& fileName) {
        ifstream inputFile(fileName); // Open the file for reading

        if (!inputFile.is_open()) { // Check if the file was opened successfully
            cerr << "File could not open." << endl;
            return; // Exit the function if the file cannot be opened
        }

        string line; // Stores each line of the file
        int row_index = 0; // Tracks the current row being processed

        // Read the file line by line
        while (getline(inputFile, line)) {
            size_t start = 0; // Start position of the current cell value
            size_t end = line.find(','); // Find the position of the first comma
            int col_index = 0; // Tracks the current column being processed

            // Process each value in the row, separated by commas
            while (end != string::npos) {
                string cellValue = line.substr(start, end - start); // Extract the cell value

                // Set the value for the current cell
                cells[row_index][col_index]->setData(cellValue);

                start = end + 1; // Move to the next value
                end = line.find(',', start); // Find the next comma
                col_index++; // Move to the next column
            }

            // Handle the last cell in the row (no trailing comma)
            string cellValue = line.substr(start);
            cells[row_index][col_index]->setData(cellValue);

            row_index++; // Move to the next row
        }

        inputFile.close(); // Close the file after reading
    }
}
