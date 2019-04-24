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
	const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
	if (argument.IsMapMode(Argument::MapMode::ToList)) {
		while (argument.ReadyToPickValue()) {
			RefPtr<Value> pValue(DoEval(processor, argument));
			//if (!pPUnitOfCaller->GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
		}
	} else {
		RefPtr<Value> pValue(DoEval(processor, argument));
		if (!pPUnitOfCaller->GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
	}
	processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
}

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
