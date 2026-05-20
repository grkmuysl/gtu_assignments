#include "SpreadSheet.h"

namespace spread_sheet {
    // Constructor: Initializes the spreadsheet with the given number of rows and columns.
    // Each cell is initially set as a StringValueCell.
    SpreadSheet::SpreadSheet(int rows, int cols) : rows(rows), cols(cols) {
        // Allocate memory for the 2D array of cells.
        data = make_unique<unique_ptr<unique_ptr<Cell>[]>[]>(rows);

        for (int i = 0; i < rows; i++) {
            data[i] = make_unique<unique_ptr<Cell>[]>(cols);
            for (int j = 0; j < cols; j++) {
                // Initialize each cell as a StringValueCell by default.
                data[i][j] = make_unique<StringValueCell>();
            }
        }
    }

    // Sets a specific cell at the given row and column with a new cell object.
    void SpreadSheet::setCell(int row, int col, unique_ptr<Cell> cell) {
        // Ensure the row and column indices are valid.
        if (rows >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = move(cell); // Move ownership of the new cell.
        }
    }

    // Retrieves a pointer to the cell at the specified row and column.
    Cell* SpreadSheet::getCell(int row, int col) {
        // Ensure the row and column indices are valid.
        if (rows >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col].get(); // Return a raw pointer to the cell.
        }
        return nullptr; // Return nullptr if indices are invalid.
    }

    // Sets the data for a specific cell at the given row and column.
    // Automatically determines the type of the cell (int, double, or string).
    void SpreadSheet::setData(int row, int col, const string& input) {
        // Check if the row and column indices are within bounds.
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Cell index out of range");
        }

        try {
            // If the input is an integer, create an IntValueCell.
            int intValue = stoi(input);
            data[row][col] = make_unique<IntValueCell>();
            data[row][col]->setData(input);
        } catch (...) {
            try {
                // If the input is a double, create a DoubleValueCell.
                double doubleValue = stod(input);
                data[row][col] = make_unique<DoubleValueCell>();
                data[row][col]->setData(input);
            } catch (...) {
                // If the input is neither int nor double, treat it as a string.
                data[row][col] = make_unique<StringValueCell>();
                data[row][col]->setData(input);
            }
        }
    }

    // Retrieves the data from the cell at the given row and column as a string.
    string SpreadSheet::getData(int row, int col) const {
        // Check if the row and column indices are within bounds.
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Cell index out of range");
        }

        if (data[row][col]) {
            return data[row][col]->getData(); // Return the cell's data as a string.
        } else {
            return ""; // Return an empty string if the cell is null.
        }
    }

    // Adds a new row to the spreadsheet.
    void SpreadSheet::addRow() {
        // Create a new 2D array with one additional row.
        auto newData = make_unique<unique_ptr<unique_ptr<Cell>[]>[]>(rows + 1);

        // Copy the existing rows to the new array.
        for (int i = 0; i < rows; i++) {
            newData[i] = move(data[i]);
        }

        // Initialize the new row with StringValueCells.
        newData[rows] = make_unique<unique_ptr<Cell>[]>(cols);

        data = move(newData); // Update the data array.
        ++rows; // Increment the row count.

        for (int j = 0; j < cols; j++) {
            data[rows - 1][j] = make_unique<StringValueCell>();
        }
    }

    // Adds a new column to the spreadsheet.
    void SpreadSheet::addColumn() {
        // Iterate through each row and expand it by one column.
        for (int i = 0; i < rows; i++) {
            auto newRow = make_unique<unique_ptr<Cell>[]>(cols + 1);

            // Copy the existing columns to the new row.
            for (int j = 0; j < cols; j++) {
                newRow[j] = move(data[i][j]);
            }

            data[i] = move(newRow); // Update the row in the data array.
        }
        ++cols; // Increment the column count.

        // Initialize the new column with StringValueCells.
        for (int i = 0; i < rows; i++) {
            data[i][cols - 1] = make_unique<StringValueCell>();
        }
    }

    // Retrieves a reference to the entire 2D array of cells.
    unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& SpreadSheet::getAllCells() {
        return data;
    }
}
