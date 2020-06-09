//==============================================================================
// VType_IFD.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

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
// jpeg.IFD(init[]) {block?}
Gurax_DeclareConstructor(IFD)
{
	Declare(VTYPE_IFD, Flag::None);
	DeclareArg("init", VTYPE_Any, ArgOccur::Once, ArgFlag::ListVar);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.IFD` instance.");
}

Gurax_ImplementConstructor(IFD)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	RefPtr<IFD> pIFD(IFD::CreateFromList(valueList, Symbol::Empty));
	if (!pIFD) return Value::nil();
	return argument.ReturnValue(processor, new Value_IFD(pIFD.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.IFD#EachTag() {block?}
Gurax_DeclareMethod(IFD, EachTag)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(IFD, EachTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const IFD& ifd = valueThis.GetIFD();
	RefPtr<Iterator> pIterator(new VType_Tag::Iterator_Each(ifd.GetTagOwner().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.IFD#symbol
Gurax_DeclareProperty_R(IFD, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(IFD, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetIFD().GetSymbolOfIFD());
}

//------------------------------------------------------------------------------
// VType_IFD
//------------------------------------------------------------------------------
VType_IFD VTYPE_IFD("IFD");

void VType_IFD::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(IFD));
	// Assignment of method
	Assign(Gurax_CreateMethod(IFD, EachTag));
	// Assignment of property
	Assign(Gurax_CreateProperty(IFD, symbol));
}

Value* VType_IFD::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsList()) {
		const ValueList& valueList = Value_List::GetValueOwner(value);
		RefPtr<IFD> pIFD(IFD::CreateFromList(valueList, Symbol::Empty));
		if (!pIFD) return nullptr;
		return new Value_IFD(pIFD.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_IFD
//------------------------------------------------------------------------------
VType& Value_IFD::vtype = VTYPE_IFD;

Value* Value_IFD::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const Value* pValue = GetIFD().LookupTagValue(pSymbol);
	return pValue? pValue->Reference() : Value_Object::DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

bool Value_IFD::DoPropSet(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	if (GetIFD().AssignTagValue(pSymbol, pValue.Reference())) return true;
	if (Error::IsIssued()) return false;
	return Value_Object::DoPropSet(pSymbol, pValue.release(), attr);
}

String Value_IFD::ToString(const StringStyle& ss) const
{
	return String().Format("<%s>", GetIFD().ToString(ss).c_str());
}

Gurax_EndModuleScope(jpeg)
