//==============================================================================
// VType_wxValidator.cpp
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
// wx.Validator() {block?}
Gurax_DeclareConstructorAlias(Validator_gurax, "Validator")
{
	Declare(VTYPE_wxValidator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Validator.");
}

Gurax_ImplementConstructorEx(Validator_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxValidator::EntityT();
	RefPtr<Value_wxValidator> pValue_gurax(new Value_wxValidator(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Validator#GetWindow() {block?}
Gurax_DeclareMethodAlias(wxValidator, GetWindow_gurax, "GetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxValidator, GetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetWindow()));
}

// wx.Validator#SetWindow(window as wx.Window)
Gurax_DeclareMethodAlias(wxValidator, SetWindow_gurax, "SetWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxValidator, SetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	pEntity_gurax->SetWindow(window);
	return Gurax::Value::nil();
}

// wx.Validator#TransferFromWindow()
Gurax_DeclareMethodAlias(wxValidator, TransferFromWindow_gurax, "TransferFromWindow")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxValidator, TransferFromWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->TransferFromWindow();
	return new Gurax::Value_Bool(rtn);
}

// wx.Validator#TransferToWindow()
Gurax_DeclareMethodAlias(wxValidator, TransferToWindow_gurax, "TransferToWindow")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxValidator, TransferToWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->TransferToWindow();
	return new Gurax::Value_Bool(rtn);
}

// wx.Validator#Validate(parent as wx.Window)
Gurax_DeclareMethodAlias(wxValidator, Validate_gurax, "Validate")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxValidator, Validate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->Validate(parent);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxValidator
//------------------------------------------------------------------------------
VType_wxValidator VTYPE_wxValidator("Validator");

void VType_wxValidator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Validator_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxValidator, GetWindow_gurax));
	Assign(Gurax_CreateMethod(wxValidator, SetWindow_gurax));
	Assign(Gurax_CreateMethod(wxValidator, TransferFromWindow_gurax));
	Assign(Gurax_CreateMethod(wxValidator, TransferToWindow_gurax));
	Assign(Gurax_CreateMethod(wxValidator, Validate_gurax));
}

//------------------------------------------------------------------------------
// Value_wxValidator
//------------------------------------------------------------------------------
VType& Value_wxValidator::vtype = VTYPE_wxValidator;

String Value_wxValidator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Validator");
}

//------------------------------------------------------------------------------
// Value_wxValidator::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
