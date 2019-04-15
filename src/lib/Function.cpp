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

void Function::DoCall(Processor& processor, Argument& argument) const
{
	const PUnit* pPUnitCur = processor.GetPUnitCur();
	//processor.PushFrame_Function(*this);
	RefPtr<Value> pValue(DoEval(processor, argument));
	//processor.PopFrame();
	if (!pPUnitCur->GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
	processor.ContinueLoop(pPUnitCur->GetPUnitCont());
}

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
