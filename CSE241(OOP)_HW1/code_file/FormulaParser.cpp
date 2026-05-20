#include "FormulaParser.h"
#include "Cell.h"

// Constructor initializes the FormulaParser with a reference to the spreadsheet cells
FormulaParser::FormulaParser(vector<vector<Cell>>& sheetCells) : cells(sheetCells) {}

// Extracts operators from the formula (e.g., +, -, *, /)
vector<char> FormulaParser::getOperatorsFromFormula(const string& formula) {
    vector<char> operatorsInFormula;
    for (char c : formula) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            operatorsInFormula.push_back(c);
        }
    }
    return operatorsInFormula;
}

// Extracts cell references (e.g., A1, B4) from the formula
vector<string> FormulaParser::getCellsFromFormula(const string& formula) {
    vector<string> cellsInFormula;
    regex re(R"([\+\-\*/])");
    sregex_token_iterator it(formula.begin(), formula.end(), re, -1);
    sregex_token_iterator end;

    while (it != end) {
        cellsInFormula.push_back(*it++);
    }
    return cellsInFormula;
}

// Finds the column index from a cell reference (e.g., A1 -> 0)
int FormulaParser::find_column_index(const string& inp) {
    char cell_address = inp[0];
    return static_cast<int>(cell_address) - 65; // Convert 'A' to 0
}

// Finds the row index from a cell reference (e.g., A1 -> 0)
int FormulaParser::find_row_index(const string& inp) {
    return stoi(inp.substr(1)); // Extract the numeric part of the cell reference
}

// Applies the given formula to a specific cell
void FormulaParser::applyFormula(const string& formula, int current_row, int current_col) {
    vector<string> cellsInFormula = getCellsFromFormula(formula);
    vector<char> operatorsInFormula = getOperatorsFromFormula(formula);

    vector<int> dependency = {current_row, current_col}; // Dependency tracking
    double result;

    // Process the first operand
    if (isalpha(cellsInFormula[0][0])) {
        int row = find_row_index(cellsInFormula[0]);
        int col = find_column_index(cellsInFormula[0]);
        result = cells[row][col].getNumber_Value();
        cells[row][col].setDependentCells(dependency);
        cells[row][col].setAppliedFormula(formula);
    } else {
        result = stod(cellsInFormula[0]); // Process numeric values, including negatives
    }

    // Process the remaining operators and operands
    for (size_t i = 0; i < operatorsInFormula.size(); ++i) {
        double operandValue;
        if (isalpha(cellsInFormula[i + 1][0])) {
            int row = find_row_index(cellsInFormula[i + 1]);
            int col = find_column_index(cellsInFormula[i + 1]);
            operandValue = cells[row][col].getNumber_Value();
            cells[row][col].setDependentCells(dependency);
            cells[row][col].setAppliedFormula(formula);
        } else {
            operandValue = stod(cellsInFormula[i + 1]);
        }

        // Apply the operator
        switch (operatorsInFormula[i]) {
            case '+': result += operandValue; break;
            case '-': result -= operandValue; break;
            case '*': result *= operandValue; break;
            case '/': result /= operandValue; break;
        }
    }

    // Store the result in the target cell
    cells[current_row][current_col].setString_Value(to_string(result));
}

// Converts SUM formulas (e.g., SUM(A1..A3) -> A1+A2+A3)
string FormulaParser::formulaConverterForSum(string& formula) {
    size_t sumPos = formula.find("SUM(");
    while (sumPos != string::npos) {
        size_t rangeStart = sumPos + 4;
        size_t rangeEnd = formula.find("..", rangeStart);
        if (rangeEnd == string::npos) break;
        size_t closeParen = formula.find(")", rangeEnd);
        if (closeParen == string::npos) break;

        string startCell = formula.substr(rangeStart, rangeEnd - rangeStart);
        string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2);

        char startCol = startCell[0];
        int startRow = stoi(startCell.substr(1));
        char endCol = endCell[0];
        int endRow = stoi(endCell.substr(1));

        string expandedRange = "";
        for (char col = startCol; col <= endCol; ++col) {
            for (int row = startRow; row <= endRow; ++row) {
                if (!expandedRange.empty()) {
                    expandedRange += "+";
                }
                expandedRange += col + to_string(row);
            }
        }

        formula.replace(sumPos, closeParen - sumPos + 1, expandedRange);
        sumPos = formula.find("SUM(", sumPos + expandedRange.size());
    }
    return formula;
}

