#include "IntValueCell.h"
#include <stdexcept>

// Sets the data for the cell by converting a string to an integer.
void IntValueCell::setData(const string& data) {
    try {
        value = stoi(data); // Convert string to integer.
    } catch (...) {
        // Throw an exception if the string cannot be converted to an integer.
        throw invalid_argument("Invalid integer value");
    }
}

// Retrieves the data in the cell as a string.
string IntValueCell::getData() const {
    return to_string(value); // Convert the integer value to a string.
}

// Retrieves the data in the cell as an integer.
int IntValueCell::getIntData() const {
    return value; // Return the integer value.
}

// Checks if the cell has any dependencies or applied formulas.
bool IntValueCell::isCellHasDependent() const {
    // Returns true if there are dependent cells or applied formulas.
    return !dependentCells.empty() || !appliedFormulas.empty();
}

// Adds a formula that has been applied to this cell.
void IntValueCell::setAppliedFormula(const string& appliedFormula) {
    appliedFormulas.push_back(appliedFormula); // Add the formula to the list.
}

// Sets multiple applied formulas for this cell.
void IntValueCell::setAppliedFormulas(vector<string> appliedFormulas) {
    for (int i = 0; i < appliedFormulas.size(); i++) {
        string formula = appliedFormulas[i];
        this->appliedFormulas.push_back(formula); // Add each formula to the list.
    }
}

// Adds a dependency for this cell.
void IntValueCell::setDependentCells(const vector<int> dependicies) {
    dependentCells.push_back(dependicies); // Add the dependency to the list.
}

// Retrieves the list of formulas applied to this cell.
vector<string>& IntValueCell::getAppliedFormulas() {
    return appliedFormulas; // Return the list of applied formulas.
}

// Retrieves the list of dependent cells for this cell.
vector<vector<int>>& IntValueCell::getDependentCells() {
    return dependentCells; // Return the list of dependent cells.
}
