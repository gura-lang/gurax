//==============================================================================
// ValueDeque.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueDeque
//------------------------------------------------------------------------------
const ValueDeque ValueDeque::Empty;

void ValueDeque::IncCntRefOfEach() const
{
	for (Value* pValue : *this) pValue->IncCntRef();
}

void ValueDeque::DeleteEach()
{
	for (Value* pValue : *this) Value::Delete(pValue);
}

String ValueDeque::ToString(const StringStyle& ss) const
{
	String str;
	str += "[";
	for (auto ppValue = begin(); ppValue != end(); ++ppValue) {
		if (ppValue != begin()) str += ss.GetComma();
		str += (*ppValue)->ToString(ss);
	}
	str += "]";
	return str;
}

}
