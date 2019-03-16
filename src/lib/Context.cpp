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
	VType::PrepareBasic(GetFrame());
	Value::PrepareBasic(GetFrame());
	Functions::PrepareBasic(GetFrame());
	Statements::PrepareBasic(GetFrame());
}

}
