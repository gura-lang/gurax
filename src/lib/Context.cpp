//==============================================================================
// Context.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Context
//------------------------------------------------------------------------------
Context Context::_context;

Context::Context() : _pFrame(new Frame_Root())
{
}

void Context::Prepare()
{
	Frame& frame = GetFrame();
	VType::PrepareBasic(frame);
	Value::PrepareBasic(frame);
	Functions::PrepareBasic(frame);
	Statements::PrepareBasic(frame);
	frame.Assign(Module_path::Create(frame.Reference()));
	frame.Assign(Module_re::Create(frame.Reference()));
	frame.Assign(Module_sys::Create(frame.Reference()));
}

}
