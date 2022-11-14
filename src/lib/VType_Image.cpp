//==============================================================================
// VType_Image.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Image, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Image, `en)}

${help.ComposeMethodHelp(Image, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Image(stream?:Stream:r, imgType?:String):map:[rgb,rgba] {block?}
Gurax_DeclareConstructor(Image)
{
	Declare(VTYPE_Expr, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareArg("imgType", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an `Image` instance. If the argument `stream` is specified, reads image data from the stream.
If omitted, an image with empty data is created.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the 32-bit format is specified.
)**");
}

Gurax_ImplementConstructor(Image)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	const char* imgType = args.IsValid()? args.PickString() : nullptr;
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Image> pImage(new Image(format));
	if (pStream && !pImage->Read(*pStream, imgType)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Image.Create(width:Number, height:Number, color?:Color):[rgb,rgba] {block?}
Gurax_DeclareClassMethod(Image, Create)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an `Image` instance filled with the specified color.
If the argument `color` is omitted, it will be filled with black.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the 32-bit format is specified.
)**");
}

Gurax_ImplementClassMethod(Image, Create)
{
	// Arguments
	ArgPicker args(argument);
	size_t width = args.PickNumberPos<size_t>();
	size_t height = args.PickNumberPos<size_t>();
	if (Error::IsIssued()) return Value::nil();
	const Color& color = args.IsValid()? Value_Color::GetColor(args.PickValue()) : Color::black;
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB : Image::Format::RGBA;
	// Function body
	RefPtr<Image> pImage(new Image(format));
	if (!pImage->Allocate(width, height)) return Value::nil();
	pImage->Fill(color);
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Image#Crop(x:Number, y:Number, width:Number, height:Number):map:[rgb,rgba]
Gurax_DeclareMethod(Image, Crop)
{
	Declare(VTYPE_Image, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	AddHelp(Gurax_Symbol(en), u8R"**(
Created a cropped image from the target.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the created image inherits the target's format.
)**");
}

Gurax_ImplementMethod(Image, Crop)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& imageSrc = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	size_t x = args.PickNumberNonNeg<size_t>();
	size_t y = args.PickNumberNonNeg<size_t>();
	size_t width = args.PickNumberNonNeg<size_t>();
	size_t height = args.PickNumberNonNeg<size_t>();
	if (Error::IsIssued()) return Value::nil();
	//const Image::Format& format =
	//	argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB :
	//	argument.IsSet(Gurax_Symbol(rgba))? Image::Format::RGBA :
	//	imageSrc.GetFormat();
	// Function body
	RefPtr<Image> pImage(imageSrc.Crop(x, y, width, height));
	if (!pImage) return Value::nil();
	return new Value_Image(pImage.release());
}

// Image#Fill(color:Color):reduce
Gurax_DeclareMethod(Image, Fill)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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

// Image#FillRect(x:Number, y:Number, width:Number, height:Number, color:Color):reduce
Gurax_DeclareMethod(Image, FillRect)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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

// Image#Flip(orient:Symbol) {block?}
Gurax_DeclareMethod(Image, Flip)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("orient", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Flips the image in the orientation specified by `` `orient`` that takes one of the following symbols:

- `` `horz`` .. left-to-right
- `` `vert`` .. upside-down
- `` `both`` .. turns by 180 degrees
)**");
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
	if (!pImage) return Value::nil();
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// Image#GetPixel(x:Number, y:Number):map {block?}
Gurax_DeclareMethod(Image, GetPixel)
{
	Declare(VTYPE_Image, Flag::Map);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a pixel color at the specified position.
)**");
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

// Image#GrayScale():[rgb,rgba] {block?}
Gurax_DeclareMethod(Image, GrayScale)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Translates to a gray-scale image.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the created image inherits the target's format.
)**");
}

Gurax_ImplementMethod(Image, GrayScale)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB :
		argument.IsSet(Gurax_Symbol(rgba))? Image::Format::RGBA :
		image.GetFormat();
	// Function body
	RefPtr<Image> pImage(image.GrayScale(format));
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// Image#MapAlphaLevel(mapA:Pointer) {block?}
Gurax_DeclareMethod(Image, MapAlphaLevel)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("mapA", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Translates each pixel's alpha element according to the mapping data pointed by the given pointer mapA
that contains at least 256 bytes of data.
)**");
}

