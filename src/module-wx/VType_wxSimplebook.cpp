//==============================================================================
// VType_wxSimplebook.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wxSimplebook)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxSimplebook)}

${help.ComposeMethodHelp(wxSimplebook)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Simplebook(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Simplebook_gurax, "Simplebook")
{
	Declare(VTYPE_wxSimplebook, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Simplebook.");
}

Gurax_ImplementConstructorEx(Simplebook_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	auto pEntity_gurax = new Value_wxSimplebook::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxSimplebook> pValue_gurax(new Value_wxSimplebook(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Simplebook#SetEffects(showEffect as Number, hideEffect as Number)
Gurax_DeclareMethodAlias(wxSimplebook, SetEffects_gurax, "SetEffects")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("showEffect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hideEffect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimplebook, SetEffects_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxShowEffect showEffect = args_gurax.PickNumber<wxShowEffect>();
	wxShowEffect hideEffect = args_gurax.PickNumber<wxShowEffect>();
	// Function body
	pEntity_gurax->SetEffects(showEffect, hideEffect);
	return Gurax::Value::nil();
}

// wx.Simplebook#SetEffect(effect as Number)
Gurax_DeclareMethodAlias(wxSimplebook, SetEffect_gurax, "SetEffect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("effect", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimplebook, SetEffect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxShowEffect effect = args_gurax.PickNumber<wxShowEffect>();
	// Function body
	pEntity_gurax->SetEffect(effect);
	return Gurax::Value::nil();
}

// wx.Simplebook#SetEffectsTimeouts(showTimeout as Number, hideTimeout as Number)
Gurax_DeclareMethodAlias(wxSimplebook, SetEffectsTimeouts_gurax, "SetEffectsTimeouts")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("showTimeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("hideTimeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimplebook, SetEffectsTimeouts_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned showTimeout = args_gurax.PickNumber<unsigned>();
	unsigned hideTimeout = args_gurax.PickNumber<unsigned>();
	// Function body
	pEntity_gurax->SetEffectsTimeouts(showTimeout, hideTimeout);
	return Gurax::Value::nil();
}

// wx.Simplebook#SetEffectTimeout(timeout as Number)
Gurax_DeclareMethodAlias(wxSimplebook, SetEffectTimeout_gurax, "SetEffectTimeout")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("timeout", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimplebook, SetEffectTimeout_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned timeout = args_gurax.PickNumber<unsigned>();
	// Function body
	pEntity_gurax->SetEffectTimeout(timeout);
	return Gurax::Value::nil();
}

// wx.Simplebook#ShowNewPage(page as wx.Window)
Gurax_DeclareMethodAlias(wxSimplebook, ShowNewPage_gurax, "ShowNewPage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimplebook, ShowNewPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_page = args_gurax.Pick<Value_wxWindow>();
	wxWindow* page = value_page.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->ShowNewPage(page);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSimplebook
//------------------------------------------------------------------------------
VType_wxSimplebook VTYPE_wxSimplebook("Simplebook");

void VType_wxSimplebook::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlBase, Flag::Mutable, Gurax_CreateConstructor(Simplebook_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSimplebook, SetEffects_gurax));
	Assign(Gurax_CreateMethod(wxSimplebook, SetEffect_gurax));
	Assign(Gurax_CreateMethod(wxSimplebook, SetEffectsTimeouts_gurax));
	Assign(Gurax_CreateMethod(wxSimplebook, SetEffectTimeout_gurax));
	Assign(Gurax_CreateMethod(wxSimplebook, ShowNewPage_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSimplebook
//------------------------------------------------------------------------------
VType& Value_wxSimplebook::vtype = VTYPE_wxSimplebook;

String Value_wxSimplebook::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Simplebook");
}

//------------------------------------------------------------------------------
// Value_wxSimplebook::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
