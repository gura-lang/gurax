//==============================================================================
// Value_Bool.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Value_Bool
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Bool
//------------------------------------------------------------------------------
VType_Bool VTYPE_Bool("Bool");

void VType_Bool::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
