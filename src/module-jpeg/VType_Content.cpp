//==============================================================================
// VType_Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(jpeg.Content, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(jpeg.Content, `en)}

${help.ComposeMethodHelp(jpeg.Content, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// jpeg.Content(stream?:Stream) {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads JPEG image data from `stream` and creates a `jpeg.Content` instance.
)""");
}

Gurax_ImplementConstructor(Content)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	// Function body
	RefPtr<Content> pContent(new Content());
	if (pStream) if (!pContent->Read(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Content(pContent.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// jpeg.Content#AddSegment(segment as Segment):void:map
Gurax_DeclareMethod(Content, AddSegment)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("segment", VTYPE_Segment, DeclArg::Occur::Once, DeclArg::Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds a `segment` to the target content.
)""");
}

Gurax_ImplementMethod(Content, AddSegment)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Segment& segment = args.Pick<Value_Segment>().GetSegment();
	// Function body
	valueThis.GetContent().AddSegment(segment.Reference());
	return Value::nil();
}

// jpeg.Content#EachSegment() {block?}
Gurax_DeclareMethod(Content, EachSegment)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns each `Segment` instance in the content.
)""");
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

// jpeg.Content#GetBuffImage() {block?}
Gurax_DeclareMethod(Content, GetBuffImage)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns an image data in `Binary`.
)""");
}

Gurax_ImplementMethod(Content, GetBuffImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const BinaryReferable* pBuffImage = valueThis.GetContent().GetBuffImage();
	return argument.ReturnValue(processor, pBuffImage? Value::nil() : new Value_Binary(pBuffImage->Reference()));
}

// jpeg.Content#SetBuffImage(buffImage as Binary)
Gurax_DeclareMethod(Content, SetBuffImage)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Sets an image data `buffImage`.
)""");
}

Gurax_ImplementMethod(Content, SetBuffImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const BinaryReferable& buffImage = args.Pick<Value_Binary>().GetBinaryReferable();
	// Function body
	valueThis.GetContent().SetBuffImage(buffImage.Reference());
	return Value::nil();
}

// jpeg.Content#Write(stream:Stream:w):reduce
Gurax_DeclareMethod(Content, Write)
{
	Declare(VTYPE_Content, Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	AddHelp(Gurax_Symbol(en), u8R"""(
Writes the content data to the specified `stream`.
)""");
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
// jpeg.Content#buffImage
Gurax_DeclareProperty_RW(Content, buffImage)
{
	Declare(VTYPE_Binary, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Represents an image buffer in the content.
)""");
}

Gurax_ImplementPropertyGetter(Content, buffImage)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable* pBuffImage = valueThis.GetContent().GetBuffImage();
	if (!pBuffImage) return Value::nil();
	return new Value_Binary(pBuffImage->Reference());
}

Gurax_ImplementPropertySetter(Content, buffImage)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (value.IsInvalid()) {
		valueThis.GetContent().SetBuffImage(nullptr);
		return;
	}
	const BinaryReferable& buffImage = Value_Binary::GetBinaryReferable(value);
	valueThis.GetContent().SetBuffImage(buffImage.Reference());	
}

// jpeg.Content#exif
Gurax_DeclareProperty_R(Content, exif)
{
	Declare(VTYPE_Exif, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `jpeg.Exif` instance if exists, and `nil` otherwise.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `jpeg.JFIF` instance if exists, and `nil` otherwise.
)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Content));
	// Assignment of method
	Assign(Gurax_CreateMethod(Content, AddSegment));
	Assign(Gurax_CreateMethod(Content, EachSegment));
	Assign(Gurax_CreateMethod(Content, GetBuffImage));
	Assign(Gurax_CreateMethod(Content, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, buffImage));
	Assign(Gurax_CreateProperty(Content, exif));
	Assign(Gurax_CreateProperty(Content, jfif));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

Value* Value_Content::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	Segment* pSegment = GetContent().GetSegmentMap().Lookup(pSymbol);
	if (pSegment) return pSegment->CreateValue();
	return Value_Object::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

String Value_Content::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(jpeg)
