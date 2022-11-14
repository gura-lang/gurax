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

${help.ComposePropertyHelp(jpeg.IFD, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.IFD, `en)}

${help.ComposeMethodHelp(jpeg.IFD, `en)}
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
	AddHelp("en", u8R"**(
Creates a `jpeg.IFD` instance.
)**");
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
	AddHelp("en", u8R"**(
Adds `Tag` instance to the IFD.
)**");
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

// jpeg.IFD#CreateTag(symbol as Symbol):map {block?}
Gurax_DeclareMethod(IFD, CreateTag)
{
	Declare(VTYPE_Tag, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `Tag` instance in the IFD.
)**");
}

Gurax_ImplementMethod(IFD, CreateTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	RefPtr<Tag> pTag(valueThis.GetIFD().CreateTag(pSymbol));
	if (!pTag) return Value::nil();
	return argument.ReturnValue(processor, new Value_Tag(pTag.release()));
}

// jpeg.IFD#DeleteTag(symbol as Symbol):void:map
Gurax_DeclareMethod(IFD, DeleteTag)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp("en", u8R"**(
Deletes `Tag` instance in the IFD.
)**");
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
	AddHelp("en", u8R"**(

)**");
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

// jpeg.IFD#FindTag(symbol as Symbol):map:[raise]
Gurax_DeclareMethod(IFD, FindTag)
{
	Declare(VTYPE_Tag, Flag::Map);
	DeclareArg("symbol", VTYPE_Symbol, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	AddHelp("en", u8R"**(
Finds `Tag` instance in the IFD.
)**");
}

Gurax_ImplementMethod(IFD, FindTag)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	// Function body
	Tag* pTag = valueThis.GetIFD().GetTagMap().Lookup(pSymbol);
	if (!pTag) {
		if (argument.IsSet(Gurax_Symbol(raise))) {
			Error::Issue(ErrorType::KeyError, "specified symbol is not found");
		}
		return Value::nil();
	}
	return new Value_Tag(pTag->Reference());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.IFD#symbol
Gurax_DeclareProperty_R(IFD, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(IFD));
	// Assignment of method
	Assign(Gurax_CreateMethod(IFD, AddTag));
	Assign(Gurax_CreateMethod(IFD, CreateTag));
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
	Tag* pTag = GetIFD().GetTagMap().Lookup(pSymbol);
	return pTag? pTag->GetValue().Reference() : Value_Object::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
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
