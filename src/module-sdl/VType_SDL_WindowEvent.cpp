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

${help.ComposePropertyHelp(sdl.SDL_WindowEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_WindowEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_WindowEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_WindowEvent#type
Gurax_DeclareProperty_R(SDL_WindowEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_WindowEvent#windowID
Gurax_DeclareProperty_R(SDL_WindowEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_WindowEvent#event
Gurax_DeclareProperty_R(SDL_WindowEvent, event)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, event)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().event);
}

// sdl.SDL_WindowEvent#data1
Gurax_DeclareProperty_R(SDL_WindowEvent, data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().data1);
}

// sdl.SDL_WindowEvent#data2
Gurax_DeclareProperty_R(SDL_WindowEvent, data2)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_WindowEvent, data2)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().data2);
}

//------------------------------------------------------------------------------
// VType_SDL_WindowEvent
//------------------------------------------------------------------------------
VType_SDL_WindowEvent VTYPE_SDL_WindowEvent("SDL_WindowEvent");

void VType_SDL_WindowEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_WindowEvent, type));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, event));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, data1));
	Assign(Gurax_CreateProperty(SDL_WindowEvent, data2));
}

//------------------------------------------------------------------------------
// Value_SDL_WindowEvent
//------------------------------------------------------------------------------
VType& Value_SDL_WindowEvent::vtype = VTYPE_SDL_WindowEvent;

String Value_SDL_WindowEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_WindowEvent");
}

Gurax_EndModuleScope(sdl)
