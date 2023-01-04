﻿//==============================================================================
// VType_wxScrolledCanvas.cpp
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

${help.ComposePropertyHelp(wx.ScrolledCanvas, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ScrolledCanvas, `en)}

${help.ComposeMethodHelp(wx.ScrolledCanvas, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ScrolledCanvas, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ScrolledCanvas, `ja)}

${help.ComposeMethodHelp(wx.ScrolledCanvas, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ScrolledCanvas(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(ScrolledCanvas_gurax, "ScrolledCanvas")
{
	Declare(VTYPE_wxScrolledCanvas, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ScrolledCanvas_gurax, processor_gurax, argument_gurax)
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
	auto pEntity_gurax = new Value_wxScrolledCanvas::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxScrolledCanvas> pValue_gurax(new Value_wxScrolledCanvas(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ScrolledCanvas#CalcScrolledPositionXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, CalcScrolledPositionXY_gurax, "CalcScrolledPositionXY")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, CalcScrolledPositionXY_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#CalcScrolledPosition(pt as wx.Point) {block?}
Gurax_DeclareMethodAlias(wxScrolledCanvas, CalcScrolledPosition_gurax, "CalcScrolledPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, CalcScrolledPosition_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#CalcUnscrolledPositionXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, CalcUnscrolledPositionXY_gurax, "CalcUnscrolledPositionXY")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, CalcUnscrolledPositionXY_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#CalcUnscrolledPosition(pt as wx.Point) {block?}
Gurax_DeclareMethodAlias(wxScrolledCanvas, CalcUnscrolledPosition_gurax, "CalcUnscrolledPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, CalcUnscrolledPosition_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#DisableKeyboardScrolling()
Gurax_DeclareMethodAlias(wxScrolledCanvas, DisableKeyboardScrolling_gurax, "DisableKeyboardScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, DisableKeyboardScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DisableKeyboardScrolling();
	return Gurax::Value::nil();
}

// wx.ScrolledCanvas#DoPrepareDC(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledCanvas, DoPrepareDC_gurax, "DoPrepareDC")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, DoPrepareDC_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#EnableScrolling(xScrolling as Bool, yScrolling as Bool)
Gurax_DeclareMethodAlias(wxScrolledCanvas, EnableScrolling_gurax, "EnableScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xScrolling", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	DeclareArg("yScrolling", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, EnableScrolling_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#ShowScrollbars(horz as Number, vert as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, ShowScrollbars_gurax, "ShowScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("horz", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("vert", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, ShowScrollbars_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetScrollPixelsPerUnit()
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetScrollPixelsPerUnit_gurax, "GetScrollPixelsPerUnit")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetScrollPixelsPerUnit_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetViewStartXY()
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetViewStartXY_gurax, "GetViewStartXY")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetViewStartXY_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetViewStart() {block?}
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetViewStart_gurax, "GetViewStart")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetViewStart_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetViewStart()));
}

// wx.ScrolledCanvas#GetVirtualSize()
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetVirtualSize_gurax, "GetVirtualSize")
{
	Declare(VTYPE_Any, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetVirtualSize_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#IsRetained()
Gurax_DeclareMethodAlias(wxScrolledCanvas, IsRetained_gurax, "IsRetained")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, IsRetained_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsRetained();
	return new Gurax::Value_Bool(rtn);
}

// wx.ScrolledCanvas#OnDraw(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledCanvas, OnDraw_gurax, "OnDraw")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, OnDraw_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxScrolledCanvas::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	// Function body
	pEntity_gurax->OnDraw(dc);
	return Gurax::Value::nil();
}

// wx.ScrolledCanvas#PrepareDC(dc as wx.DC)
Gurax_DeclareMethodAlias(wxScrolledCanvas, PrepareDC_gurax, "PrepareDC")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, PrepareDC_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#ScrollXY(x as Number, y as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, ScrollXY_gurax, "ScrollXY")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, ScrollXY_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#Scroll(pt as wx.Point)
Gurax_DeclareMethodAlias(wxScrolledCanvas, Scroll_gurax, "Scroll")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, Scroll_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#SetScrollRate(xstep as Number, ystep as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetScrollRate_gurax, "SetScrollRate")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xstep", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ystep", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetScrollRate_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#SetScrollbars(pixelsPerUnitX as Number, pixelsPerUnitY as Number, noUnitsX as Number, noUnitsY as Number, xPos? as Number, yPos? as Number, noRefresh? as Bool)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetScrollbars_gurax, "SetScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pixelsPerUnitX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pixelsPerUnitY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("noUnitsX", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("noUnitsY", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("xPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("yPos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("noRefresh", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetScrollbars_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#SetTargetWindow(window as wx.Window)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetTargetWindow_gurax, "SetTargetWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("window", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetTargetWindow_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetTargetWindow() {block?}
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetTargetWindow_gurax, "GetTargetWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetTargetWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetTargetWindow()));
}

// wx.ScrolledCanvas#SetTargetRect(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetTargetRect_gurax, "SetTargetRect")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetTargetRect_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetTargetRect() {block?}
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetTargetRect_gurax, "GetTargetRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetTargetRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(
		pEntity_gurax->GetTargetRect()));
}

