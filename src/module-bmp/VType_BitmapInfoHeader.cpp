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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// bmp.BitmapInfoHeader#propSkeleton
Gurax_DeclareProperty_R(BitmapInfoHeader, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(BitmapInfoHeader, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateProperty(BitmapInfoHeader, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_BitmapInfoHeader
//------------------------------------------------------------------------------
VType& Value_BitmapInfoHeader::vtype = VTYPE_BitmapInfoHeader;

Gurax_EndModuleScope(bmp)
