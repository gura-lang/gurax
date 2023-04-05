//==============================================================================
// Gear.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Gear
//------------------------------------------------------------------------------
String Gear::ToString(const StringStyle& ss) const
{
	return String().Format("Gear");
}

//------------------------------------------------------------------------------
// GearList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// GearOwner
//------------------------------------------------------------------------------
void GearOwner::Clear()
{
	for (Gear* pGear : *this) Gear::Delete(pGear);
	clear();
}

}