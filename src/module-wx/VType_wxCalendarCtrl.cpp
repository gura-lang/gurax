//==============================================================================
// VType_wxCalendarCtrl.cpp
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
// wx.CalendarCtrl(parent as wx.Window, id as Number, date? as wx.DateTime, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(CalendarCtrl_gurax, "CalendarCtrl")
{
	Declare(VTYPE_wxCalendarCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("date", VTYPE_wxDateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.CalendarCtrl.");
}

Gurax_ImplementConstructorEx(CalendarCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxDateTime& date = args_gurax.IsValid()? args_gurax.Pick<Value_wxDateTime>().GetEntity() : wxDefaultDateTime;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : wxCAL_SHOW_HOLIDAYS;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxCalendarNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxCalendarCtrl::EntityT(parent, id, date, pos, size, style, name);
	RefPtr<Value_wxCalendarCtrl> pValue_gurax(new Value_wxCalendarCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CalendarCtrl#EnableHolidayDisplay(display? as Bool)
Gurax_DeclareMethodAlias(wxCalendarCtrl, EnableHolidayDisplay_gurax, "EnableHolidayDisplay")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("display", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, EnableHolidayDisplay_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool display = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->EnableHolidayDisplay(display);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#EnableMonthChange(enable? as Bool)
Gurax_DeclareMethodAlias(wxCalendarCtrl, EnableMonthChange_gurax, "EnableMonthChange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, EnableMonthChange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->EnableMonthChange(enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarCtrl#GetAttr(day as Number)
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetAttr_gurax, "GetAttr")
{
	Declare(VTYPE_wxCalendarDateAttr, Flag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t day = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxCalendarDateAttr(
		*pEntity_gurax->GetAttr(day)));
}

// wx.CalendarCtrl#GetDate()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetDate_gurax, "GetDate")
{
	Declare(VTYPE_wxDateTime, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetDate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateTime(
		pEntity_gurax->GetDate()));
}

// wx.CalendarCtrl#GetHeaderColourBg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHeaderColourBg_gurax, "GetHeaderColourBg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHeaderColourBg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHeaderColourBg()));
}

// wx.CalendarCtrl#GetHeaderColourFg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHeaderColourFg_gurax, "GetHeaderColourFg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHeaderColourFg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHeaderColourFg()));
}

// wx.CalendarCtrl#GetHighlightColourBg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHighlightColourBg_gurax, "GetHighlightColourBg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHighlightColourBg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHighlightColourBg()));
}

// wx.CalendarCtrl#GetHighlightColourFg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHighlightColourFg_gurax, "GetHighlightColourFg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHighlightColourFg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHighlightColourFg()));
}

// wx.CalendarCtrl#GetHolidayColourBg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHolidayColourBg_gurax, "GetHolidayColourBg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHolidayColourBg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHolidayColourBg()));
}

// wx.CalendarCtrl#GetHolidayColourFg()
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetHolidayColourFg_gurax, "GetHolidayColourFg")
{
	Declare(VTYPE_wxColour, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetHolidayColourFg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetHolidayColourFg()));
}

