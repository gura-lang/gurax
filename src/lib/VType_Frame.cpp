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
}

Value* VType_Frame::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Frame> pFrame;
	if (value.IsType(VTYPE_Module)) {
		pFrame.reset(Value_Module::GetModule(value).GetFrame().Reference());
	} else if (value.IsType(VTYPE_VType)) {
		pFrame.reset(Value_VType::GetVTypeThis(value).GetFrame().Reference());
	} else {
		pFrame.reset(value.GetVType().GetFrame().Reference());
	}
	return new Value_Frame(pFrame.release());
}

//------------------------------------------------------------------------------
// Value_Frame
//------------------------------------------------------------------------------

}
