//==============================================================================
// VType_SDL_DropEvent.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_DropEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_DropEvent, `en)}

${help.ComposeMethodHelp(sdl.SDL_DropEvent, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_DropEvent#type
Gurax_DeclareProperty_R(SDL_DropEvent, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_DropEvent, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_DropEvent#timestamp
Gurax_DeclareProperty_R(SDL_DropEvent, timestamp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_DropEvent, timestamp)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().timestamp);
}

// sdl.SDL_DropEvent#file
Gurax_DeclareProperty_R(SDL_DropEvent, file)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_DropEvent, file)
{
	auto& valueThis = GetValueThis(valueTarget);
	char* file = valueThis.GetEntity().file;
	valueThis.GetEntity().file = nullptr;
	RefPtr<Value> pValue(new Value_Number(file));
	SDL_free(file);
	return pValue.release();
}

// sdl.SDL_DropEvent#windowID
Gurax_DeclareProperty_R(SDL_DropEvent, windowID)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_DropEvent, windowID)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().windowID);
}

//------------------------------------------------------------------------------
// VType_SDL_DropEvent
//------------------------------------------------------------------------------
VType_SDL_DropEvent VTYPE_SDL_DropEvent("SDL_DropEvent");

void VType_SDL_DropEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_DropEvent, type));
	Assign(Gurax_CreateProperty(SDL_DropEvent, timestamp));
	Assign(Gurax_CreateProperty(SDL_DropEvent, file));
	Assign(Gurax_CreateProperty(SDL_DropEvent, windowID));
}

//------------------------------------------------------------------------------
// Value_SDL_DropEvent
//------------------------------------------------------------------------------
VType& Value_SDL_DropEvent::vtype = VTYPE_SDL_DropEvent;

String Value_SDL_DropEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_DropEvent");
}

Gurax_EndModuleScope(sdl)
