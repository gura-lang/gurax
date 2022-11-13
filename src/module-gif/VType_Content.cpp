//==============================================================================
// VType_Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(gif.Content, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(gif.Content, `en)}

${help.ComposeMethodHelp(gif.Content, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// gif.Content(stream?:Stream:r):[rgb,rgba] {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `gif.Content` instance.
)**");
}

Gurax_ImplementConstructor(Content)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Content> pContent(new Content());
	if (pStream && !pContent->Read(*pStream, format)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Content(pContent.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// gif.Content#AddImage(image:Image, delayTime?:Number, leftPos?:Number, topPos?:Number, disposalMethod?:Symbol):reduce:map
Gurax_DeclareMethod(Content, AddImage)
{
	Declare(VTYPE_Content, Flag::Reduce | Flag::Map);
	DeclareArg("image", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
	DeclareArg("delayTime", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("leftPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("topPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("disposalMethod", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethod(Content, AddImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Image& image = args.PickImage();
	UInt16 delayTime = args.IsValid()? args.PickNumberNonNeg<UInt16>() : 0;
	UInt16 imageLeftPosition = args.IsValid()? args.PickNumberNonNeg<UInt16>() : 0;
	UInt16 imageTopPosition = args.IsValid()? args.PickNumberNonNeg<UInt16>() : 0;
	UInt8 disposalMethod = Content::DisposalMethod::None;
	if (args.IsValid()) {
		const Symbol* pSymbol = args.PickSymbol();
		disposalMethod = 
			pSymbol->IsIdentical(Gurax_Symbol(keep))? Content::DisposalMethod::Keep :
			pSymbol->IsIdentical(Gurax_Symbol(background))? Content::DisposalMethod::Background :
			pSymbol->IsIdentical(Gurax_Symbol(previous))? Content::DisposalMethod::Previous :
			Content::DisposalMethod::None;
		if (disposalMethod == Content::DisposalMethod::None) {
			Error::Issue(ErrorType::SymbolError, "invalid symbol for disposalMethod");
			return Value::nil();
		}
	}
	// Function body
	valueThis.GetContent().AddImage(image, delayTime, imageLeftPosition, imageTopPosition, disposalMethod);
	return valueThis.Reference();
}

// gif.Content#EachImage() {block?}
Gurax_DeclareMethod(Content, EachImage)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an iterator that returns images stored in the GIF file.
)**");
}

Gurax_ImplementMethod(Content, EachImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Content::Iterator_EachImage(valueThis.GetContent().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

// gif.Content#Write(stream:Stream:w, colorBackground?:Color):reduce
Gurax_DeclareMethod(Content, Write)
{
	Declare(VTYPE_Content, Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("colorBackground", VTYPE_Color, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethod(Content, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	bool validBackgroundFlag = false;
	const Color& colorBackground = (validBackgroundFlag = args.IsValid())? args.PickColor() : Color::zero;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (!valueThis.GetContent().Write(stream, colorBackground, validBackgroundFlag)) return Value::nil();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gif.Content#CommentExtension:nil
Gurax_DeclareProperty_R(Content, CommentExtension)
{
	Declare(VTYPE_CommentExtension, Flag::Nil);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, CommentExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& content = valueThis.GetContent();
	if (!content.GetExtensions().commentExtension.validFlag) return Value::nil();
	return new Value_CommentExtension(content.GetExtensions().commentExtension, content.Reference());
}

// gif.Content#LogicalScreenDescriptor
Gurax_DeclareProperty_R(Content, LogicalScreenDescriptor)
{
	Declare(VTYPE_LogicalScreenDescriptor, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, LogicalScreenDescriptor)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_LogicalScreenDescriptor(valueThis.GetContent().Reference());
}

// gif.Content#LoopCount
Gurax_DeclareProperty_RW(Content, LoopCount)
{
	Declare(VTYPE_Number, Flag::Nil);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, LoopCount)
{
	auto& valueThis = GetValueThis(valueTarget);
	int loopCount = valueThis.GetContent().GetLoopCount();
	if (loopCount < 0) return Value::nil();
	return new Value_Number(loopCount);
}

Gurax_ImplementPropertySetter(Content, LoopCount)
{
	auto& valueThis = GetValueThis(valueTarget);
	int loopCount = value.IsValid()? Value_Number::GetNumber<int>(value) : -1;
	valueThis.GetContent().SetLoopCount(loopCount);
}

// gif.Content#PlainTextExtension:nil
Gurax_DeclareProperty_R(Content, PlainTextExtension)
{
	Declare(VTYPE_PlainTextExtension, Flag::Nil);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, PlainTextExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& content = valueThis.GetContent();
	if (!content.GetExtensions().commentExtension.validFlag) return Value::nil();
	return new Value_PlainTextExtension(content.GetExtensions().plainTextExtension, content.Reference());
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
	Assign(Gurax_CreateMethod(Content, AddImage));
	Assign(Gurax_CreateMethod(Content, EachImage));
	Assign(Gurax_CreateMethod(Content, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, CommentExtension));
	Assign(Gurax_CreateProperty(Content, LogicalScreenDescriptor));
	Assign(Gurax_CreateProperty(Content, LoopCount));
	Assign(Gurax_CreateProperty(Content, PlainTextExtension));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

String Value_Content::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(gif)
