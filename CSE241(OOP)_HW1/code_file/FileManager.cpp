#include "FileManager.h"
#include "Cell.h"

// Constructor initializes the FileManager with the provided spreadsheet cells
FileManager::FileManager(vector<vector<Cell>>& sheetCells) : cells(sheetCells) {}

// Saves the spreadsheet to a CSV file
void FileManager::saveToFile(const string& fileName) {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "File could not open." << endl;
        return; // Exit if file cannot be opened
    }

    size_t maxRows = cells.size(); // Total number of rows
    size_t maxCols = 0;

    // Determine the maximum number of columns in any row
    for (const auto& row : cells) {
        maxCols = max(maxCols, row.size());
    }

    // Process each row and column, writing data to the CSV file
    for (size_t row = 0; row < maxRows; ++row) {
        for (size_t col = 0; col < maxCols; ++col) {
            if (col > 0) {
                outputFile << ","; // Add a comma between columns
            }

            // Write the cell value if it exists; otherwise, leave it blank
            if (row < cells.size() && col < cells[row].size()) {
                string value = cells[row][col].getString_Value();
                if (!value.empty()) {
                    outputFile << value;
                }
            }
        }
        outputFile << endl; // Move to the next row
    }

    outputFile.close(); // Close the file after writing
}

// Loads spreadsheet data from a CSV file
void FileManager::loadFromFile(const string& fileName) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << "File could not open." << endl;
        return; // Exit if file cannot be opened
    }

    string line;
    int row_index = 0;

    // Read the file line by line
    while (getline(inputFile, line)) {
        size_t start = 0;
        size_t end = line.find(','); // Find the first comma
        int col_index = 0;

        // Process each value in the row, separated by commas
        while (end != string::npos) {
            string cellValue = line.substr(start, end - start); // Extract the cell value

            // Resize cells vector if necessary
            if (row_index >= cells.size()) {
                cells.resize(row_index + 1);
            }
            if (col_index >= cells[row_index].size()) {
                cells[row_index].resize(col_index + 1);
            }

            // Set the value for the current cell
            cells[row_index][col_index].setString_Value(cellValue);

            start = end + 1; // Move to the next value
            end = line.find(',', start); // Find the next comma
            col_index++;
        }

        // Handle the last cell in the row (no trailing comma)
        string cellValue = line.substr(start);
        if (row_index >= cells.size()) {
            cells.resize(row_index + 1);
        }
        if (col_index >= cells[row_index].size()) {
            cells[row_index].resize(col_index + 1);
        }
        cells[row_index][col_index].setString_Value(cellValue);

        row_index++; // Move to the next row
    }

    inputFile.close(); // Close the file after reading
}
