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

bool VTypeCustom::AssignPropSlot(Frame& frame, const Symbol* pSymbol, VType* pVType,
									PropSlot::Flags flags, RefPtr<Value> pValueInit)
{
	bool ofClassFlag = (flags & PropSlot::Flag::OfClass);
	ValueOwner& valuesProp = ofClassFlag? GetValuesPropOfClass() : GetValuesPropInit();
	size_t iProp = valuesProp.size();
	if (pValueInit->IsNil()) flags |= PropSlot::Flag::Nil;
	if (pVType) {
		if (!pValueInit->IsNil()) {
			pValueInit.reset(pVType->Cast(*pValueInit, pSymbol, flags));
			if (!pValueInit) return false;
		}
	} else if (flags & PropSlot::Flag::ListVar) {
		pVType = &VTYPE_Any;
		if (pValueInit->IsType(VTYPE_List)) {
			const ValueTypedOwner& valueTypedOwner = Value_List::GetValueTypedOwner(*pValueInit);
			if (valueTypedOwner.HasDeterminedVTypeOfElems()) {
				pVType = &valueTypedOwner.GetVTypeOfElems();
			}
		} else if (!pValueInit->IsNil()) {
			Error::Issue(ErrorType::PropertyError, "must be initialized by a list");
			return false;
		}
	} else if (pValueInit->IsNil()) {
		pVType = &VTYPE_Any;
	} else {
		pVType = &pValueInit->GetVTypeCustom();
	}
	valuesProp.push_back(pValueInit.release());
	if (ofClassFlag) {
		RefPtr<PropSlot> pPropSlot(new PropSlotCustom_Class(pSymbol, iProp));
		pPropSlot->Declare(*pVType, flags);
		GetPropSlotMap().Assign(pPropSlot.release());
	} else {
		RefPtr<PropSlot> pPropSlot(new PropSlotCustom_Instance(pSymbol, iProp));
		pPropSlot->Declare(*pVType, flags);
		GetPropSlotMap().Assign(pPropSlot.release());
	}
	return true;
}

