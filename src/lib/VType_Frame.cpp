//==============================================================================
// VType_Frame.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Frame
//------------------------------------------------------------------------------
VType_Frame VTYPE_Frame("Frame");

void VType_Frame::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	frameOuter.Assign(*this);
}

Value* VType_Frame::DoCastFrom(const Value& value) const
{
	RefPtr<Frame> pFrame;
	if (value.IsType(VTYPE_Module)) {
		pFrame.reset(dynamic_cast<const Value_Module&>(value).GetModule().GetFrame().Reference());
	} else if (value.IsType(VTYPE_VType)) {
		pFrame.reset(dynamic_cast<const Value_VType&>(value).GetVType().GetFrame().Reference());
	} else {
		return nullptr;
	}
	return new Value_Frame(pFrame.release());
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------

}
