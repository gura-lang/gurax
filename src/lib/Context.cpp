//==============================================================================
// Context.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Context
//------------------------------------------------------------------------------
Context Context::_context;

void Context::Prepare()
{
	VType::PrepareBasic(GetFrame());
	Value::PrepareBasic(GetFrame());
	Functions::PrepareBasic(GetFrame());
}

}
