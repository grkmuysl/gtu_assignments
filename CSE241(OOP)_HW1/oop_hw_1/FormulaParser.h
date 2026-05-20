#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Cell.h"
#include <cmath>
using namespace std;

// The FormulaParser class processes formulas in spreadsheet cells,
// including parsing, converting, and applying formulas to the grid of cells.
class FormulaParser {
private:
    vector<vector<Cell>>& cells; // Reference to the spreadsheet cells

public:
    // Constructor
    FormulaParser(vector<vector<Cell>>& sheetCells);

    // Extracts operators (+, -, *, /) from a formula
    vector<char> getOperatorsFromFormula(const string& formula);

    // Extracts cell references (e.g., A1, B2) from a formula
    vector<string> getCellsFromFormula(const string& formula);

    // Applies a formula to a specific cell
    void applyFormula(const string& formula, int current_row, int current_col);

    // Determines the column index from a cell reference (e.g., A1 -> 0)
    int find_column_index(const string& inp);

    // Determines the row index from a cell reference (e.g., A1 -> 0)
    int find_row_index(const string& inp);

    // Converts SUM formulas to expanded formats (e.g., SUM(A1..A3) -> A1+A2+A3)
    string formulaConverterForSum(string& formula);

    // Converts AVER formulas to their computed values
    string formulaConverterForAver(string& formula);

    // Converts MAX formulas to their computed maximum value
    string formulaConverterForMax(string& formula);

    // Converts MIN formulas to their computed minimum value
    string formulaConverterForMin(string& formula);

    // Converts STDDEV formulas to their computed standard deviation value
    string formulaConverterForSDTDEV(string& formula);
};

#endif
