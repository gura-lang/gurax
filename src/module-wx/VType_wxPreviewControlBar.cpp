//==============================================================================
// VType_wxPreviewControlBar.cpp
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
// wx.PreviewControlBar(preview as wx.PrintPreview, buttons as Number, parent as wx.Window, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(PreviewControlBar_gurax, "PreviewControlBar")
{
	Declare(VTYPE_wxPreviewControlBar, Flag::None);
	DeclareArg("preview", VTYPE_wxPrintPreview, ArgOccur::Once, ArgFlag::None);
	DeclareArg("buttons", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.PreviewControlBar.");
}

Gurax_ImplementConstructorEx(PreviewControlBar_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPrintPreview& value_preview = args_gurax.Pick<Value_wxPrintPreview>();
	wxPrintPreview* preview = value_preview.GetEntityPtr();
	long buttons = args_gurax.PickNumber<long>();
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "panel";
	// Function body
	auto pEntity_gurax = new Value_wxPreviewControlBar::EntityT(preview, buttons, parent, pos, size, style, name);
	RefPtr<Value_wxPreviewControlBar> pValue_gurax(new Value_wxPreviewControlBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.PreviewControlBar#CreateButtons()
Gurax_DeclareMethodAlias(wxPreviewControlBar, CreateButtons_gurax, "CreateButtons")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPreviewControlBar, CreateButtons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->CreateButtons();
	return Gurax::Value::nil();
}

// wx.PreviewControlBar#GetZoomControl()
Gurax_DeclareMethodAlias(wxPreviewControlBar, GetZoomControl_gurax, "GetZoomControl")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPreviewControlBar, GetZoomControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetZoomControl();
	return new Gurax::Value_Number(rtn);
}

// wx.PreviewControlBar#SetZoomControl(percent as Number)
Gurax_DeclareMethodAlias(wxPreviewControlBar, SetZoomControl_gurax, "SetZoomControl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("percent", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPreviewControlBar, SetZoomControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int percent = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetZoomControl(percent);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPreviewControlBar
//------------------------------------------------------------------------------
VType_wxPreviewControlBar VTYPE_wxPreviewControlBar("PreviewControlBar");

void VType_wxPreviewControlBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable, Gurax_CreateConstructor(PreviewControlBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPreviewControlBar, CreateButtons_gurax));
	Assign(Gurax_CreateMethod(wxPreviewControlBar, GetZoomControl_gurax));
	Assign(Gurax_CreateMethod(wxPreviewControlBar, SetZoomControl_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPreviewControlBar
//------------------------------------------------------------------------------
VType& Value_wxPreviewControlBar::vtype = VTYPE_wxPreviewControlBar;

String Value_wxPreviewControlBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PreviewControlBar");
}

//------------------------------------------------------------------------------
// Value_wxPreviewControlBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
