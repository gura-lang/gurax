//==============================================================================
// Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
bool Pointer::Advance(int distance)
{
	if (distance >= 0) {
		_offset += distance;
		return true;
	}
	if (_offset >= static_cast<size_t>(-distance)) {
		_offset += distance;
		return true;
	}
	Error::Issue(ErrorType::RangeError, "pointer offset is out of range");
	return false;
}

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
