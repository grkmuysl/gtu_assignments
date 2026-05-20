#include "Cell.h"

// Destructor implementation for the Cell class.
// Since the destructor is declared as virtual in the header file,
// this ensures proper cleanup of derived class objects when deleted via a base class pointer.
Cell::~Cell() = default;
