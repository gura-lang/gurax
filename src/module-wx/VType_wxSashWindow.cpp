//==============================================================================
// VType_wxSashWindow.cpp
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
// wx.SashWindow(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(SashWindow_gurax, "SashWindow")
{
	Declare(VTYPE_wxSashWindow, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.SashWindow.");
}

Gurax_ImplementConstructorEx(SashWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : (wxCLIP_CHILDREN | wxSW_3D);
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "sashWindow";
	// Function body
	auto pEntity_gurax = new Value_wxSashWindow::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxSashWindow> pValue_gurax(new Value_wxSashWindow(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SashWindow#GetMaximumSizeX()
Gurax_DeclareMethodAlias(wxSashWindow, GetMaximumSizeX_gurax, "GetMaximumSizeX")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetMaximumSizeX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMaximumSizeX();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#GetMaximumSizeY()
Gurax_DeclareMethodAlias(wxSashWindow, GetMaximumSizeY_gurax, "GetMaximumSizeY")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetMaximumSizeY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMaximumSizeY();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#GetMinimumSizeX()
Gurax_DeclareMethodAlias(wxSashWindow, GetMinimumSizeX_gurax, "GetMinimumSizeX")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetMinimumSizeX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMinimumSizeX();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#GetMinimumSizeY()
Gurax_DeclareMethodAlias(wxSashWindow, GetMinimumSizeY_gurax, "GetMinimumSizeY")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetMinimumSizeY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMinimumSizeY();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#GetSashVisible(edge as Number)
Gurax_DeclareMethodAlias(wxSashWindow, GetSashVisible_gurax, "GetSashVisible")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("edge", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetSashVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxSashEdgePosition edge = args_gurax.PickNumber<wxSashEdgePosition>();
	// Function body
	bool rtn = pEntity_gurax->GetSashVisible(edge);
	return new Gurax::Value_Bool(rtn);
}

// wx.SashWindow#SetMaximumSizeX(min as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetMaximumSizeX_gurax, "SetMaximumSizeX")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetMaximumSizeX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMaximumSizeX(min);
	return Gurax::Value::nil();
}

// wx.SashWindow#SetMaximumSizeY(min as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetMaximumSizeY_gurax, "SetMaximumSizeY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetMaximumSizeY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMaximumSizeY(min);
	return Gurax::Value::nil();
}

// wx.SashWindow#SetMinimumSizeX(min as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetMinimumSizeX_gurax, "SetMinimumSizeX")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetMinimumSizeX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinimumSizeX(min);
	return Gurax::Value::nil();
}

// wx.SashWindow#SetMinimumSizeY(min as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetMinimumSizeY_gurax, "SetMinimumSizeY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("min", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetMinimumSizeY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int min = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetMinimumSizeY(min);
	return Gurax::Value::nil();
}

// wx.SashWindow#SetSashVisible(edge as Number, visible as Bool)
Gurax_DeclareMethodAlias(wxSashWindow, SetSashVisible_gurax, "SetSashVisible")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("edge", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("visible", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetSashVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxSashEdgePosition edge = args_gurax.PickNumber<wxSashEdgePosition>();
	bool visible = args_gurax.PickBool();
	// Function body
	pEntity_gurax->SetSashVisible(edge, visible);
	return Gurax::Value::nil();
}

// wx.SashWindow#GetEdgeMargin(edge as Number)
Gurax_DeclareMethodAlias(wxSashWindow, GetEdgeMargin_gurax, "GetEdgeMargin")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("edge", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetEdgeMargin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxSashEdgePosition edge = args_gurax.PickNumber<wxSashEdgePosition>();
	// Function body
	int rtn = pEntity_gurax->GetEdgeMargin(edge);
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#SetDefaultBorderSize(width as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetDefaultBorderSize_gurax, "SetDefaultBorderSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetDefaultBorderSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetDefaultBorderSize(width);
	return Gurax::Value::nil();
}

// wx.SashWindow#GetDefaultBorderSize()
Gurax_DeclareMethodAlias(wxSashWindow, GetDefaultBorderSize_gurax, "GetDefaultBorderSize")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetDefaultBorderSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDefaultBorderSize();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#SetExtraBorderSize(width as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SetExtraBorderSize_gurax, "SetExtraBorderSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SetExtraBorderSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int width = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetExtraBorderSize(width);
	return Gurax::Value::nil();
}

// wx.SashWindow#GetExtraBorderSize()
Gurax_DeclareMethodAlias(wxSashWindow, GetExtraBorderSize_gurax, "GetExtraBorderSize")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, GetExtraBorderSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetExtraBorderSize();
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#SashHitTest(x as Number, y as Number, tolerance? as Number)
Gurax_DeclareMethodAlias(wxSashWindow, SashHitTest_gurax, "SashHitTest")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("tolerance", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SashHitTest_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	bool tolerance_validFlag = args_gurax.IsValid();
	int tolerance = tolerance_validFlag? args_gurax.PickNumber<int>() : 2;
	// Function body
	wxSashEdgePosition rtn = pEntity_gurax->SashHitTest(x, y, tolerance);
	return new Gurax::Value_Number(rtn);
}

// wx.SashWindow#SizeWindows()
Gurax_DeclareMethodAlias(wxSashWindow, SizeWindows_gurax, "SizeWindows")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSashWindow, SizeWindows_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->SizeWindows();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSashWindow
//------------------------------------------------------------------------------
VType_wxSashWindow VTYPE_wxSashWindow("SashWindow");

void VType_wxSashWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(SashWindow_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSashWindow, GetMaximumSizeX_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetMaximumSizeY_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetMinimumSizeX_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetMinimumSizeY_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetSashVisible_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetMaximumSizeX_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetMaximumSizeY_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetMinimumSizeX_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetMinimumSizeY_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetSashVisible_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetEdgeMargin_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetDefaultBorderSize_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetDefaultBorderSize_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SetExtraBorderSize_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, GetExtraBorderSize_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SashHitTest_gurax));
	Assign(Gurax_CreateMethod(wxSashWindow, SizeWindows_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSashWindow
//------------------------------------------------------------------------------
VType& Value_wxSashWindow::vtype = VTYPE_wxSashWindow;

String Value_wxSashWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SashWindow");
}

//------------------------------------------------------------------------------
// Value_wxSashWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
