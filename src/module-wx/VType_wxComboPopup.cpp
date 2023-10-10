﻿//==============================================================================
// VType_wxComboPopup.cpp
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

${help.ComposePropertyHelp(wx.ComboPopup, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ComboPopup, `en)}

${help.ComposeMethodHelp(wx.ComboPopup, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ComboPopup, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ComboPopup, `ja)}

${help.ComposeMethodHelp(wx.ComboPopup, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.ComboPopup() {block?}
Gurax_DeclareConstructorAlias(ComboPopup_gurax, "ComboPopup")
{
	Declare(VTYPE_wxComboPopup, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(ComboPopup_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxComboPopup::EntityT();
	RefPtr<Value_wxComboPopup> pValue_gurax(new Value_wxComboPopup(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ComboPopup#Create(parent as wx.Window)
Gurax_DeclareMethodAlias(wxComboPopup, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	// Function body
	bool rtn = pEntity_gurax->Create(parent);
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboPopup#DestroyPopup()
Gurax_DeclareMethodAlias(wxComboPopup, DestroyPopup_gurax, "DestroyPopup")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, DestroyPopup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->DestroyPopup();
	return Gurax::Value::nil();
}

// wx.ComboPopup#Dismiss()
Gurax_DeclareMethodAlias(wxComboPopup, Dismiss_gurax, "Dismiss")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, Dismiss_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Dismiss();
	return Gurax::Value::nil();
}

// wx.ComboPopup#FindItem(item as String, &trueItem?:nilRef as String)
Gurax_DeclareMethodAlias(wxComboPopup, FindItem_gurax, "FindItem")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("trueItem", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::NilRef | ArgFlag::Referencer);
}

Gurax_ImplementMethodEx(wxComboPopup, FindItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* item = args_gurax.PickString();
	RefPtr<Referencer> trueItem(args_gurax.IsValid()? args_gurax.PickReferencer().Reference() : nullptr);
	// Function body
	bool rtn;
	if (trueItem) {
		wxString trueItem_;
		rtn = pEntity_gurax->FindItem(item, &trueItem_);
		trueItem->SetValue(new Value_String(trueItem_.ToUTF8().data()));
	} else {
		rtn = pEntity_gurax->FindItem(item);
	}
	return new Value_Bool(rtn);
}

// wx.ComboPopup#GetAdjustedSize(minWidth as Number, prefHeight as Number, maxHeight as Number) {block?}
Gurax_DeclareMethodAlias(wxComboPopup, GetAdjustedSize_gurax, "GetAdjustedSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("minWidth", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("prefHeight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxHeight", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxComboPopup, GetAdjustedSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int minWidth = args_gurax.PickNumber<int>();
	int prefHeight = args_gurax.PickNumber<int>();
	int maxHeight = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->GetAdjustedSize(minWidth, prefHeight, maxHeight)));
}

// wx.ComboPopup#GetComboCtrl() {block?}
Gurax_DeclareMethodAlias(wxComboPopup, GetComboCtrl_gurax, "GetComboCtrl")
{
	Declare(VTYPE_wxComboCtrl, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxComboPopup, GetComboCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxComboCtrl(
		pEntity_gurax->GetComboCtrl()));
}

// wx.ComboPopup#GetControl() {block?}
Gurax_DeclareMethodAlias(wxComboPopup, GetControl_gurax, "GetControl")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxComboPopup, GetControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetControl()));
}

// wx.ComboPopup#GetStringValue()
Gurax_DeclareMethodAlias(wxComboPopup, GetStringValue_gurax, "GetStringValue")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, GetStringValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetStringValue();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.ComboPopup#Init()
Gurax_DeclareMethodAlias(wxComboPopup, Init_gurax, "Init")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, Init_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Init();
	return Gurax::Value::nil();
}

// wx.ComboPopup#IsCreated()
Gurax_DeclareMethodAlias(wxComboPopup, IsCreated_gurax, "IsCreated")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, IsCreated_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsCreated();
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboPopup#LazyCreate()
Gurax_DeclareMethodAlias(wxComboPopup, LazyCreate_gurax, "LazyCreate")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, LazyCreate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->LazyCreate();
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboPopup#OnComboDoubleClick()
Gurax_DeclareMethodAlias(wxComboPopup, OnComboDoubleClick_gurax, "OnComboDoubleClick")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, OnComboDoubleClick_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnComboDoubleClick();
	return Gurax::Value::nil();
}

// wx.ComboPopup#OnDismiss()
Gurax_DeclareMethodAlias(wxComboPopup, OnDismiss_gurax, "OnDismiss")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, OnDismiss_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnDismiss();
	return Gurax::Value::nil();
}

// wx.ComboPopup#OnPopup()
Gurax_DeclareMethodAlias(wxComboPopup, OnPopup_gurax, "OnPopup")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, OnPopup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnPopup();
	return Gurax::Value::nil();
}

