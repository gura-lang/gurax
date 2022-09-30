//==============================================================================
// Attr.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Attr
//------------------------------------------------------------------------------
String Attr::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Attr");
}

//------------------------------------------------------------------------------
// AttrList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// AttrOwner
//------------------------------------------------------------------------------
void AttrOwner::Clear()
{
	for (Attr* pAttr : *this) Attr::Delete(pAttr);
	clear();
}

//------------------------------------------------------------------------------
// Iterator_Attr
//------------------------------------------------------------------------------
Value* Iterator_Attr::DoNextValue()
{
	const AttrOwner& attrOwner = GetAttrOwner();
	if (_idx >= attrOwner.size()) return nullptr;
	return new Value_Attr(attrOwner[_idx++]->Reference());
}

String Iterator_Attr::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Attr");
	return str;
}

Gurax_EndModuleScope(xml)
