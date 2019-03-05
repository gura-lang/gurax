//==============================================================================
// FunctionCustom.h
//==============================================================================
#ifndef GURAX_FUNCTIONCUSTOM_H
#define GURAX_FUNCTIONCUSTOM_H
#include "Function.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
class FunctionCustom : public Function {
public:
	using Function::Function;
public:
	// Virtual functions of Function
	virtual Value* DoCall(Processor& processor, Argument& argument) const override;
};

}

#endif
