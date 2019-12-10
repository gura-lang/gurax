//==============================================================================
// VType_Document.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(markdown)

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
// markdown.Document(stream?:Stream:r) {block?}
Gurax_DeclareConstructor(Document)
{
	Declare(VTYPE_Document, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns an instance of `markdown.document`.\n"
		"If `stream` is specified, the content of the instance shall be initialized\n"
		"with the result of parsing the stream.\n");
}

Gurax_ImplementConstructor(Document)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	// Function body
	RefPtr<Document> pDocument(new Document());
	if (pStream && !pDocument->ParseStream(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Document(pDocument.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// markdown.Document#CountItem(type:Symbol)
Gurax_DeclareMethod(Document, CountItem)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("type", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Count the number of items of the specified type.");
}

Gurax_ImplementMethod(Document, CountItem)
{
	// Target
	Document& document = GetValueThis(argument).GetDocument();
	// Arguments
	ArgPicker args(argument);
	const Symbol* pSymbol = args.PickSymbol();
	Item::Type type = Item::SymbolAssoc_Type::GetInstance().ToAssociated(pSymbol);
	if (type == Item::Type::None) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for item type: `%s", pSymbol->GetName());
		return Value::nil();
	}
	// Function body
	size_t cnt = Item::CountByType(*document.GetItemRoot().GetItemOwner(), type, true);
	return new Value_Number(cnt);
}

// markdown.Document#Parse(str:String):reduce
Gurax_DeclareMethod(Document, Parse)
{
	Declare(VTYPE_Document, Flag::Reduce);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Parses a Markdown text in a string.");
}

Gurax_ImplementMethod(Document, Parse)
{
	// Target
	Document& document = GetValueThis(argument).GetDocument();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	if (!document.ParseString(str)) return Value::nil();
	return argument.GetValueThis().Reference();
}

// markdown.Document#Read(stream:Stream:r):reduce
Gurax_DeclareMethod(Document, Read)
{
	Declare(VTYPE_Document, Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	AddHelp(
		Gurax_Symbol(en),
		"Parses a Markdown text from a stream.");
}

Gurax_ImplementMethod(Document, Read)
{
	// Target
	Document& document = GetValueThis(argument).GetDocument();
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!document.ParseStream(stream)) return Value::nil();
	return argument.GetValueThis().Reference();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// markdown.Document#refs
Gurax_DeclareProperty_R(Document, refs)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"An `iterator` that returns referee items typed as `markdown.Item`.");
}

Gurax_ImplementPropertyGetter(Document, refs)
{
	// Target
	Document& document = GetValueThis(valueTarget).GetDocument();
	RefPtr<Iterator> pIterator(new Iterator_Item(document.GetItemRefereeOwner().Reference()));
	return new Value_Iterator(pIterator.release());
}

// markdown.document#root
Gurax_DeclareProperty_R(Document, root)
{
	Declare(VTYPE_Item, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The root item of the parsed Markdown document.");
}

Gurax_ImplementPropertyGetter(Document, root)
{
	// Target
	Document& document = GetValueThis(valueTarget).GetDocument();
	document.ResolveReference();
	return new Value_Item(document.GetItemRoot().Reference());
}

//------------------------------------------------------------------------------
// Implementation of operators
//------------------------------------------------------------------------------
// operator <<
Gurax_ImplementOpBinary(Shl, Document, String)
{
	Document& document = Value_Document::GetDocument(valueL);
	const char* str = Value_String::GetString(valueR);
	if (!document.ParseString(str)) return Value::nil();
	return valueL.Reference();
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
	Assign(Gurax_CreateMethod(Document, CountItem));
	Assign(Gurax_CreateMethod(Document, Parse));
	Assign(Gurax_CreateMethod(Document, Read));
	// Assignment of property
	Assign(Gurax_CreateProperty(Document, refs));
	Assign(Gurax_CreateProperty(Document, root));
	// Assignment of operator
	Gurax_AssignOpBinary(Shl, Document, String);
}

//------------------------------------------------------------------------------
// Value_Document
//------------------------------------------------------------------------------
VType& Value_Document::vtype = VTYPE_Document;

Gurax_EndModuleScope(markdown)