Gurax_ImplementMethod(Image, MapAlphaLevel)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	const Pointer& ptrA = args.PickPointer();
	if (ptrA.GetBytesAvailable() < 256) {
		Error::Issue(ErrorType::RangeError, "mapA must contain data of at least 256 bytes");
		return Value::nil();
	}
	// Function body
	if (!image.IsFormat(Image::Format::RGBA)) {
		Error::Issue(ErrorType::ValueError, "the image data must be of RGBA format.");
		return Value::nil();
	}
	RefPtr<Image> pImage(image.MapAlphaLevel(ptrA.GetPointerC<UInt8>()));
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// Image#MapColorLevel(mapR:Pointer, mapG:Pointer, mapB:Pointer):[rgb,rgba] {block?}
Gurax_DeclareMethod(Image, MapColorLevel)
{
	Declare(VTYPE_Image, Flag::None);
	DeclareArg("mapR", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapG", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mapB", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Translates each pixel's RGB elements according to the mapping data pointed by the given pointers:
`mapR`, `mapG` and `mapB`, which contain at least 256 bytes of data.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the created image inherits the target's format.
)**");
}

Gurax_ImplementMethod(Image, MapColorLevel)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	const Pointer& ptrR = args.PickPointer();
	const Pointer& ptrG = args.PickPointer();
	const Pointer& ptrB = args.PickPointer();
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB :
		argument.IsSet(Gurax_Symbol(rgba))? Image::Format::RGBA :
		image.GetFormat();
	if (ptrR.GetBytesAvailable() < 256) {
		Error::Issue(ErrorType::RangeError, "mapR must contain data of at least 256 bytes");
		return Value::nil();
	}
	if (ptrG.GetBytesAvailable() < 256) {
		Error::Issue(ErrorType::RangeError, "mapG must contain data of at least 256 bytes");
		return Value::nil();
	}
	if (ptrB.GetBytesAvailable() < 256) {
		Error::Issue(ErrorType::RangeError, "mapB must contain data of at least 256 bytes");
		return Value::nil();
	}
	// Function body
	RefPtr<Image> pImage(image.MapColorLevel(format, ptrR.GetPointerC<UInt8>(),
											 ptrG.GetPointerC<UInt8>(), ptrB.GetPointerC<UInt8>()));
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// Image#PutPixel(x:Number, y:Number, color:Color):map:reduce
Gurax_DeclareMethod(Image, PutPixel)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("color", VTYPE_Color, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Puts a pixel color at the specified position.
)**");
}

Gurax_ImplementMethod(Image, PutPixel)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.PickNumber<int>();
	int y = args.PickNumber<int>();
	const Color& color = args.PickColor();
	// Function body
	if (!image.CheckCoord(x, y)) return Value::nil();
	image.PutPixelColor(x, y, color);
	return valueThis.Reference();
}

// Image#Paste(xDst:Number, yDst:Number, imageSrc:Image,
//             xSrc?:Number, ySrc?:Number, width?:Number, height?:Number):reduce
Gurax_DeclareMethod(Image, Paste)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("xDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSrc", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("ySrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Copies the image data of `imageSrc` into the target image at the specified position `[xDst, yDst]`.

The optional argument `[xSrc, ySrc]` specifies the left-top position from where the image is copied.
The optional argument `[width, height]` specifies the image area to be copied.
)**");
}

