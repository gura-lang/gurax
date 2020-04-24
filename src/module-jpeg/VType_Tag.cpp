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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// jpeg.Tag() {block?}
Gurax_DeclareConstructor(Tag)
{
	Declare(VTYPE_Tag, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.Tag` instance.");
}

Gurax_ImplementConstructor(Tag)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<Tag> pTag(new Tag());
	//return argument.ReturnValue(processor, new Value_Tag(pTag.release()));
	return Value::nil();
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
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Tag, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetTag().GetSymbol()->GetName());
}

// jpeg.Tag#symbol
Gurax_DeclareProperty_R(Tag, symbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Tag, symbol)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetTag().GetSymbol());
}

// jpeg.Tag#type
Gurax_DeclareProperty_R(Tag, type)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Tag, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(Tag::TypeIdToSymbol(valueThis.GetTag().GetTypeId()));
}

// jpeg.Tag#value
Gurax_DeclareProperty_R(Tag, value)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Tag, value)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetTag().GetValue().Reference();
}

//------------------------------------------------------------------------------
// VType_Tag
//------------------------------------------------------------------------------
VType_Tag VTYPE_Tag("Tag");

void VType_Tag::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Tag));
	// Assignment of method
	Assign(Gurax_CreateMethod(Tag, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Tag, name));
	Assign(Gurax_CreateProperty(Tag, symbol));
	Assign(Gurax_CreateProperty(Tag, type));
	Assign(Gurax_CreateProperty(Tag, value));
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

Gurax_EndModuleScope(jpeg)
