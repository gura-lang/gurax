//==============================================================================
// VType_wxScrolledWindow.cpp
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
// wx.ScrolledWindow(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(ScrolledWindow_gurax, "ScrolledWindow")
{
	Declare(VTYPE_wxScrolledWindow, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ScrolledWindow.");
}

Gurax_ImplementConstructorEx(ScrolledWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : -1;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : (wxHSCROLL | wxVSCROLL);
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "scrolledWindow";
	// Function body
	auto pEntity_gurax = new Value_wxScrolledWindow::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxScrolledWindow> pValue_gurax(new Value_wxScrolledWindow(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ScrolledWindow#CalcScrolledPositionXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, CalcScrolledPositionXY_gurax, "CalcScrolledPositionXY")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, CalcScrolledPositionXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	int xx, yy;
	pEntity_gurax->CalcScrolledPosition(x, y, &xx, &yy);
	return Value_Tuple::Create(new Value_Number(xx), new Value_Number(yy));
}

// wx.ScrolledWindow#CalcScrolledPosition(pt as wx.Point) {block?}
Gurax_DeclareMethodAlias(wxScrolledWindow, CalcScrolledPosition_gurax, "CalcScrolledPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, CalcScrolledPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->CalcScrolledPosition(pt)));
}

// wx.ScrolledWindow#CalcUnscrolledPositionXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, CalcUnscrolledPositionXY_gurax, "CalcUnscrolledPositionXY")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, CalcUnscrolledPositionXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	int xx, yy;
	pEntity_gurax->CalcUnscrolledPosition(x, y, &xx, &yy);
	return Value_Tuple::Create(new Value_Number(xx), new Value_Number(yy));
}

// wx.ScrolledWindow#CalcUnscrolledPosition(pt as wx.Point) {block?}
Gurax_DeclareMethodAlias(wxScrolledWindow, CalcUnscrolledPosition_gurax, "CalcUnscrolledPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, CalcUnscrolledPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->CalcUnscrolledPosition(pt)));
}

// wx.ScrolledWindow#DisableKeyboardScrolling()
Gurax_DeclareMethodAlias(wxScrolledWindow, DisableKeyboardScrolling_gurax, "DisableKeyboardScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, DisableKeyboardScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DisableKeyboardScrolling();
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#DoPrepareDC(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledWindow, DoPrepareDC_gurax, "DoPrepareDC")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, DoPrepareDC_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	// Function body
	pEntity_gurax->DoPrepareDC(dc);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#EnableScrolling(xScrolling as Bool, yScrolling as Bool)
Gurax_DeclareMethodAlias(wxScrolledWindow, EnableScrolling_gurax, "EnableScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xScrolling", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yScrolling", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, EnableScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool xScrolling = args_gurax.PickBool();
	bool yScrolling = args_gurax.PickBool();
	// Function body
	pEntity_gurax->EnableScrolling(xScrolling, yScrolling);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#ShowScrollbars(horz as Number, vert as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, ShowScrollbars_gurax, "ShowScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("horz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vert", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, ShowScrollbars_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxScrollbarVisibility horz = args_gurax.PickNumber<wxScrollbarVisibility>();
	wxScrollbarVisibility vert = args_gurax.PickNumber<wxScrollbarVisibility>();
	// Function body
	pEntity_gurax->ShowScrollbars(horz, vert);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#GetScrollPixelsPerUnit()
Gurax_DeclareMethodAlias(wxScrolledWindow, GetScrollPixelsPerUnit_gurax, "GetScrollPixelsPerUnit")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetScrollPixelsPerUnit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int xUnit, yUnit;
	pEntity_gurax->GetScrollPixelsPerUnit(&xUnit, &yUnit);
	return Value_Tuple::Create(new Value_Number(xUnit), new Value_Number(yUnit));
}

// wx.ScrolledWindow#GetViewStartXY()
Gurax_DeclareMethodAlias(wxScrolledWindow, GetViewStartXY_gurax, "GetViewStartXY")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetViewStartXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int x, y;
	pEntity_gurax->GetViewStart(&x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// wx.ScrolledWindow#GetViewStart() {block?}
Gurax_DeclareMethodAlias(wxScrolledWindow, GetViewStart_gurax, "GetViewStart")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetViewStart_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetViewStart()));
}

// wx.ScrolledWindow#GetVirtualSize()
Gurax_DeclareMethodAlias(wxScrolledWindow, GetVirtualSize_gurax, "GetVirtualSize")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetVirtualSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int x, y;
	pEntity_gurax->GetVirtualSize(&x, &y);
	return Value_Tuple::Create(new Value_Number(x), new Value_Number(y));
}

