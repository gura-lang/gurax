//==============================================================================
// VType_Palette.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Palette.h>

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
// Implementation of class method
//------------------------------------------------------------------------------
// Palette.Basic()
Gurax_DeclareClassMethod(Palette, Basic)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, Basic)
{
	// Function body
	RefPtr<Palette> pPalette(new Palette(0));
	return new Value_Palette(pPalette.release());
}

// Palette.WebSafe()
Gurax_DeclareClassMethod(Palette, WebSafe)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, WebSafe)
{
	// Function body
	RefPtr<Palette> pPalette(new Palette(0));
	return new Value_Palette(pPalette.release());
}

// Palette.Win256()
Gurax_DeclareClassMethod(Palette, Win256)
{
	Declare(VTYPE_Palette, Flag::None);
}

Gurax_ImplementClassMethod(Palette, Win256)
{
	// Function body
	RefPtr<Palette> pPalette(new Palette(0));
	return new Value_Palette(pPalette.release());
}

//------------------------------------------------------------------------------
// VType_Palette
//------------------------------------------------------------------------------
VType_Palette VTYPE_Palette("Palette");

void VType_Palette::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Palette, Basic));
	Assign(Gurax_CreateClassMethod(Palette, WebSafe));
	Assign(Gurax_CreateClassMethod(Palette, Win256));
}

//------------------------------------------------------------------------------
// Value_Palette
//------------------------------------------------------------------------------
VType& Value_Palette::vtype = VTYPE_Palette;

}
