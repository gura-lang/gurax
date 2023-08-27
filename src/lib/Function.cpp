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

Function* Function::CreateBlockFunction(Frame& frameOuter,
		const Symbol* pSymbol, const Expr_Block& exprOfBlock, bool holdFrameFlag)
{
	//const PUnit* pPUnit = exprOfBlock.GetPUnitFirst();
	//if (pPUnit->IsSequenceBegin()) pPUnit = pPUnit->GetPUnitCont();
	RefPtr<FunctionCustom> pFunction(new FunctionCustom(
		Type::Function, pSymbol, exprOfBlock.GetDeclCallable().Reference(), exprOfBlock.Reference()));
	pFunction->Declare(VTYPE_Any, Flag::CutExtraArgs);
	pFunction->SetFrameOuter(frameOuter);
	if (holdFrameFlag) pFunction->SetFrameHolder(frameOuter.Reference());
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
	RefPtr<FunctionCustom> pFunction(new FunctionCustom(
		Type::Function, pSymbol, pDeclCallable.release(), exprOfBlock.Reference()));
	pFunction->Declare(VTYPE_Any, Flag::None);
	return pFunction.release();
}

String Function::MakeFullName() const
{
	if (GetVTypeOfOwner()) {
		String str = GetVTypeOfOwner()->MakeFullName();
		str += IsHybridMethod()? "##" : IsInstanceMethod()? "#" : ".";
		str += GetName();
		return str;
	} else {
		RefPtr<Frame> pFrame(LockFrameOuter());
		return Frame::MakeFullName(pFrame.get(), GetName());
	}
}

void Function::LinkHelp(VType& vtype, const Symbol* pSymbol)
{
	RefPtr<Value> pValue(vtype.GetFrameOfMember().Retrieve(pSymbol));
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

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg, DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValue(pValueArg.release())) return Value::nil();
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2, DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValues(pValueArg1.release(), pValueArg2.release())) return Value::nil();
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2, RefPtr<Value> pValueArg3, DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValues(pValueArg1.release(),
			pValueArg2.release(), pValueArg3.release())) return Value::nil();
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, RefPtr<Value> pValueArg4, DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValues(pValueArg1.release(),
			pValueArg2.release(), pValueArg3.release(), pValueArg4.release())) return Value::nil();
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, RefPtr<Value> pValueArg4, RefPtr<Value> pValueArg5, DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValues(pValueArg1.release(),
			pValueArg2.release(), pValueArg3.release(), pValueArg4.release(), pValueArg5.release())) return Value::nil();
	return Eval(processor, *pArg);
}

Value* Function::EvalEasy(Processor& processor, RefPtr<Value> pValueArg1, RefPtr<Value> pValueArg2,
						RefPtr<Value> pValueArg3, RefPtr<Value> pValueArg4, RefPtr<Value> pValueArg5, RefPtr<Value> pValueArg6,
						DeclCallable::Flags flags) const
{
	RefPtr<Argument> pArg(new Argument(processor, *this, flags));
	ArgFeeder args(*pArg, processor.GetFrameCur());
	if (!args.FeedValues(pValueArg1.release(),
			pValueArg2.release(), pValueArg3.release(), pValueArg4.release(), pValueArg5.release(), pValueArg6.release())) return Value::nil();
	return Eval(processor, *pArg);
}

void Function::Call(Processor& processor, Argument& argument) const
{
	auto MapToList = [this](Processor& processor, Argument& argument) {
		Frame& frame = processor.GetFrameCur();
		const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
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
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToXList = [this](Processor& processor, Argument& argument) {
		Frame& frame = processor.GetFrameCur();
		const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
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
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToIter = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
		RefPtr<Iterator> pIterator(
			new Iterator_FunctionImpMap<false>(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
	};
	auto MapToXIter = [this](Processor& processor, Argument& argument) {
		const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
		RefPtr<Iterator> pIterator(
			new Iterator_FunctionImpMap<true>(processor.Reference(), Reference(), argument.Reference()));
		processor.PushValue(new Value_Iterator(pIterator.release()));
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
	};
	Frame& frame = processor.GetFrameCur();
	const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
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
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
	} else if (GetDeclCallable().IsResultVoid()) {
		while (argument.ReadyToPickValue(frame)) {
			Value::Delete(Eval(processor, argument));
		}
		if (Error::IsIssued()) {
			//processor.ErrorDone();
			return;
		}
		processor.PushValue(Value::nil());
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
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
		processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
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
	if (!GetDeclCallable().GetDeclArgOwner().IsValidArgNum(exprCaller.CountExprParam())) {
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
	const PUnit* pPUnitOfCaller = processor.GetPUnitCur();
	RefPtr<Value> pValue(DoEval(processor, argument));
	if (!pPUnitOfCaller->GetDiscardValueFlag()) processor.PushValue(pValue->Reference());
	processor.SetPUnitCur(pPUnitOfCaller->GetPUnitCont());
}

void Function::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	String str = ToString();
	const Help* pHelp = GetHelpHolder().LookupLoose(pLangCode);
	if (pHelp) {
		str += "\n---\n";
		str += pHelp->GetDoc();
		if (!str.EndsWith('\n')) str += '\n';
	}
	Basement::Inst.Present(processor, str.c_str());
}

String Function::ToString(const StringStyle& ss) const
{
	return String().Format("%s%s", MakeFullName().c_str(), GetDeclCallable().ToString(ss).c_str());
}

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
RefPtr<Constructor> Constructor::Empty;

void Constructor::Bootup()
{
	Empty.reset(new Constructor_Empty());
}

}