Gurax_ImplementMethod(Image, Paste)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int xDst = args.PickNumber<int>();
	int yDst = args.PickNumber<int>();
	const Image& imageSrc = Value_Image::GetImage(args.PickValue());
	int xSrc = args.IsValid()? args.PickNumber<int>() : 0;
	int ySrc = args.IsValid()? args.PickNumber<int>() : 0;
	int width = args.IsValid()? args.PickNumber<int>() : imageSrc.GetWidth() - xSrc;
	int height = args.IsValid()? args.PickNumber<int>() : imageSrc.GetHeight() - ySrc;
	// Function body
	Image::Rect rect;
	if (xSrc + width > static_cast<int>(imageSrc.GetWidth())) width = imageSrc.GetWidth() - xSrc;
	if (ySrc + height > static_cast<int>(imageSrc.GetHeight())) height = imageSrc.GetHeight() - ySrc;
	if (image.AdjustCoord(&rect, xDst, yDst, width, height)) {
		if (xDst < 0) xSrc -= xDst;
		if (yDst < 0) ySrc -= yDst;
		image.Paste(rect.x, rect.y, imageSrc, xSrc, ySrc, rect.width, rect.height);
	}
	return valueThis.Reference();
}

// Image#Read(stream:Stream:r, imgType?:String):map:reduce
Gurax_DeclareMethod(Image, Read)
{
	Declare(VTYPE_Image, Flag::Map | Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("imgType", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Reads image data from a stream.

The format of the image data is determined
by the byte sequence of the stream data and its file name.

You can also explicitly specify the image data format by the argument `imgType`.

This method returns the reference to the target instance itself.
)**");
}

Gurax_ImplementMethod(Image, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const char* imgType = args.IsValid()? args.PickString() : nullptr;
	// Function body
	if (!image.Read(stream, imgType)) return Value::nil();
	return valueThis.Reference();
}

// Image#ReduceColor(palette:Palette)
Gurax_DeclareMethod(Image, ReduceColor)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("palette", VTYPE_Palette, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethod(Image, ReduceColor)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Arguments
	ArgPicker args(argument);
	const Palette& palette = args.PickPalette();
	// Function body
	RefPtr<Image> pImageRtn(image.ReduceColor(palette));
	if (!pImageRtn) return Value::nil();
	return new Value_Image(pImageRtn.release());
}

// Image#Resize(wdDst:Number, htDst:Number, xSrc?:Number, ySrc?:Number,
//              wdSrc?:Number, htSrc?:Number):[rgb,rgba]
Gurax_DeclareMethod(Image, Resize)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("wdDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("htDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("ySrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wdSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("htSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	AddHelp(Gurax_Symbol(en), u8R"**(
Created a resized image from the target.

The arguments `wdDst` and `htDst` specify the size of the resized image.

The arguments `xSrc`, `ySrc`, `wdSrc` and `htSrc` specify the image area that is resized.
Part of or all of them can be omitted. If `xSrc` and `ySrc` are omitted, left-top position is specified.
If `wdSrc` and `htSrc` are omitted, the area up to right or bottom is speicied.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the created image inherits the target's format.
)**");
}

Gurax_ImplementMethod(Image, Resize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& imageSrc = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int wdDst = args.PickNumber<int>();
	int htDst = args.PickNumber<int>();
	int xSrc = args.IsValid()? args.PickNumber<int>() : 0;
	int ySrc = args.IsValid()? args.PickNumber<int>() : 0;
	int wdSrc = args.IsValid()? args.PickNumber<int>() : imageSrc.GetWidth() - xSrc;
	int htSrc = args.IsValid()? args.PickNumber<int>() : imageSrc.GetHeight() - ySrc;
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB :
		argument.IsSet(Gurax_Symbol(rgba))? Image::Format::RGBA :
		imageSrc.GetFormat();
	// Function body
	if (wdDst <= 0 || htDst <= 0) {
		Error::Issue(ErrorType::RangeError, "invalid value for wdDst and htDst.");
		return Value::nil();
	}
	if (!imageSrc.CheckArea(xSrc, ySrc, wdSrc, htSrc)) return Value::nil();
	RefPtr<Image> pImage(new Image(format, imageSrc.GetAlphaDefault()));
	if (!pImage->Allocate(wdDst, htDst)) {
		Error::Issue(ErrorType::MemoryError, "memory allocation error.");
		return Value::nil();
	}
	pImage->ResizePaste(0, 0, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
	return new Value_Image(pImage.release());
}

// Image#ResizePaste(xDst:Number, yDst:Number, wdDst:Number, htDst:Number,
//                   imageSrc:Image, xSrc?:Number, ySrc?:Number, wdSrc?:Number, htSrc?:Number):reduce
Gurax_DeclareMethod(Image, ResizePaste)
{
	Declare(VTYPE_Image, Flag::Reduce);
	DeclareArg("xDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("wdDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("htDst", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("imageSrc", VTYPE_Image, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("ySrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wdSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("htSrc", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethod(Image, ResizePaste)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int xDst = args.PickNumber<int>();
	int yDst = args.PickNumber<int>();
	int wdDst = args.PickNumber<int>();
	int htDst = args.PickNumber<int>();
	const Image& imageSrc = Value_Image::GetImage(args.PickValue());
	int xSrc = args.IsValid()? args.PickNumber<int>() : 0;
	int ySrc = args.IsValid()? args.PickNumber<int>() : 0;
	int wdSrc = args.IsValid()? args.PickNumber<int>() : imageSrc.GetWidth() - xSrc;
	int htSrc = args.IsValid()? args.PickNumber<int>() : imageSrc.GetHeight() - ySrc;
	// Function body
	if (!image.CheckArea(xDst, yDst, wdDst, htDst) ||
		!imageSrc.CheckArea(xSrc, ySrc, wdSrc, htSrc)) return Value::nil();
	image.ResizePaste(xDst, yDst, wdDst, htDst, imageSrc, xSrc, ySrc, wdSrc, htSrc);
	return valueThis.Reference();
}

// Image#Rotate(angle:Number, colorBg?:Color):map:[rgb,rgba] {block?}
Gurax_DeclareMethod(Image, Rotate)
{
	Declare(VTYPE_Image, Flag::Map);
	DeclareArg("angle", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colorBg", VTYPE_Color, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rgb));
	DeclareAttrOpt(Gurax_Symbol(rgba));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an image that rotates the original image.

The argument `angle` specifies the rotation angle in degree unit,
where a positive number means counterclockwise direction and negative clockwise direction.
The created instance has a size that exactly fits the rotated image.

The argument `colorBg` specifies the color of pixels to fill
the empty area that appears after rotation.
If omitted, the color that has all elements set to zero is used for filling.

The attributes `rgb` and `rgba` specify the format of the image:
`rgb` for 24-bit format that consists of elements red, green and blue,
and `rgba` for 32-bit format that consits of elements red, green, blue and alpha.
If omitted, the created image inherits the target's format.
)**");
}

Gurax_ImplementMethod(Image, Rotate)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	Double angle = args.PickNumber<Double>();
	const Color& colorBg = args.IsValid()? Value_Color::GetColor(args.PickValue()) : Color::zero;
	const Image::Format& format =
		argument.IsSet(Gurax_Symbol(rgb))? Image::Format::RGB :
		argument.IsSet(Gurax_Symbol(rgba))? Image::Format::RGBA :
		image.GetFormat();
	// Function body
	RefPtr<Image> pImage(image.Rotate(format, angle, colorBg));
	if (!pImage) return Value::nil();
	return argument.ReturnValue(processor, new Value_Image(pImage.release()));
}

// Image#Scan(x:Number, y:Number, width:Number, height:Numbrer, scanDir?:Symbol):[pixel] {block?}
Gurax_DeclareMethod(Image, Scan)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("scanDir", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(pixel));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns `Color` instance including RGB color data in the image.
When the attribute `:pixel` is speicified, the iterator returns `Pixel` instance
that contains position information as well as color data.

The arguments `x`, `y`, `width` and `height` specify the area in which the scanning is performed.
If either of the argumens `x` or `y` is omitted,
the scan covers to the left- or top-end of the image.
If either of the arguments `width` or `height` is omitted,
the scan covers to the right- or bottom-end of the image.

The argument `scanDir` specifies the direction of the scanning, which takes one of the symbols:

- 
)**");
}

Gurax_ImplementMethod(Image, Scan)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	int x = args.IsValid()? args.PickNumber<int>() : 0;
	int y = args.IsValid()? args.PickNumber<int>() : 0;
	int width = args.IsValid()? args.PickNumber<int>() : static_cast<int>(image.GetWidth()) - x;
	int height = args.IsValid()? args.PickNumber<int>() : static_cast<int>(image.GetHeight()) - y;
	Image::ScanDir scanDir = args.IsValid()? Image::SymbolToScanDir(args.PickSymbol()) : Image::ScanDir::LeftTopHorz;
	if (scanDir == Image::ScanDir::None) {
		Error::Issue(ErrorType::SymbolError, "invalid symbol for scanDir");
		return Value::nil();
	}
	bool pixelFlag = argument.IsSet(Gurax_Symbol(pixel));
	// Function body
	if (!image.CheckArea(x, y, width, height)) return Value::nil();
	Image::Scanner scanner(Image::Scanner::CreateByDir(image, x, y, width, height, scanDir));
	RefPtr<Iterator> pIterator;
	if (pixelFlag) {
		pIterator.reset(new VType_Image::Iterator_ScanPixel(image.Reference(), scanner));
	} else {
		pIterator.reset(new VType_Image::Iterator_ScanColor(image.Reference(), scanner));
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// Image#Write(stream:Stream:w, imgType?:String):map:reduce
Gurax_DeclareMethod(Image, Write)
{
	Declare(VTYPE_Image, Flag::Map | Flag::Reduce);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("imgType", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Writes image data to a stream.

The format of the image data is determined by the stream's file name.

You can also explicitly specify the image data format by the argument `imgType`.

This method returns the reference to the target instance itself.
)**");
}

Gurax_ImplementMethod(Image, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Image& image = valueThis.GetImage();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	const char* imgType = args.IsValid()? args.PickString() : nullptr;
	// Function body
	if (!image.Write(stream, imgType)) return Value::nil();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Image#alphaDefault
Gurax_DeclareProperty_RW(Image, alphaDefault)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The alpha value that is used when the source image doesn't have alpha element
in operations like pasting.
)**");
}

Gurax_ImplementPropertyGetter(Image, alphaDefault)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetMetrics().alphaDefault);
}

Gurax_ImplementPropertySetter(Image, alphaDefault)
{
	auto& valueThis = GetValueThis(valueTarget);
	UInt8 alphaDefault = Value_Number::GetNumberRanged<UInt8>(value, 0, 255);
	if (Error::IsIssued()) return;
	valueThis.GetImage().GetMetrics().alphaDefault = alphaDefault;
}

// Image#bytes
Gurax_DeclareProperty_R(Image, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The image's size in bytes.
)**");
}

Gurax_ImplementPropertyGetter(Image, bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetBytes());
}

