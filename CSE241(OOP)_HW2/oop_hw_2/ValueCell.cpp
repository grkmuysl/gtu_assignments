#include "ValueCell.h"

// Default destructor for the ValueCell class.
// Declared as virtual to ensure proper cleanup of derived class objects when deleted through a base class pointer.
ValueCell::~ValueCell() = default;
