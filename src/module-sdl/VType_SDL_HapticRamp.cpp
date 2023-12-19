//==============================================================================
// VType_SDL_HapticRamp.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticRamp, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticRamp, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticRamp, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticRamp#type
Gurax_DeclareProperty_R(SDL_HapticRamp, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticRamp#direction
Gurax_DeclareProperty_R(SDL_HapticRamp, direction)
{
	Declare(VTYPE_SDL_HapticDirection, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, direction)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_HapticDirection(valueThis.GetValue_HapticEffect().Reference());
}

// sdl.SDL_HapticRamp#length
Gurax_DeclareProperty_R(SDL_HapticRamp, length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().length);
}

// sdl.SDL_HapticRamp#delay
Gurax_DeclareProperty_R(SDL_HapticRamp, delay)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, delay)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().delay);
}

// sdl.SDL_HapticRamp#button
Gurax_DeclareProperty_R(SDL_HapticRamp, button)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().button);
}

// sdl.SDL_HapticRamp#interval
Gurax_DeclareProperty_R(SDL_HapticRamp, interval)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, interval)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().interval);
}

// sdl.SDL_HapticRamp#start
Gurax_DeclareProperty_R(SDL_HapticRamp, start)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, start)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().start);
}

// sdl.SDL_HapticRamp#end
Gurax_DeclarePropertyAlias_R(SDL_HapticRamp, end_, "end")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, end_)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().end);
}

// sdl.SDL_HapticRamp#attack_length
Gurax_DeclareProperty_R(SDL_HapticRamp, attack_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, attack_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_length);
}

// sdl.SDL_HapticRamp#attack_level
Gurax_DeclareProperty_R(SDL_HapticRamp, attack_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, attack_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().attack_level);
}

// sdl.SDL_HapticRamp#fade_length
Gurax_DeclareProperty_R(SDL_HapticRamp, fade_length)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, fade_length)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_length);
}

// sdl.SDL_HapticRamp#fade_level
Gurax_DeclareProperty_R(SDL_HapticRamp, fade_level)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticRamp, fade_level)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().fade_level);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticRamp
//------------------------------------------------------------------------------
VType_SDL_HapticRamp VTYPE_SDL_HapticRamp("SDL_HapticRamp");

void VType_SDL_HapticRamp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticRamp, type));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, direction));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, length));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, delay));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, button));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, interval));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, start));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, end_));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, attack_length));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, attack_level));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, fade_length));
	Assign(Gurax_CreateProperty(SDL_HapticRamp, fade_level));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticRamp
//------------------------------------------------------------------------------
VType& Value_SDL_HapticRamp::vtype = VTYPE_SDL_HapticRamp;

String Value_SDL_HapticRamp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticRamp");
}

Gurax_EndModuleScope(sdl)
