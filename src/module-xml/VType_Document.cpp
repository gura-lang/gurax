//==============================================================================
// VType_Document.cpp
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
// xml.Document() {block?}
Gurax_DeclareConstructor(Document)
{
	Declare(VTYPE_Document, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.Document` instance.");
}

Gurax_ImplementConstructor(Document)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Document> pDocument(new Document());
	return argument.ReturnValue(processor, new Value_Document(pDocument.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.Document#Compose(stream? as Stream):void
Gurax_DeclareMethod(Document, Compose)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Document, Compose)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : Stream::COut.get();
	// Function body
	valueThis.GetDocument().Compose(*pStream);
	return Value::nil();
}

// xml.Document#Path(path as String) {block?} as Element
Gurax_DeclareMethod(Document, Path)
{
	Declare(VTYPE_Element, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Document, Path)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* path = args.PickString();
	// Function body
	const Element* pElement = valueThis.GetDocument().Path(path);
	if (!pElement) return Value::nil();
	return argument.ReturnValue(processor, new Value_Element(pElement->Reference()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Document#root
Gurax_DeclareProperty_R(Document, root)
{
	Declare(VTYPE_Element, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Document, root)
{
	Document& doc = GetValueThis(valueTarget).GetDocument();
	if (doc.HasElementRoot()) return new Value_Element(doc.GetElementRoot().Reference());
	return Value::nil();
}

// xml.Document#xmlDecl
Gurax_DeclareProperty_R(Document, xmlDecl)
{
	Declare(VTYPE_Element, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Document, xmlDecl)
{
	Document& doc = GetValueThis(valueTarget).GetDocument();
	if (doc.HasXmlDecl()) return new Value_XmlDecl(doc.GetXmlDecl().Reference());
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Document
//------------------------------------------------------------------------------
VType_Document VTYPE_Document("Document");

void VType_Document::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Document));
	// Assignment of method
	Assign(Gurax_CreateMethod(Document, Compose));
	Assign(Gurax_CreateMethod(Document, Path));
	// Assignment of property
	Assign(Gurax_CreateProperty(Document, root));
	Assign(Gurax_CreateProperty(Document, xmlDecl));
}

//------------------------------------------------------------------------------
// Value_Document
//------------------------------------------------------------------------------
VType& Value_Document::vtype = VTYPE_Document;

String Value_Document::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetDocument().ToString(ss));
}

Gurax_EndModuleScope(xml)