// wx.ScrolledWindow#IsRetained()
Gurax_DeclareMethodAlias(wxScrolledWindow, IsRetained_gurax, "IsRetained")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, IsRetained_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsRetained();
	return new Gurax::Value_Bool(rtn);
}

// wx.ScrolledWindow#OnDraw(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledWindow, OnDraw_gurax, "OnDraw")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, OnDraw_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	// Function body
	pEntity_gurax->OnDraw(dc);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#PrepareDC(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledWindow, PrepareDC_gurax, "PrepareDC")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, PrepareDC_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	// Function body
	pEntity_gurax->PrepareDC(dc);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#ScrollXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, ScrollXY_gurax, "ScrollXY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, ScrollXY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->Scroll(x, y);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#Scroll(pt as wx.Point)
Gurax_DeclareMethodAlias(wxScrolledWindow, Scroll_gurax, "Scroll")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, Scroll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	// Function body
	pEntity_gurax->Scroll(pt);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#SetScrollRate(xstep as Number, ystep as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetScrollRate_gurax, "SetScrollRate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xstep", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ystep", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetScrollRate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int xstep = args_gurax.PickNumber<int>();
	int ystep = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetScrollRate(xstep, ystep);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#SetScrollbars(pixelsPerUnitX as Number, pixelsPerUnitY as Number, noUnitsX as Number, noUnitsY as Number, xPos? as Number, yPos? as Number, noRefresh? as Bool)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetScrollbars_gurax, "SetScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pixelsPerUnitX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixelsPerUnitY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("noUnitsX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("noUnitsY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("yPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("noRefresh", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetScrollbars_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pixelsPerUnitX = args_gurax.PickNumber<int>();
	int pixelsPerUnitY = args_gurax.PickNumber<int>();
	int noUnitsX = args_gurax.PickNumber<int>();
	int noUnitsY = args_gurax.PickNumber<int>();
	bool xPos_validFlag = args_gurax.IsValid();
	int xPos = xPos_validFlag? args_gurax.PickNumber<int>() : 0;
	bool yPos_validFlag = args_gurax.IsValid();
	int yPos = yPos_validFlag? args_gurax.PickNumber<int>() : 0;
	bool noRefresh = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	pEntity_gurax->SetScrollbars(pixelsPerUnitX, pixelsPerUnitY, noUnitsX, noUnitsY, xPos, yPos, noRefresh);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#SetTargetWindow(window as wx.Window)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetTargetWindow_gurax, "SetTargetWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetTargetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_window = args_gurax.Pick<Value_wxWindow>();
	wxWindow* window = value_window.GetEntityPtr();
	// Function body
	pEntity_gurax->SetTargetWindow(window);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#GetTargetWindow() {block?}
Gurax_DeclareMethodAlias(wxScrolledWindow, GetTargetWindow_gurax, "GetTargetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetTargetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetTargetWindow()));
}

// wx.ScrolledWindow#SetTargetRect(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetTargetRect_gurax, "SetTargetRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetTargetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	pEntity_gurax->SetTargetRect(rect);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#GetTargetRect() {block?}
Gurax_DeclareMethodAlias(wxScrolledWindow, GetTargetRect_gurax, "GetTargetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetTargetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetTargetRect()));
}

