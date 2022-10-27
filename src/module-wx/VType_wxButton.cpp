//==============================================================================
// VType_wxButton.cpp
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

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Button(parent as wx.Window, id as Number, label? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(Button_gurax, "Button")
{
	Declare(VTYPE_wxButton, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Button.");
}

Gurax_ImplementConstructorEx(Button_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxButtonNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxButton::EntityT(parent, id, label, pos, size, style, validator, name);
	RefPtr<Value_wxButton> pValue_gurax(new Value_wxButton(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Button#GetAuthNeeded()
Gurax_DeclareMethodAlias(wxButton, GetAuthNeeded_gurax, "GetAuthNeeded")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxButton, GetAuthNeeded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetAuthNeeded();
	return new Gurax::Value_Bool(rtn);
}

// wx.Button#GetLabel()
Gurax_DeclareMethodAlias(wxButton, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxButton, GetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLabel();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.Button#SetAuthNeeded(needed? as Bool)
Gurax_DeclareMethodAlias(wxButton, SetAuthNeeded_gurax, "SetAuthNeeded")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("needed", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxButton, SetAuthNeeded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool needed = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetAuthNeeded(needed);
	return Gurax::Value::nil();
}

// wx.Button#SetDefault() {block?}
Gurax_DeclareMethodAlias(wxButton, SetDefault_gurax, "SetDefault")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxButton, SetDefault_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->SetDefault()));
}

// wx.Button#SetLabel(label as String)
Gurax_DeclareMethodAlias(wxButton, SetLabel_gurax, "SetLabel")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxButton, SetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetLabel(label);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxButton
//------------------------------------------------------------------------------
VType_wxButton VTYPE_wxButton("Button");

void VType_wxButton::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAnyButton, Flag::Mutable, Gurax_CreateConstructor(Button_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxButton, GetAuthNeeded_gurax));
	Assign(Gurax_CreateMethod(wxButton, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxButton, SetAuthNeeded_gurax));
	Assign(Gurax_CreateMethod(wxButton, SetDefault_gurax));
	Assign(Gurax_CreateMethod(wxButton, SetLabel_gurax));
}

//------------------------------------------------------------------------------
// Value_wxButton
//------------------------------------------------------------------------------
VType& Value_wxButton::vtype = VTYPE_wxButton;

String Value_wxButton::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Button");
}

//------------------------------------------------------------------------------
// Value_wxButton::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
