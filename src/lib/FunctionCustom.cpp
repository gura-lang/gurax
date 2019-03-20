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

Value* FunctionCustom::DoEval(Processor& processor, Argument& argument) const
{
	Frame& frame = processor.PushFrame_Function();
	argument.AssignToFrame(frame);
	processor.PushPUnit(nullptr);	// push a terminator so that Return exits the loop
	processor.Run(GetPUnitBody());
	if (Error::IsIssued()) return Value::nil();
	return processor.PopValue();
}

String FunctionCustom::ToString(const StringStyle& ss) const
{
	String str;
	str += GetSymbol()->GetName();
	str += GetDeclCallable().ToString(ss);
	str += ss.IsCram()? "=" : " = ";
	if (GetPUnitBody()) {
		str.Printf("#%zu", GetPUnitBody()->GetSeqId());
	} else {
		str += "null";
	}
	return str;
}

}
