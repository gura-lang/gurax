﻿//==============================================================================
// VType_wxVListBox.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.VListBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.VListBox, `en)}

${help.ComposeMethodHelp(wx.VListBox, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.VListBox, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.VListBox, `ja)}

${help.ComposeMethodHelp(wx.VListBox, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.VListBox(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(VListBox_gurax, "VListBox")
{
	Declare(VTYPE_wxVListBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(VListBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxVListBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxVListBox::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxVListBox> pValue_gurax(new Value_wxVListBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.VListBox#Clear()
Gurax_DeclareMethodAlias(wxVListBox, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.VListBox#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxVListBox, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, Create_gurax, processor_gurax, argument_gurax)
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
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxVListBoxNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#DeselectAll()
Gurax_DeclareMethodAlias(wxVListBox, DeselectAll_gurax, "DeselectAll")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, DeselectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DeselectAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#GetFirstSelected(&cookie:nilRef as Number)
Gurax_DeclareMethodAlias(wxVListBox, GetFirstSelected_gurax, "GetFirstSelected")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cookie", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxVListBox, GetFirstSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> cookie(args_gurax.PickReferencer().Reference());
	// Function body
	unsigned long cookie_ = cookie->Get<Value_Number>().GetNumber<unsigned long>();
	int rtn = pEntity_gurax->GetFirstSelected(cookie_);
	cookie->SetValue(processor_gurax, new Value_Number(cookie_));
	return new Value_Number(rtn);
}

// wx.VListBox#GetItemCount()
Gurax_DeclareMethodAlias(wxVListBox, GetItemCount_gurax, "GetItemCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, GetItemCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetItemCount();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetMargins() {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetMargins_gurax, "GetMargins")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxVListBox, GetMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(pEntity_gurax->GetMargins()));
}

// wx.VListBox#GetItemRect(item as Number) {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetItemRect_gurax, "GetItemRect")
{
	Declare(VTYPE_wxRect, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxVListBox, GetItemRect_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRect(pEntity_gurax->GetItemRect(item)));
}

// wx.VListBox#GetNextSelected(&cookie:nilRef as Number)
Gurax_DeclareMethodAlias(wxVListBox, GetNextSelected_gurax, "GetNextSelected")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("cookie", VTYPE_Number, ArgOccur::Once, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxVListBox, GetNextSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	RefPtr<Referencer> cookie(args_gurax.PickReferencer().Reference());
	// Function body
	unsigned long cookie_ = cookie->Get<Value_Number>().GetNumber<unsigned long>();
	int rtn = pEntity_gurax->GetNextSelected(cookie_);
	cookie->SetValue(processor_gurax, new Value_Number(cookie_));
	return new Value_Number(rtn);
}

// wx.VListBox#GetSelectedCount()
Gurax_DeclareMethodAlias(wxVListBox, GetSelectedCount_gurax, "GetSelectedCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, GetSelectedCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetSelectedCount();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetSelection()
Gurax_DeclareMethodAlias(wxVListBox, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.VListBox#GetSelectionBackground() {block?}
Gurax_DeclareMethodAlias(wxVListBox, GetSelectionBackground_gurax, "GetSelectionBackground")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxVListBox, GetSelectionBackground_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(pEntity_gurax->GetSelectionBackground()));
}

// wx.VListBox#HasMultipleSelection()
Gurax_DeclareMethodAlias(wxVListBox, HasMultipleSelection_gurax, "HasMultipleSelection")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, HasMultipleSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasMultipleSelection();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#IsCurrent(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, IsCurrent_gurax, "IsCurrent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, IsCurrent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsCurrent(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#IsSelected(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, IsSelected_gurax, "IsSelected")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, IsSelected_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsSelected(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#Select(item as Number, select? as Bool)
Gurax_DeclareMethodAlias(wxVListBox, Select_gurax, "Select")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("select", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, Select_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	bool select = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->Select(item, select);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SelectAll()
Gurax_DeclareMethodAlias(wxVListBox, SelectAll_gurax, "SelectAll")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SelectAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->SelectAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SelectRange(from as Number, to as Number)
Gurax_DeclareMethodAlias(wxVListBox, SelectRange_gurax, "SelectRange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("from", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("to", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SelectRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t from = args_gurax.PickNumber<size_t>();
	size_t to = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->SelectRange(from, to);
	return new Gurax::Value_Bool(rtn);
}

// wx.VListBox#SetItemCount(count as Number)
Gurax_DeclareMethodAlias(wxVListBox, SetItemCount_gurax, "SetItemCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SetItemCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t count = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetItemCount(count);
	return Gurax::Value::nil();
}

// wx.VListBox#SetSelection(selection as Number)
Gurax_DeclareMethodAlias(wxVListBox, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("selection", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int selection = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(selection);
	return Gurax::Value::nil();
}

// wx.VListBox#SetSelectionBackground(col as wx.Colour)
Gurax_DeclareMethodAlias(wxVListBox, SetSelectionBackground_gurax, "SetSelectionBackground")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SetSelectionBackground_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_col = args_gurax.Pick<Value_wxColour>();
	const wxColour& col = value_col.GetEntity();
	// Function body
	pEntity_gurax->SetSelectionBackground(col);
	return Gurax::Value::nil();
}

// wx.VListBox#Toggle(item as Number)
Gurax_DeclareMethodAlias(wxVListBox, Toggle_gurax, "Toggle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, Toggle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t item = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->Toggle(item);
	return Gurax::Value::nil();
}

// wx.VListBox#SetMargins(args* as Any)
Gurax_DeclareMethodAlias(wxVListBox, SetMargins_gurax, "SetMargins")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, SetMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	//SetMargins(pt as const_Point_r) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxPoint& pt = args.Pick<Value_wxPoint>().GetEntity();
		pEntity_gurax->SetMargins(pt);
		return Value::nil();
	} while (0);
	Error::ClearIssuedFlag();
	//SetMargins(x as Coord, y as Coord) as void
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number);
			pDeclCallable->DeclareArg("y", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxCoord x = args.PickNumber<wxCoord>();
		wxCoord y = args.PickNumber<wxCoord>();
		pEntity_gurax->SetMargins(x, y);
		return Value::nil();
	} while (0);
	return Value::nil();
}

// wx.VListBox#OnDrawItem(dc as wx.DC, rect as wx.Rect, n as Number)
Gurax_DeclareMethodAlias(wxVListBox, OnDrawItem_gurax, "OnDrawItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, OnDrawItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxVListBox::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->OnDrawItem(dc, rect, n);
	return Gurax::Value::nil();
}

// wx.VListBox#OnDrawBackground(dc as wx.DC, rect as wx.Rect, n as Number)
Gurax_DeclareMethodAlias(wxVListBox, OnDrawBackground_gurax, "OnDrawBackground")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, OnDrawBackground_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxVListBox::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->OnDrawBackground(dc, rect, n);
	return Gurax::Value::nil();
}

// wx.VListBox#OnDrawSeparator(dc as wx.DC, rect as wx.Rect, n as Number)
Gurax_DeclareMethodAlias(wxVListBox, OnDrawSeparator_gurax, "OnDrawSeparator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, OnDrawSeparator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxVListBox::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	wxRect& rect = value_rect.GetEntity();
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->OnDrawSeparator(dc, rect, n);
	return Gurax::Value::nil();
}

// wx.VListBox#OnMeasureItem(n as Number)
Gurax_DeclareMethodAlias(wxVListBox, OnMeasureItem_gurax, "OnMeasureItem")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxVListBox, OnMeasureItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxVListBox::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	wxCoord rtn = pEntity_gurax->OnMeasureItem(n);
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxVListBox
//------------------------------------------------------------------------------
VType_wxVListBox VTYPE_wxVListBox("VListBox");

void VType_wxVListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxVScrolledWindow, Flag::Mutable, Gurax_CreateConstructor(VListBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxVListBox, Clear_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, Create_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, DeselectAll_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetFirstSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetItemCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetMargins_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetItemRect_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetNextSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelectedCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, GetSelectionBackground_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, HasMultipleSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, IsCurrent_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, IsSelected_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, Select_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SelectAll_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SelectRange_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetItemCount_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetSelectionBackground_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, Toggle_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, SetMargins_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, OnDrawItem_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, OnDrawBackground_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, OnDrawSeparator_gurax));
	Assign(Gurax_CreateMethod(wxVListBox, OnMeasureItem_gurax));
}

//------------------------------------------------------------------------------
// Value_wxVListBox
//------------------------------------------------------------------------------
VType& Value_wxVListBox::vtype = VTYPE_wxVListBox;

String Value_wxVListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.VListBox");
}

//------------------------------------------------------------------------------
// Value_wxVListBox::EntityT
//------------------------------------------------------------------------------
void Value_wxVListBox::EntityT::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDrawItem");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxDC(dc))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxRect(rect))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(n))) {
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
	public_OnDrawItem(dc, rect, n);
}

void Value_wxVListBox::EntityT::OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDrawBackground");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxDC(dc))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxRect(rect))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(n))) {
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
	public_OnDrawBackground(dc, rect, n);
}

void Value_wxVListBox::EntityT::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDrawSeparator");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxDC(dc))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Value_wxRect(rect))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(n))) {
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
	public_OnDrawSeparator(dc, rect, n);
}

wxCoord Value_wxVListBox::EntityT::OnMeasureItem(size_t n) const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnMeasureItem");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(n))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsInstanceOf(VTYPE_Number)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function OnMeasureItem is expected to return a value of %s or its derived class",
				VTYPE_Number.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Number::GetNumber<wxCoord>(*pValueRtn);
	} while (0);
	return public_OnMeasureItem(n);
}

Gurax_EndModuleScope(wx)
