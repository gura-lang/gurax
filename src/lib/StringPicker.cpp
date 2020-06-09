//==============================================================================
// StringPicker.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// StringPicker
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StringPicker_StringList
//------------------------------------------------------------------------------
const char* StringPicker_StringList::Pick()
{
	if (_pStr == _pStrEnd) return nullptr;
	const String& str = *(_pStr++);
	return str.c_str();
}

//------------------------------------------------------------------------------
// StringPicker_ValueList
//------------------------------------------------------------------------------
const char* StringPicker_ValueList::Pick()
{
	if (_ppValue == _ppValueEnd) return nullptr;
	const Value* pValue = *(_ppValue++);
	if (pValue->IsInstanceOf(VTYPE_String)) {
		return dynamic_cast<const Value_String*>(pValue)->GetString();
	} else {
		_str = pValue->ToString(StringStyle::SymbolQuoted_NilVisible);
		return _str.c_str();
	}
}

}
