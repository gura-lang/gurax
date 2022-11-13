//==============================================================================
// VType_SDL_Cursor.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Cursor, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Cursor, `en)}

${help.ComposeMethodHelp(sdl.SDL_Cursor, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Cursor#propSkeleton
Gurax_DeclareProperty_R(SDL_Cursor, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Cursor, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_Cursor
//------------------------------------------------------------------------------
VType_SDL_Cursor VTYPE_SDL_Cursor("SDL_Cursor");

void VType_SDL_Cursor::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Cursor, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_SDL_Cursor
//------------------------------------------------------------------------------
VType& Value_SDL_Cursor::vtype = VTYPE_SDL_Cursor;

String Value_SDL_Cursor::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Cursor");
}

Gurax_EndModuleScope(sdl)
