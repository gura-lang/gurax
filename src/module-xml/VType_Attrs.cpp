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

${help.ComposePropertyHelp(xml.Attrs, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Attrs, `en)}

${help.ComposeMethodHelp(xml.Attrs, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.Attrs() {block?}
Gurax_DeclareConstructor(Attrs)
{
	Declare(VTYPE_Attrs, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `xml.Attrs` instance.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
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
// xml.Attrs#len
Gurax_DeclareProperty_R(Attrs, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Attrs, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetAttrs().size());
}

//------------------------------------------------------------------------------
// VType_Attrs
//------------------------------------------------------------------------------
VType_Attrs VTYPE_Attrs("Attrs");

void VType_Attrs::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Attrs));
	// Assignment of method
	Assign(Gurax_CreateMethod(Attrs, Each));
	// Assignment of property
	Assign(Gurax_CreateProperty(Attrs, len));
}

//------------------------------------------------------------------------------
// Value_Attrs
//------------------------------------------------------------------------------
VType& Value_Attrs::vtype = VTYPE_Attrs;

bool Value_Attrs::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const Attr* pAttr = GetAttrs().IndexGet(valueIndex);
	if (!pAttr) return false;
	*ppValue = new Value_Attr(pAttr->Reference());
	return true;
}

String Value_Attrs::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "xml.Attrs");
}

Gurax_EndModuleScope(xml)
