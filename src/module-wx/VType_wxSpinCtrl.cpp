//==============================================================================
// VType_wxSpinCtrl.cpp
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

${help.ComposePropertyHelp(wx.SpinCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.SpinCtrl, `en)}

${help.ComposeMethodHelp(wx.SpinCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.SpinCtrl(parent as wx.Window, id? as Number, value? as String, pos? as wx.Point, size? as wx.Size, style? as Number, min? as Number, max? as Number, initial? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(SpinCtrl_gurax, "SpinCtrl")
{
	Declare(VTYPE_wxSpinCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initial", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.SpinCtrl.");
}

Gurax_ImplementConstructorEx(SpinCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* value = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSP_ARROW_KEYS;
	bool min_validFlag = args_gurax.IsValid();
	int min = min_validFlag? args_gurax.PickNumber<int>() : 0;
	bool max_validFlag = args_gurax.IsValid();
	int max = max_validFlag? args_gurax.PickNumber<int>() : 100;
	bool initial_validFlag = args_gurax.IsValid();
	int initial = initial_validFlag? args_gurax.PickNumber<int>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "wxSpinCtrl";
	// Function body
	auto pEntity_gurax = new Value_wxSpinCtrl::EntityT(parent, id, value, pos, size, style, min, max, initial, name);
	RefPtr<Value_wxSpinCtrl> pValue_gurax(new Value_wxSpinCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SpinCtrl#Create(parent as wx.Window, id? as Number, value? as String, pos? as wx.Point, size? as wx.Size, style? as Number, min? as Number, max? as Number, initial? as Number, name? as String)
Gurax_DeclareMethodAlias(wxSpinCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("max", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("initial", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* value = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSP_ARROW_KEYS;
	bool min_validFlag = args_gurax.IsValid();
	int min = min_validFlag? args_gurax.PickNumber<int>() : 0;
	bool max_validFlag = args_gurax.IsValid();
	int max = max_validFlag? args_gurax.PickNumber<int>() : 100;
	bool initial_validFlag = args_gurax.IsValid();
	int initial = initial_validFlag? args_gurax.PickNumber<int>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "wxSpinCtrl";
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, value, pos, size, style, min, max, initial, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.SpinCtrl#GetBase()
Gurax_DeclareMethodAlias(wxSpinCtrl, GetBase_gurax, "GetBase")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, GetBase_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetBase();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinCtrl#GetMax()
Gurax_DeclareMethodAlias(wxSpinCtrl, GetMax_gurax, "GetMax")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, GetMax_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMax();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinCtrl#GetMin()
Gurax_DeclareMethodAlias(wxSpinCtrl, GetMin_gurax, "GetMin")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, GetMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMin();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinCtrl#GetValue()
Gurax_DeclareMethodAlias(wxSpinCtrl, GetValue_gurax, "GetValue")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, GetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetValue();
	return new Gurax::Value_Number(rtn);
}

// wx.SpinCtrl#SetBase(base as Number)
Gurax_DeclareMethodAlias(wxSpinCtrl, SetBase_gurax, "SetBase")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("base", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, SetBase_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int base = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->SetBase(base);
	return new Gurax::Value_Bool(rtn);
}

// wx.SpinCtrl#SetRange(minVal as Number, maxVal as Number)
Gurax_DeclareMethodAlias(wxSpinCtrl, SetRange_gurax, "SetRange")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("minVal", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxVal", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, SetRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minVal = args_gurax.PickNumber<int>();
	int maxVal = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRange(minVal, maxVal);
	return Gurax::Value::nil();
}

// wx.SpinCtrl#SetSelection(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxSpinCtrl, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long from = args_gurax.PickNumber<long>();
	long to = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetSelection(from, to);
	return Gurax::Value::nil();
}

// wx.SpinCtrl#SetValue(text as String)
Gurax_DeclareMethodAlias(wxSpinCtrl, SetValue_gurax, "SetValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSpinCtrl, SetValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetValue(text);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSpinCtrl
//------------------------------------------------------------------------------
VType_wxSpinCtrl VTYPE_wxSpinCtrl("SpinCtrl");

void VType_wxSpinCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(SpinCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSpinCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, GetBase_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, GetMax_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, GetMin_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, GetValue_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, SetBase_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, SetRange_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxSpinCtrl, SetValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSpinCtrl
//------------------------------------------------------------------------------
VType& Value_wxSpinCtrl::vtype = VTYPE_wxSpinCtrl;

String Value_wxSpinCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SpinCtrl");
}

//------------------------------------------------------------------------------
// Value_wxSpinCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