// Image#bytesPerLine
Gurax_DeclareProperty_R(Image, bytesPerLine)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The size per line in bytes.
)**");
}

Gurax_ImplementPropertyGetter(Image, bytesPerLine)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetBytesPerLine());
}

// Image#bytesPerPixel
Gurax_DeclareProperty_R(Image, bytesPerPixel)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The size per pixel in bytes.
)**");
}

Gurax_ImplementPropertyGetter(Image, bytesPerPixel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetBytesPerPixel());
}

// Image#extra
Gurax_DeclareProperty_R(Image, extra)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Additional information associated with the image.
)**");
}

Gurax_ImplementPropertyGetter(Image, extra)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetImage().GetValueExtra().Reference();
}

// Image#format
Gurax_DeclareProperty_R(Image, format)
{
	Declare(VTYPE_Symbol, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
A symbol that represents the image's format: `` `rgb`` or `` `rgba``.
)**");
}

Gurax_ImplementPropertyGetter(Image, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(Image::FormatToSymbol(valueThis.GetImage().GetFormat()));
}

// Image#height
Gurax_DeclareProperty_R(Image, height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The image's height.
)**");
}

Gurax_ImplementPropertyGetter(Image, height)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetHeight());
}

// Image#p
Gurax_DeclareProperty_R(Image, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
A `Pointer` instance that points at the first address of the image buffer.
)**");
}

