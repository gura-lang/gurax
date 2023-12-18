//==============================================================================
// VType_SDL_HapticConstant.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticConstant, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticConstant, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticConstant, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticConstant#type
Gurax_DeclareProperty_R(SDL_HapticConstant, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticConstant#direction
Gurax_DeclareProperty_R(SDL_HapticConstant, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticConstant#length
Gurax_DeclareProperty_R(SDL_HapticConstant, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticConstant#delay
Gurax_DeclareProperty_R(SDL_HapticConstant, delay)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, delay)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().delay);
}

// sdl.SDL_HapticConstant#button
Gurax_DeclareProperty_R(SDL_HapticConstant, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_HapticConstant#interval
Gurax_DeclareProperty_R(SDL_HapticConstant, interval)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, interval)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().interval);
}

// sdl.SDL_HapticConstant#level
Gurax_DeclareProperty_R(SDL_HapticConstant, level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().level);
}

// sdl.SDL_HapticConstant#attack_length
Gurax_DeclareProperty_R(SDL_HapticConstant, attack_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, attack_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_length);
}

// sdl.SDL_HapticConstant#attack_level
Gurax_DeclareProperty_R(SDL_HapticConstant, attack_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, attack_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_level);
}

// sdl.SDL_HapticConstant#fade_length
Gurax_DeclareProperty_R(SDL_HapticConstant, fade_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, fade_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_length);
}

// sdl.SDL_HapticConstant#fade_level
Gurax_DeclareProperty_R(SDL_HapticConstant, fade_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticConstant, fade_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_level);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticConstant
//------------------------------------------------------------------------------
VType_SDL_HapticConstant VTYPE_SDL_HapticConstant("SDL_HapticConstant");

void VType_SDL_HapticConstant::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticConstant, type));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, direction));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, length));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, delay));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, button));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, interval));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, level));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, attack_length));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, attack_level));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, fade_length));
	Assign(Gurax_CreateProperty(SDL_HapticConstant, fade_level));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticConstant
//------------------------------------------------------------------------------
VType& Value_SDL_HapticConstant::vtype = VTYPE_SDL_HapticConstant;

String Value_SDL_HapticConstant::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticConstant");
}

Gurax_EndModuleScope(sdl)
