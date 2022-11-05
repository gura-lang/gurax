//==============================================================================
// VType_wxHtmlCellEvent.cpp
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

${help.ComposePropertyHelp(wxHtmlCellEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxHtmlCellEvent, `en)}

${help.ComposeMethodHelp(wxHtmlCellEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HtmlCellEvent#GetCell() {block?}
Gurax_DeclareMethodAlias(wxHtmlCellEvent, GetCell_gurax, "GetCell")
{
	Declare(VTYPE_wxHtmlCell, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHtmlCellEvent, GetCell_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxHtmlCell(
		*pEntity_gurax->GetCell()));
}

// wx.HtmlCellEvent#GetLinkClicked()
Gurax_DeclareMethodAlias(wxHtmlCellEvent, GetLinkClicked_gurax, "GetLinkClicked")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHtmlCellEvent, GetLinkClicked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->GetLinkClicked();
	return new Gurax::Value_Bool(rtn);
}

// wx.HtmlCellEvent#GetPoint() {block?}
Gurax_DeclareMethodAlias(wxHtmlCellEvent, GetPoint_gurax, "GetPoint")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHtmlCellEvent, GetPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPoint()));
}

// wx.HtmlCellEvent#SetLinkClicked(linkclicked as Bool)
Gurax_DeclareMethodAlias(wxHtmlCellEvent, SetLinkClicked_gurax, "SetLinkClicked")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("linkclicked", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHtmlCellEvent, SetLinkClicked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool linkclicked = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetLinkClicked(linkclicked);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHtmlCellEvent
//------------------------------------------------------------------------------
VType_wxHtmlCellEvent VTYPE_wxHtmlCellEvent("HtmlCellEvent");

void VType_wxHtmlCellEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxCommandEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHtmlCellEvent, GetCell_gurax));
	Assign(Gurax_CreateMethod(wxHtmlCellEvent, GetLinkClicked_gurax));
	Assign(Gurax_CreateMethod(wxHtmlCellEvent, GetPoint_gurax));
	Assign(Gurax_CreateMethod(wxHtmlCellEvent, SetLinkClicked_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHtmlCellEvent
//------------------------------------------------------------------------------
VType& Value_wxHtmlCellEvent::vtype = VTYPE_wxHtmlCellEvent;
EventValueFactoryDeriv<Value_wxHtmlCellEvent> Value_wxHtmlCellEvent::eventValueFactory;

String Value_wxHtmlCellEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HtmlCellEvent");
}

Gurax_EndModuleScope(wx)
