//==============================================================================
// VType_SDL_HapticCondition.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticCondition, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticCondition, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticCondition, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticCondition#type
Gurax_DeclareProperty_R(SDL_HapticCondition, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticCondition#direction
Gurax_DeclareProperty_R(SDL_HapticCondition, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticCondition#length
Gurax_DeclareProperty_R(SDL_HapticCondition, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticCondition#delay
Gurax_DeclareProperty_R(SDL_HapticCondition, delay)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, delay)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().delay);
}

// sdl.SDL_HapticCondition#button
Gurax_DeclareProperty_R(SDL_HapticCondition, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_HapticCondition#interval
Gurax_DeclareProperty_R(SDL_HapticCondition, interval)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, interval)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().interval);
}

// sdl.SDL_HapticCondition#right_sat
Gurax_DeclareProperty_R(SDL_HapticCondition, right_sat)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, right_sat)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().right_sat);
}

// sdl.SDL_HapticCondition#left_sat
Gurax_DeclareProperty_R(SDL_HapticCondition, left_sat)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, left_sat)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().left_sat);
}

// sdl.SDL_HapticCondition#right_coeff
Gurax_DeclareProperty_R(SDL_HapticCondition, right_coeff)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, right_coeff)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().right_coeff);
}

// sdl.SDL_HapticCondition#left_coeff
Gurax_DeclareProperty_R(SDL_HapticCondition, left_coeff)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, left_coeff)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().left_coeff);
}

// sdl.SDL_HapticCondition#deadband
Gurax_DeclareProperty_R(SDL_HapticCondition, deadband)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, deadband)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().deadband);
}

// sdl.SDL_HapticCondition#center
Gurax_DeclareProperty_R(SDL_HapticCondition, center)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticCondition, center)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().center);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticCondition
//------------------------------------------------------------------------------
VType_SDL_HapticCondition VTYPE_SDL_HapticCondition("SDL_HapticCondition");

void VType_SDL_HapticCondition::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticCondition, type));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, direction));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, length));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, delay));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, button));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, interval));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, right_sat));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, left_sat));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, right_coeff));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, left_coeff));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, deadband));
	Assign(Gurax_CreateProperty(SDL_HapticCondition, center));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticCondition
//------------------------------------------------------------------------------
VType& Value_SDL_HapticCondition::vtype = VTYPE_SDL_HapticCondition;

String Value_SDL_HapticCondition::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticCondition");
}

Gurax_EndModuleScope(sdl)
