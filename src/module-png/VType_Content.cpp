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

${help.ComposePropertyHelp(png.Content, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(png.Content, `en)}

${help.ComposeMethodHelp(png.Content, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// png.Content(stream:Stream) {block?}
Gurax_DeclareConstructor(Content)
{
	Declare(VTYPE_Content, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `png.Content` instance.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
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
// png.Content#rowbytes
Gurax_DeclareProperty_R(Content, rowbytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, rowbytes)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_rowbytes(c.png_ptr, c.info_ptr));
}

// png.Content#image_width
Gurax_DeclareProperty_R(Content, image_width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, image_height)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_image_height(c.png_ptr, c.info_ptr));
}

// png.Content#bit_depth
Gurax_DeclareProperty_R(Content, bit_depth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, bit_depth)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_bit_depth(c.png_ptr, c.info_ptr));
}

// png.Content#color_type
Gurax_DeclareProperty_R(Content, color_type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, color_type)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_color_type(c.png_ptr, c.info_ptr));
}

// png.Content#filter_type
Gurax_DeclareProperty_R(Content, filter_type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, filter_type)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_filter_type(c.png_ptr, c.info_ptr));
}

// png.Content#interlace_type
Gurax_DeclareProperty_R(Content, interlace_type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, interlace_type)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_interlace_type(c.png_ptr, c.info_ptr));
}

// png.Content#compression_type
Gurax_DeclareProperty_R(Content, compression_type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, compression_type)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_compression_type(c.png_ptr, c.info_ptr));
}

// png.Content#compression_x_pixels_per_meter
Gurax_DeclareProperty_R(Content, x_pixels_per_meter)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, x_pixels_per_meter)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_x_pixels_per_meter(c.png_ptr, c.info_ptr));
}

// png.Content#y_pixels_per_meter
Gurax_DeclareProperty_R(Content, y_pixels_per_meter)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, y_pixels_per_meter)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_y_pixels_per_meter(c.png_ptr, c.info_ptr));
}

// png.Content#pixels_per_meter
Gurax_DeclareProperty_R(Content, pixels_per_meter)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, pixels_per_meter)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_pixels_per_meter(c.png_ptr, c.info_ptr));
}

// png.Content#pixel_aspect_ratio
Gurax_DeclareProperty_R(Content, pixel_aspect_ratio)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, pixel_aspect_ratio)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_pixel_aspect_ratio(c.png_ptr, c.info_ptr));
}

// png.Content#x_offset_microns
Gurax_DeclareProperty_R(Content, x_offset_microns)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, x_offset_microns)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_x_offset_microns(c.png_ptr, c.info_ptr));
}

// png.Content#y_offset_microns
Gurax_DeclareProperty_R(Content, y_offset_microns)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, y_offset_microns)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_y_offset_microns(c.png_ptr, c.info_ptr));
}

// png.Content#x_offset_pixels
Gurax_DeclareProperty_R(Content, x_offset_pixels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, x_offset_pixels)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_x_offset_pixels(c.png_ptr, c.info_ptr));
}

// png.Content#y_offset_pixels
Gurax_DeclareProperty_R(Content, y_offset_pixels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, y_offset_pixels)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_y_offset_pixels(c.png_ptr, c.info_ptr));
}

// png.Content#compression_x_pixels_per_inch
Gurax_DeclareProperty_R(Content, x_pixels_per_inch)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, x_pixels_per_inch)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_x_pixels_per_inch(c.png_ptr, c.info_ptr));
}

// png.Content#y_pixels_per_inch
Gurax_DeclareProperty_R(Content, y_pixels_per_inch)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, y_pixels_per_inch)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_y_pixels_per_inch(c.png_ptr, c.info_ptr));
}

// png.Content#pixels_per_inch
Gurax_DeclareProperty_R(Content, pixels_per_inch)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, pixels_per_inch)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_pixels_per_inch(c.png_ptr, c.info_ptr));
}

// png.Content#x_offset_inches
Gurax_DeclareProperty_R(Content, x_offset_inches)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, x_offset_inches)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_x_offset_inches(c.png_ptr, c.info_ptr));
}

// png.Content#y_offset_inches
Gurax_DeclareProperty_R(Content, y_offset_inches)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, y_offset_inches)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_y_offset_inches(c.png_ptr, c.info_ptr));
}

// png.Content#channels
Gurax_DeclareProperty_R(Content, channels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(Content, channels)
{
	Content& c = GetValueThis(valueTarget).GetContent();
	return new Value_Number(::png_get_channels(c.png_ptr, c.info_ptr));
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
	Assign(Gurax_CreateMethod(Content, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Content, rowbytes));
	Assign(Gurax_CreateProperty(Content, image_width));
	Assign(Gurax_CreateProperty(Content, image_height));
	Assign(Gurax_CreateProperty(Content, bit_depth));
	Assign(Gurax_CreateProperty(Content, color_type));
	Assign(Gurax_CreateProperty(Content, filter_type));
	Assign(Gurax_CreateProperty(Content, interlace_type));
	Assign(Gurax_CreateProperty(Content, compression_type));
	Assign(Gurax_CreateProperty(Content, x_pixels_per_meter));
	Assign(Gurax_CreateProperty(Content, y_pixels_per_meter));
	Assign(Gurax_CreateProperty(Content, pixels_per_meter));
	Assign(Gurax_CreateProperty(Content, pixel_aspect_ratio));
	Assign(Gurax_CreateProperty(Content, x_offset_microns));
	Assign(Gurax_CreateProperty(Content, y_offset_microns));
	Assign(Gurax_CreateProperty(Content, x_offset_pixels));
	Assign(Gurax_CreateProperty(Content, y_offset_pixels));
	Assign(Gurax_CreateProperty(Content, x_pixels_per_inch));
	Assign(Gurax_CreateProperty(Content, y_pixels_per_inch));
	Assign(Gurax_CreateProperty(Content, pixels_per_inch));
	Assign(Gurax_CreateProperty(Content, x_offset_inches));
	Assign(Gurax_CreateProperty(Content, y_offset_inches));
	Assign(Gurax_CreateProperty(Content, channels));
}

//------------------------------------------------------------------------------
// Value_Content
//------------------------------------------------------------------------------
VType& Value_Content::vtype = VTYPE_Content;

String Value_Content::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(png)
