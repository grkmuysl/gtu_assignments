#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <memory>
#include <string>
#include "Cell.h"
#include "IntValueCell.h"
#include "StringValueCell.h"
#include "DoubleValueCell.h"
#include "FormulaCell.h"

using namespace std;

namespace spread_sheet {
    // The SpreadSheet class represents a 2D grid of cells.
    // It supports dynamic resizing and allows cells to store different types of data.
    class SpreadSheet {
    private:
        int rows, cols; // Number of rows and columns in the spreadsheet.
        unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]> data; // 2D array of cells.

    public:
        // Constructor: Initializes the spreadsheet with the given number of rows and columns.
        SpreadSheet(int rows, int cols);

        // Sets a specific cell at the given row and column.
        void setCell(int row, int col, unique_ptr<Cell> cell);

        // Retrieves a pointer to the cell at the specified row and column.
        Cell* getCell(int row, int col);

        // Sets the data for a specific cell.
        void setData(int row, int col, const string& input);

        // Retrieves the data from a specific cell as a string.
        string getData(int row, int col) const;

        // Adds a new column to the spreadsheet.
        void addColumn();

        // Adds a new row to the spreadsheet.
        void addRow();

        // Retrieves a reference to the entire 2D array of cells.
        unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& getAllCells();

        // Default destructor.
        ~SpreadSheet() = default;
    };
}

#endif