// Converts AVER formulas (e.g., AVER(A1..A3) -> calculated average value)
string FormulaParser::formulaConverterForAver(string& formula) {
    size_t averPos = formula.find("AVER(");
    while (averPos != string::npos) {
        size_t rangeStart = averPos + 5;
        size_t rangeEnd = formula.find("..", rangeStart);
        if (rangeEnd == string::npos) break;
        size_t closeParen = formula.find(")", rangeEnd);
        if (closeParen == string::npos) break;

        string startCell = formula.substr(rangeStart, rangeEnd - rangeStart);
        string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2);

        char startCol = startCell[0];
        int startRow = stoi(startCell.substr(1));
        char endCol = endCell[0];
        int endRow = stoi(endCell.substr(1));

        double sum = 0.0;
        int count = 0;

        // Calculate the sum and count of all cells in the range
        for (char col = startCol; col <= endCol; ++col) {
            for (int row = startRow; row <= endRow; ++row) {
                int colIndex = col - 'A';
                sum += cells[row][colIndex].getNumber_Value();
                count++;
            }
        }

        double average = sum / count;
        string converResult = to_string(average);

        formula.replace(averPos, closeParen - averPos + 1, converResult);
        averPos = formula.find("AVER(", averPos + converResult.size());
    }
    return formula;
}

// Converts MAX formulas (e.g., MAX(A1..A3) -> calculated maximum value)
string FormulaParser::formulaConverterForMax(string& formula) {
    size_t maxPos = formula.find("MAX(");
    while (maxPos != string::npos) {
        size_t rangeStart = maxPos + 4;
        size_t rangeEnd = formula.find("..", rangeStart);
        if (rangeEnd == string::npos) break;
        size_t closeParen = formula.find(")", rangeEnd);
        if (closeParen == string::npos) break;

        string startCell = formula.substr(rangeStart, rangeEnd - rangeStart);
        string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2);

        char startCol = startCell[0];
        int startRow = stoi(startCell.substr(1));
        char endCol = endCell[0];
        int endRow = stoi(endCell.substr(1));

        double maxValue = cells[startRow][find_column_index(startCell)].getNumber_Value();

        for (char col = startCol; col <= endCol; ++col) {
            for (int row = startRow; row <= endRow; ++row) {
                int colIndex = col - 'A';
                double cellValue = cells[row][colIndex].getNumber_Value();
                if (cellValue > maxValue) {
                    maxValue = cellValue;
                }
            }
        }

        string converResult = to_string(maxValue);
        formula.replace(maxPos, closeParen - maxPos + 1, converResult);
        maxPos = formula.find("MAX(", maxPos + converResult.size());
    }
    return formula;
}

// Converts MIN formulas (e.g., MIN(A1..A3) -> calculated minimum value)
string FormulaParser::formulaConverterForMin(string& formula) {
    size_t minPos = formula.find("MIN(");
    while (minPos != string::npos) {
        size_t rangeStart = minPos + 4;
        size_t rangeEnd = formula.find("..", rangeStart);
        if (rangeEnd == string::npos) break;
        size_t closeParen = formula.find(")", rangeEnd);
        if (closeParen == string::npos) break;

        string startCell = formula.substr(rangeStart, rangeEnd - rangeStart);
        string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2);

        char startCol = startCell[0];
        int startRow = stoi(startCell.substr(1));
        char endCol = endCell[0];
        int endRow = stoi(endCell.substr(1));

        double minValue = cells[startRow][find_column_index(startCell)].getNumber_Value();

        for (char col = startCol; col <= endCol; ++col) {
            for (int row = startRow; row <= endRow; ++row) {
                int colIndex = col - 'A';
                double cellValue = cells[row][colIndex].getNumber_Value();
                if (cellValue < minValue) {
                    minValue = cellValue;
                }
            }
        }

        string converResult = to_string(minValue);
        formula.replace(minPos, closeParen - minPos + 1, converResult);
        minPos = formula.find("MIN(", minPos + converResult.size());
    }
    return formula;
}

// Converts STDDEV formulas (e.g., STDDEV(A1..A3) -> calculated standard deviation)
string FormulaParser::formulaConverterForSDTDEV(string& formula) {
    size_t stddevPos = formula.find("STDDEV(");
    while (stddevPos != string::npos) {
        size_t rangeStart = stddevPos + 7;
        size_t rangeEnd = formula.find("..", rangeStart);
        if (rangeEnd == string::npos) break;
        size_t closeParen = formula.find(")", rangeEnd);
        if (closeParen == string::npos) break;

        string startCell = formula.substr(rangeStart, rangeEnd - rangeStart);
        string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2);

        char startCol = startCell[0];
        int startRow = stoi(startCell.substr(1));
        char endCol = endCell[0];
        int endRow = stoi(endCell.substr(1));

        double total = 0;
        int cellCount = 0;
        vector<double> cellValues;

        // Collect cell values and calculate the total
        for (char col = startCol; col <= endCol; ++col) {
            for (int row = startRow; row <= endRow; ++row) {
                int colIndex = col - 'A';
                double cellValue = cells[row][colIndex].getNumber_Value();
                total += cellValue;
                cellValues.push_back(cellValue);
                ++cellCount;
            }
        }

        double average = total / cellCount;

        // Calculate variance
        double varianceSum = 0;
        for (double value : cellValues) {
            double diff = value - average;
            varianceSum += diff * diff;
        }
        double stddev = sqrt(varianceSum / cellCount);

        string converResult = to_string(stddev);
        formula.replace(stddevPos, closeParen - stddevPos + 1, converResult);
        stddevPos = formula.find("STDDEV(", stddevPos + converResult.size());
    }
    return formula;
}
