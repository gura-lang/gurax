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
// jpeg.IFD(symbol as Symbol) {block?}
Gurax_DeclareConstructor(IFD)
{
	Declare(VTYPE_IFD, Flag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.IFD` instance.");
}

Gurax_ImplementConstructor(IFD)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	RefPtr<IFD> pIFD(new IFD(pSymbol, new TagOwner()));
	return argument.ReturnValue(processor, new Value_IFD(pIFD.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.IFD#AddTag(tag as Tag):void:map
Gurax_DeclareMethod(IFD, AddTag)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("tag", VTYPE_Tag, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds `Tag` instance to the IFD.");
}

Gurax_ImplementMethod(IFD, AddTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Tag& tag = args.Pick<Value_Tag>().GetTag();
	// Function body
	valueThis.GetIFD().AddTag(tag.Reference());
	return Value::nil();
}

// jpeg.IFD#DeleteTag(symbol as Symbol):void:map
Gurax_DeclareMethod(IFD, DeleteTag)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Deletes `Tag` instance in the IFD.");
}

Gurax_ImplementMethod(IFD, DeleteTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	valueThis.GetIFD().DeleteTag(pSymbol);
	return Value::nil();
}

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

// jpeg.IFD#FindTag(symbol as Symbol):map
Gurax_DeclareMethod(IFD, FindTag)
{
	Declare(VTYPE_Tag, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Finds `Tag` instance in the IFD.");
}

Gurax_ImplementMethod(IFD, FindTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Tag* pTag = valueThis.GetIFD().FindTag(pSymbol);
	if (!pTag) return Value::nil(); 
	return new Value_Tag(pTag->Reference());
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
	Assign(Gurax_CreateMethod(IFD, AddTag));
	Assign(Gurax_CreateMethod(IFD, DeleteTag));
	Assign(Gurax_CreateMethod(IFD, EachTag));
	Assign(Gurax_CreateMethod(IFD, FindTag));
	// Assignment of property
	Assign(Gurax_CreateProperty(IFD, symbol));
}

Value* VType_IFD::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsList()) {
		const ValueList& valueList = Value_List::GetValueOwner(value);
		RefPtr<IFD> pIFD(IFD::CreateFromList(Symbol::Empty, valueList));
		if (!pIFD) return nullptr;
		return new Value_IFD(pIFD.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_IFD
//------------------------------------------------------------------------------
VType& Value_IFD::vtype = VTYPE_IFD;

Value* Value_IFD::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const Value* pValue = GetIFD().LookupTagValue(pSymbol);
	return pValue? pValue->Reference() : Value_Object::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

bool Value_IFD::DoSetProperty(const Symbol* pSymbol, RefPtr<Value> pValue, const Attribute& attr)
{
	if (GetIFD().AssignTagValue(pSymbol, pValue.Reference())) return true;
	if (Error::IsIssued()) return false;
	return Value_Object::DoSetProperty(pSymbol, pValue.release(), attr);
}

String Value_IFD::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetIFD().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
