//==============================================================================
// VType_PathMgr.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PathMgr
//------------------------------------------------------------------------------
VType_PathMgr VTYPE_PathMgr("PathMgr");

void VType_PathMgr::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_PathMgr
//------------------------------------------------------------------------------

}
