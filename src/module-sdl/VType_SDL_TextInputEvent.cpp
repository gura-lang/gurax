//==============================================================================
// VType_SDL_TextInputEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_TextInputEvent#type
Gurax_DeclareProperty_R(SDL_TextInputEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_TextInputEvent#timestamp
Gurax_DeclareProperty_R(SDL_TextInputEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 windowID;                            /**< The window with keyboard focus, if any */
char text[SDL_TEXTEDITINGEVENT_TEXT_SIZE];  /**< The editing text */
#endif

//------------------------------------------------------------------------------
// VType_SDL_TextInputEvent
//------------------------------------------------------------------------------
VType_SDL_TextInputEvent VTYPE_SDL_TextInputEvent("SDL_TextInputEvent");

void VType_SDL_TextInputEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TextInputEvent, type));
	Assign(Gurax_CreateProperty(SDL_TextInputEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_TextInputEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TextInputEvent::vtype = VTYPE_SDL_TextInputEvent;

String Value_SDL_TextInputEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_TextInputEvent";
}

Gurax_EndModuleScope(sdl)
