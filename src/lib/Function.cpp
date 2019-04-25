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
	if (argument.IsMapMode(Argument::MapMode::None)) {
		DoExec(processor, argument);
	} else if (pPUnitOfCaller->GetDiscardValueFlag()) {
		while (argument.ReadyToPickValue()) {
			Value::Delete(DoEval(processor, argument));
		}
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else if (GetDeclCallable().IsResultVoid()) {
		while (argument.ReadyToPickValue()) {
			Value::Delete(DoEval(processor, argument));
		}
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else if (GetDeclCallable().IsResultReduce()) {
		RefPtr<Value> pValueRtn(Value::nil());
		while (argument.ReadyToPickValue()) {
			pValueRtn.reset(DoEval(processor, argument));
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else if (argument.IsMapMode(Argument::MapMode::ToList)) {
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		while (argument.ReadyToPickValue()) {
			valueTypedOwner.Add(DoEval(processor, argument));
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else { // argument.IsMapMode(Argument::MapMode::ToIter)
		RefPtr<Iterator> pIterator(
			new Iterator_ImplicitMap(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	}
}

void Function::DoExec(Processor& processor, Argument& argument) const
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
	RefPtr<Value> pValue(DoEval(processor, argument));
	if (!pPUnitOfCaller->GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
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
