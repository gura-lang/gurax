//==============================================================================
// VType_BitmapInfoHeader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(bmp.BitmapInfoHeader, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(bmp.BitmapInfoHeader, `en)}

${help.ComposeMethodHelp(bmp.BitmapInfoHeader, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.BitmapInfoHeader#biSize
Gurax_DeclareProperty_R(BitmapInfoHeader, biSize)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biSize.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biSize)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biSize));
}

// bmp.BitmapInfoHeader#biWidth
Gurax_DeclareProperty_R(BitmapInfoHeader, biWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biWidth.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biWidth)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biWidth));
}

// bmp.BitmapInfoHeader#biHeight
Gurax_DeclareProperty_R(BitmapInfoHeader, biHeight)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biHeight.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biHeight)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biHeight));
}

// bmp.BitmapInfoHeader#biPlanes
Gurax_DeclareProperty_R(BitmapInfoHeader, biPlanes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biPlanes.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biPlanes)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt16(bih.biPlanes));
}

// bmp.BitmapInfoHeader#biBitCount
Gurax_DeclareProperty_R(BitmapInfoHeader, biBitCount)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biBitCount.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biBitCount)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt16(bih.biBitCount));
}

// bmp.BitmapInfoHeader#biCompression
Gurax_DeclareProperty_R(BitmapInfoHeader, biCompression)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biCompression.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biCompression)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biCompression));
}

// bmp.BitmapInfoHeader#biSizeImage
Gurax_DeclareProperty_R(BitmapInfoHeader, biSizeImage)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biSizeImage.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biSizeImage)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biSizeImage));
}

// bmp.BitmapInfoHeader#biXPelsPerMeter
Gurax_DeclareProperty_R(BitmapInfoHeader, biXPelsPerMeter)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biXPelsPerMeter.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biXPelsPerMeter)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biXPelsPerMeter));
}

// bmp.BitmapInfoHeader#biYPelsPerMeter
Gurax_DeclareProperty_R(BitmapInfoHeader, biYPelsPerMeter)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biYPelsPerMeter.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biYPelsPerMeter)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biYPelsPerMeter));
}

// bmp.BitmapInfoHeader#biClrUsed
Gurax_DeclareProperty_R(BitmapInfoHeader, biClrUsed)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biClrUsed.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biClrUsed)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biClrUsed));
}

// bmp.BitmapInfoHeader#biClrImportant
Gurax_DeclareProperty_R(BitmapInfoHeader, biClrImportant)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(
The value of biClrImportant.
)**");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, biClrImportant)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapInfoHeader& bih = valueThis.GetContent().GetBitmapInfoHeader();
	return new Value_Number(Gurax_UnpackUInt32(bih.biClrImportant));
}

//------------------------------------------------------------------------------
// VType_BitmapInfoHeader
//------------------------------------------------------------------------------
VType_BitmapInfoHeader VTYPE_BitmapInfoHeader("BitmapInfoHeader");

void VType_BitmapInfoHeader::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biSize));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biWidth));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biHeight));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biPlanes));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biBitCount));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biCompression));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biSizeImage));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biXPelsPerMeter));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biYPelsPerMeter));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biClrUsed));
	Assign(Gurax_CreateProperty(BitmapInfoHeader, biClrImportant));
}

//------------------------------------------------------------------------------
// Value_BitmapInfoHeader
//------------------------------------------------------------------------------
VType& Value_BitmapInfoHeader::vtype = VTYPE_BitmapInfoHeader;

String Value_BitmapInfoHeader::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(bmp)
