//==============================================================================
// VType_wxStyledTextCtrl.cpp
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
// wx.StyledTextCtrl(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(StyledTextCtrl_gurax, "StyledTextCtrl")
{
	Declare(VTYPE_wxStyledTextCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.StyledTextCtrl.");
}

Gurax_ImplementConstructorEx(StyledTextCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.IsValid()? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxSTCNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxStyledTextCtrl::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxStyledTextCtrl> pValue_gurax(new Value_wxStyledTextCtrl(pEntity_gurax));
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
// VType_wxStyledTextCtrl
//------------------------------------------------------------------------------
VType_wxStyledTextCtrl VTYPE_wxStyledTextCtrl("StyledTextCtrl");

void VType_wxStyledTextCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StyledTextCtrl_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxStyledTextCtrl
//------------------------------------------------------------------------------
VType& Value_wxStyledTextCtrl::vtype = VTYPE_wxStyledTextCtrl;

String Value_wxStyledTextCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StyledTextCtrl");
}

//------------------------------------------------------------------------------
// Value_wxStyledTextCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)