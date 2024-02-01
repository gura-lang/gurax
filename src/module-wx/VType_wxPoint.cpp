﻿//==============================================================================
// VType_wxPoint.cpp
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

${help.ComposePropertyHelp(wx.Point, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Point, `en)}

${help.ComposeMethodHelp(wx.Point, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Point, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Point, `ja)}

${help.ComposeMethodHelp(wx.Point, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Point(args* as Any) {block?}
Gurax_DeclareConstructorAlias(Point_gurax, "Point")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Point_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wxPoint(x as int = 0, y as int = 0)
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
		int x = args.IsValid()? args.PickNumber<int>() : 0;
		int y = args.IsValid()? args.PickNumber<int>() : 0;
		return new Value_wxPoint(wxPoint(x, y));
	} while (0);
	Error::ClearIssuedFlag();
	// wxPoint(pt as const_RealPoint_r)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("pt", VTYPE_wxRealPoint);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const wxRealPoint& pt = args.Pick<Value_wxRealPoint>().GetEntity();
		return new Value_wxPoint(wxPoint(pt));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxPoint, x)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(wxPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().x);
}

Gurax_ImplementPropertySetter(wxPoint, x)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int x = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().x = x;
}

Gurax_DeclareProperty_RW(wxPoint, y)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(wxPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().y);
}

Gurax_ImplementPropertySetter(wxPoint, y)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int y = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().y = y;
}

//------------------------------------------------------------------------------
// VType_wxPoint
//------------------------------------------------------------------------------
VType_wxPoint VTYPE_wxPoint("Point");

void VType_wxPoint::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Point_gurax));
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(wxPoint, x));
	Assign(Gurax_CreateProperty(wxPoint, y));
}

Value* VType_wxPoint::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	if (value.IsInstanceOf(VTYPE_wxRealPoint)) {
		const wxRealPoint& pt = Value_wxRealPoint::GetEntity(value);
		return new Value_wxPoint(wxPoint(pt));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_wxPoint
//------------------------------------------------------------------------------
VType& Value_wxPoint::vtype = VTYPE_wxPoint;

String Value_wxPoint::ToString(const StringStyle& ss) const
{
	const wxPoint& pt = GetEntity();
	return ToStringGeneric(ss, String().Format("wx.Point:x=%d:y=%d", pt.x, pt.y));
}

Gurax_EndModuleScope(wx)