// wx.ComboPopup#PaintComboControl(dc as wx.DC, rect as wx.Rect)
Gurax_DeclareMethodAlias(wxComboPopup, PaintComboControl_gurax, "PaintComboControl")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dc", VTYPE_wxDC, ArgOccur::Once, ArgFlag::None);
	DeclareArg("rect", VTYPE_wxRect, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, PaintComboControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxDC& value_dc = args_gurax.Pick<Value_wxDC>();
	wxDC& dc = value_dc.GetEntity();
	Value_wxRect& value_rect = args_gurax.Pick<Value_wxRect>();
	const wxRect& rect = value_rect.GetEntity();
	// Function body
	pEntity_gurax->PaintComboControl(dc, rect);
	return Gurax::Value::nil();
}

// wx.ComboPopup#SetStringValue(value as String)
Gurax_DeclareMethodAlias(wxComboPopup, SetStringValue_gurax, "SetStringValue")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxComboPopup, SetStringValue_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxComboPopup::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* value = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetStringValue(value);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxComboPopup
//------------------------------------------------------------------------------
VType_wxComboPopup VTYPE_wxComboPopup("ComboPopup");

void VType_wxComboPopup::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(ComboPopup_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxComboPopup, Create_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, DestroyPopup_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, Dismiss_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, FindItem_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, GetAdjustedSize_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, GetComboCtrl_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, GetControl_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, GetStringValue_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, Init_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, IsCreated_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, LazyCreate_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, OnComboDoubleClick_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, OnDismiss_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, OnPopup_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, PaintComboControl_gurax));
	Assign(Gurax_CreateMethod(wxComboPopup, SetStringValue_gurax));
}

//------------------------------------------------------------------------------
// Value_wxComboPopup
//------------------------------------------------------------------------------
VType& Value_wxComboPopup::vtype = VTYPE_wxComboPopup;

String Value_wxComboPopup::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ComboPopup");
}

//------------------------------------------------------------------------------
// Value_wxComboPopup::EntityT
//------------------------------------------------------------------------------
bool Value_wxComboPopup::EntityT::Create(wxWindow* parent)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Create");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxWindow(parent))) {
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
	return public_Create(parent);
}

void Value_wxComboPopup::EntityT::DestroyPopup()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("DestroyPopup");
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
		return;
	} while (0);
	public_DestroyPopup();
}

wxSize Value_wxComboPopup::EntityT::GetAdjustedSize(int minWidth, int prefHeight, int maxHeight)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("GetAdjustedSize");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_Number(minWidth))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(new Gurax::Value_Number(prefHeight))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(new Gurax::Value_Number(maxHeight))) {
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
		if (!pValueRtn->IsType(VTYPE_wxSize)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_wxSize.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_wxSize::GetEntity(*pValueRtn);
	} while (0);
	return public_GetAdjustedSize(minWidth, prefHeight, maxHeight);
}

wxWindow* Value_wxComboPopup::EntityT::GetControl()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("GetControl");
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
		if (!pValueRtn->IsType(VTYPE_wxWindow)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_wxWindow.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_wxWindow::GetEntityPtr(*pValueRtn);
	} while (0);
	return public_GetControl();
}

wxString Value_wxComboPopup::EntityT::GetStringValue() const
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("GetStringValue");
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
		if (!pValueRtn->IsType(VTYPE_String)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_String.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_String::GetString(*pValueRtn);
	} while (0);
	return public_GetStringValue();
}

void Value_wxComboPopup::EntityT::Init()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("Init");
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
		return;
	} while (0);
	public_Init();
}

bool Value_wxComboPopup::EntityT::LazyCreate()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("LazyCreate");
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
	return public_LazyCreate();
}

void Value_wxComboPopup::EntityT::OnComboDoubleClick()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnComboDoubleClick");
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
		return;
	} while (0);
	public_OnComboDoubleClick();
}

void Value_wxComboPopup::EntityT::OnDismiss()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnDismiss");
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
		return;
	} while (0);
	public_OnDismiss();
}

void Value_wxComboPopup::EntityT::OnPopup()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnPopup");
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
		return;
	} while (0);
	public_OnPopup();
}

void Value_wxComboPopup::EntityT::PaintComboControl(wxDC& dc, const wxRect& rect)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("PaintComboControl");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxDC(dc))) {
			Util::ExitMainLoop();
			break;
		}
		if (!args_gurax.FeedValue(new Value_wxRect(rect))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_PaintComboControl(dc, rect);
}

void Value_wxComboPopup::EntityT::SetStringValue(const wxString& value)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("SetStringValue");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Gurax::Value_String(value.utf8_str().data()))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_SetStringValue(value);
}

Gurax_EndModuleScope(wx)
