//==============================================================================
// VType_Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(png)

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
// png.Content(stream:Stream) {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `png.Content` instance.");
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
// png.Content#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Content, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Content, MethodSkeleton)
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
// png.Content#image_width
Gurax_DeclareProperty_R(Content, image_width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, image_width)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_image_width(c.png_ptr, c.info_ptr));
}

// png.Content#image_height
Gurax_DeclareProperty_R(Content, image_height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Content, image_height)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_image_height(c.png_ptr, c.info_ptr));
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
	Assign(Gurax_CreateMethod(Content, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, image_width));
	Assign(Gurax_CreateProperty(Content, image_height));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

Gurax_EndModuleScope(png)
