#ifndef DOUBLEVALUECELL_H
#define DOUBLEVALUECELL_H

#include "ValueCell.h"
#include <stdexcept>

// DoubleValueCell is a derived class of ValueCell that stores and manages double values.
// It also tracks dependent cells and applied formulas.
class DoubleValueCell : public ValueCell {
private:
    double value = 0.0; // Stores the numeric value of the cell

    string formula; // Stores a formula applied to the cell
    vector<vector<int>> dependentCells; // Stores dependent cells (e.g., row/column indices)
    vector<string> appliedFormulas; // Stores the list of formulas applied to the cell

public:
    // Sets the data for the cell by converting a string to a double.
    void setData(const string& data) override;

    // Retrieves the data stored in the cell as a string.
    string getData() const override;

    // Retrieves the data stored in the cell as a double.
    double getDoubleData() const;

    // Checks if the cell has any dependent cells or applied formulas.
    // Returns true if there are dependent cells or formulas, false otherwise.
    bool isCellHasDependent() const override;

    // Adds a single formula to the list of applied formulas for this cell.
    void setAppliedFormula(const string& appliedFormula) override;

    // Adds multiple formulas to the list of applied formulas for this cell.
    void setAppliedFormulas(vector<string> appliedFormulas) override;

    // Adds a set of dependent cells to this cell.
    // Dependencies are represented as a vector of integers.
    void setDependentCells(const vector<int> dependicies) override;

    // Retrieves the list of applied formulas for this cell.
    // Returns a reference to the vector of formulas.
    vector<string>& getAppliedFormulas() override;

    // Retrieves the list of dependent cells for this cell.
    // Returns a reference to the 2D vector of dependencies.
    vector<vector<int>>& getDependentCells() override;
};

#endif
