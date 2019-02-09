//==============================================================================
// Object_Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_Binary
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
VType_Binary VTYPE_Binary("Binary");

void VType_Binary::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
