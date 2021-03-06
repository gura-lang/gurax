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

# Property

# Operator

# Cast Operation

# Constructor

# Method
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
	wxWindowID id = args_gurax.IsValid()? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* value = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : wxSP_ARROW_KEYS;
	int min = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	int max = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 100;
	int initial = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(SpinCtrl_gurax));
	// Assignment of method
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
