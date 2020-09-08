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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.SDL_Surface#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_Surface, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_Surface, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Surface#propSkeleton
Gurax_DeclareProperty_R(SDL_Surface, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Surface, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_Surface, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Surface, propSkeleton));
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
	return "sdl.SDL_Surface";
}

Gurax_EndModuleScope(sdl)
