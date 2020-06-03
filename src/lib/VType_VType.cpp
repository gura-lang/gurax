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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// VType(value):map {block?}
Gurax_DeclareFunction(VType)
{
	Declare(VTYPE_VType, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `VType` instance that represents the type information of the given `value`.\n");
}

Gurax_ImplementFunction(VType)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	return argument.ReturnValue(processor, new Value_VType(value.GetVType()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// VType#__EachPropSlot__() {block?}
Gurax_DeclareClassMethod(VType, __EachPropSlot__)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(VType, __EachPropSlot__)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<PropSlotOwner> pPropSlotOwner(new PropSlotOwner());
	for (auto iter : valueThis.GetVTypeThis().GetPropSlotMap()) {
		pPropSlotOwner->push_back(iter.second->Reference());
	}
	for (auto iter : valueThis.GetVTypeThis().GetPropSlotMapOfClass()) {
		pPropSlotOwner->push_back(iter.second->Reference());
	}
	pPropSlotOwner->SortBySymbolName();
	RefPtr<Iterator> pIterator(new Iterator_PropSlot(pPropSlotOwner.release()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// VType#__GetPropSlot__(symbol:Symbol):map {block?}
Gurax_DeclareClassMethod(VType, __GetPropSlot__)
{
	Declare(VTYPE_PropSlot, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethod(VType, __GetPropSlot__)
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

//------------------------------------------------------------------------------
// VType_VType
//------------------------------------------------------------------------------
VType_VType VTYPE_VType("VType");

void VType_VType::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateFunction(VType));
	// Assignment of method
	Assign(Gurax_CreateMethod(VType, __EachPropSlot__));
	Assign(Gurax_CreateMethod(VType, __GetPropSlot__));
	// Assignment of property
	Assign(Gurax_CreateProperty(VType, __fullName__));
}

//------------------------------------------------------------------------------
// Value_VType
//------------------------------------------------------------------------------
VType& Value_VType::vtype = VTYPE_VType;

String Value_VType::ToStringDigest(const StringStyle& ss) const
{
	const Function& constructor = GetVTypeThis().GetConstructor();
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += constructor.IsEmpty()?
		GetVTypeThis().MakeFullName() : constructor.ToString(StringStyle().SetCram());
	str += ">";
	return str;
}

String Value_VType::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

bool Value_VType::CanEvalAsMethod(const Function& function) const
{
	if ((function.IsTypeMethod() && function.IsSet(Function::Flag::OfClass)) || function.IsTypeConstructor()) {
		return true;
	} else if (function.IsTypeMethod()) {
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

Value* Value_VType::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const PropSlot* pPropSlot = GetVTypeThis().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		Value* pValue = GetVTypeThis().GetFrame().Lookup(pSymbol);
		return pValue? pValue->Reference() : Value::DoPropGet(pSymbol, attr, notFoundErrorFlag);
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

bool Value_VType::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	const PropSlot* pPropSlot = GetVTypeThis().LookupPropSlot(pSymbol);
	if (!pPropSlot) {
		GetVTypeThis().GetFrame().Assign(pSymbol, pValue.release());
		return true;
	}
	if (!pPropSlot->CheckValidAttribute(attr)) return false;
	if (!pPropSlot->IsSet(PropSlot::Flag::Writable)) {
		Error::Issue(ErrorType::PropertyError, "property '%s' is not writable", pSymbol->GetName());
		return false;
	}
	return pPropSlot->SetValue(*this, *pValue, attr);
}

bool Value_VType::DoAssignCustomMethod(RefPtr<Function> pFunction)
{
	return GetVTypeThis().DoAssignCustomMethod(pFunction.release());
}

}
