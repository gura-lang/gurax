//==============================================================================
// VType_wxColourPickerCtrl.cpp
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

${help.ComposePropertyHelp(wxColourPickerCtrl)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxColourPickerCtrl)}

${help.ComposeMethodHelp(wxColourPickerCtrl)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ColourPickerCtrl(parent as wx.Window, id as Number, colour? as wx.Colour, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(ColourPickerCtrl_gurax, "ColourPickerCtrl")
{
	Declare(VTYPE_wxColourPickerCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ColourPickerCtrl.");
}

Gurax_ImplementConstructorEx(ColourPickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxColour& colour = args_gurax.IsValid()? args_gurax.Pick<Value_wxColour>().GetEntity() : *wxBLACK;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxCLRP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxColourPickerCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxColourPickerCtrl::EntityT(parent, id, colour, pos, size, style, validator, name);
	RefPtr<Value_wxColourPickerCtrl> pValue_gurax(new Value_wxColourPickerCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ColourPickerCtrl#Create(parent as wx.Window, id as Number, colour? as wx.Colour, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxColourPickerCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colour", VTYPE_wxColour, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourPickerCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxColour& colour = args_gurax.IsValid()? args_gurax.Pick<Value_wxColour>().GetEntity() : *wxBLACK;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxCLRP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxColourPickerCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, colour, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.ColourPickerCtrl#GetColour() {block?}
Gurax_DeclareMethodAlias(wxColourPickerCtrl, GetColour_gurax, "GetColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourPickerCtrl, GetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetColour()));
}

// wx.ColourPickerCtrl#SetColour(col as wx.Colour)
Gurax_DeclareMethodAlias(wxColourPickerCtrl, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxColourPickerCtrl, SetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_col = args_gurax.Pick<Value_wxColour>();
	const wxColour& col = value_col.GetEntity();
	// Function body
	pEntity_gurax->SetColour(col);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxColourPickerCtrl
//------------------------------------------------------------------------------
VType_wxColourPickerCtrl VTYPE_wxColourPickerCtrl("ColourPickerCtrl");

void VType_wxColourPickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable, Gurax_CreateConstructor(ColourPickerCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxColourPickerCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxColourPickerCtrl, GetColour_gurax));
	Assign(Gurax_CreateMethod(wxColourPickerCtrl, SetColour_gurax));
}

//------------------------------------------------------------------------------
// Value_wxColourPickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxColourPickerCtrl::vtype = VTYPE_wxColourPickerCtrl;

String Value_wxColourPickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ColourPickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxColourPickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
