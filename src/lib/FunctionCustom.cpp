//==============================================================================
// FunctionCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// FunctionCustom
//------------------------------------------------------------------------------
Value* FunctionCustom::DoCall(Processor& processor, Argument& argument) const
{
	Frame& frame = processor.PushFrame_Function();
	argument.AssignToFrame(frame);
	argument.SetPUnitCont(GetPUnitBody());
	return Value::nil();
}

String FunctionCustom::ToString(const StringStyle& ss) const
{
	String rtn;
	rtn += GetSymbol()->GetName();
	rtn += GetDeclCallable().ToString(ss);
	rtn += ss.IsCram()? "=" : " = ";
	if (GetPUnitBody()) {
		rtn += "#";
		rtn += std::to_string(GetPUnitBody()->GetSeqId());
	} else {
		rtn += "null";
	}
	return rtn;
}

}
