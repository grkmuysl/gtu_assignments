#include "DoubleValueCell.h"
#include <stdexcept>

// Sets the data for the cell by converting a string to a double.
// Throws an exception if the string cannot be converted to a valid double.
void DoubleValueCell::setData(const string& data) {
    try {
        value = stod(data); // Convert string to double
    } catch (...) { // Catch any exception
        throw invalid_argument("Invalid double value");
    }
}

// Retrieves the data stored in the cell as a string.
string DoubleValueCell::getData() const {
    return to_string(value); // Convert double to string
}

// Retrieves the data stored in the cell as a double.
double DoubleValueCell::getDoubleData() const {
    return value;
}

// Checks if the cell has any dependent cells or applied formulas.
// Returns true if there are dependent cells or formulas, false otherwise.
bool DoubleValueCell::isCellHasDependent() const {
    return !dependentCells.empty() || !appliedFormulas.empty();
}

// Adds a single formula to the list of applied formulas for this cell.
void DoubleValueCell::setAppliedFormula(const string& appliedFormula) {
    appliedFormulas.push_back(appliedFormula);
}

// Adds multiple formulas to the list of applied formulas for this cell.
void DoubleValueCell::setAppliedFormulas(vector<string> appliedFormulas) {
    for (int i = 0; i < appliedFormulas.size(); i++) {
        string formula = appliedFormulas[i];
        this->appliedFormulas.push_back(formula); // Add each formula to the list
    }
}

// Adds a set of dependent cells to this cell.
// Dependencies are represented as a vector of integers.
void DoubleValueCell::setDependentCells(const vector<int> dependicies) {
    dependentCells.push_back(dependicies);
}

// Retrieves the list of applied formulas for this cell.
// Returns a reference to the vector of formulas.
vector<string>& DoubleValueCell::getAppliedFormulas() {
    return appliedFormulas;
}

// Retrieves the list of dependent cells for this cell.
// Returns a reference to the 2D vector of dependencies.
vector<vector<int>>& DoubleValueCell::getDependentCells() {
    return dependentCells;
}
