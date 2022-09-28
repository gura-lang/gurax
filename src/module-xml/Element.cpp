//==============================================================================
// Element.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Element
//------------------------------------------------------------------------------
Element::Element(Type type, String str) :
	_type(type), _str(str), _pAttrs(new AttrOwner()), _pElementsChild(new ElementOwner())
{
}

String Element::ToString(const StringStyle& ss) const
{
	return String().Format("xml.Element");
}

//------------------------------------------------------------------------------
// ElementList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ElementOwner
//------------------------------------------------------------------------------
void ElementOwner::Clear()
{
	for (Element* pElement : *this) Element::Delete(pElement);
	clear();
}

Gurax_EndModuleScope(xml)
