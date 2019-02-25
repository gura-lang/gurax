//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function_Print
//------------------------------------------------------------------------------
class Function_Print : public Function {
public:
	Function_Print();
	// Virtual functions of Function
	virtual Value* Eval(const Argument& argument) const override;
};

Function_Print::Function_Print() : Function("Print")
{
	DeclareCaller(VTYPE_Nil, DeclCaller::Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::OccurPattern::Once, DeclArg::Flag::None, nullptr);
	DeclareAttrOpt("list");
}

Value* Function_Print::Eval(const Argument& argument) const
{
	
	return Value::nil();
}

}