// wx.ScrolledCanvas#GetScrollPageSize(orient as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetScrollPageSize_gurax, "GetScrollPageSize")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetScrollPageSize_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#SetScrollPageSize(orient as Number, pageSize as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetScrollPageSize_gurax, "SetScrollPageSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pageSize", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetScrollPageSize_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetScrollLines(orient as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetScrollLines_gurax, "GetScrollLines")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("orient", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetScrollLines_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#SetScale(xs as Number, ys as Number)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SetScale_gurax, "SetScale")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("xs", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("ys", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SetScale_gurax, processor_gurax, argument_gurax)
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

// wx.ScrolledCanvas#GetScaleX()
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetScaleX_gurax, "GetScaleX")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetScaleX_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetScaleX();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledCanvas#GetScaleY()
Gurax_DeclareMethodAlias(wxScrolledCanvas, GetScaleY_gurax, "GetScaleY")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, GetScaleY_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetScaleY();
	return new Gurax::Value_Number(rtn);
}

// wx.ScrolledCanvas#AdjustScrollbars()
Gurax_DeclareMethodAlias(wxScrolledCanvas, AdjustScrollbars_gurax, "AdjustScrollbars")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, AdjustScrollbars_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxScrolledCanvas::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->AdjustScrollbars();
	return Gurax::Value::nil();
}

// wx.ScrolledCanvas#IsAutoScrolling()
Gurax_DeclareMethodAlias(wxScrolledCanvas, IsAutoScrolling_gurax, "IsAutoScrolling")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, IsAutoScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsAutoScrolling();
	return new Gurax::Value_Bool(rtn);
}

// wx.ScrolledCanvas#StopAutoScrolling()
Gurax_DeclareMethodAlias(wxScrolledCanvas, StopAutoScrolling_gurax, "StopAutoScrolling")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, StopAutoScrolling_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->StopAutoScrolling();
	return Gurax::Value::nil();
}

// wx.ScrolledCanvas#SendAutoScrollEvents(event as wx.ScrollWinEvent)
Gurax_DeclareMethodAlias(wxScrolledCanvas, SendAutoScrollEvents_gurax, "SendAutoScrollEvents")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("event", VTYPE_wxScrollWinEvent, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxScrolledCanvas, SendAutoScrollEvents_gurax, processor_gurax, argument_gurax)
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
// VType_wxScrolledCanvas
//------------------------------------------------------------------------------
VType_wxScrolledCanvas VTYPE_wxScrolledCanvas("ScrolledCanvas");

void VType_wxScrolledCanvas::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(ScrolledCanvas_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxScrolledCanvas, CalcScrolledPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, CalcScrolledPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, CalcUnscrolledPositionXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, CalcUnscrolledPosition_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, DisableKeyboardScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, DoPrepareDC_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, EnableScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, ShowScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetScrollPixelsPerUnit_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetViewStartXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetViewStart_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetVirtualSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, IsRetained_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, OnDraw_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, PrepareDC_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, ScrollXY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, Scroll_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetScrollRate_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetTargetWindow_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetTargetWindow_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetTargetRect_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetTargetRect_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetScrollPageSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetScrollPageSize_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetScrollLines_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SetScale_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetScaleX_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, GetScaleY_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, AdjustScrollbars_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, IsAutoScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, StopAutoScrolling_gurax));
	Assign(Gurax_CreateMethod(wxScrolledCanvas, SendAutoScrollEvents_gurax));
}

//------------------------------------------------------------------------------
// Value_wxScrolledCanvas
//------------------------------------------------------------------------------
VType& Value_wxScrolledCanvas::vtype = VTYPE_wxScrolledCanvas;

String Value_wxScrolledCanvas::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ScrolledCanvas");
}

//------------------------------------------------------------------------------
// Value_wxScrolledCanvas::EntityT
//------------------------------------------------------------------------------
void Value_wxScrolledCanvas::EntityT::OnDraw(wxDC& dc)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDraw");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxDC(dc))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_OnDraw(dc);
}

void Value_wxScrolledCanvas::EntityT::AdjustScrollbars()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("AdjustScrollbars");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
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
	public_AdjustScrollbars();
}

Gurax_EndModuleScope(wx)
