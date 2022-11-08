//==============================================================================
// VType_wxStdDialogButtonSizer.cpp
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

${help.ComposePropertyHelp(wx.StdDialogButtonSizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StdDialogButtonSizer, `en)}

${help.ComposeMethodHelp(wx.StdDialogButtonSizer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StdDialogButtonSizer() {block?}
Gurax_DeclareConstructorAlias(StdDialogButtonSizer_gurax, "StdDialogButtonSizer")
{
	Declare(VTYPE_wxStdDialogButtonSizer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.StdDialogButtonSizer.");
}

Gurax_ImplementConstructorEx(StdDialogButtonSizer_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new wxStdDialogButtonSizer();
	RefPtr<Value_wxStdDialogButtonSizer> pValue_gurax(new Value_wxStdDialogButtonSizer(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StdDialogButtonSizer#AddButton(button as wx.Button)
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, AddButton_gurax, "AddButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button", VTYPE_wxButton, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, AddButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxButton& value_button = args_gurax.Pick<Value_wxButton>();
	wxButton* button = value_button.GetEntityPtr();
	// Function body
	pEntity_gurax->AddButton(button);
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#Realize()
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, Realize_gurax, "Realize")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, Realize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Realize();
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#SetAffirmativeButton(button as wx.Button)
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, SetAffirmativeButton_gurax, "SetAffirmativeButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button", VTYPE_wxButton, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, SetAffirmativeButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxButton& value_button = args_gurax.Pick<Value_wxButton>();
	wxButton* button = value_button.GetEntityPtr();
	// Function body
	pEntity_gurax->SetAffirmativeButton(button);
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#SetCancelButton(button as wx.Button)
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, SetCancelButton_gurax, "SetCancelButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button", VTYPE_wxButton, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, SetCancelButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxButton& value_button = args_gurax.Pick<Value_wxButton>();
	wxButton* button = value_button.GetEntityPtr();
	// Function body
	pEntity_gurax->SetCancelButton(button);
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#SetNegativeButton(button as wx.Button)
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, SetNegativeButton_gurax, "SetNegativeButton")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("button", VTYPE_wxButton, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, SetNegativeButton_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxButton& value_button = args_gurax.Pick<Value_wxButton>();
	wxButton* button = value_button.GetEntityPtr();
	// Function body
	pEntity_gurax->SetNegativeButton(button);
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

// wx.StdDialogButtonSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxStdDialogButtonSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStdDialogButtonSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStdDialogButtonSizer
//------------------------------------------------------------------------------
VType_wxStdDialogButtonSizer VTYPE_wxStdDialogButtonSizer("StdDialogButtonSizer");

void VType_wxStdDialogButtonSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBoxSizer, Flag::Mutable, Gurax_CreateConstructor(StdDialogButtonSizer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, AddButton_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, Realize_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, SetAffirmativeButton_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, SetCancelButton_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, SetNegativeButton_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, RecalcSizes_gurax));
	Assign(Gurax_CreateMethod(wxStdDialogButtonSizer, CalcMin_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStdDialogButtonSizer
//------------------------------------------------------------------------------
VType& Value_wxStdDialogButtonSizer::vtype = VTYPE_wxStdDialogButtonSizer;

String Value_wxStdDialogButtonSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StdDialogButtonSizer");
}

Gurax_EndModuleScope(wx)
