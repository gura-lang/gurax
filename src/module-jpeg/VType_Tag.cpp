//==============================================================================
// VType_Tag.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(jpeg.Tag, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.Tag, `en)}

${help.ComposeMethodHelp(jpeg.Tag, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// jpeg.Tag(symbolOfIFD as Symbol, symbol as Symbol, value as any) {block?}
Gurax_DeclareConstructor(Tag)
{
	Declare(VTYPE_Tag, Flag::None);
	DeclareArg("symbolOfIFD", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("symbol", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `jpeg.Tag` instance.
)**");
}

Gurax_ImplementConstructor(Tag)
{
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbolOfIFD = args.PickSymbol();
	const Symbol* pSymbol = args.PickSymbol();
	const Value& value = args.PickValue();
	// Function body
	RefPtr<Tag> pTag(Tag::Create(pSymbolOfIFD, pSymbol));
	if (!pTag) return Value::nil();
	if (!pTag->AssignValue(value.Reference())) return false;
	return argument.ReturnValue(processor, new Value_Tag(pTag.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Tag#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Tag, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Tag, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.Tag#name
Gurax_DeclareProperty_R(Tag, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetTag().GetSymbol()->GetName());
}

// jpeg.Tag#orderHint
Gurax_DeclareProperty_R(Tag, orderHint)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, orderHint)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTag().GetOrderHint());
}

// jpeg.Tag#symbol
Gurax_DeclareProperty_R(Tag, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetTag().GetSymbol());
}

// jpeg.Tag#tagId
Gurax_DeclareProperty_R(Tag, tagId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, tagId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTag().GetTagId());
}

// jpeg.Tag#type
Gurax_DeclareProperty_R(Tag, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(Tag::TypeIdToSymbol(valueThis.GetTag().GetTypeId()));
}

// jpeg.Tag#typeId
Gurax_DeclareProperty_R(Tag, typeId)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, typeId)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetTag().GetTypeIdRaw());
}

// jpeg.Tag#value
Gurax_DeclareProperty_RW(Tag, value)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetTag().GetValue().Reference();
}

Gurax_ImplementPropertySetter(Tag, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetTag().AssignValue(value.Reference());
}

// jpeg.Tag#vtypeAcceptable
Gurax_DeclareProperty_R(Tag, vtypeAcceptable)
{
	Declare(VTYPE_VType, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Tag, vtypeAcceptable)
{
	auto& valueThis = GetValueThis(valueTarget);
	VType& vtype = valueThis.GetTag().GetVTypeAcceptable();
	return new Value_VType(vtype);
}

//------------------------------------------------------------------------------
// VType_Tag
//------------------------------------------------------------------------------
VType_Tag VTYPE_Tag("Tag");

void VType_Tag::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Tag));
	// Assignment of method
	Assign(Gurax_CreateMethod(Tag, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Tag, name));
	Assign(Gurax_CreateProperty(Tag, orderHint));
	Assign(Gurax_CreateProperty(Tag, symbol));
	Assign(Gurax_CreateProperty(Tag, tagId));
	Assign(Gurax_CreateProperty(Tag, type));
	Assign(Gurax_CreateProperty(Tag, typeId));
	Assign(Gurax_CreateProperty(Tag, value));
	Assign(Gurax_CreateProperty(Tag, vtypeAcceptable));
}

//------------------------------------------------------------------------------
// VType_Tag::Iterator_Each
//------------------------------------------------------------------------------
Value* VType_Tag::Iterator_Each::DoNextValue()
{
	if (_idx >= GetTagOwner().size()) return nullptr;
	RefPtr<Tag> pTag(GetTagOwner()[_idx]->Reference());
	_idx++;
	return new Value_Tag(pTag.release());
}

String VType_Tag::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "Tag.Each";
}

//------------------------------------------------------------------------------
// Value_Tag
//------------------------------------------------------------------------------
VType& Value_Tag::vtype = VTYPE_Tag;

String Value_Tag::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetTag().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
