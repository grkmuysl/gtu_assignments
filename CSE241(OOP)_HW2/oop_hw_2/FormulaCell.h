#ifndef FORMULACELL_H
#define FORMULACELL_H

#include <string>
#include <vector>
#include <stdexcept>
#include "Cell.h"
using namespace std;

// Template class for a FormulaCell that stores and manages formulas and their computed values.
// This class inherits from the Cell base class and supports generic types (e.g., int, double).
template <typename T>
class FormulaCell : public Cell {
private:
    T value; // The computed value of the formula
    string formula; // The formula string
    vector<vector<int>> dependentCells; // List of dependent cells (row and column indices)
    vector<string> appliedFormulas; // List of formulas applied to the cell

public:
    // Sets the data in the cell by converting a string to the appropriate type (int or double).
    void setData(const string& data) override {
        try {
            if (typeid(T) == typeid(int)) {
                value = static_cast<T>(stoi(data, nullptr, 10)); // Convert string to int
            } else if (typeid(T) == typeid(double)) {
                value = static_cast<T>(stod(data)); // Convert string to double
            } else {
                throw invalid_argument("Unsupported type");
            }
        } catch (const invalid_argument& e) {
            throw invalid_argument("Invalid value for the specified type: " + string(e.what()));
        } catch (...) {
            throw invalid_argument("Invalid value for the specified type");
        }
    }

    // Retrieves the data stored in the cell as a string.
    string getData() const override {
        if (typeid(T) == typeid(int)) {
            return to_string(static_cast<int>(value));
        } else if (typeid(T) == typeid(double)) {
            return to_string(static_cast<double>(value));
        } else {
            throw invalid_argument("Unsupported type");
        }
    }

    // Retrieves the data stored in the cell as its original type (e.g., int or double).
    T getDataAsType() const {
        return value;
    }

    // Sets the formula for the cell.
    void setFormula(const string& inputFormula) {
        formula = inputFormula;
    }

    // Retrieves the formula for the cell.
    string getFormula() const {
        return formula;
    }

    // Checks if the cell has any dependent cells or applied formulas.
    bool isCellHasDependent() const override {
        return !dependentCells.empty() || !appliedFormulas.empty();
    }

    // Adds a single formula to the list of applied formulas for this cell.
    void setAppliedFormula(const string& appliedFormula) override {
        appliedFormulas.push_back(appliedFormula);
    }

    // Sets multiple applied formulas for this cell.
    void setAppliedFormulas(vector<string> appliedFormulas) override {
        this->appliedFormulas = appliedFormulas;
    }

    // Adds a set of dependent cells to this cell.
    void setDependentCells(const vector<int> dependencies) override {
        dependentCells.push_back(dependencies);
    }

    // Retrieves the list of applied formulas for this cell.
    vector<string>& getAppliedFormulas() override {
        return appliedFormulas;
    }

    // Retrieves the list of dependent cells for this cell.
    vector<vector<int>>& getDependentCells() override {
        return dependentCells;
    }
};

#endif