Gurax_ImplementPropertyGetter(Image, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Memory* pMemory = valueThis.GetImage().GetMemory();
	if (!pMemory) {
		Error::Issue(ErrorType::MemoryError, "the image buffer is not allocated");
		return Value::nil();
	}
	return new Value_Pointer(new Pointer_Memory(pMemory->Reference()));
}

// Image#palette:nil
Gurax_DeclareProperty_RW(Image, palette)
{
	Declare(VTYPE_Palette, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"**(
Set or get the image's palette. If the image doesn't own a palette, this returns `nil`.
When you want to remove the palette, set `nil` value to this.
)**");
}

Gurax_ImplementPropertyGetter(Image, palette)
{
	auto& valueThis = GetValueThis(valueTarget);
	Palette* pPalette = valueThis.GetImage().GetPalette();
	return pPalette? new Value_Palette(pPalette->Reference()) : Value::nil();
}

Gurax_ImplementPropertySetter(Image, palette)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetImage().SetPalette(value.IsValid()? Value_Palette::GetPalette(value).Reference() : nullptr);
}

// Image#width
Gurax_DeclareProperty_R(Image, width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The image's width.
)**");
}

Gurax_ImplementPropertyGetter(Image, width)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetImage().GetWidth());
}

//------------------------------------------------------------------------------
// VType_Image
//------------------------------------------------------------------------------
VType_Image VTYPE_Image("Image");

