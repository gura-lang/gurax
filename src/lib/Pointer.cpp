//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/Pointer.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
bool Pointer::PackStay(const char* format, const ValueList& valListArg)
{
	size_t offset = _offset;
	if (!Pack(format, valListArg)) return false;
	_offset = offset;
	return true;
}

Value* Pointer::UnpackStay(const char* format, const ValueList& valListArg, bool exceedErrorFlag)
{
	size_t offset = _offset;
	RefPtr<Value> pValue(Unpack(format, valListArg, exceedErrorFlag));
	_offset = offset;
	return pValue.release();
}

String Pointer::ToString(const StringStyle& ss) const
{
	return "Pointer";
}

}
