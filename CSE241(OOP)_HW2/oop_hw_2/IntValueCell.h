#ifndef INTVALUECELL_H
#define INTVALUECELL_H

#include <string>
#include <vector>
#include "ValueCell.h"
using namespace std;

// The IntValueCell class represents a cell that stores an integer value.
// It also tracks dependencies and formulas applied to the cell.
class IntValueCell : public ValueCell {
private:
    int value = 0; // The integer value stored in the cell.
    
    string formula; // The formula applied to the cell (if any).
    vector<vector<int>> dependentCells; // List of dependent cells (row and column indices).
    vector<string> appliedFormulas; // List of formulas applied to this cell.

public:
    // Sets the data for the cell as a string (converted to an integer).
    void setData(const string& data) override;

    // Retrieves the data in the cell as a string.
    string getData() const override;

    // Retrieves the data in the cell as an integer.
    int getIntData() const;

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
