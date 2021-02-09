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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `gif.Content` instance.");
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
// gif.Content#EachImage() {block?}
Gurax_DeclareMethod(Content, EachImage)
{
	Declare(VTYPE_Iterator, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns images stored in the GIF file.\n");
}

Gurax_ImplementMethod(Content, EachImage)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Iterator> pIterator(new Content::Iterator_EachImage(valueThis.GetContent().Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// gif.Content#LogicalScreenDescriptor
Gurax_DeclareProperty_R(Content, LogicalScreenDescriptor)
{
	Declare(VTYPE_LogicalScreenDescriptor, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, LogicalScreenDescriptor)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_LogicalScreenDescriptor(valueThis.GetContent().Reference());
}

// gif.Content#CommentExtension:nil
Gurax_DeclareProperty_R(Content, CommentExtension)
{
	Declare(VTYPE_CommentExtension, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, CommentExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& content = valueThis.GetContent();
	if (!content.GetExtensions().comment.validFlag) return Value::nil();
	return new Value_CommentExtension(content.Reference());
}

// gif.Content#PlainTextExtension:nil
Gurax_DeclareProperty_R(Content, PlainTextExtension)
{
	Declare(VTYPE_PlainTextExtension, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, PlainTextExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& content = valueThis.GetContent();
	if (!content.GetExtensions().comment.validFlag) return Value::nil();
	return new Value_PlainTextExtension(content.Reference());
}

// gif.Content#ApplicationExtension:nil
Gurax_DeclareProperty_R(Content, ApplicationExtension)
{
	Declare(VTYPE_ApplicationExtension, Flag::Nil);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, ApplicationExtension)
{
	auto& valueThis = GetValueThis(valueTarget);
	auto& content = valueThis.GetContent();
	if (!content.GetExtensions().comment.validFlag) return Value::nil();
	return new Value_ApplicationExtension(content.Reference());
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
	Assign(Gurax_CreateMethod(Content, EachImage));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, LogicalScreenDescriptor));
	Assign(Gurax_CreateProperty(Content, CommentExtension));
	Assign(Gurax_CreateProperty(Content, PlainTextExtension));
	Assign(Gurax_CreateProperty(Content, ApplicationExtension));
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
