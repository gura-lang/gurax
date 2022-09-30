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
// xml.Document#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Document, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Document, MethodSkeleton)
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
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Element(valueThis.GetDocument().GetElementRoot().Reference());
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
	Assign(Gurax_CreateMethod(Document, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Document, root));
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
