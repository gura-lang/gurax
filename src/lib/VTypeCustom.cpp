//==============================================================================
// VTypeCustom.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VTypeCustom
//------------------------------------------------------------------------------
VTypeCustom::VTypeCustom() :
	VType(Symbol::Empty), _pValuesPropOfInstInit(new ValueOwner()), _pValuesPropOfClass(new ValueOwner())
{
	// _pConstructor, _pDestructor and _pCastFunction must be initialized.
	_pConstructor.reset(Constructor::Empty.Reference());
	_pDestructor.reset(Function::Empty.Reference());
	_pCastFunction.reset(Function::Empty.Reference());
}

void VTypeCustom::Inherit()
{
	if (GetVTypeInh().IsCustom()) {
		VTypeCustom& vtypeInh = dynamic_cast<VTypeCustom&>(GetVTypeInh());
		_pValuesPropOfInstInit.reset(vtypeInh.GetValuesPropOfInstInit().Clone());
		_pValuesPropOfClass.reset(vtypeInh.GetValuesPropOfClass().Clone());
	}
}

bool VTypeCustom::AssignPropSlot(Processor& processor, const Symbol* pSymbol, VType* pVType,
									PropSlot::Flags flags, RefPtr<Value> pValueInit)
{
	if (pValueInit->IsNil()) {
		flags |= PropSlot::Flag::Nil;
	} else if (pValueInit->IsVType()) {
		VType& vtype = Value_VType::GetVTypeThis(*pValueInit);
		vtype.SetFrameOuter(GetFrame().Reference());
		vtype.PrepareForAssignment(processor, pSymbol);
		flags |= PropSlot::Flag::OfClass;
	}
	bool ofClassFlag = (flags & PropSlot::Flag::OfClass);
	ValueOwner& valuesProp = ofClassFlag? GetValuesPropOfClass() : GetValuesPropOfInstInit();
	size_t iProp = valuesProp.size();
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

bool VTypeCustom::AssignPropSlot(Processor& processor, const Symbol* pSymbol, const DottedSymbol& dottedSymbol,
									PropSlot::Flags flags, RefPtr<Value> pValueInit)
{
	Frame& frame = processor.GetFrameCur();
	RefPtr<Value> pValue(frame.Retrieve(dottedSymbol));
	VType* pVType = (pValue && pValue->IsType(VTYPE_VType))?
					&dynamic_cast<Value_VType&>(*pValue).GetVTypeThis() : nullptr;
	return AssignPropSlot(processor, pSymbol, pVType, flags, pValueInit.release());
}

void VTypeCustom::PrepareForAssignment(Processor& processor, const Symbol* pSymbol)
{
	if (!_pSymbol->IsEmpty()) return;
	_pSymbol = pSymbol;
	if (GetConstructor().IsEmpty()) {
		Function& constructorInh = GetVTypeInh().GetConstructor();
		RefPtr<Constructor> pConstructor(new ConstructorClassDefault(*this, constructorInh.GetDeclCallable().Reference()));
		pConstructor->SetFrameOuter(processor.GetFrameCur());
		SetConstructor(pConstructor.release());
	}
	GetConstructor().SetSymbol(pSymbol);
}

Value* VTypeCustom::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	//if (GetCastFunction().IsEmpty()) return nullptr;
	//GetCastFunction().EvalEasy(GetProcessor(), value.Reference(), new Value_DeclArg());
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
		RefPtr<Constructor> pConstructor(new ConstructorClass(
						*this, pFunction->GetDeclCallable().Reference(), pExprBody.release()));
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
	} else if (pSymbol->IsIdentical(Gurax_Symbol(__cast__))) {
		pFunction->SetFrameOuter(GetFrame());
		SetCastFunction(pFunction.release());
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
VTypeCustom::ConstructorClass::ConstructorClass(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable, Expr_Block* pExprBody) :
	Constructor(Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pExprBody(pExprBody), _pPUnitBody(pExprBody->GetPUnitFirst())
{
	if (_pPUnitBody && _pPUnitBody->IsSequenceBegin()) _pPUnitBody = _pPUnitBody->GetPUnitCont();
}

Value* VTypeCustom::ConstructorClass::DoEval(Processor& processor, Argument& argument) const
{
	VType& vtypeInh = GetVTypeCustom().GetVTypeInh();
	Function& constructorInh = vtypeInh.GetConstructor();
	if (constructorInh.IsEmpty()) {
		Error::Issue(ErrorType::ValueError,
			 "value type %s does not have a constructor", vtypeInh.MakeFullName().c_str());
		return Value::nil();
	}
	bool dynamicScopeFlag = false;
	Frame& frame = processor.BeginFunction(*this, dynamicScopeFlag);
	argument.AssignToFrame(frame, processor.GetFrameCur());
	RefPtr<Argument> pArgumentInh(new Argument(processor, constructorInh));
	processor.PushValue(new Value_Argument(pArgumentInh.Reference()));
	Value::Delete(processor.ProcessPUnit(GetExprBody().GetPUnitSubFirst()));
	if (Error::IsIssued()) {
		processor.EndFunction(true);
		return Value::nil();
	}
	if (!pArgumentInh->CompleteFeedValue(processor)) {
		processor.EndFunction(true);
		return Value::nil();
	}
	RefPtr<Value> pValueThis(constructorInh.Eval(processor, *pArgumentInh));
	if (Error::IsIssued()) {
		processor.EndFunction(true);
		return Value::nil();
	}
	if (!pValueThis->InitCustomProp(GetVTypeCustom(), processor.Reference())) {
		processor.EndFunction(true);
		return Value::nil();
	}
	argument.AssignThisToFrame(frame, pValueThis->PickValue());
	Value::Delete(processor.ProcessPUnit(GetPUnitBody()));
	processor.EndFunction(true);
	processor.ClearEvent();
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, pValueThis.release());
}

String VTypeCustom::ConstructorClass::ToString(const StringStyle& ss) const
{
	String str;
	str += MakeFullName();
	str += GetDeclCallable().ToString(ss);
	return str;
}

//------------------------------------------------------------------------------
// VTypeCustom::ConstructorClassDefault
//------------------------------------------------------------------------------
VTypeCustom::ConstructorClassDefault::ConstructorClassDefault(VTypeCustom& vtypeCustom, DeclCallable* pDeclCallable) :
	Constructor(Symbol::Empty, pDeclCallable), _vtypeCustom(vtypeCustom)
{
}

Value* VTypeCustom::ConstructorClassDefault::DoEval(Processor& processor, Argument& argument) const
{
	VType& vtypeInh = GetVTypeCustom().GetVTypeInh();
	Function& constructorInh = vtypeInh.GetConstructor();
	if (constructorInh.IsEmpty()) {
		Error::Issue(ErrorType::ValueError,
			 "value type %s does not have a constructor", vtypeInh.MakeFullName().c_str());
		return Value::nil();
	}
	RefPtr<Expr_Block> pExprBlock(argument.SuspendExprOfBlock());
	RefPtr<Value> pValueThis(constructorInh.Eval(processor, argument));
	argument.ResumeExprOfBlock(pExprBlock.release());
	if (Error::IsIssued()) return Value::nil();
	if (!pValueThis->InitCustomProp(GetVTypeCustom(), processor.Reference())) {
		processor.EndFunction(true);
		return Value::nil();
	}
	return argument.ReturnValue(processor, pValueThis.release());
}

String VTypeCustom::ConstructorClassDefault::ToString(const StringStyle& ss) const
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
	Constructor(Symbol::Empty, pDeclCallable),
	_vtypeCustom(vtypeCustom), _pPropSlotOwner(pPropSlotOwner)
{
}

Value* VTypeCustom::ConstructorStruct::DoEval(Processor& processor, Argument& argument) const
{
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

}
