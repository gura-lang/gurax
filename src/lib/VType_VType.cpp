//==============================================================================
// VType_VType.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(VType, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(VType, `en)}

${help.ComposeMethodHelp(VType, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// VType(value):map {block?}
Gurax_DeclareConstructor(VType)
{
	Declare(VTYPE_VType, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `VType` instance that represents the type information of the given `value`.\n");
}

Gurax_ImplementConstructor(VType)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	return argument.ReturnValue(processor, new Value_VType(value.GetVTypeCustom()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// VType##__help__(lang? as Symbol):[class] {block?}
Gurax_DeclareHybridMethod(VType, __help__)
{
	Declare(VTYPE_Help, Flag::Map);
	DeclareArg("lang", VTYPE_Symbol, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(class_));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementHybridMethod(VType, __help__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pLangCode = args.IsValid()? args.PickSymbol() : nullptr;
	// Function body
	const VType& vtypeThis = valueThis.GetVTypeThis();
	const Help* pHelp = argument.IsSet(Gurax_Symbol(class_))?
				vtypeThis.GetHelpHolder().LookupLoose(pLangCode) :
				vtypeThis.GetConstructor().GetHelpHolder().LookupLoose(pLangCode);
	RefPtr<Value> pValueRtn(Value::nil());
	if (pHelp) pValueRtn.reset(new Value_Help(pHelp->Reference()));
	return argument.ReturnValue(processor, pValueRtn.release());
}

// VType##__methodSymbols__():[class,hybrid,instance] {block?}
Gurax_DeclareHybridMethod(VType, __methodSymbols__)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareAttrOpt(Gurax_Symbol(class_));
	DeclareAttrOpt(Gurax_Symbol(hybrid));
	DeclareAttrOpt(Gurax_Symbol(instance));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementHybridMethod(VType, __methodSymbols__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	SymbolList symbolList;
	VType& vtype = valueThis.IsType(VTYPE_VType)? valueThis.GetVTypeThis() : valueThis.GetVTypeCustom();
	bool allFlag = true;
	if (argument.IsSet(Gurax_Symbol(class_))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_ClassMethod(), false);
		allFlag = false;
	}
	if (argument.IsSet(Gurax_Symbol(hybrid))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_HybridMethod(), false);
		allFlag = false;
	}
	if (argument.IsSet(Gurax_Symbol(instance))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_InstanceMethod(), false);
		allFlag = false;
	}
	if (allFlag) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_Method(), false);
	}
	symbolList.Sort();
	RefPtr<Iterator> pIterator(new Iterator_Symbol(std::move(symbolList)));
	return argument.ReturnIterator(processor, pIterator.release());
}

// VType##__methods__():[class,hybrid,instance] {block?}
Gurax_DeclareHybridMethod(VType, __methods__)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareAttrOpt(Gurax_Symbol(class_));
	DeclareAttrOpt(Gurax_Symbol(hybrid));
	DeclareAttrOpt(Gurax_Symbol(instance));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementHybridMethod(VType, __methods__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	SymbolList symbolList;
	VType& vtype = valueThis.IsType(VTYPE_VType)? valueThis.GetVTypeThis() : valueThis.GetVTypeCustom();
	bool allFlag = true;
	if (argument.IsSet(Gurax_Symbol(class_))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_ClassMethod(), false);
		allFlag = false;
	}
	if (argument.IsSet(Gurax_Symbol(hybrid))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_HybridMethod(), false);
		allFlag = false;
	}
	if (argument.IsSet(Gurax_Symbol(instance))) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_InstanceMethod(), false);
		allFlag = false;
	}
	if (allFlag) {
		vtype.GatherMemberSymbolIf(symbolList, Value_Function::GatherCriteria_Method(), false);
	}
	symbolList.Sort();
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	for (const Symbol* pSymbol : symbolList) {
		RefPtr<Value> pValue(vtype.GetFrameOfMember().Retrieve(pSymbol));
		if (pValue) pValueOwner->push_back(pValue.release());
	}
	RefPtr<Iterator> pIterator(new Iterator_Each(pValueOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// VType#__propSlots__() {block?}
Gurax_DeclareClassMethod(VType, __propSlots__)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(VType, __propSlots__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<PropSlotOwner> pPropSlotOwner(new PropSlotOwner());
	valueThis.GetVTypeThis().GetPropSlotMap().GatherPropSlot(*pPropSlotOwner);
	pPropSlotOwner->SortBySymbolName();
	RefPtr<Iterator> pIterator(new Iterator_PropSlot(pPropSlotOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// VType#__propSlot__(symbol:Symbol):map {block?}
Gurax_DeclareClassMethod(VType, __propSlot__)
{
	Declare(VTYPE_PropSlot, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(VType, __propSlot__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	const PropSlot* pPropSlot = valueThis.GetVTypeThis().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		Error::Issue(ErrorType::PropertyError, "no property named '%s'", pSymbol->GetName());
		return Value::nil();
	}
	return argument.ReturnValue(processor, new Value_PropSlot(pPropSlot->Reference()));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// VType##__fullName__
Gurax_DeclareHybridProperty_R(VType, __fullName__)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The full name of the VType.");
}

Gurax_ImplementHybridPropertyGetter(VType, __fullName__)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetVTypeThis().MakeFullName());
}

// VType##__init__
Gurax_DeclareHybridProperty_R(VType, __init__)
{
	Declare(VTYPE_Function, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The constructor of the VType.");
}

Gurax_ImplementHybridPropertyGetter(VType, __init__)
{
	Function& constructor = GetValueThis(valueTarget).GetVTypeThis().GetConstructor();
	if (constructor.IsEmpty()) return Value::nil();
	return new Value_Function(constructor.Reference());
}

// VType##__name__
Gurax_DeclareHybridProperty_R(VType, __name__)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The name of the VType.");
}

Gurax_ImplementHybridPropertyGetter(VType, __name__)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetVTypeThis().GetName());
}

// VType##__symbol__
Gurax_DeclareHybridProperty_R(VType, __symbol__)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The symbol of the VType.");
}

Gurax_ImplementHybridPropertyGetter(VType, __symbol__)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetVTypeThis().GetSymbol());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Any as VType
Gurax_ImplementOpBinary(As, Any, VType)
{
	const VType& vtype = Value_VType::GetVTypeThis(valueR);
	RefPtr<Value> pValueResult(vtype.Cast(valueL));
	if (!pValueResult) return Value::undefined();
	return pValueResult.release();
}

