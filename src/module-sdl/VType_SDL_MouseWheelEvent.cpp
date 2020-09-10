//==============================================================================
// VType_SDL_MouseWheelEvent.cpp
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
// sdl.SDL_MouseWheelEvent#type
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_MouseWheelEvent#timestamp
Gurax_DeclareProperty_R(SDL_MouseWheelEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_MouseWheelEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 windowID;    /**< The window with mouse focus, if any */
Uint32 which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
Sint32 x;           /**< The amount scrolled horizontally, positive to the right and negative to the left */
Sint32 y;           /**< The amount scrolled vertically, positive away from the user and negative toward the user */
Uint32 direction;   /**< Set to one of the SDL_MOUSEWHEEL_* defines. When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back */
#endif

//------------------------------------------------------------------------------
// VType_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType_SDL_MouseWheelEvent VTYPE_SDL_MouseWheelEvent("SDL_MouseWheelEvent");

void VType_SDL_MouseWheelEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, type));
	Assign(Gurax_CreateProperty(SDL_MouseWheelEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_MouseWheelEvent
//------------------------------------------------------------------------------
VType& Value_SDL_MouseWheelEvent::vtype = VTYPE_SDL_MouseWheelEvent;

String Value_SDL_MouseWheelEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_MouseWheelEvent";
}

Gurax_EndModuleScope(sdl)
