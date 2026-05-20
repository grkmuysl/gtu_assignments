#include "StringValueCell.h"

// Sets the string data for the cell.
void StringValueCell::setData(const string& data) {
    value = data; // Store the input string in the value variable.
}

// Retrieves the string data from the cell.
string StringValueCell::getData() const {
    if (value.size() > 0) {
        return value; // Return the value if it is not empty.
    } else {
        return ""; // Return an empty string if the value is empty.
    }
}

// Checks if the cell has any dependencies or applied formulas.
bool StringValueCell::isCellHasDependent() const {
    // Returns true if either dependent cells or applied formulas exist.
    return !dependentCells.empty() || !appliedFormulas.empty();
}

// Adds a single formula that has been applied to this cell.
void StringValueCell::setAppliedFormula(const string& appliedFormula) {
    appliedFormulas.push_back(appliedFormula); // Add the formula to the appliedFormulas list.
}

// Adds multiple formulas that have been applied to this cell.
void StringValueCell::setAppliedFormulas(vector<string> appliedFormulas) {
    for (int i = 0; i < appliedFormulas.size(); i++) {
        string formula = appliedFormulas[i];
        this->appliedFormulas.push_back(formula); // Add each formula to the appliedFormulas list.
    }
}

// Adds a dependency for this cell.
void StringValueCell::setDependentCells(const vector<int> dependicies) {
    dependentCells.push_back(dependicies); // Add the dependency to the dependentCells list.
}

// Retrieves the list of formulas applied to this cell.
vector<string>& StringValueCell::getAppliedFormulas() {
    return appliedFormulas; // Return the appliedFormulas list.
}

// Retrieves the list of dependent cells for this cell.
vector<vector<int>>& StringValueCell::getDependentCells() {
    return dependentCells; // Return the dependentCells list.
}
