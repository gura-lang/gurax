//==============================================================================
// VType_SDL_RendererInfo.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_RendererInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_RendererInfo, `en)}

${help.ComposeMethodHelp(sdl.SDL_RendererInfo, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_RendererInfo#name
Gurax_DeclareProperty_R(SDL_RendererInfo, name)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetEntity().name);
}

// sdl.SDL_RendererInfo#flags
Gurax_DeclareProperty_R(SDL_RendererInfo, flags)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, flags)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().flags);
}

// sdl.SDL_RendererInfo#num_texture_formats
Gurax_DeclareProperty_R(SDL_RendererInfo, num_texture_formats)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, num_texture_formats)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().num_texture_formats);
}

// sdl.SDL_RendererInfo#texture_formats
Gurax_DeclareProperty_R(SDL_RendererInfo, texture_formats)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, texture_formats)
{
	auto& valueThis = GetValueThis(valueTarget);
	const SDL_RendererInfo& info = valueThis.GetEntity();
	return Value_List::Create<Uint32>(info.texture_formats, info.num_texture_formats);
}

// sdl.SDL_RendererInfo#max_texture_width
Gurax_DeclareProperty_R(SDL_RendererInfo, max_texture_width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, max_texture_width)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().max_texture_width);
}

// sdl.SDL_RendererInfo#max_texture_height
Gurax_DeclareProperty_R(SDL_RendererInfo, max_texture_height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_RendererInfo, max_texture_height)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().max_texture_height);
}
//------------------------------------------------------------------------------
// VType_SDL_RendererInfo
//------------------------------------------------------------------------------
VType_SDL_RendererInfo VTYPE_SDL_RendererInfo("SDL_RendererInfo");

void VType_SDL_RendererInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_RendererInfo, name));
	Assign(Gurax_CreateProperty(SDL_RendererInfo, flags));
	Assign(Gurax_CreateProperty(SDL_RendererInfo, num_texture_formats));
	Assign(Gurax_CreateProperty(SDL_RendererInfo, texture_formats));
	Assign(Gurax_CreateProperty(SDL_RendererInfo, max_texture_width));
	Assign(Gurax_CreateProperty(SDL_RendererInfo, max_texture_height));
}

//------------------------------------------------------------------------------
// Value_SDL_RendererInfo
//------------------------------------------------------------------------------
VType& Value_SDL_RendererInfo::vtype = VTYPE_SDL_RendererInfo;

String Value_SDL_RendererInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_RendererInfo");
}

Gurax_EndModuleScope(sdl)
