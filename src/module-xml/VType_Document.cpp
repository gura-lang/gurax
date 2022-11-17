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

${help.ComposePropertyHelp(xml.Document, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(xml.Document, `en)}

${help.ComposeMethodHelp(xml.Document, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// xml.Document() {block?}
Gurax_DeclareConstructor(Document)
{
	Declare(VTYPE_Document, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `xml.Document` instance.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Document, Path)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* path = args.PickString();
	// Function body
	RefPtr<Value> pValueRtn(valueThis.GetDocument().Path(path));
	if (!pValueRtn) return Value::nil();
	return argument.ReturnValue(processor, pValueRtn.release());
}

// xml.Document#Walk(tagName? as String):[cdata,comment,element,text] {block?}
Gurax_DeclareMethod(Document, Walk)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("tagName", VTYPE_String, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None);
	DeclareAttrOpt(Gurax_Symbol(cdata));
	DeclareAttrOpt(Gurax_Symbol(comment));
	DeclareAttrOpt(Gurax_Symbol(element));
	DeclareAttrOpt(Gurax_Symbol(text));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(Document, Walk)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	ArgPicker args(argument);
	const char* tagName = args.IsValid()? args.PickString() : "";
	// Function body
	const Element& element = valueThis.GetDocument().GetElementRoot();
	RefPtr<Iterator> pIterator(new Iterator_Walk(
			element.Reference(), Node::GetTypeMask(argument.GetAttr()), tagName));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.Document#root
Gurax_DeclareProperty_R(Document, root)
{
	Declare(VTYPE_Element, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Document));
	// Assignment of method
	Assign(Gurax_CreateMethod(Document, Compose));
	Assign(Gurax_CreateMethod(Document, Path));
	Assign(Gurax_CreateMethod(Document, Walk));
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
