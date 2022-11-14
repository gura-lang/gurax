//==============================================================================
// VType_BitmapFileHeader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(bmp.BitmapFileHeader, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(bmp.BitmapFileHeader, `en)}

${help.ComposeMethodHelp(bmp.BitmapFileHeader, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.BitmapFileHeader#bfType
Gurax_DeclareProperty_R(BitmapFileHeader, bfType)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The value of bfType.
)**");
}

Gurax_ImplementPropertyGetter(BitmapFileHeader, bfType)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapFileHeader& bfh = valueThis.GetContent().GetBitmapFileHeader();
	return new Value_Number(Gurax_UnpackUInt16(bfh.bfType));
}

// bmp.BitmapFileHeader#bfSize
Gurax_DeclareProperty_R(BitmapFileHeader, bfSize)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The value of bfSize.
)**");
}

Gurax_ImplementPropertyGetter(BitmapFileHeader, bfSize)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapFileHeader& bfh = valueThis.GetContent().GetBitmapFileHeader();
	return new Value_Number(Gurax_UnpackUInt32(bfh.bfSize));
}

// bmp.BitmapFileHeader#bfOffBits
Gurax_DeclareProperty_R(BitmapFileHeader, bfOffBits)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The value of bfOffBits.
)**");
}

Gurax_ImplementPropertyGetter(BitmapFileHeader, bfOffBits)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BitmapFileHeader& bfh = valueThis.GetContent().GetBitmapFileHeader();
	return new Value_Number(Gurax_UnpackUInt32(bfh.bfOffBits));
}

//------------------------------------------------------------------------------
// VType_BitmapFileHeader
//------------------------------------------------------------------------------
VType_BitmapFileHeader VTYPE_BitmapFileHeader("BitmapFileHeader");

void VType_BitmapFileHeader::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(BitmapFileHeader, bfType));
	Assign(Gurax_CreateProperty(BitmapFileHeader, bfSize));
	Assign(Gurax_CreateProperty(BitmapFileHeader, bfOffBits));
}

//------------------------------------------------------------------------------
// Value_BitmapFileHeader
//------------------------------------------------------------------------------
VType& Value_BitmapFileHeader::vtype = VTYPE_BitmapFileHeader;

String Value_BitmapFileHeader::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetContent().ToString(ss));
}

Gurax_EndModuleScope(bmp)
