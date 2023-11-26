//==============================================================================
// VType_SDL_HapticEffect.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_HapticEffect, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_HapticEffect, `en)}

${help.ComposeMethodHelp(sdl.SDL_HapticEffect, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_HapticEffect#type
Gurax_DeclareProperty_R(SDL_HapticEffect, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_HapticEffect#constant
Gurax_DeclareProperty_R(SDL_HapticEffect, constant)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, constant)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_HapticEffect#periodic
Gurax_DeclareProperty_R(SDL_HapticEffect, periodic)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, periodic)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_HapticEffect#condition
Gurax_DeclareProperty_R(SDL_HapticEffect, condition)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, condition)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_HapticEffect#ramp
Gurax_DeclareProperty_R(SDL_HapticEffect, ramp)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, ramp)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_HapticEffect#leftright
Gurax_DeclareProperty_R(SDL_HapticEffect, leftright)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, leftright)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_HapticEffect#custom
Gurax_DeclareProperty_R(SDL_HapticEffect, custom)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_HapticEffect, custom)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_HapticEffect
//------------------------------------------------------------------------------
VType_SDL_HapticEffect VTYPE_SDL_HapticEffect("SDL_HapticEffect");

void VType_SDL_HapticEffect::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_HapticEffect, type));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, constant));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, periodic));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, condition));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, ramp));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, leftright));
	Assign(Gurax_CreateProperty(SDL_HapticEffect, custom));
}

//------------------------------------------------------------------------------
// Value_SDL_HapticEffect
//------------------------------------------------------------------------------
VType& Value_SDL_HapticEffect::vtype = VTYPE_SDL_HapticEffect;

String Value_SDL_HapticEffect::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_HapticEffect");
}

Gurax_EndModuleScope(sdl)