// VType == VType
Gurax_ImplementOpBinary(Eq, VType, VType)
{
	const VType& vtypeL = Value_VType::GetVTypeThis(valueL);
	const VType& vtypeR = Value_VType::GetVTypeThis(valueR);
	return new Value_Bool(vtypeL.IsIdentical(vtypeR));
}

// VType != VType
Gurax_ImplementOpBinary(Ne, VType, VType)
{
	const VType& vtypeL = Value_VType::GetVTypeThis(valueL);
	const VType& vtypeR = Value_VType::GetVTypeThis(valueR);
	return new Value_Bool(!vtypeL.IsIdentical(vtypeR));
}

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
VType_VType VTYPE_VType("VType");

void VType_VType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(VType));
	// Assignment of method
	Assign(Gurax_CreateMethod(VType, __help__));
	Assign(Gurax_CreateMethod(VType, __methodSymbols__));
	Assign(Gurax_CreateMethod(VType, __methods__));
	Assign(Gurax_CreateMethod(VType, __propSlots__));
	Assign(Gurax_CreateMethod(VType, __propSlot__));
	// Assignment of property
	Assign(Gurax_CreateProperty(VType, __fullName__));
	Assign(Gurax_CreateProperty(VType, __init__));
	Assign(Gurax_CreateProperty(VType, __name__));
	Assign(Gurax_CreateProperty(VType, __symbol__));
	// Assignment of operator
	Gurax_AssignOpBinary(As, Any, VType);
	Gurax_AssignOpBinary(Eq, VType, VType);
	Gurax_AssignOpBinary(Ne, VType, VType);
}

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
VType& Value_VType::vtype = VTYPE_VType;

String Value_VType::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetVTypeThis().ToString(ss));
}

bool Value_VType::CanEvalAsMethod(const Function& function) const
{
	if (function.IsTypeConstructor()) {
		return true;
	} else if (function.IsTypeMethod()) {
		if (function.IsSet(Function::Flag::OfClass)) return true;
		Error::Issue(ErrorType::ValueError, "the function must be evaluated with an instance");
	} else {
		Error::Issue(ErrorType::ValueError, "the function can not be evaluated as a method");
	}
	return false;
}

const DeclCallable* Value_VType::GetDeclCallableWithError()
{
	const DeclCallable* pDeclCallable = GetDeclCallable();
	if (pDeclCallable) return pDeclCallable;
	Error::Issue(ErrorType::ValueError,
				 "value type %s does not have a constructor", GetVTypeThis().MakeFullName().c_str());
	return nullptr;
}

void Value_VType::PresentHelp(Processor& processor, const Symbol* pLangCode) const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	if (!constructor.IsEmpty()) constructor.PresentHelp(processor, pLangCode);
}

const DeclCallable* Value_VType::GetDeclCallable()
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	return constructor.IsEmpty()? nullptr : &constructor.GetDeclCallable();
}

void Value_VType::DoCall(Processor& processor, Argument& argument)
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	constructor.Call(processor, argument);
}

Value* Value_VType::DoEval(Processor& processor, Argument& argument) const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	return constructor.Eval(processor, argument);
}

Value* Value_VType::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const PropSlot* pPropSlot = GetVTypeThis().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		RefPtr<Value> pValue(GetVTypeThis().GetFrameOfMember().Retrieve(pSymbol));
		return pValue? pValue.release() : Value::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
	}
	if (!pPropSlot->CheckValidAttribute(attr)) return nullptr;
	if (!pPropSlot->IsSet(PropSlot::Flag::Readable)) {
		Error::Issue(ErrorType::PropertyError,
			"property '%s' is not readable", pSymbol->GetName());
		return nullptr;
	}
	if (!pPropSlot->IsSet(PropSlot::Flag::OfClass)) {
		Error::Issue(ErrorType::PropertyError,
			"property '%s' belongs to an instance", pSymbol->GetName());
		return nullptr;
	}
	return pPropSlot->GetValue(*this, attr);
}

bool Value_VType::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropSlot* pPropSlot = GetVTypeThis().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		GetVTypeThis().GetFrameOfMember().Assign(pSymbol, pValue.release());
		return true;
	}
	if (!pPropSlot->CheckValidAttribute(attr)) return false;
	if (!pPropSlot->IsSet(PropSlot::Flag::Writable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
		return false;
	}
	if (!pPropSlot->IsSet(PropSlot::Flag::OfClass)) {
		Error::Issue(ErrorType::PropertyError,
			"property '%s' belongs to an instance", pSymbol->GetName());
		return false;
	}
	return pPropSlot->SetValue(*this, *pValue, attr);
}

bool Value_VType::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	return GetVTypeThis().DoAssignCustomMethod(pFunction.release());
}

}