void VType_Image::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Image));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Image, Create));
	// Assignment of method
	Assign(Gurax_CreateMethod(Image, Crop));
	Assign(Gurax_CreateMethod(Image, Fill));
	Assign(Gurax_CreateMethod(Image, FillRect));
	Assign(Gurax_CreateMethod(Image, Flip));
	Assign(Gurax_CreateMethod(Image, GetPixel));
	Assign(Gurax_CreateMethod(Image, GrayScale));
	Assign(Gurax_CreateMethod(Image, MapAlphaLevel));
	Assign(Gurax_CreateMethod(Image, MapColorLevel));
	Assign(Gurax_CreateMethod(Image, PutPixel));
	Assign(Gurax_CreateMethod(Image, Paste));
	Assign(Gurax_CreateMethod(Image, Read));
	Assign(Gurax_CreateMethod(Image, ReduceColor));
	Assign(Gurax_CreateMethod(Image, Resize));
	Assign(Gurax_CreateMethod(Image, ResizePaste));
	Assign(Gurax_CreateMethod(Image, Rotate));
	Assign(Gurax_CreateMethod(Image, Scan));
	Assign(Gurax_CreateMethod(Image, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Image, alphaDefault));
	Assign(Gurax_CreateProperty(Image, bytes));
	Assign(Gurax_CreateProperty(Image, bytesPerLine));
	Assign(Gurax_CreateProperty(Image, bytesPerPixel));
	Assign(Gurax_CreateProperty(Image, extra));
	Assign(Gurax_CreateProperty(Image, format));
	Assign(Gurax_CreateProperty(Image, height));
	Assign(Gurax_CreateProperty(Image, p));
	Assign(Gurax_CreateProperty(Image, palette));
	Assign(Gurax_CreateProperty(Image, width));
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
// VType_Image::Iterator_ScanColor
//------------------------------------------------------------------------------
Value* VType_Image::Iterator_ScanColor::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_Color(_scanner.GetColor()));
	_doneFlag = !_scanner.Next();
	return pValue.release();
}

String VType_Image::Iterator_ScanColor::ToString(const StringStyle& ss) const
{
	return "Image.ScanColor";
}

//------------------------------------------------------------------------------
// VType_Image::Iterator_ScanPixel
//------------------------------------------------------------------------------
Value* VType_Image::Iterator_ScanPixel::DoNextValue()
{
	if (_doneFlag) return nullptr;
	RefPtr<Value> pValue(new Value_Pixel(
			new Pixel(_scanner.GetColor(), _scanner.GetX(), _scanner.GetY())));
	_doneFlag = !_scanner.Next();
	return pValue.release();
}

String VType_Image::Iterator_ScanPixel::ToString(const StringStyle& ss) const
{
	return "Image.ScanPixel";
}

//------------------------------------------------------------------------------
// Value_Image
//------------------------------------------------------------------------------
VType& Value_Image::vtype = VTYPE_Image;

String Value_Image::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetImage().ToString(ss));
}

}
