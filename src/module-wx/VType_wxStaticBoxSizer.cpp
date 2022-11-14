﻿//==============================================================================
// VType_wxStaticBoxSizer.cpp
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

${help.ComposePropertyHelp(wx.StaticBoxSizer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StaticBoxSizer, `en)}

${help.ComposeMethodHelp(wx.StaticBoxSizer, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StaticBoxSizer(args* as Any) {block?}
Gurax_DeclareConstructorAlias(StaticBoxSizer_gurax, "StaticBoxSizer")
{
	Declare(VTYPE_wxStaticBoxSizer, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.StaticBoxSizer.
)**");
}

Gurax_ImplementConstructorEx(StaticBoxSizer_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("box", VTYPE_wxStaticBox);
			pDeclCallable->DeclareArg("orient", VTYPE_Number);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxStaticBox* box = args.Pick<Value_wxStaticBox>().GetEntityPtr();
		int orient = args.PickNumber<int>();
		wxStaticBoxSizer* rtn = new wxStaticBoxSizer(box, orient);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxStaticBoxSizer(rtn));
	} while (0);
	Error::ClearIssuedFlag();
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("orient", VTYPE_Number);
			pDeclCallable->DeclareArg("parent", VTYPE_wxWindow);
			pDeclCallable->DeclareArg("label", VTYPE_String, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		int orient = args.PickNumber<int>();
		wxWindow* parent = args.Pick<Value_wxWindow>().GetEntityPtr();
		const char* label = args.IsValid()? args.PickString() : "";
		wxStaticBoxSizer* rtn = new wxStaticBoxSizer(orient, parent, label);
		return argument_gurax.ReturnValue(processor_gurax, new Value_wxStaticBoxSizer(rtn));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StaticBoxSizer#GetStaticBox() {block?}
Gurax_DeclareMethodAlias(wxStaticBoxSizer, GetStaticBox_gurax, "GetStaticBox")
{
	Declare(VTYPE_wxStaticBox, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxStaticBoxSizer, GetStaticBox_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxStaticBox(
		pEntity_gurax->GetStaticBox()));
}

// wx.StaticBoxSizer#CalcMin() {block?}
Gurax_DeclareMethodAlias(wxStaticBoxSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxStaticBoxSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.StaticBoxSizer#RecalcSizes()
Gurax_DeclareMethodAlias(wxStaticBoxSizer, RecalcSizes_gurax, "RecalcSizes")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxStaticBoxSizer, RecalcSizes_gurax, processor_gurax, argument_gurax)
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
// VType_wxStaticBoxSizer
//------------------------------------------------------------------------------
VType_wxStaticBoxSizer VTYPE_wxStaticBoxSizer("StaticBoxSizer");

void VType_wxStaticBoxSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBoxSizer, Flag::Mutable, Gurax_CreateConstructor(StaticBoxSizer_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStaticBoxSizer, GetStaticBox_gurax));
	Assign(Gurax_CreateMethod(wxStaticBoxSizer, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxStaticBoxSizer, RecalcSizes_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStaticBoxSizer
//------------------------------------------------------------------------------
VType& Value_wxStaticBoxSizer::vtype = VTYPE_wxStaticBoxSizer;

String Value_wxStaticBoxSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StaticBoxSizer");
}

Gurax_EndModuleScope(wx)
