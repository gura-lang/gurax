//==============================================================================
// VType_Image.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Image.h>

namespace Gurax {

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
// Image(stream:Stream, format?:Symbol):map {block?}
Gurax_DeclareConstructor(Image)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("format", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `Image` instance by reading an image data from the given stream.\n"
		"The argument `format` specifies the image format: `` `rgb`` or `` `rgba`,\n"
		"where `` `rgba` is used if omitted.");
}

Gurax_ImplementConstructor(Image)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.Pick<Value_Stream>().GetStream();
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	const Image::Format& format = pSymbol? Image::SymbolToFormat(pSymbol) : Image::Format::RGBA;
	if (!format.IsValid()) {
		Error::Issue(ErrorType::ValueError, "format takes `rgb or `rgba");
		return Value::nil();
	}
	// Function body
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Image#Fill(color:Color)
Gurax_DeclareMethod(Image, Fill)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, Fill)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	const Color& color = Value_Color::GetColor(args.PickValue());
	// Function body
	image.Fill(color);
	return valueThis.Reference();
}

// Image#FillRect(x:Number, y:Number, width:Number, height:Number, color:Color)
Gurax_DeclareMethod(Image, FillRect)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, FillRect)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.PickNumber<int>();
	int y = args.PickNumber<int>();
	int width = args.PickNumber<int>();
	int height = args.PickNumber<int>();
	const Color& color = Value_Color::GetColor(args.PickValue());
	// Function body
	Image::Rect rect;
	if (image.AdjustCoord(&rect, x, y, width, height)) {
		image.FillRect(rect.x, rect.y, rect.width, rect.height, color);
	}
	return valueThis.Reference();
}

// Image#Flip(orient:Symbol)
Gurax_DeclareMethod(Image, Flip)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("orient", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, Flip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	bool horzFlag = false, vertFlag = false;
	const Symbol* pSymbol = args.PickSymbol();
	if (pSymbol->IsIdentical(Gurax_Symbol(horz))) {
		horzFlag = true;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(vert))) {
		vertFlag = true;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(both))) {
		horzFlag = vertFlag = true;
	} else {
		Error::Issue(ErrorType::ValueError, "orient must be one of `horz, `vert and `both");
		return Value::nil();
	}
	// Function body
	RefPtr<Image> pImage(image.Flip(horzFlag, vertFlag));
	return pImage? new Value_Image(pImage.release()) : Value::nil();
}

// Image#GetPixel(x:Number, y:Number):map {block?}
Gurax_DeclareMethod(Image, GetPixel)
{
	Declare(VTYPE_Image, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, GetPixel)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.PickNumber<int>();
	int y = args.PickNumber<int>();
	// Function body
	if (!image.CheckCoord(x, y)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Color(image.GetPixelColor(x, y)));
}

// Image#SetPixel(x:Number, y:Number, color:Color):map
Gurax_DeclareMethod(Image, SetPixel)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Image, SetPixel)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.PickNumber<int>();
	int y = args.PickNumber<int>();
	const Color& color = Value_Color::GetColor(args.PickValue());
	// Function body
	if (!image.CheckCoord(x, y)) return Value::nil();
	image.SetPixelColor(x, y, color);
	return valueThis.Reference();
}

//------------------------------------------------------------------------------
// VType_Image
//------------------------------------------------------------------------------
VType_Image VTYPE_Image("Image");

void VType_Image::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Image, Fill));
	Assign(Gurax_CreateMethod(Image, FillRect));
	Assign(Gurax_CreateMethod(Image, Flip));
	Assign(Gurax_CreateMethod(Image, GetPixel));
	Assign(Gurax_CreateMethod(Image, SetPixel));
}

Value* VType_Image::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Value_Stream> pValueCasted(value.Cast<Value_Stream>(flags));
	if (!pValueCasted) return nullptr;
	RefPtr<Image> pImage(new Image(Image::Format::RGBA));
	if (!pImage->Read(pValueCasted->GetStream())) return nullptr;
	return new Value_Image(pImage.release());
}

//------------------------------------------------------------------------------
// Value_Image
//------------------------------------------------------------------------------
VType& Value_Image::vtype = VTYPE_Image;

}
