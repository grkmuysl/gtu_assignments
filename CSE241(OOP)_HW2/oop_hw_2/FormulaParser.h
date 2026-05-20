#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Cell.h"
#include <cmath>
using namespace std;

namespace formula_parser {

    // The FormulaParser class is responsible for parsing, converting, 
    // and applying formulas in a spreadsheet. It processes formulas 
    // such as SUM, AVER, MAX, MIN, and STDDEV, and evaluates them based 
    // on the data in the spreadsheet cells.
    class FormulaParser {
    private:
        // Reference to the grid of spreadsheet cells
        unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]> &cells;

        // Tracks whether the result of a formula is a double value
        bool isResultDouble = false;
        
    public:
        // Constructor
        // Initializes the FormulaParser with a reference to the spreadsheet cells.
        FormulaParser(unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& sheetCells);

        // Extracts operators (+, -, *, /) from a formula string.
        // Example: For "A1+B2-C3", it returns ['+', '-'].
        vector<char> getOperatorsFromFormula(const string& formula);

        // Extracts cell references (e.g., A1, B2) from a formula string.
        // Example: For "A1+B2-C3", it returns ["A1", "B2", "C3"].
        vector<string> getCellsFromFormula(const string& formula);

        // Applies a formula to a specific cell in the spreadsheet.
        // The formula is evaluated, and the result is stored in the given cell.
        void applyFormula(const string& formula, int current_row, int current_col);

        // Determines the column index from a cell reference.
        // Example: For "A1", it returns 0 (column A).
        int find_column_index(const string& inp);

        // Determines the row index from a cell reference.
        // Example: For "A1", it returns 0 (row 1).
        int find_row_index(const string& inp);

        // Converts SUM formulas into expanded formats.
        // Example: SUM(A1..A3) -> A1+A2+A3.
        string formulaConverterForSum(string& formula);

        // Converts AVER formulas into their computed values.
        // Example: AVER(A1..A3) -> the average of A1, A2, and A3.
        string formulaConverterForAver(string& formula);

        // Converts MAX formulas into their computed maximum value.
        // Example: MAX(A1..A3) -> the maximum value from A1, A2, and A3.
        string formulaConverterForMax(string& formula);

        // Converts MIN formulas into their computed minimum value.
        // Example: MIN(A1..A3) -> the minimum value from A1, A2, and A3.
        string formulaConverterForMin(string& formula);

        // Converts STDDEV formulas into their computed standard deviation value.
        // Example: STDDEV(A1..A3) -> the standard deviation of A1, A2, and A3.
        string formulaConverterForSDTDEV(string& formula);

        // Checks if the formula contains references to cells with double values.
        bool isContainsDoubleCell(string& formula);

        // Sets whether the result of the formula is a double value.
        void setIsResultDouble(bool state);

        // Retrieves whether the result of the formula is a double value.
        bool getIsResultDouble();

        // Helper function to check if a string represents an integer
        bool isInteger(const std::string& str);
        // Helper function to check if a string represents a double (floating-point number)
        bool isDouble(const std::string& str);
    };
}

#endif
