﻿//==============================================================================
// VType_wxFontMetrics.cpp
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

${help.ComposePropertyHelp(wx.FontMetrics, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FontMetrics, `en)}

${help.ComposeMethodHelp(wx.FontMetrics, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FontMetrics() {block?}
Gurax_DeclareConstructorAlias(FontMetrics_gurax, "FontMetrics")
{
	Declare(VTYPE_wxFontMetrics, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates an instance of wx.FontMetrics.
)**");
}

Gurax_ImplementConstructorEx(FontMetrics_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFontMetrics(
		wxFontMetrics()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
Gurax_DeclareProperty_RW(wxFontMetrics, height)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, height)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().height);
}

Gurax_ImplementPropertySetter(wxFontMetrics, height)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int height = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().height = height;
}

Gurax_DeclareProperty_RW(wxFontMetrics, ascent)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, ascent)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().ascent);
}

Gurax_ImplementPropertySetter(wxFontMetrics, ascent)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int ascent = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().ascent = ascent;
}

Gurax_DeclareProperty_RW(wxFontMetrics, descent)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, descent)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().descent);
}

Gurax_ImplementPropertySetter(wxFontMetrics, descent)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int descent = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().descent = descent;
}

Gurax_DeclareProperty_RW(wxFontMetrics, internalLeading)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, internalLeading)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().internalLeading);
}

Gurax_ImplementPropertySetter(wxFontMetrics, internalLeading)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int internalLeading = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().internalLeading = internalLeading;
}

Gurax_DeclareProperty_RW(wxFontMetrics, externalLeading)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, externalLeading)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().externalLeading);
}

Gurax_ImplementPropertySetter(wxFontMetrics, externalLeading)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int externalLeading = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().externalLeading = externalLeading;
}

Gurax_DeclareProperty_RW(wxFontMetrics, averageWidth)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(wxFontMetrics, averageWidth)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	return new Value_Number(valueThis_gurax.GetEntity().averageWidth);
}

Gurax_ImplementPropertySetter(wxFontMetrics, averageWidth)
{
	auto& valueThis_gurax = GetValueThis(valueTarget);
	auto& value_gurax = value;
	int averageWidth = Value_Number::GetNumber<int>(value_gurax);
	valueThis_gurax.GetEntity().averageWidth = averageWidth;
}

//------------------------------------------------------------------------------
// VType_wxFontMetrics
//------------------------------------------------------------------------------
VType_wxFontMetrics VTYPE_wxFontMetrics("FontMetrics");

void VType_wxFontMetrics::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(FontMetrics_gurax));
	// Assignment of method
	// Assignment of property
	Assign(Gurax_CreateProperty(wxFontMetrics, height));
	Assign(Gurax_CreateProperty(wxFontMetrics, ascent));
	Assign(Gurax_CreateProperty(wxFontMetrics, descent));
	Assign(Gurax_CreateProperty(wxFontMetrics, internalLeading));
	Assign(Gurax_CreateProperty(wxFontMetrics, externalLeading));
	Assign(Gurax_CreateProperty(wxFontMetrics, averageWidth));
}

//------------------------------------------------------------------------------
// Value_wxFontMetrics
//------------------------------------------------------------------------------
VType& Value_wxFontMetrics::vtype = VTYPE_wxFontMetrics;

String Value_wxFontMetrics::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FontMetrics");
}

Gurax_EndModuleScope(wx)
