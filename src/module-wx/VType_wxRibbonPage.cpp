﻿//==============================================================================
// VType_wxRibbonPage.cpp
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

${help.ComposePropertyHelp(wx.RibbonPage, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonPage, `en)}

${help.ComposeMethodHelp(wx.RibbonPage, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonPage, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonPage, `ja)}

${help.ComposeMethodHelp(wx.RibbonPage, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RibbonPage(parent as wx.RibbonBar, id? as Number, label? as String, icon? as wx.Bitmap, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RibbonPage_gurax, "RibbonPage")
{
	Declare(VTYPE_wxRibbonPage, Flag::None);
	DeclareArg("parent", VTYPE_wxRibbonBar, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("icon", VTYPE_wxBitmap, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RibbonPage_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonBar& value_parent = args_gurax.Pick<Value_wxRibbonBar>();
	wxRibbonBar* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxBitmap& icon = args_gurax.IsValid()? args_gurax.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxRibbonPage::EntityT(parent, id, label, icon, style);
	RefPtr<Value_wxRibbonPage> pValue_gurax(new Value_wxRibbonPage(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonPage#Create(parent as wx.RibbonBar, id? as Number, label? as String, icon? as wx.Bitmap, style? as Number)
Gurax_DeclareMethodAlias(wxRibbonPage, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxRibbonBar, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("icon", VTYPE_wxBitmap, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonBar& value_parent = args_gurax.Pick<Value_wxRibbonBar>();
	wxRibbonBar* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxBitmap& icon = args_gurax.IsValid()? args_gurax.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, label, icon, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#SetArtProvider(art as wx.RibbonArtProvider)
Gurax_DeclareMethodAlias(wxRibbonPage, SetArtProvider_gurax, "SetArtProvider")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("art", VTYPE_wxRibbonArtProvider, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, SetArtProvider_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonArtProvider& value_art = args_gurax.Pick<Value_wxRibbonArtProvider>();
	wxRibbonArtProvider* art = value_art.GetEntityPtr();
	// Function body
	pEntity_gurax->SetArtProvider(art);
	return Gurax::Value::nil();
}

// wx.RibbonPage#GetIcon() {block?}
Gurax_DeclareMethodAlias(wxRibbonPage, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonPage, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetIcon()));
}

// wx.RibbonPage#SetSizeWithScrollButtonAdjustment(x as Number, y as Number, width as Number, height as Number)
Gurax_DeclareMethodAlias(wxRibbonPage, SetSizeWithScrollButtonAdjustment_gurax, "SetSizeWithScrollButtonAdjustment")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, SetSizeWithScrollButtonAdjustment_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int x = args_gurax.PickNumber<int>();
	int y = args_gurax.PickNumber<int>();
	int width = args_gurax.PickNumber<int>();
	int height = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSizeWithScrollButtonAdjustment(x, y, width, height);
	return Gurax::Value::nil();
}

// wx.RibbonPage#AdjustRectToIncludeScrollButtons(rect as wx.Rect)
Gurax_DeclareMethodAlias(wxRibbonPage, AdjustRectToIncludeScrollButtons_gurax, "AdjustRectToIncludeScrollButtons")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, AdjustRectToIncludeScrollButtons_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	wxRect* rect = value_rect.GetEntityPtr();
	// Function body
	pEntity_gurax->AdjustRectToIncludeScrollButtons(rect);
	return Gurax::Value::nil();
}

// wx.RibbonPage#DismissExpandedPanel()
Gurax_DeclareMethodAlias(wxRibbonPage, DismissExpandedPanel_gurax, "DismissExpandedPanel")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, DismissExpandedPanel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DismissExpandedPanel();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#Realize()
Gurax_DeclareMethodAlias(wxRibbonPage, Realize_gurax, "Realize")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, Realize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonPage::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Realize();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#ScrollLines(lines as Number)
Gurax_DeclareMethodAlias(wxRibbonPage, ScrollLines_gurax, "ScrollLines")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("lines", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, ScrollLines_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonPage::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int lines = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollLines(lines);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#ScrollPixels(pixels as Number)
Gurax_DeclareMethodAlias(wxRibbonPage, ScrollPixels_gurax, "ScrollPixels")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pixels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, ScrollPixels_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pixels = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollPixels(pixels);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#ScrollSections(sections as Number)
Gurax_DeclareMethodAlias(wxRibbonPage, ScrollSections_gurax, "ScrollSections")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("sections", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, ScrollSections_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int sections = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollSections(sections);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonPage#GetMajorAxis()
Gurax_DeclareMethodAlias(wxRibbonPage, GetMajorAxis_gurax, "GetMajorAxis")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonPage, GetMajorAxis_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxOrientation rtn = pEntity_gurax->GetMajorAxis();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonPage
//------------------------------------------------------------------------------
VType_wxRibbonPage VTYPE_wxRibbonPage("RibbonPage");

void VType_wxRibbonPage::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable, Gurax_CreateConstructor(RibbonPage_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonPage, Create_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, SetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, SetSizeWithScrollButtonAdjustment_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, AdjustRectToIncludeScrollButtons_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, DismissExpandedPanel_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, Realize_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, ScrollLines_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, ScrollPixels_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, ScrollSections_gurax));
	Assign(Gurax_CreateMethod(wxRibbonPage, GetMajorAxis_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonPage
//------------------------------------------------------------------------------
VType& Value_wxRibbonPage::vtype = VTYPE_wxRibbonPage;

String Value_wxRibbonPage::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonPage");
}

//------------------------------------------------------------------------------
// Value_wxRibbonPage::EntityT
//------------------------------------------------------------------------------
bool Value_wxRibbonPage::EntityT::Realize()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Realize");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_Realize();
}

bool Value_wxRibbonPage::EntityT::ScrollLines(int lines)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("ScrollLines");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(lines))) {
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
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_ScrollLines(lines);
}

Gurax_EndModuleScope(wx)
