//==============================================================================
// VType_wxGridSizer.cpp
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
// wx.GridSizer(args* as Any) {block?} {block?}
Gurax_DeclareConstructorAlias(GridSizer_gurax, "GridSizer")
{
	Declare(VTYPE_wxGridSizer, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.GridSizer.");
}

Gurax_ImplementConstructorEx(GridSizer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("cols", VTYPE_Number);
			pDeclCallable->DeclareArg("vgap", VTYPE_Number);
			pDeclCallable->DeclareArg("hgap", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int cols = args.PickNumber<int>();
		int vgap = args.PickNumber<int>();
		int hgap = args.PickNumber<int>();
		wxGridSizer* rtn = new wxGridSizer(cols, vgap, hgap);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridSizer(rtn));
	} while (0);
	Error::ClearIssuedFlag();
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("cols", VTYPE_Number);
			pDeclCallable->DeclareArg("gap", VTYPE_wxSize, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int cols = args.PickNumber<int>();
		const wxSize& gap = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxSize(0, 0);
		wxGridSizer* rtn = new wxGridSizer(cols, gap);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridSizer(rtn));
	} while (0);
	Error::ClearIssuedFlag();
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("rows", VTYPE_Number);
			pDeclCallable->DeclareArg("cols", VTYPE_Number);
			pDeclCallable->DeclareArg("vgap", VTYPE_Number);
			pDeclCallable->DeclareArg("hgap", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int rows = args.PickNumber<int>();
		int cols = args.PickNumber<int>();
		int vgap = args.PickNumber<int>();
		int hgap = args.PickNumber<int>();
		wxGridSizer* rtn = new wxGridSizer(rows, cols, vgap, hgap);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridSizer(rtn));
	} while (0);
	Error::ClearIssuedFlag();
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("rows", VTYPE_Number);
			pDeclCallable->DeclareArg("cols", VTYPE_Number);
			pDeclCallable->DeclareArg("gap", VTYPE_wxSize, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int rows = args.PickNumber<int>();
		int cols = args.PickNumber<int>();
		const wxSize& gap = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxSize(0, 0);
		wxGridSizer* rtn = new wxGridSizer(rows, cols, gap);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxGridSizer(rtn));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GridSizer#GetCols()
Gurax_DeclareMethodAlias(wxGridSizer, GetCols_gurax, "GetCols")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetCols_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCols();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#GetRows()
Gurax_DeclareMethodAlias(wxGridSizer, GetRows_gurax, "GetRows")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetRows_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRows();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#GetEffectiveColsCount()
Gurax_DeclareMethodAlias(wxGridSizer, GetEffectiveColsCount_gurax, "GetEffectiveColsCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetEffectiveColsCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetEffectiveColsCount();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#GetEffectiveRowsCount()
Gurax_DeclareMethodAlias(wxGridSizer, GetEffectiveRowsCount_gurax, "GetEffectiveRowsCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetEffectiveRowsCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetEffectiveRowsCount();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#GetHGap()
Gurax_DeclareMethodAlias(wxGridSizer, GetHGap_gurax, "GetHGap")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetHGap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetHGap();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#GetVGap()
Gurax_DeclareMethodAlias(wxGridSizer, GetVGap_gurax, "GetVGap")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, GetVGap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetVGap();
	return new Gurax::Value_Number(rtn);
}

// wx.GridSizer#SetCols(cols as Number)
Gurax_DeclareMethodAlias(wxGridSizer, SetCols_gurax, "SetCols")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("cols", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, SetCols_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int cols = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetCols(cols);
	return Gurax::Value::nil();
}

// wx.GridSizer#SetHGap(gap as Number)
Gurax_DeclareMethodAlias(wxGridSizer, SetHGap_gurax, "SetHGap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, SetHGap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int gap = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetHGap(gap);
	return Gurax::Value::nil();
}

// wx.GridSizer#SetRows(rows as Number)
Gurax_DeclareMethodAlias(wxGridSizer, SetRows_gurax, "SetRows")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rows", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, SetRows_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int rows = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetRows(rows);
	return Gurax::Value::nil();
}

// wx.GridSizer#SetVGap(gap as Number)
Gurax_DeclareMethodAlias(wxGridSizer, SetVGap_gurax, "SetVGap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("gap", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, SetVGap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int gap = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetVGap(gap);
	return Gurax::Value::nil();
}

// wx.GridSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxGridSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.GridSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxGridSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxGridSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->RecalcSizes();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGridSizer
//------------------------------------------------------------------------------
VType_wxGridSizer VTYPE_wxGridSizer("GridSizer");

void VType_wxGridSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxSizer, Flag::Mutable, Gurax_CreateConstructor(GridSizer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGridSizer, GetCols_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, GetRows_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, GetEffectiveColsCount_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, GetEffectiveRowsCount_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, GetHGap_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, GetVGap_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, SetCols_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, SetHGap_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, SetRows_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, SetVGap_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxGridSizer, RecalcSizes_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGridSizer
//------------------------------------------------------------------------------
VType& Value_wxGridSizer::vtype = VTYPE_wxGridSizer;

String Value_wxGridSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GridSizer");
}

Gurax_EndModuleScope(wx)
