//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::Array(ElemType elemType, Memory* pMemory) : _elemType(elemType), _pMemory(pMemory)
{
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Format("Array:%s", ElemTypeToSymbol(_elemType)->GetName());
}

}
