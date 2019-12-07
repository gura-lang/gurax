//==============================================================================
// Functions.h
//==============================================================================
#ifndef GURAX_FUNCTIONS_H
#define GURAX_FUNCTIONS_H
#include "Function.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function_Empty
//------------------------------------------------------------------------------
class Function_Empty : public Function {
public:
	Function_Empty() : Function(Type::Function, Flag::None) {}
public:
	virtual bool IsEmpty() const override { return true; }
};

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
class Functions {
public:
	static void AssignToBasement(Frame& frame);
};

}

#endif
