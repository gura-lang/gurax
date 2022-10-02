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
// xml.Element(name as String) {block?}
Gurax_DeclareConstructor(Element)
{
	Declare(VTYPE_Element, Flag::None);
	DeclareArg("name", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Element` instance.");
}

Gurax_ImplementConstructor(Element)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	RefPtr<Element> pElement(new Element(name));
	return argument.ReturnValue(processor, new Value_Element(pElement.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Element#attrs
Gurax_DeclareProperty_R(Element, attrs)
{
	Declare(VTYPE_Attrs, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Element, attrs)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Attrs(valueThis.GetElement().GetAttrs().Reference());
}

// xml.Element#children
Gurax_DeclareProperty_R(Element, children)
{
	Declare(VTYPE_Nodes, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Element, children)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Nodes(valueThis.GetElement().GetNodesChild().Reference());
}

// xml.Element#name
Gurax_DeclareProperty_R(Element, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Element, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetElement().GetName());
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
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(Element));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Element, Each));
	// Assignment of property
	Assign(Gurax_CreateProperty(Element, attrs));
	Assign(Gurax_CreateProperty(Element, children));
	Assign(Gurax_CreateProperty(Element, name));
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
