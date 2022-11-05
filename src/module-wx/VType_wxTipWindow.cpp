//==============================================================================
// VType_wxTipWindow.cpp
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

${help.ComposePropertyHelp(wxTipWindow, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxTipWindow, `en)}

${help.ComposeMethodHelp(wxTipWindow, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.TipWindow#SetBoundingRect(rectBound as wx.Rect)
Gurax_DeclareMethodAlias(wxTipWindow, SetBoundingRect_gurax, "SetBoundingRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rectBound", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxTipWindow, SetBoundingRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rectBound = args_gurax.Pick<Value_wxRect>();
	const wxRect& rectBound = value_rectBound.GetEntity();
	// Function body
	pEntity_gurax->SetBoundingRect(rectBound);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxTipWindow
//------------------------------------------------------------------------------
VType_wxTipWindow VTYPE_wxTipWindow("TipWindow");

void VType_wxTipWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxTipWindow, SetBoundingRect_gurax));
}

//------------------------------------------------------------------------------
// Value_wxTipWindow
//------------------------------------------------------------------------------
VType& Value_wxTipWindow::vtype = VTYPE_wxTipWindow;

String Value_wxTipWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.TipWindow");
}

//------------------------------------------------------------------------------
// Value_wxTipWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
