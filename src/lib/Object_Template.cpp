//==============================================================================
// Value_Template.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Value_Template
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Template
//------------------------------------------------------------------------------
VType_Template VTYPE_Template("Template");

void VType_Template::DoPrepare(Frame* pFrame)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	pFrame->AssignVType(*this);
}

}
