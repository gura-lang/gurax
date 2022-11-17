//==============================================================================
// VType_SDL_AudioSpec.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_AudioSpec, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_AudioSpec, `en)}

${help.ComposeMethodHelp(sdl.SDL_AudioSpec, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_AudioSpec() {block?}
Gurax_DeclareConstructor(SDL_AudioSpec)
{
	Declare(VTYPE_Color, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `SDL_AudioSpec` instance.
)**");
}

Gurax_ImplementConstructor(SDL_AudioSpec)
{
	// Arguments
	ArgPicker args(argument);
	SDL_AudioSpec audioSpec = {};
	// Function body
	return argument.ReturnValue(processor,
			new Value_SDL_AudioSpec(audioSpec, processor.CreateSubProcessor()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_AudioSpec#freq
Gurax_DeclareProperty_RW(SDL_AudioSpec, freq)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, freq)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().freq);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, freq)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().freq = Value_Number::GetNumber<int>(value);
}

// sdl.SDL_AudioSpec#format
Gurax_DeclareProperty_RW(SDL_AudioSpec, format)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().format);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, format)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().format = Value_Number::GetNumber<SDL_AudioFormat>(value);
}

// sdl.SDL_AudioSpec#channels
Gurax_DeclareProperty_RW(SDL_AudioSpec, channels)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, channels)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().channels);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, channels)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().channels = Value_Number::GetNumber<Uint8>(value);
}

// sdl.SDL_AudioSpec#silence
Gurax_DeclareProperty_RW(SDL_AudioSpec, silence)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, silence)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().silence);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, silence)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().silence = Value_Number::GetNumber<Uint8>(value);
}

// sdl.SDL_AudioSpec#samples
Gurax_DeclareProperty_RW(SDL_AudioSpec, samples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, samples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().samples);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, samples)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().samples = Value_Number::GetNumber<Uint16>(value);
}

// sdl.SDL_AudioSpec#size
Gurax_DeclareProperty_RW(SDL_AudioSpec, size)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, size)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().size);
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, size)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().size = Value_Number::GetNumber<Uint32>(value);
}

// sdl.SDL_AudioSpec#callback
Gurax_DeclareProperty_RW(SDL_AudioSpec, callback)
{
	Declare(VTYPE_Function, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, callback)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetEntity().callback = Value_SDL_AudioSpec::AudioCallback;
	Function* pFunc = valueThis.GetFuncAudioCallback();
	if (!pFunc) return Value::nil();
	return new Value_Function(pFunc->Reference());
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, callback)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetFuncAudioCallback(Value_Function::GetFunction(value).Reference());
}

// sdl.SDL_AudioSpec#userdata
Gurax_DeclareProperty_RW(SDL_AudioSpec, userdata)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(SDL_AudioSpec, userdata)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetValueUserdata().Reference();
}

Gurax_ImplementPropertySetter(SDL_AudioSpec, userdata)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.SetValueUserdata(value.Reference());
}

//------------------------------------------------------------------------------
// VType_SDL_AudioSpec
//------------------------------------------------------------------------------
VType_SDL_AudioSpec VTYPE_SDL_AudioSpec("SDL_AudioSpec");

void VType_SDL_AudioSpec::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_AudioSpec));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_AudioSpec, freq));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, format));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, channels));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, silence));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, samples));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, size));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, callback));
	Assign(Gurax_CreateProperty(SDL_AudioSpec, userdata));
}

//------------------------------------------------------------------------------
// Value_SDL_AudioSpec
//------------------------------------------------------------------------------
VType& Value_SDL_AudioSpec::vtype = VTYPE_SDL_AudioSpec;

Value_SDL_AudioSpec::Value_SDL_AudioSpec(Processor* pProcessor, VType& vtype) :
	Value_Object(vtype), _pProcessor(pProcessor), _pValueUserdata(Value::nil())
{
	_entity.callback = AudioCallback;
	_entity.userdata = this;
}

Value_SDL_AudioSpec::Value_SDL_AudioSpec(const SDL_AudioSpec& entity, Processor* pProcessor, VType& vtype) :
	Value_Object(vtype), _entity(entity), _pProcessor(pProcessor), _pValueUserdata(Value::nil())
{
	_entity.callback = AudioCallback;
	_entity.userdata = this;
}

void Value_SDL_AudioSpec::AudioCallback(void* userdata, Uint8* stream, int len)
{
	auto& valueThis = *reinterpret_cast<Value_SDL_AudioSpec*>(userdata);
	Function* pFunc = valueThis.GetFuncAudioCallback();
	if (!pFunc) return;
	RefPtr<Memory> pMemory(new MemorySloth(len, stream));
	Value::Delete(pFunc->EvalEasy(valueThis.GetProcessor(),
				valueThis.GetValueUserdata().Reference(),
				new Value_Pointer(new Pointer_Memory(pMemory.release()))));
}

String Value_SDL_AudioSpec::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_AudioSpec");
}

Gurax_EndModuleScope(sdl)
