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

${help.ComposePropertyHelp(sdl.SDL_TextInputEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_TextInputEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_TextInputEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_TextInputEvent#type
Gurax_DeclareProperty_R(SDL_TextInputEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
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
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_TextInputEvent#windowID
Gurax_DeclareProperty_R(SDL_TextInputEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_TextInputEvent#text
Gurax_DeclareProperty_R(SDL_TextInputEvent, text)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextInputEvent, text)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetEntity().text);
}

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
	Assign(Gurax_CreateProperty(SDL_TextInputEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_TextInputEvent, text));
}

//------------------------------------------------------------------------------
// Value_SDL_TextInputEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TextInputEvent::vtype = VTYPE_SDL_TextInputEvent;

String Value_SDL_TextInputEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_TextInputEvent");
}

Gurax_EndModuleScope(sdl)
