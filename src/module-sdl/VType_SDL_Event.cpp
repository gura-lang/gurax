//==============================================================================
// VType_SDL_Event.cpp
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

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// SDL_Event() {block?}
Gurax_DeclareConstructor(SDL_Event)
{
	Declare(VTYPE_SDL_Event, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `sdl.SDL_Event` instance.\n");
}

Gurax_ImplementConstructor(SDL_Event)
{
	// Function body
	return argument.ReturnValue(processor, new Value_SDL_Event());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// sdl.SDL_Event#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(SDL_Event, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(SDL_Event, MethodSkeleton)
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
// Implementation of property (window)
//-----------------------------------------------------------------------------
// sdl.SDL_Event#window_data1
Gurax_DeclareProperty_R(SDL_Event, window_data1)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, window_data1)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_Event#window_data2
Gurax_DeclareProperty_R(SDL_Event, window_data2)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, window_data2)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//-----------------------------------------------------------------------------
// Implementation of property (key)
//-----------------------------------------------------------------------------
// sdl.SDL_Event#key_state
Gurax_DeclareProperty_R(SDL_Event, key_state)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, key_state)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_Event#key_repeat
Gurax_DeclareProperty_R(SDL_Event, key_repeat)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, key_repeat)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

// sdl.SDL_Event#key_keysym
Gurax_DeclareProperty_R(SDL_Event, key_keysym)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, key_keysym)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//-----------------------------------------------------------------------------
// Implementation of property (text)
//-----------------------------------------------------------------------------
// sdl.SDL_Event#text_text
Gurax_DeclareProperty_R(SDL_Event, text_text)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(SDL_Event, text_text)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_SDL_Event
//------------------------------------------------------------------------------
VType_SDL_Event VTYPE_SDL_Event("SDL_Event");

void VType_SDL_Event::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(SDL_Event));
	// Assignment of method
	Assign(Gurax_CreateMethod(SDL_Event, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(SDL_Event, propSkeleton));
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, window_data1));
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, window_data2));
		pPropSlotMap_window.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, key_state));
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, key_repeat));
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, key_keysym));
		pPropSlotMap_key.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap->Assign(Gurax_CreateProperty(SDL_Event, text_text));
		pPropSlotMap_edit.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_text.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_motion.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_button.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_wheel.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_jaxis.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_jball.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_jhat.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_jbutton.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_jdevice.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_caxis.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_cbutton.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_cdevice.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_adevice.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_quit.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_user.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_syswm.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_tfinger.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_mgesture.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_dgesture.reset(pPropSlotMap.release());
	} while (0);
	do {
		RefPtr<PropSlotMap> pPropSlotMap(new PropSlotMap());
		pPropSlotMap_drop.reset(pPropSlotMap.release());
	} while (0);
}

//------------------------------------------------------------------------------
// Value_SDL_Event
//------------------------------------------------------------------------------
VType& Value_SDL_Event::vtype = VTYPE_SDL_Event;

