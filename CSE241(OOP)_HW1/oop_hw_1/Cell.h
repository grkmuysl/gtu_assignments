#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>
using namespace std;

// The Cell class represents a cell that can store string values, numeric values,
// formulas, and manage dependencies with other cells.
class Cell {
public:
    // Default constructor
    Cell();

    // Returns the string value stored in the cell
    string getString_Value() const;

    // Returns the numeric value stored in the cell
    double getNumber_Value();

    // Sets the string value of the cell
    void setString_Value(const string& newValue);

    // Sets the numeric value of the cell by converting a string input
    void setNumber_Value(const string& newValue);

    // Checks if the cell contains a formula
    bool isFormula();

    // Determines if the given string contains only digits
    bool isDigit(const string& input);

    // Sets the dependent cells of this cell
    void setDependentCells(const vector<int> dependicies);

    // Sets the formula applied to the cell
    void setAppliedFormula(const string& appliedFormula);

    // Checks if the cell has dependent cells
    bool isCellHasDependent();

    // Returns a reference to the list of applied formulas
    vector<string>& getAppliedFormulas();

    // Returns a reference to the dependent cells list
    vector<vector<int>>& getDependentCells();

private:
    string string_value;               // Stores the string value of the cell
    double number_value;               // Stores the numeric value of the cell
    string formula;                    // Stores the formula applied to the cell
    vector<vector<int>> dependentCells; // Stores the list of dependent cells
    vector<string> appliedFormulas;    // Stores applied formulas for dependencies
};

#endif