// wx.ScrolledWindow#GetScrollPageSize(orient as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, GetScrollPageSize_gurax, "GetScrollPageSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetScrollPageSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	int rtn = pEntity_gurax->GetScrollPageSize(orient);
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledWindow#SetScrollPageSize(orient as Number, pageSize as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetScrollPageSize_gurax, "SetScrollPageSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetScrollPageSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	int pageSize = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetScrollPageSize(orient, pageSize);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#GetScrollLines(orient as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, GetScrollLines_gurax, "GetScrollLines")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetScrollLines_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int orient = args_gurax.PickNumber<int>();
	// Function body
	int rtn = pEntity_gurax->GetScrollLines(orient);
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledWindow#SetScale(xs as Number, ys as Number)
Gurax_DeclareMethodAlias(wxScrolledWindow, SetScale_gurax, "SetScale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ys", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SetScale_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double xs = args_gurax.PickNumber<double>();
	double ys = args_gurax.PickNumber<double>();
	// Function body
	pEntity_gurax->SetScale(xs, ys);
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#GetScaleX()
Gurax_DeclareMethodAlias(wxScrolledWindow, GetScaleX_gurax, "GetScaleX")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetScaleX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetScaleX();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledWindow#GetScaleY()
Gurax_DeclareMethodAlias(wxScrolledWindow, GetScaleY_gurax, "GetScaleY")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, GetScaleY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetScaleY();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledWindow#AdjustScrollbars()
Gurax_DeclareMethodAlias(wxScrolledWindow, AdjustScrollbars_gurax, "AdjustScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, AdjustScrollbars_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->AdjustScrollbars();
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#IsAutoScrolling()
Gurax_DeclareMethodAlias(wxScrolledWindow, IsAutoScrolling_gurax, "IsAutoScrolling")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, IsAutoScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsAutoScrolling();
	return new Gurax::Value_Bool(rtn);
}

// wx.ScrolledWindow#StopAutoScrolling()
Gurax_DeclareMethodAlias(wxScrolledWindow, StopAutoScrolling_gurax, "StopAutoScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, StopAutoScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->StopAutoScrolling();
	return Gurax::Value::nil();
}

// wx.ScrolledWindow#SendAutoScrollEvents(event as wx.ScrollWinEvent)
Gurax_DeclareMethodAlias(wxScrolledWindow, SendAutoScrollEvents_gurax, "SendAutoScrollEvents")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("event", VTYPE_wxScrollWinEvent, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxScrolledWindow, SendAutoScrollEvents_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxScrollWinEvent& value_event = args_gurax.Pick<Value_wxScrollWinEvent>();
	wxScrollWinEvent& event = value_event.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SendAutoScrollEvents(event);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxScrolledWindow
//------------------------------------------------------------------------------
VType_wxScrolledWindow VTYPE_wxScrolledWindow("ScrolledWindow");

void VType_wxScrolledWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable, Gurax_CreateConstructor(ScrolledWindow_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxScrolledWindow, CalcScrolledPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, CalcScrolledPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, CalcUnscrolledPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, CalcUnscrolledPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, DisableKeyboardScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, DoPrepareDC_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, EnableScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, ShowScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetScrollPixelsPerUnit_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetViewStartXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetViewStart_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetVirtualSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, IsRetained_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, OnDraw_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, PrepareDC_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, ScrollXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, Scroll_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetScrollRate_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetTargetWindow_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetTargetWindow_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetTargetRect_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetTargetRect_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetScrollPageSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetScrollPageSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetScrollLines_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SetScale_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetScaleX_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, GetScaleY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, AdjustScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, IsAutoScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, StopAutoScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledWindow, SendAutoScrollEvents_gurax));
}

//------------------------------------------------------------------------------
// Value_wxScrolledWindow
//------------------------------------------------------------------------------
VType& Value_wxScrolledWindow::vtype = VTYPE_wxScrolledWindow;

String Value_wxScrolledWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ScrolledWindow");
}

//------------------------------------------------------------------------------
// Value_wxScrolledWindow::EntityT
//------------------------------------------------------------------------------
void Value_wxScrolledWindow::EntityT::OnDraw(wxDC& dc)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDraw");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxDC(dc))) break;
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
}

void Value_wxScrolledWindow::EntityT::AdjustScrollbars()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("AdjustScrollbars");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
}

Gurax_EndModuleScope(wx)
