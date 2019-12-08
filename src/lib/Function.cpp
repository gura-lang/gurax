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
			Type::Function, pSymbol, exprOfBlock.GetDeclCallable().Reference(), exprOfBlock.Reference()));
	pFunction->Declare(VTYPE_Any, Flag::CutExtraArgs);
	return pFunction.release();
}

Function* Function::CreateDynamicFunction(
	const Symbol* pSymbol, const ValueList& valuesExpr, const Expr_Block& exprOfBlock)
{
	RefPtr<ExprLink> pExprLink(new ExprLink());
	for (const Value* pValue : valuesExpr) {
		pExprLink->AddExpr(Value_Expr::GetExpr(*pValue).Reference());
	}
	RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
	if (!pDeclCallable->Prepare(*pExprLink, *Attribute::Empty, nullptr)) return nullptr;
	RefPtr<FunctionCustom> pFunction(
		new FunctionCustom(Type::Function, pSymbol, pDeclCallable.release(), exprOfBlock.Reference()));
	pFunction->Declare(VTYPE_Any, Flag::None);
	return pFunction.release();
}

String Function::MakeFullName() const
{
	if (GetVTypeOfOwner()) {
		String str = GetVTypeOfOwner()->MakeFullName();
		Flags flags = GetFlags() & (Flag::OfClass | Flag::OfInstance);
		str += (flags == Flag::OfInstance)? "#" :
			(flags == (Flag::OfClass | Flag::OfInstance))? "##" : ".";
		str += GetName();
		return str;
	}
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

void Function::Exec(Processor& processor, Argument& argument) const
{
	if (!argument.GetValueThis().CanEvalAsMethod(*this)) return;
	DoExec(processor, argument);
}

Value* Function::Eval(Processor& processor, Argument& argument) const
{
	if (!argument.GetValueThis().CanEvalAsMethod(*this)) Value::nil();
	return DoEval(processor, argument);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArg(new Argument(*this));
	ArgFeeder arg(*pArg);
	arg.FeedValue(frame, pValueArg.release());
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArg(new Argument(*this));
	ArgFeeder arg(*pArg);
	arg.FeedValue(frame, pValueArg1.release());
	arg.FeedValue(frame, pValueArg2.release());
	return Eval(processor, *pArg);
}

void Function::Call(Processor& processor, Argument& argument) const
{
	auto MapToList = [this](Processor& processor, Argument& argument) {
		Frame& frame = processor.GetFrameCur();
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		bool flatFlag = argument.IsSet(DeclCallable::Flag::Flat);
		while (argument.ReadyToPickValue(frame)) {
			RefPtr<Value> pValueRtn(Eval(processor, argument));
			if (Error::IsIssued()) {
				//processor.ErrorDone();
				return;
			}
			if (flatFlag && pValueRtn->IsType(VTYPE_List)) {
				valueTypedOwner.Add(dynamic_cast<Value_List&>(*pValueRtn).GetValueTypedOwner());
			} else {
				valueTypedOwner.Add(pValueRtn.release());
			}
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
		}
		processor.PushValue(pValueRtn.release());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToXList = [this](Processor& processor, Argument& argument) {
		Frame& frame = processor.GetFrameCur();
		const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
		RefPtr<Value_List> pValueRtn(new Value_List());
		ValueTypedOwner& valueTypedOwner = pValueRtn->GetValueTypedOwner();
		bool flatFlag = argument.IsSet(DeclCallable::Flag::Flat);
		while (argument.ReadyToPickValue(frame)) {
			RefPtr<Value> pValueRtn(Eval(processor, argument));
			if (Error::IsIssued()) {
				//processor.ErrorDone();
				return;
			}
			if (flatFlag && pValueRtn->IsType(VTYPE_List)) {
				valueTypedOwner.Add(dynamic_cast<Value_List&>(*pValueRtn).GetValueTypedOwner());
			} else if (pValueRtn->IsValid()) {
				valueTypedOwner.Add(pValueRtn.release());
			}
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
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
	Frame& frame = processor.GetFrameCur();
	const PUnit* pPUnitOfCaller = processor.GetPUnitNext();
	if (argument.IsMapNone()) {
		Exec(processor, argument);
	} else if (pPUnitOfCaller->GetDiscardValueFlag()) {
		while (argument.ReadyToPickValue(frame)) {
			Value::Delete(Eval(processor, argument));
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
		}
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else if (GetDeclCallable().IsResultVoid()) {
		while (argument.ReadyToPickValue(frame)) {
			Value::Delete(Eval(processor, argument));
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
		}
		processor.PushValue(Value::nil());
		processor.SetPUnitNext(pPUnitOfCaller->GetPUnitCont());
	} else if (GetDeclCallable().IsResultReduce()) {
		RefPtr<Value> pValueRtn(Value::nil());
		while (argument.ReadyToPickValue(frame)) {
			pValueRtn.reset(Eval(processor, argument));
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
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

String Function::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

}
