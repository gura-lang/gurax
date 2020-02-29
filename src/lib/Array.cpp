//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax/Array.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::Array(ElemType elemType, Memory* pMemory) : _elemType(elemType), _pMemory(pMemory)
{
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Printf("Array:%s", ElemTypeToSymbol(_elemType)->GetName());
}

}
