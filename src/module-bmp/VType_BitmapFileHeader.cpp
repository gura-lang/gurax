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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.BitmapFileHeader#propSkeleton
Gurax_DeclareProperty_R(BitmapFileHeader, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(BitmapFileHeader, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_BitmapFileHeader
//------------------------------------------------------------------------------
VType_BitmapFileHeader VTYPE_BitmapFileHeader("BitmapFileHeader");

void VType_BitmapFileHeader::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(BitmapFileHeader, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_BitmapFileHeader
//------------------------------------------------------------------------------
VType& Value_BitmapFileHeader::vtype = VTYPE_BitmapFileHeader;

Gurax_EndModuleScope(bmp)
