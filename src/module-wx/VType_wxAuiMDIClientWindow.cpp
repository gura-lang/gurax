//==============================================================================
// VType_wxAuiMDIClientWindow.cpp
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

${help.ComposePropertyHelp(wxAuiMDIClientWindow)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxAuiMDIClientWindow)}

${help.ComposeMethodHelp(wxAuiMDIClientWindow)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AuiMDIClientWindow(parent as wx.AuiMDIParentFrame, style? as Number) {block?}
Gurax_DeclareConstructorAlias(AuiMDIClientWindow_gurax, "AuiMDIClientWindow")
{
	Declare(VTYPE_wxAuiMDIClientWindow, Flag::None);
	DeclareArg("parent", VTYPE_wxAuiMDIParentFrame, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AuiMDIClientWindow.");
}

Gurax_ImplementConstructorEx(AuiMDIClientWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAuiMDIParentFrame& value_parent = args_gurax.Pick<Value_wxAuiMDIParentFrame>();
	wxAuiMDIParentFrame* parent = value_parent.GetEntityPtr();
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxAuiMDIClientWindow::EntityT(parent, style);
	RefPtr<Value_wxAuiMDIClientWindow> pValue_gurax(new Value_wxAuiMDIClientWindow(pEntity_gurax));
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
// VType_wxAuiMDIClientWindow
//------------------------------------------------------------------------------
VType_wxAuiMDIClientWindow VTYPE_wxAuiMDIClientWindow("AuiMDIClientWindow");

void VType_wxAuiMDIClientWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAuiNotebook, Flag::Mutable, Gurax_CreateConstructor(AuiMDIClientWindow_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxAuiMDIClientWindow
//------------------------------------------------------------------------------
VType& Value_wxAuiMDIClientWindow::vtype = VTYPE_wxAuiMDIClientWindow;

String Value_wxAuiMDIClientWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AuiMDIClientWindow");
}

//------------------------------------------------------------------------------
// Value_wxAuiMDIClientWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
