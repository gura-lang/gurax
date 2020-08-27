//==============================================================================
// Util.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

void IssueError_SDL()
{
	Error::Issue(ErrorType::GuestError, "%s", SDL_GetError());
}

Gurax_EndModuleScope(sdl)
