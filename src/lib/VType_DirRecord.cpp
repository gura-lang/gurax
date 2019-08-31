//==============================================================================
// VType_DirRecord.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DirRecord
//------------------------------------------------------------------------------
VType_DirRecord VTYPE_DirRecord("DirRecord");

void VType_DirRecord::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_DirRecord
//------------------------------------------------------------------------------
VType& Value_DirRecord::vtype = VTYPE_DirRecord;

}
