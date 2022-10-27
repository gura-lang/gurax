//==============================================================================
// VType_wxListEvent.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ListEvent#GetCacheFrom()
Gurax_DeclareMethodAlias(wxListEvent, GetCacheFrom_gurax, "GetCacheFrom")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetCacheFrom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetCacheFrom();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetCacheTo()
Gurax_DeclareMethodAlias(wxListEvent, GetCacheTo_gurax, "GetCacheTo")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetCacheTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetCacheTo();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetColumn()
Gurax_DeclareMethodAlias(wxListEvent, GetColumn_gurax, "GetColumn")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetColumn();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetImage()
Gurax_DeclareMethodAlias(wxListEvent, GetImage_gurax, "GetImage")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetImage();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetIndex()
Gurax_DeclareMethodAlias(wxListEvent, GetIndex_gurax, "GetIndex")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetIndex();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetItem() {block?}
Gurax_DeclareMethodAlias(wxListEvent, GetItem_gurax, "GetItem")
{
	Declare(VTYPE_wxListItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxListItem(
		pEntity_gurax->GetItem()));
}

// wx.ListEvent#GetKeyCode()
Gurax_DeclareMethodAlias(wxListEvent, GetKeyCode_gurax, "GetKeyCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetKeyCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetKeyCode();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetLabel()
Gurax_DeclareMethodAlias(wxListEvent, GetLabel_gurax, "GetLabel")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetLabel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLabel();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.ListEvent#GetMask()
Gurax_DeclareMethodAlias(wxListEvent, GetMask_gurax, "GetMask")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetMask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	long rtn = pEntity_gurax->GetMask();
	return new Gurax::Value_Number(rtn);
}

// wx.ListEvent#GetPoint() {block?}
Gurax_DeclareMethodAlias(wxListEvent, GetPoint_gurax, "GetPoint")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPoint()));
}

// wx.ListEvent#GetText()
Gurax_DeclareMethodAlias(wxListEvent, GetText_gurax, "GetText")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, GetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetText();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.ListEvent#IsEditCancelled()
Gurax_DeclareMethodAlias(wxListEvent, IsEditCancelled_gurax, "IsEditCancelled")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, IsEditCancelled_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEditCancelled();
	return new Gurax::Value_Bool(rtn);
}

// wx.ListEvent#SetKeyCode(code as Number)
Gurax_DeclareMethodAlias(wxListEvent, SetKeyCode_gurax, "SetKeyCode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetKeyCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int code = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetKeyCode(code);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetIndex(index as Number)
Gurax_DeclareMethodAlias(wxListEvent, SetIndex_gurax, "SetIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long index = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetIndex(index);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetColumn(col as Number)
Gurax_DeclareMethodAlias(wxListEvent, SetColumn_gurax, "SetColumn")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("col", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetColumn_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int col = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetColumn(col);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetPoint(point as wx.Point)
Gurax_DeclareMethodAlias(wxListEvent, SetPoint_gurax, "SetPoint")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("point", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetPoint_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_point = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& point = value_point.GetEntity();
	// Function body
	pEntity_gurax->SetPoint(point);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetItem(item as wx.ListItem)
Gurax_DeclareMethodAlias(wxListEvent, SetItem_gurax, "SetItem")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxListItem, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxListItem& value_item = args_gurax.Pick<Value_wxListItem>();
	const wxListItem& item = value_item.GetEntity();
	// Function body
	pEntity_gurax->SetItem(item);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetCacheFrom(cacheFrom as Number)
Gurax_DeclareMethodAlias(wxListEvent, SetCacheFrom_gurax, "SetCacheFrom")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cacheFrom", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetCacheFrom_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long cacheFrom = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetCacheFrom(cacheFrom);
	return Gurax::Value::nil();
}

// wx.ListEvent#SetCacheTo(cacheTo as Number)
Gurax_DeclareMethodAlias(wxListEvent, SetCacheTo_gurax, "SetCacheTo")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cacheTo", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxListEvent, SetCacheTo_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long cacheTo = args_gurax.PickNumber<long>();
	// Function body
	pEntity_gurax->SetCacheTo(cacheTo);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxListEvent
//------------------------------------------------------------------------------
VType_wxListEvent VTYPE_wxListEvent("ListEvent");

void VType_wxListEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxNotifyEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxListEvent, GetCacheFrom_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetCacheTo_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetColumn_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetImage_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetIndex_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetItem_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetKeyCode_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetLabel_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetMask_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetPoint_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, GetText_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, IsEditCancelled_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetKeyCode_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetIndex_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetColumn_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetPoint_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetItem_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetCacheFrom_gurax));
	Assign(Gurax_CreateMethod(wxListEvent, SetCacheTo_gurax));
}

//------------------------------------------------------------------------------
// Value_wxListEvent
//------------------------------------------------------------------------------
VType& Value_wxListEvent::vtype = VTYPE_wxListEvent;
EventValueFactoryDeriv<Value_wxListEvent> Value_wxListEvent::eventValueFactory;

String Value_wxListEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ListEvent");
}

Gurax_EndModuleScope(wx)
