//==============================================================================
// Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
String Function::MakeFullName() const
{
	return GetName();
}

Value* Function::DoCall(Processor& processor, Argument& argument) const
{
	//processor.PushFrame_Function(*this);
	RefPtr<Value> pValue(DoEval(processor, argument));
	//processor.PopFrame();
	return pValue.release();
}

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
