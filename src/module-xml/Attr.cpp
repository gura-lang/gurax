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
const Attr* AttrList::Find(const char* name) const
{
	for (auto pAttr : *this) {
		if (::strcmp(pAttr->GetName(), name) == 0) return pAttr;
	}
	Error::Issue(ErrorType::IndexError, "the specified attribute is not found.");
	return nullptr;
}

const Attr* AttrList::IndexGet(const Value& valueIndex) const
{
	if (valueIndex.IsType(VTYPE_Number)) {
		size_t idx = 0;
		if (!Index::GetIndexNumber(valueIndex, size(), &idx)) return false;
		return at(idx);
	} else if (valueIndex.IsType(VTYPE_String)) {
		const Attr* pAttr = Find(Value_String::GetString(valueIndex));
		if (pAttr) return pAttr;
		Error::Issue(ErrorType::IndexError, "the specified attribute is not found.");
		return nullptr;
	}
	Error::Issue(ErrorType::IndexError, "the index value for attributes must be a Number or String.");
	return nullptr;
}

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
