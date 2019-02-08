//==============================================================================
// Context.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Context
//------------------------------------------------------------------------------
Context Context::_context;

Context::Context() : _pObjectStack(new ObjectStack()), _pFrame(Frame::CreateSource())
{
	_pObjectStack->reserve(8192);
}

}
