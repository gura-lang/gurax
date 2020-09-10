//==============================================================================
// VType_SDL_MouseButtonEvent.cpp
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
// sdl.SDL_MouseButtonEvent#type
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseButtonEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseButtonEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseButtonEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 windowID;    /**< The window with mouse focus, if any */
Uint32 which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
Uint8 button;       /**< The mouse button index */
Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
Uint8 clicks;       /**< 1 for single-click, 2 for double-click, etc. */
Uint8 padding1;
Sint32 x;           /**< X coordinate, relative to window */
Sint32 y;           /**< Y coordinate, relative to window */
#endif

//------------------------------------------------------------------------------
// VType_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType_SDL_MouseButtonEvent VTYPE_SDL_MouseButtonEvent("SDL_MouseButtonEvent");

void VType_SDL_MouseButtonEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseButtonEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseButtonEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseButtonEvent::vtype = VTYPE_SDL_MouseButtonEvent;

String Value_SDL_MouseButtonEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MouseButtonEvent";
}

Gurax_EndModuleScope(sdl)
