//==============================================================================
// VType_SDL_HapticCustom.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticCustom, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticCustom, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticCustom, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticCustom#type
Gurax_DeclareProperty_R(SDL_HapticCustom, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticCustom#direction
Gurax_DeclareProperty_R(SDL_HapticCustom, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticCustom#length
Gurax_DeclareProperty_R(SDL_HapticCustom, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticCustom#delay
Gurax_DeclareProperty_R(SDL_HapticCustom, delay)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, delay)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().delay);
}

// sdl.SDL_HapticCustom#button
Gurax_DeclareProperty_R(SDL_HapticCustom, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_HapticCustom#interval
Gurax_DeclareProperty_R(SDL_HapticCustom, interval)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, interval)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().interval);
}

// sdl.SDL_HapticCustom#channels
Gurax_DeclareProperty_R(SDL_HapticCustom, channels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, channels)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().channels);
}

// sdl.SDL_HapticCustom#period
Gurax_DeclareProperty_R(SDL_HapticCustom, period)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, period)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().period);
}

// sdl.SDL_HapticCustom#samples
Gurax_DeclareProperty_R(SDL_HapticCustom, samples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, samples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().samples);
}

// sdl.SDL_HapticCustom#attack_length
Gurax_DeclareProperty_R(SDL_HapticCustom, attack_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, attack_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_length);
}

// sdl.SDL_HapticCustom#attack_level
Gurax_DeclareProperty_R(SDL_HapticCustom, attack_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, attack_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_level);
}

// sdl.SDL_HapticCustom#fade_length
Gurax_DeclareProperty_R(SDL_HapticCustom, fade_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, fade_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_length);
}

// sdl.SDL_HapticCustom#fade_level
Gurax_DeclareProperty_R(SDL_HapticCustom, fade_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCustom, fade_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_level);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticCustom
//------------------------------------------------------------------------------
VType_SDL_HapticCustom VTYPE_SDL_HapticCustom("SDL_HapticCustom");

void VType_SDL_HapticCustom::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticCustom, type));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, direction));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, length));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, delay));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, button));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, interval));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, channels));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, period));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, samples));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, attack_length));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, attack_level));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, fade_length));
	Assign(Gurax_CreateProperty(SDL_HapticCustom, fade_level));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticCustom
//------------------------------------------------------------------------------
VType& Value_SDL_HapticCustom::vtype = VTYPE_SDL_HapticCustom;

String Value_SDL_HapticCustom::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticCustom");
}

Gurax_EndModuleScope(sdl)