Value* Value_SDL_Event::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	const VType_SDL_Event& vtype = dynamic_cast<const VType_SDL_Event&>(GetVType());
	const SDL_Event& event = GetEntity();
	const PropSlot* pPropSlot =
		(event.type == SDL_WINDOWEVENT)?				vtype.pPropSlotMap_window->Lookup(pSymbol) :
		(event.type == SDL_KEYDOWN)?					vtype.pPropSlotMap_key->Lookup(pSymbol) :
		(event.type == SDL_KEYUP)?						vtype.pPropSlotMap_key->Lookup(pSymbol) :
		(event.type == SDL_TEXTEDITING)?				vtype.pPropSlotMap_edit->Lookup(pSymbol) :
		(event.type == SDL_TEXTINPUT)?					vtype.pPropSlotMap_text->Lookup(pSymbol) :
		(event.type == SDL_MOUSEMOTION)?				vtype.pPropSlotMap_motion->Lookup(pSymbol) :
		(event.type == SDL_MOUSEBUTTONDOWN)?			vtype.pPropSlotMap_button->Lookup(pSymbol) :
		(event.type == SDL_MOUSEBUTTONUP)?				vtype.pPropSlotMap_button->Lookup(pSymbol) :
		(event.type == SDL_MOUSEWHEEL)?					vtype.pPropSlotMap_wheel->Lookup(pSymbol) :
		(event.type == SDL_JOYAXISMOTION)?				vtype.pPropSlotMap_jaxis->Lookup(pSymbol) :
		(event.type == SDL_JOYBALLMOTION)?				vtype.pPropSlotMap_jball->Lookup(pSymbol) :
		(event.type == SDL_JOYHATMOTION)?				vtype.pPropSlotMap_jhat->Lookup(pSymbol) :
		(event.type == SDL_JOYBUTTONDOWN)?				vtype.pPropSlotMap_jbutton->Lookup(pSymbol) :
		(event.type == SDL_JOYBUTTONUP)?				vtype.pPropSlotMap_jbutton->Lookup(pSymbol) :
		(event.type == SDL_JOYDEVICEADDED)?				vtype.pPropSlotMap_jdevice->Lookup(pSymbol) :
		(event.type == SDL_JOYDEVICEREMOVED)?			vtype.pPropSlotMap_jdevice->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERAXISMOTION)?		vtype.pPropSlotMap_caxis->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERBUTTONDOWN)?		vtype.pPropSlotMap_cbutton->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERBUTTONUP)?			vtype.pPropSlotMap_cbutton->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERDEVICEADDED)?		vtype.pPropSlotMap_cdevice->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERDEVICEREMOVED)?	vtype.pPropSlotMap_cdevice->Lookup(pSymbol) :
		(event.type == SDL_CONTROLLERDEVICEREMAPPED)?	vtype.pPropSlotMap_cdevice->Lookup(pSymbol) :
		(event.type == SDL_AUDIODEVICEADDED)?			vtype.pPropSlotMap_adevice->Lookup(pSymbol) :
		(event.type == SDL_AUDIODEVICEREMOVED)?			vtype.pPropSlotMap_adevice->Lookup(pSymbol) :
		(event.type == SDL_QUIT)?						vtype.pPropSlotMap_quit->Lookup(pSymbol) :
		(event.type == SDL_SYSWMEVENT)?					vtype.pPropSlotMap_syswm->Lookup(pSymbol) :
		(event.type == SDL_FINGERMOTION)?				vtype.pPropSlotMap_tfinger->Lookup(pSymbol) :
		(event.type == SDL_FINGERDOWN)?					vtype.pPropSlotMap_tfinger->Lookup(pSymbol) :
		(event.type == SDL_FINGERUP)?					vtype.pPropSlotMap_tfinger->Lookup(pSymbol) :
		(event.type == SDL_MULTIGESTURE)?				vtype.pPropSlotMap_mgesture->Lookup(pSymbol) :
		(event.type == SDL_DOLLARGESTURE)?				vtype.pPropSlotMap_dgesture->Lookup(pSymbol) :
		(event.type == SDL_DOLLARRECORD)?				vtype.pPropSlotMap_dgesture->Lookup(pSymbol) :
		(event.type == SDL_DROPFILE)?					vtype.pPropSlotMap_drop->Lookup(pSymbol) :
		(event.type == SDL_DROPTEXT)?					vtype.pPropSlotMap_drop->Lookup(pSymbol) :
		(event.type == SDL_DROPBEGIN)?					vtype.pPropSlotMap_drop->Lookup(pSymbol) :
		(event.type == SDL_DROPCOMPLETE)?				vtype.pPropSlotMap_drop->Lookup(pSymbol) :
		nullptr;
	if (pPropSlot) return pPropSlot->GetValue(*this, attr);
	return Value::DoGetProperty(pSymbol, attr, notFoundErrorFlag);
}

String Value_SDL_Event::ToString(const StringStyle& ss) const
{
	return "sdl.SDL_Event";
}

Gurax_EndModuleScope(sdl)
