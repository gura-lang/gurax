//==============================================================================
// VType_wxDateSpan.cpp
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

${help.ComposePropertyHelp(wxDateSpan)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDateSpan)}

${help.ComposeMethodHelp(wxDateSpan)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DateSpan(years? as Number, months? as Number, weeks? as Number, days? as Number) {block?}
Gurax_DeclareConstructorAlias(DateSpan_gurax, "DateSpan")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("years", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("months", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("weeks", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("days", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.DateSpan.");
}

Gurax_ImplementConstructorEx(DateSpan_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool years_validFlag = args_gurax.IsValid();
	int years = years_validFlag? args_gurax.PickNumber<int>() : 0;
	bool months_validFlag = args_gurax.IsValid();
	int months = months_validFlag? args_gurax.PickNumber<int>() : 0;
	bool weeks_validFlag = args_gurax.IsValid();
	int weeks = weeks_validFlag? args_gurax.PickNumber<int>() : 0;
	bool days_validFlag = args_gurax.IsValid();
	int days = days_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan(years, months, weeks, days)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DateSpan#Add(other as wx.DateSpan) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, Add_gurax, "Add")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("other", VTYPE_wxDateSpan, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, Add_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateSpan& value_other = args_gurax.Pick<Value_wxDateSpan>();
	const wxDateSpan& other = value_other.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->Add(other)));
}

// wx.DateSpan#GetDays()
Gurax_DeclareMethodAlias(wxDateSpan, GetDays_gurax, "GetDays")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetDays_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDays();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#GetMonths()
Gurax_DeclareMethodAlias(wxDateSpan, GetMonths_gurax, "GetMonths")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetMonths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetMonths();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#GetTotalMonths()
Gurax_DeclareMethodAlias(wxDateSpan, GetTotalMonths_gurax, "GetTotalMonths")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetTotalMonths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTotalMonths();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#GetTotalDays()
Gurax_DeclareMethodAlias(wxDateSpan, GetTotalDays_gurax, "GetTotalDays")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetTotalDays_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetTotalDays();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#GetWeeks()
Gurax_DeclareMethodAlias(wxDateSpan, GetWeeks_gurax, "GetWeeks")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetWeeks_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetWeeks();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#GetYears()
Gurax_DeclareMethodAlias(wxDateSpan, GetYears_gurax, "GetYears")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, GetYears_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetYears();
	return new Gurax::Value_Number(rtn);
}

// wx.DateSpan#Multiply(factor as Number) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, Multiply_gurax, "Multiply")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("factor", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, Multiply_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int factor = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->Multiply(factor)));
}

// wx.DateSpan#Neg() {block?}
Gurax_DeclareMethodAlias(wxDateSpan, Neg_gurax, "Neg")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, Neg_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->Neg()));
}

// wx.DateSpan#Negate() {block?}
Gurax_DeclareMethodAlias(wxDateSpan, Negate_gurax, "Negate")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, Negate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->Negate()));
}

// wx.DateSpan#SetDays(n as Number) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, SetDays_gurax, "SetDays")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, SetDays_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->SetDays(n)));
}

// wx.DateSpan#SetMonths(n as Number) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, SetMonths_gurax, "SetMonths")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, SetMonths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->SetMonths(n)));
}

// wx.DateSpan#SetWeeks(n as Number) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, SetWeeks_gurax, "SetWeeks")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, SetWeeks_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->SetWeeks(n)));
}

// wx.DateSpan#SetYears(n as Number) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, SetYears_gurax, "SetYears")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, SetYears_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->SetYears(n)));
}

// wx.DateSpan#Subtract(other as wx.DateSpan) {block?}
Gurax_DeclareMethodAlias(wxDateSpan, Subtract_gurax, "Subtract")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("other", VTYPE_wxDateSpan, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDateSpan, Subtract_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDateSpan& value_other = args_gurax.Pick<Value_wxDateSpan>();
	const wxDateSpan& other = value_other.GetEntity();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		pEntity_gurax->Subtract(other)));
}

// wx.DateSpan.Day() {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Day_gurax, "Day")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Day_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Day()));
}

// wx.DateSpan.Days(days as Number) {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Days_gurax, "Days")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("days", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Days_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int days = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Days(days)));
}

// wx.DateSpan.Month() {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Month_gurax, "Month")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Month_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Month()));
}

// wx.DateSpan.Months(mon as Number) {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Months_gurax, "Months")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("mon", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Months_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int mon = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Months(mon)));
}

// wx.DateSpan.Week() {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Week_gurax, "Week")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Week_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Week()));
}

// wx.DateSpan.Weeks(weeks as Number) {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Weeks_gurax, "Weeks")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("weeks", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Weeks_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int weeks = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Weeks(weeks)));
}

// wx.DateSpan.Year() {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Year_gurax, "Year")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Year_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Year()));
}

// wx.DateSpan.Years(years as Number) {block?}
Gurax_DeclareClassMethodAlias(wxDateSpan, Years_gurax, "Years")
{
	Declare(VTYPE_wxDateSpan, Flag::None);
	DeclareArg("years", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxDateSpan, Years_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int years = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxDateSpan(
		wxDateSpan::Years(years)));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDateSpan
//------------------------------------------------------------------------------
VType_wxDateSpan VTYPE_wxDateSpan("DateSpan");

void VType_wxDateSpan::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(DateSpan_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDateSpan, Add_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetDays_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetMonths_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetTotalMonths_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetTotalDays_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetWeeks_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, GetYears_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Multiply_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Neg_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Negate_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, SetDays_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, SetMonths_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, SetWeeks_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, SetYears_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Subtract_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Day_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Days_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Month_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Months_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Week_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Weeks_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Year_gurax));
	Assign(Gurax_CreateMethod(wxDateSpan, Years_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDateSpan
//------------------------------------------------------------------------------
VType& Value_wxDateSpan::vtype = VTYPE_wxDateSpan;

String Value_wxDateSpan::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DateSpan");
}

Gurax_EndModuleScope(wx)
