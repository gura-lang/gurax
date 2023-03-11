//==============================================================================
// VType_SDL_Event.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(sdl.SDL_Event, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(sdl.SDL_Event, `en)}

${help.ComposeMethodHelp(sdl.SDL_Event, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Event() {block?}
Gurax_DeclareConstructor(SDL_Event)
{
	Declare(VTYPE_SDL_Event, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `sdl.SDL_Event` instance.
)""");
}

Gurax_ImplementConstructor(SDL_Event)
{
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Event());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// sdl.SDL_Event#type
Gurax_DeclareProperty_R(SDL_Event, type)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, type)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetEntity().type);
}

// sdl.SDL_Event#common
Gurax_DeclareProperty_R(SDL_Event, common)
{
	Declare(VTYPE_SDL_CommonEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, common)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_CommonEvent(valueThis.Reference());
}

// sdl.SDL_Event#window
Gurax_DeclareProperty_R(SDL_Event, window)
{
	Declare(VTYPE_SDL_WindowEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, window)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_WindowEvent(valueThis.Reference());
}

// sdl.SDL_Event#key
Gurax_DeclareProperty_R(SDL_Event, key)
{
	Declare(VTYPE_SDL_KeyboardEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, key)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_KeyboardEvent(valueThis.Reference());
}

// sdl.SDL_Event#edit
Gurax_DeclareProperty_R(SDL_Event, edit)
{
	Declare(VTYPE_SDL_TextEditingEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, edit)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_TextEditingEvent(valueThis.Reference());
}

// sdl.SDL_Event#text
Gurax_DeclareProperty_R(SDL_Event, text)
{
	Declare(VTYPE_SDL_TextInputEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, text)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_TextInputEvent(valueThis.Reference());
}

// sdl.SDL_Event#motion
Gurax_DeclareProperty_R(SDL_Event, motion)
{
	Declare(VTYPE_SDL_MouseMotionEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, motion)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_MouseMotionEvent(valueThis.Reference());
}

// sdl.SDL_Event#button
Gurax_DeclareProperty_R(SDL_Event, button)
{
	Declare(VTYPE_SDL_MouseButtonEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, button)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_MouseButtonEvent(valueThis.Reference());
}

// sdl.SDL_Event#wheel
Gurax_DeclareProperty_R(SDL_Event, wheel)
{
	Declare(VTYPE_SDL_MouseWheelEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, wheel)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_MouseWheelEvent(valueThis.Reference());
}

// sdl.SDL_Event#jaxis
Gurax_DeclareProperty_R(SDL_Event, jaxis)
{
	Declare(VTYPE_SDL_JoyAxisEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, jaxis)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_JoyAxisEvent(valueThis.Reference());
}

// sdl.SDL_Event#jball
Gurax_DeclareProperty_R(SDL_Event, jball)
{
	Declare(VTYPE_SDL_JoyBallEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, jball)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_JoyBallEvent(valueThis.Reference());
}

// sdl.SDL_Event#jhat
Gurax_DeclareProperty_R(SDL_Event, jhat)
{
	Declare(VTYPE_SDL_JoyHatEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, jhat)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_JoyHatEvent(valueThis.Reference());
}

// sdl.SDL_Event#jbutton
Gurax_DeclareProperty_R(SDL_Event, jbutton)
{
	Declare(VTYPE_SDL_JoyButtonEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, jbutton)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_JoyButtonEvent(valueThis.Reference());
}

// sdl.SDL_Event#jdevice
Gurax_DeclareProperty_R(SDL_Event, jdevice)
{
	Declare(VTYPE_SDL_JoyDeviceEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, jdevice)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_JoyDeviceEvent(valueThis.Reference());
}

// sdl.SDL_Event#caxis
Gurax_DeclareProperty_R(SDL_Event, caxis)
{
	Declare(VTYPE_SDL_ControllerAxisEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, caxis)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_ControllerAxisEvent(valueThis.Reference());
}

// sdl.SDL_Event#cbutton
Gurax_DeclareProperty_R(SDL_Event, cbutton)
{
	Declare(VTYPE_SDL_ControllerButtonEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, cbutton)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_ControllerButtonEvent(valueThis.Reference());
}

// sdl.SDL_Event#cdevice
Gurax_DeclareProperty_R(SDL_Event, cdevice)
{
	Declare(VTYPE_SDL_ControllerDeviceEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, cdevice)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_ControllerDeviceEvent(valueThis.Reference());
}

// sdl.SDL_Event#adevice
Gurax_DeclareProperty_R(SDL_Event, adevice)
{
	Declare(VTYPE_SDL_AudioDeviceEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, adevice)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_AudioDeviceEvent(valueThis.Reference());
}

// sdl.SDL_Event#quit
Gurax_DeclareProperty_R(SDL_Event, quit)
{
	Declare(VTYPE_SDL_QuitEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, quit)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_QuitEvent(valueThis.Reference());
}

// sdl.SDL_Event#user
Gurax_DeclareProperty_R(SDL_Event, user)
{
	Declare(VTYPE_SDL_UserEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, user)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_UserEvent(valueThis.Reference());
}

// sdl.SDL_Event#syswm
Gurax_DeclareProperty_R(SDL_Event, syswm)
{
	Declare(VTYPE_SDL_SysWMEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, syswm)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_SysWMEvent(valueThis.Reference());
}

// sdl.SDL_Event#tfinger
Gurax_DeclareProperty_R(SDL_Event, tfinger)
{
	Declare(VTYPE_SDL_TouchFingerEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, tfinger)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_TouchFingerEvent(valueThis.Reference());
}

// sdl.SDL_Event#mgesture
Gurax_DeclareProperty_R(SDL_Event, mgesture)
{
	Declare(VTYPE_SDL_MultiGestureEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, mgesture)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_MultiGestureEvent(valueThis.Reference());
}

// sdl.SDL_Event#dgesture
Gurax_DeclareProperty_R(SDL_Event, dgesture)
{
	Declare(VTYPE_SDL_DollarGestureEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, dgesture)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_DollarGestureEvent(valueThis.Reference());
}

// sdl.SDL_Event#drop
Gurax_DeclareProperty_R(SDL_Event, drop)
{
	Declare(VTYPE_SDL_DropEvent, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(SDL_Event, drop)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_SDL_DropEvent(valueThis.Reference());
}

//------------------------------------------------------------------------------
// VType_SDL_Event
//------------------------------------------------------------------------------
VType_SDL_Event VTYPE_SDL_Event("SDL_Event");

void VType_SDL_Event::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Event));
	// Assignment of property
	Assign(Gurax_CreateProperty(SDL_Event, type));
	Assign(Gurax_CreateProperty(SDL_Event, common));
	Assign(Gurax_CreateProperty(SDL_Event, window));
	Assign(Gurax_CreateProperty(SDL_Event, key));
	Assign(Gurax_CreateProperty(SDL_Event, edit));
	Assign(Gurax_CreateProperty(SDL_Event, text));
	Assign(Gurax_CreateProperty(SDL_Event, motion));
	Assign(Gurax_CreateProperty(SDL_Event, button));
	Assign(Gurax_CreateProperty(SDL_Event, wheel));
	Assign(Gurax_CreateProperty(SDL_Event, jaxis));
	Assign(Gurax_CreateProperty(SDL_Event, jball));
	Assign(Gurax_CreateProperty(SDL_Event, jhat));
	Assign(Gurax_CreateProperty(SDL_Event, jbutton));
	Assign(Gurax_CreateProperty(SDL_Event, jdevice));
	Assign(Gurax_CreateProperty(SDL_Event, caxis));
	Assign(Gurax_CreateProperty(SDL_Event, cbutton));
	Assign(Gurax_CreateProperty(SDL_Event, cdevice));
	Assign(Gurax_CreateProperty(SDL_Event, adevice));
	Assign(Gurax_CreateProperty(SDL_Event, quit));
	Assign(Gurax_CreateProperty(SDL_Event, user));
	Assign(Gurax_CreateProperty(SDL_Event, syswm));
	Assign(Gurax_CreateProperty(SDL_Event, tfinger));
	Assign(Gurax_CreateProperty(SDL_Event, mgesture));
	Assign(Gurax_CreateProperty(SDL_Event, dgesture));
	Assign(Gurax_CreateProperty(SDL_Event, drop));
}

//------------------------------------------------------------------------------
// Value_SDL_Event
//------------------------------------------------------------------------------
VType& Value_SDL_Event::vtype = VTYPE_SDL_Event;

String Value_SDL_Event::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "sdl.SDL_Event");
}

Gurax_EndModuleScope(sdl)
