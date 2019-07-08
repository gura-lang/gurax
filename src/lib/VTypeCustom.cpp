//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
VTypeCustom::VTypeCustom() :
	VType(Symbol::Empty), _pValuesPropInit(new ValueOwner()), _pValuesPropOfClass(new ValueOwner())
{
	// _pConstructor and _pDestructor must be initialized here
	_pConstructor.reset(Function::Empty.Reference());
	_pDestructor.reset(Function::Empty.Reference());
}

void VTypeCustom::Inherit()
{
	if (GetVTypeInh()->IsCustom()) {
		VTypeCustom* pVTypeInh = dynamic_cast<VTypeCustom*>(GetVTypeInh());
		_pValuesPropInit.reset(pVTypeInh->GetValuesPropInit().Reference());
		_pValuesPropOfClass.reset(pVTypeInh->GetValuesPropOfClass().Reference());
	}
}

bool VTypeCustom::AssignMethod(Function* pFunction)
{
	const Symbol* pSymbol = pFunction->GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__init__))) {
		pFunction->DeclareBlock(Gurax_Symbol(block), DeclBlock::Occur::ZeroOrOnce);
		RefPtr<Function> pConstructor;
		if (GetVTypeInh()->IsCustom()) {
			VTypeCustom* pVTypeInh = dynamic_cast<VTypeCustom*>(GetVTypeInh());
			pConstructor.reset(new ConstructorClass(
								   *this, pFunction->GetDeclCallable().Reference(),
								   pFunction->GetExprBody().Reference(),
								   pVTypeInh->GetConstructor().Reference()));
		} else {
			pConstructor.reset(new ConstructorClass(
								   *this, pFunction->GetDeclCallable().Reference(),
								   pFunction->GetExprBody().Reference(), nullptr));
		}
		RefPtr<Frame> pFrameOuter(pFunction->LockFrameOuter());
		pConstructor->SetFrameOuter(*pFrameOuter);
		SetConstructor(pConstructor.release());
	} else if (pSymbol->IsIdentical(Gurax_Symbol(__del__))) {
		if (!pFunction->GetDeclCallable().IsNaked()) {
			Error::Issue(ErrorType::SyntaxError, "destructors can't have any arguments");
			return false;
		}
		SetDestructor(pFunction);
	} else {
		GetFrame().Assign(pSymbol, new Value_Function(pFunction));
	}
	return true;
}

bool VTypeCustom::AssignPropHandler(Frame& frame, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
									PropHandler::Flags flags, RefPtr<Value> pValueInit)
{
	bool ofClassFlag = (flags & PropHandler::Flag::OfClass);
	ValueOwner& valuesProp = ofClassFlag? GetValuesPropOfClass() : GetValuesPropInit();
	size_t iProp = valuesProp.size();
	const VType *pVType = &VTYPE_Any;
	Value* pValue = frame.Lookup(dottedSymbol);
	if (pValueInit->IsNil()) flags |= PropHandler::Flag::Nil;
	if (pValue && pValue->IsType(VTYPE_VType)) {
		pVType = &dynamic_cast<Value_VType*>(pValue)->GetVTypeThis();
		if (!pValueInit->IsNil()) {
			pValueInit.reset(pVType->Cast(*pValueInit, flags));
			if (!pValueInit) return false;
		}
	} else if (flags & PropHandler::Flag::ListVar) {
		if (pValueInit->IsType(VTYPE_List)) {
			const Value_List& valueEx = dynamic_cast<const Value_List&>(*pValueInit);
			const ValueTypedOwner& valueTypedOwner = valueEx.GetValueTypedOwner();
			if (valueTypedOwner.HasDeterminedVTypeOfElems()) {
				pVType = valueTypedOwner.GetVTypeOfElems();
			}
		} else if (!pValueInit->IsNil()) {
			Error::Issue(ErrorType::PropertyError, "must be initialized by a list");
			return false;
		}
	} else if (!pValueInit->IsNil()) {
		pVType = &pValueInit->GetVType();
	}
	valuesProp.push_back(pValueInit.release());
	if (ofClassFlag) {
		RefPtr<PropHandler> pPropHandler(new PropHandlerCustom_Class(pSymbol, iProp));
		pPropHandler->Declare(*pVType, flags);
		GetPropHandlerMapOfClass().Assign(pPropHandler.release());
	} else {
		RefPtr<PropHandler> pPropHandler(new PropHandlerCustom_Instance(pSymbol, iProp));
		pPropHandler->Declare(*pVType, flags);
		GetPropHandlerMap().Assign(pPropHandler.release());
	}
	return true;
}

void VTypeCustom::PrepareForAssignment(Processor& processor, const Symbol* pSymbol)
{
	if (!_pSymbol->IsEmpty()) return;
	_pSymbol = pSymbol;
	if (GetConstructor().IsEmpty()) {
		RefPtr<DeclCallable> pDeclCallable(new DeclCallable());
		pDeclCallable->GetDeclBlock().SetOccur(DeclBlock::Occur::ZeroOrOnce).SetFlags(Flag::None);
		RefPtr<Function> pConstructor;
		if (GetVTypeInh()->IsCustom()) {
			VTypeCustom* pVTypeInh = dynamic_cast<VTypeCustom*>(GetVTypeInh());
			pConstructor.reset(new ConstructorClass(
								   *this, pDeclCallable.release(), Expr::Empty.Reference(),
								   pVTypeInh->GetConstructor().Reference()));
		} else {
			pConstructor.reset(new ConstructorClass(
								   *this, pDeclCallable.release(), Expr::Empty.Reference(), nullptr));
		}
		pConstructor->SetFrameOuter(processor.GetFrameCur());
		SetConstructor(pConstructor.release());
	}
	GetConstructor().SetSymbol(pSymbol);
}

