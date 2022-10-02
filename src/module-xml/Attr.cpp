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
	return String().Format("%s=\"%s\"", GetName(), String::EscapeHTML(GetValue(), true).c_str());
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
	return String().Format("Attr");
}

Gurax_EndModuleScope(xml)