// wx.CalendarCtrl#ResetAttr(day as Number)
Gurax_DeclareMethodAlias(wxCalendarCtrl, ResetAttr_gurax, "ResetAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, ResetAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t day = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->ResetAttr(day);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetAttr(day as Number, attr as wx.CalendarDateAttr)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetAttr_gurax, "SetAttr")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("attr", VTYPE_wxCalendarDateAttr, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetAttr_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t day = args_gurax.PickNumber<size_t>();
	Value_wxCalendarDateAttr& value_attr = args_gurax.Pick<Value_wxCalendarDateAttr>();
	wxCalendarDateAttr* attr = value_attr.GetEntityPtr();
	// Function body
	pEntity_gurax->SetAttr(day, attr);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetDate(date as wx.DateTime)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetDate_gurax, "SetDate")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("date", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetDate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_date = args_gurax.Pick<Value_wxDateTime>();
	const wxDateTime& date = value_date.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetDate(date);
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarCtrl#SetHeaderColours(colFg as wx.Colour, colBg as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetHeaderColours_gurax, "SetHeaderColours")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colFg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colBg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetHeaderColours_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colFg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colFg = value_colFg.GetEntity();
	Value_wxColour& value_colBg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBg = value_colBg.GetEntity();
	// Function body
	pEntity_gurax->SetHeaderColours(colFg, colBg);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetHighlightColours(colFg as wx.Colour, colBg as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetHighlightColours_gurax, "SetHighlightColours")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colFg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colBg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetHighlightColours_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colFg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colFg = value_colFg.GetEntity();
	Value_wxColour& value_colBg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBg = value_colBg.GetEntity();
	// Function body
	pEntity_gurax->SetHighlightColours(colFg, colBg);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetHoliday(day as Number)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetHoliday_gurax, "SetHoliday")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetHoliday_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t day = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->SetHoliday(day);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetHolidayColours(colFg as wx.Colour, colBg as wx.Colour)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetHolidayColours_gurax, "SetHolidayColours")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colFg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	DeclareArg("colBg", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetHolidayColours_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_colFg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colFg = value_colFg.GetEntity();
	Value_wxColour& value_colBg = args_gurax.Pick<Value_wxColour>();
	const wxColour& colBg = value_colBg.GetEntity();
	// Function body
	pEntity_gurax->SetHolidayColours(colFg, colBg);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#Mark(day as Number, mark as Bool)
Gurax_DeclareMethodAlias(wxCalendarCtrl, Mark_gurax, "Mark")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("day", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mark", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, Mark_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t day = args_gurax.PickNumber<size_t>();
	bool mark = args_gurax.PickBool();
	// Function body
	pEntity_gurax->Mark(day, mark);
	return Gurax::Value::nil();
}

// wx.CalendarCtrl#SetDateRange(lowerdate? as wx.DateTime, upperdate? as wx.DateTime)
Gurax_DeclareMethodAlias(wxCalendarCtrl, SetDateRange_gurax, "SetDateRange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("lowerdate", VTYPE_wxDateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("upperdate", VTYPE_wxDateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, SetDateRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const wxDateTime& lowerdate = args_gurax.IsValid()? args_gurax.Pick<Value_wxDateTime>().GetEntity() : wxDefaultDateTime;
	const wxDateTime& upperdate = args_gurax.IsValid()? args_gurax.Pick<Value_wxDateTime>().GetEntity() : wxDefaultDateTime;
	// Function body
	bool rtn = pEntity_gurax->SetDateRange(lowerdate, upperdate);
	return new Gurax::Value_Bool(rtn);
}

// wx.CalendarCtrl#GetDateRange(lowerdate as wx.DateTime, upperdate as wx.DateTime)
Gurax_DeclareMethodAlias(wxCalendarCtrl, GetDateRange_gurax, "GetDateRange")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("lowerdate", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	DeclareArg("upperdate", VTYPE_wxDateTime, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCalendarCtrl, GetDateRange_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateTime& value_lowerdate = args_gurax.Pick<Value_wxDateTime>();
	wxDateTime* lowerdate = value_lowerdate.GetEntityPtr();
	Value_wxDateTime& value_upperdate = args_gurax.Pick<Value_wxDateTime>();
	wxDateTime* upperdate = value_upperdate.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->GetDateRange(lowerdate, upperdate);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCalendarCtrl
//------------------------------------------------------------------------------
VType_wxCalendarCtrl VTYPE_wxCalendarCtrl("CalendarCtrl");

void VType_wxCalendarCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(CalendarCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCalendarCtrl, EnableHolidayDisplay_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, EnableMonthChange_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetAttr_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetDate_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHeaderColourBg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHeaderColourFg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHighlightColourBg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHighlightColourFg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHolidayColourBg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetHolidayColourFg_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, ResetAttr_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetAttr_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetDate_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetHeaderColours_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetHighlightColours_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetHoliday_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetHolidayColours_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, Mark_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, SetDateRange_gurax));
	Assign(Gurax_CreateMethod(wxCalendarCtrl, GetDateRange_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCalendarCtrl
//------------------------------------------------------------------------------
VType& Value_wxCalendarCtrl::vtype = VTYPE_wxCalendarCtrl;

String Value_wxCalendarCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CalendarCtrl");
}

//------------------------------------------------------------------------------
// Value_wxCalendarCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)