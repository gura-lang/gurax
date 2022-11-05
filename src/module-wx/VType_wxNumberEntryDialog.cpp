//==============================================================================
// VType_wxNumberEntryDialog.cpp
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

${help.ComposePropertyHelp(wx.NumberEntryDialog, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.NumberEntryDialog, `en)}

${help.ComposeMethodHelp(wx.NumberEntryDialog, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.NumberEntryDialog(parent as wx.Window, message as String, prompt as String, caption as String, value as Number, min as Number, max as Number, pos? as wx.Point) {block?}
Gurax_DeclareConstructorAlias(NumberEntryDialog_gurax, "NumberEntryDialog")
{
	Declare(VTYPE_wxNumberEntryDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("prompt", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.NumberEntryDialog.");
}

Gurax_ImplementConstructorEx(NumberEntryDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* message = args_gurax.PickString();
	const char* prompt = args_gurax.PickString();
	const char* caption = args_gurax.PickString();
	long value = args_gurax.PickNumber<long>();
	long min = args_gurax.PickNumber<long>();
	long max = args_gurax.PickNumber<long>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	// Function body
	auto pEntity_gurax = new Value_wxNumberEntryDialog::EntityT(parent, message, prompt, caption, value, min, max, pos);
	RefPtr<Value_wxNumberEntryDialog> pValue_gurax(new Value_wxNumberEntryDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.NumberEntryDialog#GetValue()
Gurax_DeclareMethodAlias(wxNumberEntryDialog, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNumberEntryDialog, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxNumberEntryDialog
//------------------------------------------------------------------------------
VType_wxNumberEntryDialog VTYPE_wxNumberEntryDialog("NumberEntryDialog");

void VType_wxNumberEntryDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(NumberEntryDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxNumberEntryDialog, GetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxNumberEntryDialog
//------------------------------------------------------------------------------
VType& Value_wxNumberEntryDialog::vtype = VTYPE_wxNumberEntryDialog;

String Value_wxNumberEntryDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.NumberEntryDialog");
}

//------------------------------------------------------------------------------
// Value_wxNumberEntryDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
