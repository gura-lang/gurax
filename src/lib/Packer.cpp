//==============================================================================
// Packer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
bool Packer::Pack(const char* format, const ValueList& valListArg)
{
	return false;
}

Value* Packer::Unpack(const char* format, const ValueList& valListArg, bool exceedErrorFlag)
{
	return Value::nil();
}

bool Packer::PutBuffer(const void* buff, size_t bytes)
{
	if (!StorePrepare(bytes)) return false;
	StoreBuffer(buff, bytes);
	return true;
}

}
