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
// xml.Attrs#Each() {block?}
Gurax_DeclareMethod(Attrs, Each)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Attrs, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Attr(valueThis.GetAttrs().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
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
	Assign(Gurax_CreateMethod(Attrs, Each));
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
