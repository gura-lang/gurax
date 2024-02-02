//==============================================================================
// BasicFunction.h
//==============================================================================
#ifndef GURAX_BASICFUNCTION_H
#define GURAX_BASICFUNCTION_H
#include "Function.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function_Empty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Function_Empty : public Function {
public:
	Function_Empty() : Function(Type::Function, Flag::None) {}
public:
	virtual bool IsEmpty() const override { return true; }
};

//------------------------------------------------------------------------------
// Constructor_Empty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Constructor_Empty : public Constructor {
public:
	Constructor_Empty() : Constructor(Flag::None) {}
public:
	virtual bool IsEmpty() const override { return true; }
};

//------------------------------------------------------------------------------
// BasicFunction
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BasicFunction {
public:
	static void Prepare(Frame& frame);
};

}

#endif
