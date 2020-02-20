//==============================================================================
// Palette.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/VType_Palette.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Palette
//------------------------------------------------------------------------------
void Palette::Bootup()
{
}

Palette::Palette(size_t n) : _entryTbl(new UInt32[n])
{
}

Palette::Palette(const UInt32* entryTbl, size_t n) : _entryTbl(new UInt32[n])
{
	::memcpy(_entryTbl.get(), entryTbl, sizeof(UInt32) * n);
}

Palette* Palette::Basic()
{
	return new Palette(nullptr, 0);
}

Palette* Palette::WebSafe()
{
	return new Palette(nullptr, 0);
}

Palette* Palette::Win256()
{
	return new Palette(nullptr, 0);
}

String Palette::ToString(const StringStyle& ss) const
{
	return "";
}

//------------------------------------------------------------------------------
// PaletteList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PaletteOwner
//------------------------------------------------------------------------------
void PaletteOwner::Clear()
{
	for (Palette* pPalette : *this) Palette::Delete(pPalette);
	clear();
}

}
