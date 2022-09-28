//==============================================================================
// VType_Element.cpp
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
// xml.Element() {block?}
Gurax_DeclareConstructor(Element)
{
	Declare(VTYPE_Element, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Element` instance.");
}

Gurax_ImplementConstructor(Element)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Element> pElement(new Element("", nullptr));
	return argument.ReturnValue(processor, new Value_Element(pElement.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Element#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Element, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, MethodSkeleton)
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
// xml.Element#propSkeleton
Gurax_DeclareProperty_R(Element, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Element, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Element
//------------------------------------------------------------------------------
VType_Element VTYPE_Element("Element");

void VType_Element::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Element));
	// Assignment of method
	Assign(Gurax_CreateMethod(Element, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Element, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Element
//------------------------------------------------------------------------------
VType& Value_Element::vtype = VTYPE_Element;

String Value_Element::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetElement().ToString(ss));
}

Gurax_EndModuleScope(xml)
