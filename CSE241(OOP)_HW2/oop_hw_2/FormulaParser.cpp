#include "FormulaParser.h"
#include "Cell.h"
#include <cstdlib> //for EXIT
#include "FormulaCell.h"

namespace formula_parser{
      // Constructor initializes the FormulaParser with a reference to the spreadsheet cells.
    FormulaParser::FormulaParser(unique_ptr<unique_ptr<unique_ptr<Cell>[]>[]>& sheetCells) 
        : cells(sheetCells) {}

    // Extracts operators (+, -, *, /) from the formula string.
    vector<char> FormulaParser::getOperatorsFromFormula(const string& formula) {
        vector<char> operatorsInFormula;
        for (char c : formula) {
            // Check if the character is an operator and add it to the vector.
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                operatorsInFormula.push_back(c);
            }
        }
        return operatorsInFormula;
    }

    // Extracts cell references (e.g., A1, B4) from the formula string.
    vector<string> FormulaParser::getCellsFromFormula(const string& formula) {
        vector<string> cellsInFormula;
        regex re(R"([\+\-\*/])"); // Regular expression to split the formula by operators.
        sregex_token_iterator it(formula.begin(), formula.end(), re, -1);
        sregex_token_iterator end;

        // Iterate through the split parts and add them to the vector.
        while (it != end) {
            cellsInFormula.push_back(*it++);
        }
        return cellsInFormula;
    }

    // Finds the column index from a cell reference (e.g., A1 -> 0 for column A).
    int FormulaParser::find_column_index(const string& inp) {
        char cell_address = inp[0]; // Extract the column letter.
        return static_cast<int>(cell_address) - 65; // Convert 'A' to 0.
    }

    // Finds the row index from a cell reference (e.g., A1 -> 0 for row 1).
    int FormulaParser::find_row_index(const string& inp) {
        try {
            // Extract the numeric part of the cell reference and convert it to an integer.
            return stoi(inp.substr(1));
        } catch (const invalid_argument& e) {
            cerr << "Invalid argument while applying the formula: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    // Applies the given formula to a specific cell.
    void FormulaParser::applyFormula(const string& formula, int current_row, int current_col) {
        // Extract cell references and operators from the formula.
        vector<string> cellsInFormula = getCellsFromFormula(formula);
        vector<char> operatorsInFormula = getOperatorsFromFormula(formula);

        vector<int> dependency = {current_row, current_col}; // Track dependencies for the current cell.
        string strResult;
        double result;

        // Process the first operand in the formula.
        if (isalpha(cellsInFormula[0][0])) { // Check if it's a cell reference.
            int row = find_row_index(cellsInFormula[0]);
            int col = find_column_index(cellsInFormula[0]);
            strResult = cells[row][col]->getData(); // Get the data from the referenced cell.
            try {
                result = stod(strResult); // Convert the data to a double.
            } catch (const invalid_argument& e) {
                cerr << "Invalid argument while converting cell data: " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
            
            // Mark the referenced cell as dependent on the current cell.
            cells[row][col]->setDependentCells(dependency);
            cells[row][col]->setAppliedFormula(formula);
        } else { // If it's a numeric value.
            try {
                result = stod(cellsInFormula[0]); // Convert the value to a double.
            } catch (const invalid_argument& e) {
                cerr << "Invalid argument while converting cell data: " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        // Process the remaining operators and operands in the formula.
        for (size_t i = 0; i < operatorsInFormula.size(); ++i) {
            double operandValue;
            string strOperandVal;

            if (isalpha(cellsInFormula[i + 1][0])) { // Check if the operand is a cell reference.
                int row = find_row_index(cellsInFormula[i + 1]);
                int col = find_column_index(cellsInFormula[i + 1]);
                strOperandVal = cells[row][col]->getData(); // Get the data from the referenced cell.

                try {
                    operandValue = stod(strOperandVal); // Convert the data to a double.
                } catch (const std::invalid_argument& e) {
                    cerr << "Invalid argument while converting cell data: " << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                // Mark the referenced cell as dependent on the current cell.
                cells[row][col]->setDependentCells(dependency);
                cells[row][col]->setAppliedFormula(formula);
            } else { // If the operand is a numeric value.
                try {
                    operandValue = stod(cellsInFormula[i + 1]); // Convert the value to a double.
                } catch (const invalid_argument& e) {
                    cerr << "Invalid argument while converting cell data: " << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

            try {
                // Apply the operator to the result and the operand.
                switch (operatorsInFormula[i]) {
                    case '+': result += operandValue; break;
                    case '-': result -= operandValue; break;
                    case '*': result *= operandValue; break;
                    case '/':
                        if (operandValue == 0) { // Check for division by zero.
                            throw runtime_error("Division by zero error!");
                        }
                        result /= operandValue;
                        break;
                    default:
                        throw runtime_error("Unsupported operator encountered in formula.");
                }
            } catch (const runtime_error& e) {
                cerr << "Runtime error while applying operator: " << e.what() << endl;
                exit(EXIT_FAILURE);
            }
        }

        // Determine whether the result is an integer or a double.
        int i = static_cast<int>(result);
        if (result == static_cast<double>(i)) { // If the result is an integer.
            unique_ptr<FormulaCell<int>> intFormulaCell = make_unique<FormulaCell<int>>();
            intFormulaCell->setFormula(formula);
            cells[current_row][current_col] = move(intFormulaCell);
        } else { // If the result is a double.
            setIsResultDouble(true);
            unique_ptr<FormulaCell<double>> doubleFormulaCell = make_unique<FormulaCell<double>>();
            doubleFormulaCell->setFormula(formula);
            cells[current_row][current_col] = move(doubleFormulaCell);
        }
        
        // Store the result in the target cell.
        cells[current_row][current_col]->setData(to_string(result));
    }

    // Converts SUM formulas (e.g., SUM(A1..A3) -> A1+A2+A3).
    string FormulaParser::formulaConverterForSum(string& formula) {
        size_t sumPos = formula.find("SUM(");
        while (sumPos != string::npos) {
            size_t rangeStart = sumPos + 4; // Start of the range.
            size_t rangeEnd = formula.find("..", rangeStart); // Find the range separator.
            if (rangeEnd == string::npos) break;
            size_t closeParen = formula.find(")", rangeEnd); // Find the closing parenthesis.
            if (closeParen == string::npos) break;

            string startCell = formula.substr(rangeStart, rangeEnd - rangeStart); // Extract start cell.
            string endCell = formula.substr(rangeEnd + 2, closeParen - rangeEnd - 2); // Extract end cell.

            char startCol = startCell[0];
            char endCol = endCell[0];
            int startRow;
            int endRow;
            try
            {
                startRow = stoi(startCell.substr(1));
                endRow = stoi(endCell.substr(1));
            }catch (const invalid_argument& e) {
                cerr << "Invalid argument while applying formula" << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
            
            

            string expandedRange = "";
            for (char col = startCol; col <= endCol; ++col) {
                for (int row = startRow; row <= endRow; ++row) {
                    if (!expandedRange.empty()) {
                        expandedRange += "+"; // Add "+" between cell references.
                    }
                    expandedRange += col + to_string(row); // Add the cell reference.
                }
            }

            // Replace the SUM formula with the expanded range.
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
            char endCol = endCell[0];
            int startRow;
            int endRow;
            try
            {
                startRow = stoi(startCell.substr(1));
                endRow = stoi(endCell.substr(1));
            }catch (const invalid_argument& e) {
                cerr << "Invalid argument while applying formula" << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }

            double sum = 0.0;
            string strVal;
            double doubleVal;
            int count = 0;

            // Calculate the sum and count of all cells in the range
            for (char col = startCol; col <= endCol; ++col) {
                for (int row = startRow; row <= endRow; ++row) {
                    int colIndex = col - 'A';
                    strVal = cells[row][colIndex]->getData();
                    doubleVal = stod(strVal);
                    sum += doubleVal;
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
        try
        {
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
                char endCol = endCell[0];
                int startRow;
                int endRow;
                try
                {
                    startRow = stoi(startCell.substr(1));
                    endRow = stoi(endCell.substr(1));
                }catch (const invalid_argument& e) {
                    cerr << "Invalid argument while applying formula" << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                string strMaxVal = cells[startRow][find_column_index(startCell)]->getData();

                double maxValue = stod(strMaxVal);

                for (char col = startCol; col <= endCol; ++col) {
                    for (int row = startRow; row <= endRow; ++row) {
                        int colIndex = col - 'A';
                        string strCellValue = cells[row][colIndex]->getData();
                        double cellValue = stod(strCellValue);
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
        catch(const std::invalid_argument& e)
        {
            cerr << "Invalid argument while converting cell value: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        
        
    }

    // Converts MIN formulas (e.g., MIN(A1..A3) -> calculated minimum value)
    string FormulaParser::formulaConverterForMin(string& formula) {
        try
        {
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
                char endCol = endCell[0];
                int startRow;
                int endRow;
                try
                {
                    startRow = stoi(startCell.substr(1));
                    endRow = stoi(endCell.substr(1));
                }catch (const invalid_argument& e) {
                    cerr << "Invalid argument while applying formula" << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                string strMinValue = cells[startRow][find_column_index(startCell)]->getData();
                double minValue = stod(strMinValue);

                for (char col = startCol; col <= endCol; ++col) {
                    for (int row = startRow; row <= endRow; ++row) {
                        int colIndex = col - 'A';
                        string strCellValue = cells[row][colIndex]->getData();
                        double cellValue = stod(strCellValue);
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
        catch(const std::invalid_argument& e)
        {
            cerr << "Invalid argument while converting cell value: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        
        
    }

    // Converts STDDEV formulas (e.g., STDDEV(A1..A3) -> calculated standard deviation)
    string FormulaParser::formulaConverterForSDTDEV(string& formula) {
        try
        {
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
                char endCol = endCell[0];
                int startRow;
                int endRow;
                try
                {
                    startRow = stoi(startCell.substr(1));
                    endRow = stoi(endCell.substr(1));
                }catch (const invalid_argument& e) {
                    cerr << "Invalid argument while applying formula" << e.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                double total = 0;
                int cellCount = 0;
                vector<double> cellValues;

                // Collect cell values and calculate the total
                for (char col = startCol; col <= endCol; ++col) {
                    for (int row = startRow; row <= endRow; ++row) {
                        int colIndex = col - 'A';
                        string strCellValue = cells[row][colIndex]->getData();
                        double cellValue = stod(strCellValue);
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
        catch(const std::invalid_argument& e)
        {
            cerr << "Invalid argument while converting cell value: " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        
    }

    bool FormulaParser::isContainsDoubleCell(string& formula){
        vector<string> cellsInFormula = getCellsFromFormula(formula);
        vector<char> operatorsInFormula = getOperatorsFromFormula(formula);

        string strResult;
        double result;
        bool isInt = true; 

    // Process the first operand
    if (isalpha(cellsInFormula[0][0])) {
        int row = find_row_index(cellsInFormula[0]);
        int col = find_column_index(cellsInFormula[0]);
        strResult = cells[row][col]->getData();

        try {
            if (strResult.empty()) {
                isInt = false; 
            }

            size_t idx = 0;
            std::stoi(strResult, &idx);
            if (idx != strResult.size()) {
                isInt = false;
            }

        } catch (const std::exception&) {
            isInt = false; 
        }
    }

    // Process the remaining operators and operands
    for (size_t i = 0; i < operatorsInFormula.size(); ++i) {
        string strOperandVal;
        if (isalpha(cellsInFormula[i + 1][0])) {
            int row = find_row_index(cellsInFormula[i + 1]);
            int col = find_column_index(cellsInFormula[i + 1]);
            strOperandVal = cells[row][col]->getData();

            try {
                if (strOperandVal.empty()) {
                    isInt = false; 
                }

                size_t idx = 0;
                std::stoi(strOperandVal, &idx);
                if (idx != strOperandVal.size()) {
                    isInt = false;
                }

            } catch (const std::exception&) {
                isInt = false; 
            }
        }
    }
        return isInt;
    }

    void FormulaParser::setIsResultDouble(bool state){
        isResultDouble = state;
    }
    bool FormulaParser::getIsResultDouble(){
        return isResultDouble;
    }

    bool FormulaParser::isInteger(const std::string& str) {
    try {
        std::size_t pos; // Variable to store the number of processed characters
        std::stoi(str, &pos); // Try converting the string to an integer
        return pos == str.size(); // If the entire string was processed, it's an integer
    } catch (...) {
        return false; // If an error occurs, it's not an integer
    }
    }

    bool FormulaParser::isDouble(const std::string& str) {
        try {
            std::size_t pos; // Variable to store the number of processed characters
            std::stod(str, &pos); // Try converting the string to a double
            return pos == str.size(); // If the entire string was processed, it's a double
        } catch (...) {
            return false; // If an error occurs, it's not a double
        }
}

}
