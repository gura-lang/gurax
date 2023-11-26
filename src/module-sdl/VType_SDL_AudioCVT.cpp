//==============================================================================
// VType_SDL_AudioCVT.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioCVT, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioCVT, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioCVT, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioCVT#src_format
Gurax_DeclareProperty_R(SDL_AudioCVT, src_format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, src_format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().src_format);
}

// sdl.SDL_AudioCVT#dst_format
Gurax_DeclareProperty_R(SDL_AudioCVT, dst_format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, dst_format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().dst_format);
}

// sdl.SDL_AudioCVT#rate_incr
Gurax_DeclareProperty_R(SDL_AudioCVT, rate_incr)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, rate_incr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().rate_incr);
}

// sdl.SDL_AudioCVT#buf
Gurax_DeclareProperty_R(SDL_AudioCVT, buf)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, buf)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_AudioCVT#len
Gurax_DeclareProperty_R(SDL_AudioCVT, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, len)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().len);
}

// sdl.SDL_AudioCVT#len_cvt
Gurax_DeclareProperty_R(SDL_AudioCVT, len_cvt)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, len_cvt)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().len_cvt);
}

// sdl.SDL_AudioCVT#len_mult
Gurax_DeclareProperty_R(SDL_AudioCVT, len_mult)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, len_mult)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().len_mult);
}

// sdl.SDL_AudioCVT#len_ratio
Gurax_DeclareProperty_R(SDL_AudioCVT, len_ratio)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_AudioCVT, len_ratio)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().len_ratio);
}

//------------------------------------------------------------------------------
// VType_SDL_AudioCVT
//------------------------------------------------------------------------------
VType_SDL_AudioCVT VTYPE_SDL_AudioCVT("SDL_AudioCVT");

void VType_SDL_AudioCVT::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioCVT, src_format));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, dst_format));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, rate_incr));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, buf));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, len));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, len_cvt));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, len_mult));
	Assign(Gurax_CreateProperty(SDL_AudioCVT, len_ratio));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioCVT
//------------------------------------------------------------------------------
VType& Value_SDL_AudioCVT::vtype = VTYPE_SDL_AudioCVT;

String Value_SDL_AudioCVT::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_AudioCVT");
}

Gurax_EndModuleScope(sdl)
