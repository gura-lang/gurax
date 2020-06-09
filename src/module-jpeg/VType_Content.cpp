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
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
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
// jpeg.Content#EachSegment() {block?}
Gurax_DeclareMethod(Content, EachSegment)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns each `Segment` instance in the content.");
}

Gurax_ImplementMethod(Content, EachSegment)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new VType_Segment::Iterator_Each(
						valueThis.GetContent().GetSegmentOwner().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

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
// jpeg.Content#exif
Gurax_DeclareProperty_R(Content, exif)
{
	Declare(VTYPE_Exif, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `jpeg.Exif` instance if exists, and `nil` otherwise.");
}

Gurax_ImplementPropertyGetter(Content, exif)
{
	auto& valueThis = GetValueThis(valueTarget);
	Exif* pExif = valueThis.GetContent().FindExif();
	if (!pExif) return Value::nil();
	return new Value_Exif(pExif->Reference());
}

// jpeg.Content#jfif
Gurax_DeclareProperty_R(Content, jfif)
{
	Declare(VTYPE_Exif, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `jpeg.JFIF` instance if exists, and `nil` otherwise.");
}

Gurax_ImplementPropertyGetter(Content, jfif)
{
	auto& valueThis = GetValueThis(valueTarget);
	JFIF* pJFIF = valueThis.GetContent().FindJFIF();
	if (!pJFIF) return Value::nil();
	return new Value_JFIF(pJFIF->Reference());
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
	Assign(Gurax_CreateMethod(Content, EachSegment));
	Assign(Gurax_CreateMethod(Content, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, exif));
	Assign(Gurax_CreateProperty(Content, jfif));
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

String Value_Content::ToString(const StringStyle& ss) const
{
	return String().Format("<%s>", GetContent().ToString(ss).c_str());
}

Gurax_EndModuleScope(jpeg)
