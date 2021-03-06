//==============================================================================
// VType_wxFlexGridSizer.cpp
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
// wx.FlexGridSizer#AddGrowableCol(idx as Number, proportion? as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, AddGrowableCol_gurax, "AddGrowableCol")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("proportion", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, AddGrowableCol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	int proportion = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->AddGrowableCol(idx, proportion);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#AddGrowableRow(idx as Number, proportion? as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, AddGrowableRow_gurax, "AddGrowableRow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("proportion", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, AddGrowableRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	int proportion = args_gurax.IsValid()? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->AddGrowableRow(idx, proportion);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#GetFlexibleDirection()
Gurax_DeclareMethodAlias(wxFlexGridSizer, GetFlexibleDirection_gurax, "GetFlexibleDirection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, GetFlexibleDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlexibleDirection();
	return new Gurax::Value_Number(rtn);
}

// wx.FlexGridSizer#GetNonFlexibleGrowMode()
Gurax_DeclareMethodAlias(wxFlexGridSizer, GetNonFlexibleGrowMode_gurax, "GetNonFlexibleGrowMode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, GetNonFlexibleGrowMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFlexSizerGrowMode rtn = pEntity_gurax->GetNonFlexibleGrowMode();
	return new Gurax::Value_Number(rtn);
}

// wx.FlexGridSizer#IsColGrowable(idx as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, IsColGrowable_gurax, "IsColGrowable")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, IsColGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsColGrowable(idx);
	return new Gurax::Value_Bool(rtn);
}

// wx.FlexGridSizer#IsRowGrowable(idx as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, IsRowGrowable_gurax, "IsRowGrowable")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, IsRowGrowable_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsRowGrowable(idx);
	return new Gurax::Value_Bool(rtn);
}

// wx.FlexGridSizer#RemoveGrowableCol(idx as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, RemoveGrowableCol_gurax, "RemoveGrowableCol")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, RemoveGrowableCol_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RemoveGrowableCol(idx);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#RemoveGrowableRow(idx as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, RemoveGrowableRow_gurax, "RemoveGrowableRow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, RemoveGrowableRow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t idx = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RemoveGrowableRow(idx);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#SetFlexibleDirection(direction as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, SetFlexibleDirection_gurax, "SetFlexibleDirection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("direction", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, SetFlexibleDirection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int direction = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFlexibleDirection(direction);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#SetNonFlexibleGrowMode(mode as Number)
Gurax_DeclareMethodAlias(wxFlexGridSizer, SetNonFlexibleGrowMode_gurax, "SetNonFlexibleGrowMode")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, SetNonFlexibleGrowMode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFlexSizerGrowMode mode = args_gurax.PickNumber<wxFlexSizerGrowMode>();
	// Function body
	pEntity_gurax->SetNonFlexibleGrowMode(mode);
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxFlexGridSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

// wx.FlexGridSizer#CalcMin()
Gurax_DeclareMethodAlias(wxFlexGridSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFlexGridSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFlexGridSizer
//------------------------------------------------------------------------------
VType_wxFlexGridSizer VTYPE_wxFlexGridSizer("FlexGridSizer");

void VType_wxFlexGridSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxGridSizer, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFlexGridSizer, AddGrowableCol_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, AddGrowableRow_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, GetFlexibleDirection_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, GetNonFlexibleGrowMode_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, IsColGrowable_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, IsRowGrowable_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, RemoveGrowableCol_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, RemoveGrowableRow_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, SetFlexibleDirection_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, SetNonFlexibleGrowMode_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, RecalcSizes_gurax));
	Assign(Gurax_CreateMethod(wxFlexGridSizer, CalcMin_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFlexGridSizer
//------------------------------------------------------------------------------
VType& Value_wxFlexGridSizer::vtype = VTYPE_wxFlexGridSizer;

String Value_wxFlexGridSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FlexGridSizer");
}

Gurax_EndModuleScope(wx)
