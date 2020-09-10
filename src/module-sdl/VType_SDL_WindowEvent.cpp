//==============================================================================
// VType_SDL_WindowEvent.cpp
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
// sdl.SDL_WindowEvent#type
Gurax_DeclareProperty_R(SDL_WindowEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_WindowEvent#timestamp
Gurax_DeclareProperty_R(SDL_WindowEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 windowID;    /**< The associated window */
Uint8 event;        /**< ::SDL_WindowEventID */
Uint8 padding1;
Uint8 padding2;
Uint8 padding3;
Sint32 data1;       /**< event dependent data */
Sint32 data2;       /**< event dependent data */
#endif

//------------------------------------------------------------------------------
// VType_SDL_WindowEvent
//------------------------------------------------------------------------------
VType_SDL_WindowEvent VTYPE_SDL_WindowEvent("SDL_WindowEvent");

void VType_SDL_WindowEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_WindowEvent, type));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_WindowEvent
//------------------------------------------------------------------------------
VType& Value_SDL_WindowEvent::vtype = VTYPE_SDL_WindowEvent;

String Value_SDL_WindowEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_WindowEvent";
}

Gurax_EndModuleScope(sdl)
