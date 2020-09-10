//==============================================================================
// VType_SDL_UserEvent.cpp
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
// sdl.SDL_UserEvent#type
Gurax_DeclareProperty_R(SDL_UserEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_UserEvent#timestamp
Gurax_DeclareProperty_R(SDL_UserEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

#if 0
Uint32 windowID;    /**< The associated window if any */
Sint32 code;        /**< User defined event code */
void *data1;        /**< User defined data pointer */
void *data2;        /**< User defined data pointer */
#endif

//------------------------------------------------------------------------------
// VType_SDL_UserEvent
//------------------------------------------------------------------------------
VType_SDL_UserEvent VTYPE_SDL_UserEvent("SDL_UserEvent");

void VType_SDL_UserEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_UserEvent, type));
	Assign(Gurax_CreateProperty(SDL_UserEvent, timestamp));
}

//------------------------------------------------------------------------------
// Value_SDL_UserEvent
//------------------------------------------------------------------------------
VType& Value_SDL_UserEvent::vtype = VTYPE_SDL_UserEvent;

String Value_SDL_UserEvent::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_UserEvent";
}

Gurax_EndModuleScope(sdl)
