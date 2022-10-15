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
// xml.Element#Each():[cdata,comment,element,text] {block?}
Gurax_DeclareMethod(Element, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(cdata));
	DeclareAttrOpt(Gurax_Symbol(comment));
	DeclareAttrOpt(Gurax_Symbol(element));
	DeclareAttrOpt(Gurax_Symbol(text));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Each(
			valueThis.GetElement().GetNodesChild().Reference(), Node::GetTypeMask(argument)));
	return argument.ReturnIterator(processor, pIterator.release());
}

// xml.Element#EnumElement(tagName as String) {block?}
Gurax_DeclareMethod(Element, EnumElement)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("tagName", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, EnumElement)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* tagName = args.PickString();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_EnumElement(valueThis.GetElement().GetNodesChild().Reference(), tagName));
	return argument.ReturnIterator(processor, pIterator.release());
}

// xml.Element#FindElement(tagName as String) {block?}
Gurax_DeclareMethod(Element, FindElement)
{
	Declare(VTYPE_Element, Flag::None);
	DeclareArg("tagName", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, FindElement)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* tagName = args.PickString();
	// Function body
	const Element* pElement = valueThis.GetElement().GetNodesChild().FindElement(tagName);
	if (!pElement) return Value::nil();
	return argument.ReturnValue(processor, new Value_Element(pElement->Reference()));
}

// xml.Element#GetAttr(index)
Gurax_DeclareMethod(Element, GetAttr)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("index", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, GetAttr)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& valueIndex = args.PickValue();
	// Function body
	const Attr* pAttr = valueThis.GetElement().GetAttrs().IndexGet(valueIndex);
	if (!pAttr) return Value::nil();
	return new Value_Attr(pAttr->Reference());
}

// xml.Element#GetAttrName(index)
Gurax_DeclareMethod(Element, GetAttrName)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("index", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, GetAttrName)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& valueIndex = args.PickValue();
	// Function body
	const Attr* pAttr = valueThis.GetElement().GetAttrs().IndexGet(valueIndex);
	if (!pAttr) return Value::nil();
	return new Value_String(pAttr->GetName());
}

// xml.Element#GetAttrValue(index)
Gurax_DeclareMethod(Element, GetAttrValue)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("index", VTYPE_Any, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, GetAttrValue)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Value& valueIndex = args.PickValue();
	// Function body
	const Attr* pAttr = valueThis.GetElement().GetAttrs().IndexGet(valueIndex);
	if (!pAttr) return Value::nil();
	return new Value_String(pAttr->GetValue());
}

// xml.Element#TextizeStart()
Gurax_DeclareMethod(Element, TextizeStart)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, TextizeStart)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetElement().TextizeStart());
}

// xml.Element#TextizeEnd()
Gurax_DeclareMethod(Element, TextizeEnd)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, TextizeEnd)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetElement().TextizeEnd());
}

// xml.Element#TextizeEmpty()
Gurax_DeclareMethod(Element, TextizeEmpty)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, TextizeEmpty)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	return new Value_String(valueThis.GetElement().TextizeEmpty());
}

// xml.Element#Walk():[cdata,comment,element,text] {block?}
Gurax_DeclareMethod(Element, Walk)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(cdata));
	DeclareAttrOpt(Gurax_Symbol(comment));
	DeclareAttrOpt(Gurax_Symbol(element));
	DeclareAttrOpt(Gurax_Symbol(text));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Element, Walk)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const Element& element = valueThis.GetElement();
	RefPtr<Iterator> pIterator(new Iterator_Walk(element.Reference(), Node::GetTypeMask(argument)));
	return argument.ReturnIterator(processor, pIterator.release());
}

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

// xml.Element#text
Gurax_DeclareProperty_R(Element, text)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Element, text)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetElement().AccumText());
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
	Assign(Gurax_CreateMethod(Element, Each));
	Assign(Gurax_CreateMethod(Element, EnumElement));
	Assign(Gurax_CreateMethod(Element, FindElement));
	Assign(Gurax_CreateMethod(Element, GetAttr));
	Assign(Gurax_CreateMethod(Element, GetAttrName));
	Assign(Gurax_CreateMethod(Element, GetAttrValue));
	Assign(Gurax_CreateMethod(Element, TextizeStart));
	Assign(Gurax_CreateMethod(Element, TextizeEnd));
	Assign(Gurax_CreateMethod(Element, TextizeEmpty));
	Assign(Gurax_CreateMethod(Element, Walk));
	// Assignment of property
	Assign(Gurax_CreateProperty(Element, attrs));
	Assign(Gurax_CreateProperty(Element, children));
	Assign(Gurax_CreateProperty(Element, name));
	Assign(Gurax_CreateProperty(Element, text));
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
