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

Function* Function::CreateBlockFunction(const Symbol* pSymbol, const Expr_Block& exprOfBlock)
{
	//const PUnit* pPUnit = exprOfBlock.GetPUnitFirst();
	//if (pPUnit->IsBeginSequence()) pPUnit = pPUnit->GetPUnitCont();
	RefPtr<FunctionCustom> pFunction(
		new FunctionCustom(
			Type::Function, pSymbol,
			exprOfBlock.GetDeclCallable().Reference(), exprOfBlock.Reference()));
	pFunction->Declare(VTYPE_Any, Flag::CutExtraArgs);
	return pFunction.release();
}

String Function::MakeFullName() const
{
	RefPtr<Frame> pFrame(LockFrameOuter());
	return Frame::MakeFullName(pFrame.get(), GetName());
}

void Function::LinkHelp(VType& vtype, const Symbol* pSymbol)
{
	Value* pValue = vtype.GetFrame().Lookup(pSymbol);
	if (pValue && pValue->IsType(VTYPE_Function)) {
		_pHelpHolder.reset(Value_Function::GetFunction(*pValue).GetHelpHolder().Reference());
	}
}

void Function::DoCall(Processor& processor, Argument& argument) const
{
	auto MapToList = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		while (argument.ReadyToPickValue()) {
			RefPtr<Value> pValueRtn(DoEval(processor, argument));
			if (Error::IsIssued()) {
				processor.ErrorDone();
				return;
			}
			valueTypedOwner.Add(pValueRtn.release());
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToXList = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		while (argument.ReadyToPickValue()) {
			RefPtr<Value> pValueRtn(DoEval(processor, argument));
			if (Error::IsIssued()) {
				processor.ErrorDone();
				return;
			}
			if (pValueRtn->IsValid()) valueTypedOwner.Add(pValueRtn.release());
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToIter = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Iterator> pIterator(
			new Iterator_FunctionImpMap<false>(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToXIter = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Iterator> pIterator(
			new Iterator_FunctionImpMap<true>(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	};
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
	} else if (argument.IsSet(DeclCallable::Flag::List)) {
		MapToList(processor, argument);
	} else if (argument.IsSet(DeclCallable::Flag::XList)) {
		MapToXList(processor, argument);
	} else if (argument.IsSet(DeclCallable::Flag::Iter)) {
		MapToIter(processor, argument);
	} else if (argument.IsSet(DeclCallable::Flag::XIter)) {
		MapToXIter(processor, argument);
	} else if (argument.IsMapToList()) {
		MapToList(processor, argument);
	} else { // argument.IsMapToIter()
		MapToIter(processor, argument);
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

Value* Function::ReturnValue(Processor& processor, Argument& argument, RefPtr<Value> pValueRtn) const
{
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueRtn.release();
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	ArgFeeder args(*pArgumentSub);
	if (!args.FeedValue(frame, pValueRtn.release())) return Value::nil();
	return processor.EvalExpr(*pExprOfBlock, *pArgumentSub);
}

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
