//==============================================================================
// Function.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Function
//------------------------------------------------------------------------------
RefPtr<Function> Function::Empty;

void Function::Bootup()
{
	Empty.reset(new Function_Empty());
}

String Function::MakeFullName() const
{
	String str;
	RefPtr<Frame> pFrame(LockFrameOuter());
	if (pFrame) {
		const DottedSymbol* pDottedSymbol = pFrame->GetDottedSymbol();
		if (pDottedSymbol) {
			str += pDottedSymbol->ToString();
			str += ".";
		}
	}
	str += GetName();
	return str;
}

void Function::DoCall(Processor& processor, Argument& argument) const
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
	if (argument.IsMapNone()) {
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
	} else if (argument.IsMapToList()) {
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		while (argument.ReadyToPickValue()) {
			valueTypedOwner.Add(DoEval(processor, argument));
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else { // argument.IsMapToIter()
		RefPtr<Iterator> pIterator(
			new Iterator_FunctionImpMap(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	}
}

void Function::Compose(Composer& composer, Expr_Caller& exprCaller) const
{
	if (!GetDeclCallable().GetDeclArgOwner().IsValidArgNum(exprCaller.CountExprCdr())) {
		Error::IssueWith(ErrorType::ArgumentError, exprCaller,
						 "invalid number of arguments for %s-statement", MakeFullName().c_str());
		return;
	}
	if (GetDeclCallable().GetDeclBlock().IsOccurZero() && exprCaller.HasExprOfBlock()) {
		Error::IssueWith(ErrorType::SyntaxError, exprCaller,
						 "unnecessary block for %s-statement", MakeFullName().c_str());
		return;
	}
	if (GetDeclCallable().GetDeclBlock().IsOccurOnce() && !exprCaller.HasExprOfBlock()) {
		Error::IssueWith(ErrorType::SyntaxError, exprCaller,
						 "missing block for %s-statement", MakeFullName().c_str());
		return;
	}
	return DoCompose(composer, exprCaller);
}

void Function::DoExec(Processor& processor, Argument& argument) const
{
	const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
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
