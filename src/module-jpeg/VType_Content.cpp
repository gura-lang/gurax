//==============================================================================
// VType_Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

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
// jpeg.Content(stream:Stream) {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `jpeg.Content` instance.");
}

Gurax_ImplementConstructor(Content)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Content> pContent(new Content());
	if (!pContent->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Content(pContent.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Content#Write(stream:Stream:w):reduce
Gurax_DeclareMethod(Content, Write)
{
	Declare(VTYPE_Content, Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Writes the content data to the specified stream.\n");
}

Gurax_ImplementMethod(Content, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	if (!valueThis.GetContent().Write(stream)) return Value::nil();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// jpeg.Content#segments
Gurax_DeclareProperty_R(Content, segments)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, segments)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Iterator> pIterator(new VType_Segment::Iterator_Each(
								   valueThis.GetContent().GetSegmentOwner().Reference()));
	return new Value_Iterator(pIterator.release());
}

//------------------------------------------------------------------------------
// VType_Content
//------------------------------------------------------------------------------
VType_Content VTYPE_Content("Content");

void VType_Content::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Content));
	// Assignment of method
	Assign(Gurax_CreateMethod(Content, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, segments));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

Value* Value_Content::DoPropGet(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	Segment* pSegment = GetContent().GetSegmentMap().Lookup(pSymbol);
	if (pSegment) return pSegment->CreateValue();
	return Value_Object::DoPropGet(pSymbol, attr, notFoundErrorFlag);
}

Gurax_EndModuleScope(jpeg)
