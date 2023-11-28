﻿//==============================================================================
// VType_wxRealPoint.cpp
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

${help.ComposePropertyHelp(wx.RealPoint, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RealPoint, `en)}

${help.ComposeMethodHelp(wx.RealPoint, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RealPoint, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RealPoint, `ja)}

${help.ComposeMethodHelp(wx.RealPoint, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RealPoint(args* as Any) {block?}
Gurax_DeclareConstructorAlias(RealPoint_gurax, "RealPoint")
{
	Declare(VTYPE_wxRealPoint, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RealPoint_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wxRealPoint(x as double = 0, y as double = 0)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("x", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("y", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		double x = args.IsValid()? args.PickNumber<double>() : 0;
		double y = args.IsValid()? args.PickNumber<double>() : 0;
		return new Value_wxRealPoint(wxRealPoint(x, y));
	} while (0);
	Error::ClearIssuedFlag();
	// wxRealPoint(pt as const_RealPoint_r)
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
		return new Value_wxRealPoint(wxRealPoint(pt));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxRealPoint, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(wxRealPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().x);
}

Gurax_ImplementPropertySetter(wxRealPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	double x = Value_Number::GetNumber<double>(value_gurax);
	valueThis_gurax.GetEntity().x = x;
}

Gurax_DeclareProperty_RW(wxRealPoint, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(wxRealPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().y);
}

Gurax_ImplementPropertySetter(wxRealPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	double y = Value_Number::GetNumber<double>(value_gurax);
	valueThis_gurax.GetEntity().y = y;
}

//------------------------------------------------------------------------------
// VType_wxRealPoint
//------------------------------------------------------------------------------
VType_wxRealPoint VTYPE_wxRealPoint("RealPoint");

void VType_wxRealPoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(RealPoint_gurax));
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(wxRealPoint, x));
	Assign(Gurax_CreateProperty(wxRealPoint, y));
}

Value* VType_wxRealPoint::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsInstanceOf(VTYPE_wxPoint)) {
		const wxPoint& pt = Value_wxPoint::GetEntity(value);
		return new Value_wxRealPoint(wxRealPoint(pt));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_wxRealPoint
//------------------------------------------------------------------------------
VType& Value_wxRealPoint::vtype = VTYPE_wxRealPoint;

String Value_wxRealPoint::ToString(const StringStyle& ss) const
{
	const wxRealPoint& pt = GetEntity();
	return ToStringGeneric(ss, String().Format("wx.RealPoint:x=%g:y=%g", pt.x, pt.y));
}

Gurax_EndModuleScope(wx)