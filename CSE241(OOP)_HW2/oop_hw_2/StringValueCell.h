#ifndef STRINGVALUECELL_H
#define STRINGVALUECELL_H

#include <string>
#include "ValueCell.h"
using namespace std;

// The StringValueCell class represents a cell that stores string data.
// It also tracks dependencies and applied formulas for the cell.
class StringValueCell : public ValueCell {
private:
    string value; // The string value stored in the cell.
    string formula; // The formula applied to the cell (if any).
    vector<vector<int>> dependentCells; // Stores the list of dependent cells (row and column indices).
    vector<string> appliedFormulas; // Stores the list of applied formulas for the cell.

public:
    // Sets the string data for the cell.
    void setData(const string& data) override;

    // Retrieves the string data from the cell.
    string getData() const override;

    // Dependency management methods:

    // Checks if the cell has any dependencies or applied formulas.
    bool isCellHasDependent() const override;

    // Adds a single formula applied to this cell.
    void setAppliedFormula(const string& appliedFormula) override;

    // Adds multiple formulas applied to this cell.
    void setAppliedFormulas(vector<string> appliedFormulas) override;

    // Adds a dependency for this cell.
    void setDependentCells(const vector<int> dependicies) override;

    // Retrieves the list of formulas applied to this cell.
    vector<string>& getAppliedFormulas() override;

    // Retrieves the list of dependent cells for this cell.
    vector<vector<int>>& getDependentCells() override;
};

#endif
