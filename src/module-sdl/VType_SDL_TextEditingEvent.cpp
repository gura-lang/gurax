//==============================================================================
// VType_SDL_TextEditingEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_TextEditingEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_TextEditingEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_TextEditingEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_TextEditingEvent#type
Gurax_DeclareProperty_R(SDL_TextEditingEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_TextEditingEvent#timestamp
Gurax_DeclareProperty_R(SDL_TextEditingEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_TextEditingEvent#windowID
Gurax_DeclareProperty_R(SDL_TextEditingEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_TextEditingEvent#text
Gurax_DeclareProperty_R(SDL_TextEditingEvent, text)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, text)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetEntity().text);
}

// sdl.SDL_TextEditingEvent#start
Gurax_DeclareProperty_R(SDL_TextEditingEvent, start)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, start)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().start);
}

// sdl.SDL_TextEditingEvent#length
Gurax_DeclareProperty_R(SDL_TextEditingEvent, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_TextEditingEvent, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

//------------------------------------------------------------------------------
// VType_SDL_TextEditingEvent
//------------------------------------------------------------------------------
VType_SDL_TextEditingEvent VTYPE_SDL_TextEditingEvent("SDL_TextEditingEvent");

void VType_SDL_TextEditingEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, type));
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, text));
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, start));
	Assign(Gurax_CreateProperty(SDL_TextEditingEvent, length));
}

//------------------------------------------------------------------------------
// Value_SDL_TextEditingEvent
//------------------------------------------------------------------------------
VType& Value_SDL_TextEditingEvent::vtype = VTYPE_SDL_TextEditingEvent;

String Value_SDL_TextEditingEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_TextEditingEvent");
}

Gurax_EndModuleScope(sdl)
