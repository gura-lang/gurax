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
	argument.AssignToFrame(processor.PushFrame_Function(*this));
	argument.SetPUnitCont(GetPUnitBody());
	// PUnit_Return will do PopFrame().
	return Value::nil();
}

Value* FunctionCustom::DoEval(Processor& processor, Argument& argument) const
{
	argument.AssignToFrame(processor.PushFrame_Function(*this));
	processor.Process(GetPUnitBody());
	processor.PopFrame();
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
