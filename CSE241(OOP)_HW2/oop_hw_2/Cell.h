#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
using namespace std;

// The Cell class is an abstract base class that represents a cell in a spreadsheet or table.
// It defines the interface (pure virtual functions) that derived classes must implement.
class Cell {
public:

    // Sets the data for the cell.
    // The actual implementation will depend on the derived class.
    virtual void setData(const string& data) = 0;

    // Gets the data stored in the cell.
    // Returns the data as a string.
    virtual string getData() const = 0;

    // Checks if the cell has dependent cells.
    // Returns true if there are dependent cells, false otherwise.
    virtual bool isCellHasDependent() const = 0;

    // Sets the formula applied to this cell.
    virtual void setAppliedFormula(const string& appliedFormula) = 0;

    // Sets the dependent cells for this cell.
    // Dependencies are represented as a vector of integers (e.g., row/column indices).
    virtual void setDependentCells(const vector<int> dependicies) = 0;

    // Sets multiple formulas applied to this cell.
    virtual void setAppliedFormulas(vector<string> appliedFormulas) = 0;

    // Retrieves the list of formulas applied to this cell.
    // Returns a reference to a vector of strings.
    virtual vector<string>& getAppliedFormulas() = 0;

    // Retrieves the dependent cells for this cell.
    // Returns a reference to a 2D vector of integers.
    virtual vector<vector<int>>& getDependentCells() = 0;

    // Virtual destructor for the Cell class.
    // Ensures proper cleanup when a derived class object is deleted via a base class pointer.
    virtual ~Cell();
};

#endif
