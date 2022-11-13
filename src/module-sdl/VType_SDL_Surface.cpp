//==============================================================================
// VType_SDL_Surface.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Surface, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Surface, `en)}

${help.ComposeMethodHelp(sdl.SDL_Surface, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Surface#format
Gurax_DeclareProperty_R(SDL_Surface, format)
{
	Declare(VTYPE_SDL_PixelFormat, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_PixelFormat(valueThis.GetEntity().format);
}

// sdl.SDL_Surface#w
Gurax_DeclareProperty_R(SDL_Surface, w)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, w)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().w);
}

// sdl.SDL_Surface#h
Gurax_DeclareProperty_R(SDL_Surface, h)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, h)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().h);
}

// sdl.SDL_Surface#pitch
Gurax_DeclareProperty_R(SDL_Surface, pitch)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, pitch)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().pitch);
}

// sdl.SDL_Surface#pixels
Gurax_DeclareProperty_R(SDL_Surface, pixels)
{
	Declare(VTYPE_Array, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, pixels)
{
	auto& valueThis = GetValueThis(valueTarget);
	SDL_Surface& surface = valueThis.GetEntity();
	size_t bytes = surface.h * surface.pitch;
	RefPtr<Memory> pMemory(new MemorySloth(surface.pixels));
	RefPtr<Array> pArray(new Array(Array::ElemType::UInt8, pMemory.release(), DimSizes(bytes)));
	return new Value_Array(pArray.release());
}

#if 0
// sdl.SDL_Surface#userdata
Gurax_DeclareProperty_R(SDL_Surface, userdata)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, userdata)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().userdata);
}
#endif

// sdl.SDL_Surface#clip_rect
Gurax_DeclareProperty_R(SDL_Surface, clip_rect)
{
	Declare(VTYPE_SDL_Rect, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, clip_rect)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_Rect(valueThis.GetEntity().clip_rect);
}

// sdl.SDL_Surface#refcount
Gurax_DeclareProperty_R(SDL_Surface, refcount)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_Surface, refcount)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().refcount);
}

//------------------------------------------------------------------------------
// VType_SDL_Surface
//------------------------------------------------------------------------------
VType_SDL_Surface VTYPE_SDL_Surface("SDL_Surface");

void VType_SDL_Surface::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Surface, format));
	Assign(Gurax_CreateProperty(SDL_Surface, w));
	Assign(Gurax_CreateProperty(SDL_Surface, h));
	Assign(Gurax_CreateProperty(SDL_Surface, pitch));
	//Assign(Gurax_CreateProperty(SDL_Surface, pixels));
	//Assign(Gurax_CreateProperty(SDL_Surface, userdata));
	Assign(Gurax_CreateProperty(SDL_Surface, clip_rect));
	Assign(Gurax_CreateProperty(SDL_Surface, refcount));
}

Value* VType_SDL_Surface::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Image)) {
		return Value_SDL_Surface::Create(Value_Image::GetImage(value).Reference());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_SDL_Surface
//------------------------------------------------------------------------------
VType& Value_SDL_Surface::vtype = VTYPE_SDL_Surface;

Value_SDL_Surface* Value_SDL_Surface::Create(Image* pImage)
{
	void* pixels = pImage->GetPointerC();
	int width = static_cast<int>(pImage->GetWidth());
	int height = static_cast<int>(pImage->GetHeight());
	int depth = pImage->IsFormat(Image::Format::RGB)? 24 : 32;
	int pitch = static_cast<int>(pImage->GetBytesPerLine());
	Uint32 format = pImage->IsFormat(Image::Format::RGB)? SDL_PIXELFORMAT_BGR24 : SDL_PIXELFORMAT_BGRA32;
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format);
	return new Value_SDL_Surface(surface, pImage);
}

String Value_SDL_Surface::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Surface");
}

Gurax_EndModuleScope(sdl)
