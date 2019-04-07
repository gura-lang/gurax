//==============================================================================
// VType_Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Index
//------------------------------------------------------------------------------
VType_Index VTYPE_Index("Index");

void VType_Index::DoPrepare(Frame& frameOuter)
{
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

//------------------------------------------------------------------------------
// Value_Index
//------------------------------------------------------------------------------

}