bool VTypeCustom::AssignPropSlot(Frame& frame, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
									PropSlot::Flags flags, RefPtr<Value> pValueInit)
{
	RefPtr<Value> pValue(frame.Retrieve(dottedSymbol));
	VType* pVType = (pValue && pValue->IsType(VTYPE_VType))?
					&dynamic_cast<Value_VType&>(*pValue).GetVTypeThis() : nullptr;
	return AssignPropSlot(frame, pSymbol, pVType, flags, pValueInit.release());
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
								   *this, pDeclCallable.release(), new Expr_Block(),
								   pVTypeInh->GetConstructor().Reference()));
		} else {
			pConstructor.reset(new ConstructorClass(
								   *this, pDeclCallable.release(), new Expr_Block(), nullptr));
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

bool VTypeCustom::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	const Symbol* pSymbol = pFunction->GetSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(__init__))) {
		if (!pFunction->GetExprBody().IsType<Expr_Block>()) {
			Error::Issue(ErrorType::SyntaxError, "constructor's body must be a block");
			return false;
		}
		RefPtr<Expr_Block> pExprBody(dynamic_cast<Expr_Block*>(pFunction->GetExprBody().Reference()));
		pFunction->DeclareBlock(Gurax_Symbol(block), DeclBlock::Occur::ZeroOrOnce);
		RefPtr<Function> pConstructor;
		if (GetVTypeInh()->IsCustom()) {
			VTypeCustom* pVTypeInh = dynamic_cast<VTypeCustom*>(GetVTypeInh());
			pConstructor.reset(new ConstructorClass(
								*this, pFunction->GetDeclCallable().Reference(),
								pExprBody.release(),
								pVTypeInh->GetConstructor().Reference()));
		} else {
			pConstructor.reset(new ConstructorClass(
								*this, pFunction->GetDeclCallable().Reference(),
								pExprBody.release(), nullptr));
		}
		pConstructor->SetFrameOuter(GetFrame());
		SetConstructor(pConstructor.release());
		return true;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(__del__))) {
		if (!pFunction->GetDeclCallable().IsNaked()) {
			Error::Issue(ErrorType::SyntaxError, "destructors can't have any arguments");
			return false;
		}
		pFunction->SetFrameOuter(GetFrame());
		SetDestructor(pFunction.release());
		return true;
	}
	return VType::DoAssignCustomMethod(pFunction.release());
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
												Expr_Block* pExprBody, Function* pConstructorInh) :
	Function(Type::Constructor, Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pExprBody(pExprBody), _pPUnitBody(pExprBody->GetPUnitFirst()),
	_pConstructorInh(pConstructorInh)
{
	if (_pPUnitBody && _pPUnitBody->IsSequenceBegin()) _pPUnitBody = _pPUnitBody->GetPUnitCont();
}

#if 1
Value* VTypeCustom::ConstructorClass::DoEval(Processor& processor, Argument& argument) const
{
	RefPtr<Value> pValueThis;
	if (argument.GetValueThis().IsValid()) {
		pValueThis.reset(argument.GetValueThis().Reference());
	} else {
		pValueThis.reset(new Value_Object(GetVTypeCustom()));
		argument.SetValueThis(pValueThis.Reference());
		if (!pValueThis->InitCustomProp(GetVTypeCustom(), processor.Reference())) return Value::nil();
	}
	bool dynamicScopeFlag = false;
	argument.AssignToFrame(processor.BeginFunction(*this, dynamicScopeFlag), processor.GetFrameCur());
	if (_pConstructorInh) {
		const Expr_Block& exprBody = GetExprBody();
		RefPtr<Argument> pArgument(new Argument(*_pConstructorInh));
		pArgument->SetValueThis(pValueThis.Reference());
		//const Expr_Block& exprBodyEx = dynamic_cast<const Expr_Block&>(exprBody);
		processor.PushValue(new Value_Argument(pArgument.Reference()));
		Value::Delete(processor.ProcessPUnit(exprBody.GetPUnitSubFirst()));
		if (!pArgument->Compensate(processor)) return Value::nil();
		Value::Delete(_pConstructorInh->Eval(processor, *pArgument));
	}
	Value::Delete(processor.ProcessPUnit(GetPUnitBody()));
	processor.EndFunction(true);
	processor.ClearEvent();
	if (Error::IsIssued()) return Value::nil();
	// Clear argument's "this" value in preparation for the next iteration of a mapping operation.
	argument.SetValueThis(Value::nil());
	return argument.ReturnValue(processor, pValueThis.release());
}

#else
Value* VTypeCustom::ConstructorClass::DoEval(Processor& processor, Argument& argument) const
{
	VType* pVTypeInh = GetVTypeCustom().GetVTypeInh();
	Function& constructorInh = pVTypeInh->GetConstructor();
	if (constructorInh.IsEmpty()) {
		Error::Issue(ErrorType::ValueError,
			 "value type %s does not have a constructor", pVTypeInh->MakeFullName().c_str());
		return Value::nil();
	}
	RefPtr<Argument> pArgumentInh(new Argument(constructorInh));
	processor.PushValue(new Value_Argument(pArgumentInh.Reference()));
	Value::Delete(processor.ProcessPUnit(GetExprBody().GetPUnitSubFirst()));
	if (Error::IsIssued()) return Value::nil();
	if (!pArgumentInh->Compensate(processor)) return Value::nil();
	RefPtr<Value> pValueThis(constructorInh.Eval(processor, *pArgumentInh));
	if (Error::IsIssued()) return Value::nil();
	argument.SetValueThis(pValueThis.Reference());
	if (!pValueThis->InitCustomProp(GetVTypeCustom(), processor.Reference())) return Value::nil();
	bool dynamicScopeFlag = false;
	argument.AssignToFrame(processor.BeginFunction(*this, dynamicScopeFlag), processor.GetFrameCur());
	Value::Delete(processor.ProcessPUnit(GetPUnitBody()));
	processor.EndFunction(true);
	processor.ClearEvent();
	if (Error::IsIssued()) return Value::nil();
	// Clear argument's "this" value in preparation for the next iteration of a mapping operation.
	argument.SetValueThis(Value::nil());
	return argument.ReturnValue(processor, pValueThis.release());
}
#endif

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
	VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, PropSlotOwner* pPropSlotOwner) :
	Function(Type::Constructor, Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pPropSlotOwner(pPropSlotOwner)
{
}

Value* VTypeCustom::ConstructorStruct::DoEval(Processor& processor, Argument& argument) const
{
	//RefPtr<Value> pValueThis(new ValueCustom(GetVTypeCustom()));
	RefPtr<Value> pValueThis(new Value_Object(GetVTypeCustom()));
	if (!pValueThis->InitCustomProp(GetVTypeCustom(), processor.Reference())) return Value::nil();
	ArgPicker args(argument);
	for (PropSlot* pPropSlot : GetPropSlotOwner()) {
		if (args.IsUndefined()) {
			args.Next();
			continue;
		}
		const Value& value = args.PickValue();
		if (!pPropSlot->IsSet(PropSlot::Flag::Nil) && value.IsNil()) continue;
		if (!pPropSlot->SetValue(*pValueThis, value, *Attribute::Empty)) {
			return Value::nil();
		}
	}
	return argument.ReturnValue(processor, pValueThis.release());
}

String VTypeCustom::ConstructorStruct::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

#if 0
//------------------------------------------------------------------------------
// ValueCustom
//------------------------------------------------------------------------------
String ValueCustom::ToString(const StringStyle& ss) const
{
	return String().Format("<%s>", GetVTypeCustom().MakeFullName().c_str());
}
#endif

}
