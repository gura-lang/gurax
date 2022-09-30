//==============================================================================
// VType_Attrs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

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
// xml.Attrs() {block?}
Gurax_DeclareConstructor(Attrs)
{
	Declare(VTYPE_Attrs, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Attrs` instance.");
}

Gurax_ImplementConstructor(Attrs)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<AttrOwner> pAttrs(new AttrOwner());
	return argument.ReturnValue(processor, new Value_Attrs(pAttrs.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Attrs#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Attrs, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Attrs, MethodSkeleton)
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
// xml.Attrs#propSkeleton
Gurax_DeclareProperty_R(Attrs, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Attrs, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Attrs
//------------------------------------------------------------------------------
VType_Attrs VTYPE_Attrs("Attrs");

void VType_Attrs::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Attrs));
	// Assignment of method
	Assign(Gurax_CreateMethod(Attrs, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Attrs, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Attrs
//------------------------------------------------------------------------------
VType& Value_Attrs::vtype = VTYPE_Attrs;

String Value_Attrs::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "xml.Attrs");
}

Gurax_EndModuleScope(xml)
