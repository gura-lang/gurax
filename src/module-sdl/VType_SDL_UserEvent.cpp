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

${help.ComposePropertyHelp(sdl.SDL_UserEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_UserEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_UserEvent, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_UserEvent#type
Gurax_DeclareProperty_R(SDL_UserEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_UserEvent#windowID
Gurax_DeclareProperty_R(SDL_UserEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

// sdl.SDL_UserEvent#code
Gurax_DeclareProperty_R(SDL_UserEvent, code)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, code)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().code);
}

#if 0
// sdl.SDL_UserEvent#*data1
Gurax_DeclareProperty_R(SDL_UserEvent, *data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, *data1)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().*data1);
}

// sdl.SDL_UserEvent#*data2
Gurax_DeclareProperty_R(SDL_UserEvent, *data2)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_UserEvent, *data2)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().*data2);
}
#endif

//------------------------------------------------------------------------------
// VType_SDL_UserEvent
//------------------------------------------------------------------------------
VType_SDL_UserEvent VTYPE_SDL_UserEvent("SDL_UserEvent");

void VType_SDL_UserEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_UserEvent, type));
	Assign(Gurax_CreateProperty(SDL_UserEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_UserEvent, windowID));
	Assign(Gurax_CreateProperty(SDL_UserEvent, code));
	//Assign(Gurax_CreateProperty(SDL_UserEvent, data1));
	//Assign(Gurax_CreateProperty(SDL_UserEvent, data2));
}

//------------------------------------------------------------------------------
// Value_SDL_UserEvent
//------------------------------------------------------------------------------
VType& Value_SDL_UserEvent::vtype = VTYPE_SDL_UserEvent;

String Value_SDL_UserEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_UserEvent");
}

Gurax_EndModuleScope(sdl)