Value* VTypeCustom::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return value.Reference();
}

void VTypeCustom::SetCustomPropOfClass(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = GetValuesPropOfClass().begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

//------------------------------------------------------------------------------
// VTypeCustom::ConstructorClass
//------------------------------------------------------------------------------
VTypeCustom::ConstructorClass::ConstructorClass(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable,
												Expr* pExprBody, Function* pConstructorInh) :
	Function(Type::Function, Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pExprBody(pExprBody), _pPUnitBody(pExprBody->GetPUnitFirst()),
	_pConstructorInh(pConstructorInh)
{
	if (_pPUnitBody && _pPUnitBody->IsBeginSequence()) _pPUnitBody = _pPUnitBody->GetPUnitCont();
}

Value* VTypeCustom::ConstructorClass::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Value> pValueThis;
	if (argument.GetValueThis().IsValid()) {
		pValueThis.reset(argument.GetValueThis().Reference());
	} else {
		RefPtr<ValueCustom> pValueThisWk(new ValueCustom(GetVTypeCustom(), processor.Reference()));
		if (!pValueThisWk->InitCustomProp()) return Value::nil();
		pValueThis.reset(pValueThisWk.release());
		argument.SetValueThis(pValueThis.Reference());
	}
	bool dynamicScopeFlag = false;
	argument.AssignToFrame(processor.PushFrameForFunction(*this, dynamicScopeFlag));
	if (_pConstructorInh) {
		const Expr& exprBody = GetExprBody();
		RefPtr<Argument> pArgument(new Argument(_pConstructorInh->GetDeclCallable().Reference()));
		pArgument->SetValueThis(pValueThis.Reference());
		if (exprBody.IsType<Expr_Block>()) {
			const Expr_Block& exprBodyEx = dynamic_cast<const Expr_Block&>(exprBody);
			processor.PushValue(new Value_Argument(pArgument.Reference()));
			Value::Delete(processor.ProcessPUnit(exprBodyEx.GetPUnitSubFirst()));
		}
		_pConstructorInh->DoEvalVoid(processor, *pArgument);
	}
	Value::Delete(processor.ProcessPUnit(GetPUnitBody()));
	processor.PopFrame();
	processor.ClearEvent();
	if (Error::IsIssued()) return Value::nil();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueThis.release();
	Frame& frame = processor.GetFrameCur();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	ArgFeeder args(*pArgumentSub);
	if (!args.FeedValue(frame, pValueThis.release())) return Value::nil();
	return pExprOfBlock->DoEval(processor, *pArgumentSub);
}

String VTypeCustom::ConstructorClass::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// VTypeCustom::ConstructorStruct
//------------------------------------------------------------------------------
VTypeCustom::ConstructorStruct::ConstructorStruct(
	VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, PropHandlerOwner* pPropHandlerOwner) :
	Function(Type::Function, Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pPropHandlerOwner(pPropHandlerOwner)
{
}

Value* VTypeCustom::ConstructorStruct::DoEval(Processor& processor, Argument& argument) const
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<ValueCustom> pValueThis(new ValueCustom(GetVTypeCustom(), processor.Reference()));
	if (!pValueThis->InitCustomProp()) return Value::nil();
	ArgPicker args(argument);
	PropHandlerOwner::iterator ppPropHandler = _pPropHandlerOwner->begin();
	for ( ; ppPropHandler != _pPropHandlerOwner->end() && args.IsDefined(); ppPropHandler++) {
		PropHandler* pPropHandler = *ppPropHandler;
		const Value& value = args.PickValue();
		if (!value.IsUndefined() && !pPropHandler->SetValue(*pValueThis, value, *Attribute::Empty)) {
			return Value::nil();
		}
	}
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	if (!pExprOfBlock) return pValueThis.release();
	RefPtr<Argument> pArgumentSub(Argument::CreateForBlockCall(*pExprOfBlock));
	do {
		ArgFeeder args(*pArgumentSub);
		if (!args.FeedValue(frame, pValueThis->Reference())) return Value::nil();
	} while (0);
	return pExprOfBlock->DoEval(processor, *pArgumentSub);
}

String VTypeCustom::ConstructorStruct::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
ValueCustom::~ValueCustom()
{
	const Function& funcDestructor = GetVType().GetDestructor();
	if (!funcDestructor.IsEmpty()) {
		RefPtr<Argument> pArgument(new Argument(funcDestructor));
		funcDestructor.DoEval(GetProcessor(), *pArgument);
	}
}

bool ValueCustom::InitCustomProp()
{
	const ValueOwner& valuesPropInit = GetVType().GetValuesPropInit();
	_pValuesProp->reserve(valuesPropInit.size());
	for (const Value* pValue : valuesPropInit) {
		RefPtr<Value> pValueCloned = pValue->Clone();
		if (!pValueCloned) {
			Error::Issue(ErrorType::PropertyError, "failed to initialize property");
			return false;
		}
		_pValuesProp->push_back(pValueCloned.release());
	}
	return true;
}

void ValueCustom::SetCustomProp(size_t iProp, Value* pValue)
{
	ValueOwner::iterator ppValue = _pValuesProp->begin() + iProp;
	Value::Delete(*ppValue);
	*ppValue = pValue;
}

String ValueCustom::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ">";
	return str;
}

String ValueCustom::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
