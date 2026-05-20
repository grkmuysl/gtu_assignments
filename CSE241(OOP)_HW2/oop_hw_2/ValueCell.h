#ifndef VALUECELL_H
#define VALUECELL_H

#include <string>
#include <vector>
#include "Cell.h"
#include <iostream>
using namespace std;

// The ValueCell class serves as an abstract base class for all cell types that store values.
// It inherits from the Cell class and provides a foundation for specific value-based cells (e.g., StringValueCell, IntValueCell, etc.).
class ValueCell : public Cell {
public:
    // Virtual destructor to allow proper cleanup of derived class objects.
    virtual ~ValueCell();
};

#endif
