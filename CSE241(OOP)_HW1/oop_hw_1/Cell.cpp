#include "Cell.h"
#include <iostream>
#include <string>
#include <cmath>

// Constructor initializes the numeric value to 0
Cell::Cell() {
    number_value = 0;
}

// Returns the string value of the cell
string Cell::getString_Value() const {
    return string_value;
}

// Returns the numeric value of the cell
// Converts string value to a double if it contains digits
// Rounds the value to two decimal places
double Cell::getNumber_Value() {
    if (string_value.empty()) {
        return 0; // Default to 0 if string is empty
    }

    if (isDigit(string_value)) {
        number_value = stod(string_value);
        return round(number_value * 100) / 100; // Rounds to two decimal places
    }
    return 0; // Return 0 if the string is not numeric
}

// Sets the string value of the cell
// Checks if the new value is a formula (starts with '=')
void Cell::setString_Value(const string& newValue) {
    if (newValue.size() > 0 && newValue[0] == '=') {
        formula = newValue; // Store as a formula
    } else {
        string_value = newValue; // Store as a regular string value
    }
}

// Sets the numeric value of the cell
// Converts string input to double if it's not a formula
void Cell::setNumber_Value(const string& newValue) {
    if (newValue.size() > 0 && newValue[0] == '=') {
        formula = newValue; // Store as a formula
    } else {
        // Attempt to convert string to double
        if (isDigit(newValue)) {
            number_value = stod(newValue);
        } else {
            number_value = 0; // Default to 0 for invalid input
        }
    }
}

// Checks if the cell contains a formula (starts with '=')
bool Cell::isFormula() {
    return string_value.size() > 0 && string_value[0] == '=';
}

// Checks if the input string contains only digits
bool Cell::isDigit(const string& input) {
    size_t start = 0;
    if (input[start] == '-') { // Negatif işaret kontrolü
        start++;
    }
    for (size_t i = start; i < input.size(); ++i) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

// Adds a set of dependent cell indices to the cell
void Cell::setDependentCells(const vector<int> dependicies) {
    dependentCells.push_back(dependicies);
}

// Adds a formula to the applied formulas list
void Cell::setAppliedFormula(const string& appliedFormula) {
    appliedFormulas.push_back(appliedFormula);
}

// Checks if the cell has any dependent cells or applied formulas
bool Cell::isCellHasDependent() {
    return !dependentCells.empty() || !appliedFormulas.empty();
}

// Returns a reference to the list of applied formulas
vector<string>& Cell::getAppliedFormulas() {
    return appliedFormulas;
}

// Returns a reference to the list of dependent cells
vector<vector<int>>& Cell::getDependentCells() {
    return dependentCells;
}
