//==============================================================================
// VType_SDL_HapticPeriodic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticPeriodic, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticPeriodic, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticPeriodic, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticPeriodic#type
Gurax_DeclareProperty_R(SDL_HapticPeriodic, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticPeriodic#direction
Gurax_DeclareProperty_R(SDL_HapticPeriodic, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticPeriodic#length
Gurax_DeclareProperty_R(SDL_HapticPeriodic, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticPeriodic#delay
Gurax_DeclareProperty_R(SDL_HapticPeriodic, delay)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, delay)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().delay);
}

// sdl.SDL_HapticPeriodic#button
Gurax_DeclareProperty_R(SDL_HapticPeriodic, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_HapticPeriodic#interval
Gurax_DeclareProperty_R(SDL_HapticPeriodic, interval)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, interval)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().interval);
}

// sdl.SDL_HapticPeriodic#period
Gurax_DeclareProperty_R(SDL_HapticPeriodic, period)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, period)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().period);
}

// sdl.SDL_HapticPeriodic#attack_length
Gurax_DeclareProperty_R(SDL_HapticPeriodic, attack_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, attack_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_length);
}

// sdl.SDL_HapticPeriodic#attack_level
Gurax_DeclareProperty_R(SDL_HapticPeriodic, attack_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, attack_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_level);
}

// sdl.SDL_HapticPeriodic#fade_length
Gurax_DeclareProperty_R(SDL_HapticPeriodic, fade_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, fade_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_length);
}

// sdl.SDL_HapticPeriodic#fade_level
Gurax_DeclareProperty_R(SDL_HapticPeriodic, fade_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticPeriodic, fade_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_level);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticPeriodic
//------------------------------------------------------------------------------
VType_SDL_HapticPeriodic VTYPE_SDL_HapticPeriodic("SDL_HapticPeriodic");

void VType_SDL_HapticPeriodic::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, type));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, direction));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, length));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, delay));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, button));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, interval));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, period));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, attack_length));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, attack_level));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, fade_length));
	Assign(Gurax_CreateProperty(SDL_HapticPeriodic, fade_level));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticPeriodic
//------------------------------------------------------------------------------
VType& Value_SDL_HapticPeriodic::vtype = VTYPE_SDL_HapticPeriodic;

String Value_SDL_HapticPeriodic::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticPeriodic");
}

Gurax_EndModuleScope(sdl)
