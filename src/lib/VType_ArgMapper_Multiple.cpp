//==============================================================================
// VType_ArgMapper_Multiple.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_ArgMapper_Multiple
//------------------------------------------------------------------------------
VType_ArgMapper_Multiple VTYPE_ArgMapper_Multiple("ArgMapper_Multiple");

void VType_ArgMapper_Multiple::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_List, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_ArgMapper_Multiple
//------------------------------------------------------------------------------
String Value_ArgMapper_Multiple::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%zuitems>", GetValueOwner().size());
	return str;
}

String Value_ArgMapper_Multiple::ToStringDetail(const StringStyle& ss) const
{
	return GetValueOwner().ToString(ss);
}

bool Value_ArgMapper_Multiple::ReadyToPickValue()
{
	ValueTypedOwner& valueTypedOwner = _pValuePicked->GetValueTypedOwner();
	valueTypedOwner.Clear();
	for (Value* pValue : GetValueOwner()) {
		if (!pValue->ReadyToPickValue()) return false;
		valueTypedOwner.Add(pValue->PickValue());
	}
	return true;
}

}
