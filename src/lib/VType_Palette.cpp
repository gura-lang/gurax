//==============================================================================
// VType_Palette.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

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
	RefPtr<Palette> pPalette(new Palette());
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
	RefPtr<Palette> pPalette(new Palette());
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
	RefPtr<Palette> pPalette(new Palette());
	return new Value_Palette(pPalette.release());
}

//------------------------------------------------------------------------------
// VType_Palette
//------------------------------------------------------------------------------
VType_Palette VTYPE_Palette("Palette");

void VType_Palette::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Palette, Basic));
	Assign(Gurax_CreateClassMethod(Palette, WebSafe));
	Assign(Gurax_CreateClassMethod(Palette, Win256));
}

//------------------------------------------------------------------------------
// Value_Palette
//------------------------------------------------------------------------------

}
