﻿//==============================================================================
// VType_wxRibbonGallery.cpp
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

${help.ComposePropertyHelp(wx.RibbonGallery, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.RibbonGallery, `en)}

${help.ComposeMethodHelp(wx.RibbonGallery, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.RibbonGallery, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.RibbonGallery, `ja)}

${help.ComposeMethodHelp(wx.RibbonGallery, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RibbonGallery(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RibbonGallery_gurax, "RibbonGallery")
{
	Declare(VTYPE_wxRibbonGallery, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(RibbonGallery_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxRibbonGallery::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxRibbonGallery> pValue_gurax(new Value_wxRibbonGallery(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonGallery#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRibbonGallery, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonGallery#Clear()
Gurax_DeclareMethodAlias(wxRibbonGallery, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.RibbonGallery#IsEmpty()
Gurax_DeclareMethodAlias(wxRibbonGallery, IsEmpty_gurax, "IsEmpty")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, IsEmpty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsEmpty();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonGallery#GetCount()
Gurax_DeclareMethodAlias(wxRibbonGallery, GetCount_gurax, "GetCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonGallery#GetItem(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonGallery, GetItem_gurax, "GetItem")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->GetItem(n)));
}

// wx.RibbonGallery#Append(bitmap as wx.Bitmap, id as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonGallery, Append_gurax, "Append")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareArg("bitmap", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGallery, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bitmap = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bitmap = value_bitmap.GetEntity();
	int id = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->Append(bitmap, id)));
}

// wx.RibbonGallery#SetItemClientObject(item as wx.RibbonGalleryItem, data as Any)
Gurax_DeclareMethodAlias(wxRibbonGallery, SetItemClientObject_gurax, "SetItemClientObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, SetItemClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	const Value& data = args_gurax.PickValue();
	// Function body
	pEntity_gurax->SetItemClientObject(item, ClientData::Create(data));
	return Gurax::Value::nil();
}

// wx.RibbonGallery#GetItemClientObject(item as wx.RibbonGalleryItem)
Gurax_DeclareMethodAlias(wxRibbonGallery, GetItemClientObject_gurax, "GetItemClientObject")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetItemClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	const wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	// Function body
	ClientData* rtn = dynamic_cast<ClientData*>(pEntity_gurax->GetItemClientObject(item));
	if (!rtn) return Value::nil();
	return rtn->GetValue().Reference();
}

// wx.RibbonGallery#SetItemClientData(item as wx.RibbonGalleryItem, data as Pointer)
Gurax_DeclareMethodAlias(wxRibbonGallery, SetItemClientData_gurax, "SetItemClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, SetItemClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	void* data = args_gurax.Pick<Gurax::Value_Pointer>().GetPointer().GetWritablePointerC<void>();
	if (!data) {
		Error::Issue(ErrorType::MemoryError, "the pointer is not writable");
		return Value::nil();
	}
	// Function body
	pEntity_gurax->SetItemClientData(item, data);
	return Gurax::Value::nil();
}

// wx.RibbonGallery#SetSelection(item as wx.RibbonGalleryItem)
Gurax_DeclareMethodAlias(wxRibbonGallery, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	// Function body
	pEntity_gurax->SetSelection(item);
	return Gurax::Value::nil();
}

// wx.RibbonGallery#GetSelection() {block?}
Gurax_DeclareMethodAlias(wxRibbonGallery, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->GetSelection()));
}

// wx.RibbonGallery#GetHoveredItem() {block?}
Gurax_DeclareMethodAlias(wxRibbonGallery, GetHoveredItem_gurax, "GetHoveredItem")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetHoveredItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->GetHoveredItem()));
}

// wx.RibbonGallery#GetActiveItem() {block?}
Gurax_DeclareMethodAlias(wxRibbonGallery, GetActiveItem_gurax, "GetActiveItem")
{
	Declare(VTYPE_wxRibbonGalleryItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetActiveItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonGalleryItem(pEntity_gurax->GetActiveItem()));
}

// wx.RibbonGallery#GetUpButtonState()
Gurax_DeclareMethodAlias(wxRibbonGallery, GetUpButtonState_gurax, "GetUpButtonState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetUpButtonState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxRibbonGalleryButtonState rtn = pEntity_gurax->GetUpButtonState();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonGallery#GetDownButtonState()
Gurax_DeclareMethodAlias(wxRibbonGallery, GetDownButtonState_gurax, "GetDownButtonState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetDownButtonState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxRibbonGalleryButtonState rtn = pEntity_gurax->GetDownButtonState();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonGallery#GetExtensionButtonState()
Gurax_DeclareMethodAlias(wxRibbonGallery, GetExtensionButtonState_gurax, "GetExtensionButtonState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, GetExtensionButtonState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxRibbonGalleryButtonState rtn = pEntity_gurax->GetExtensionButtonState();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonGallery#IsHovered()
Gurax_DeclareMethodAlias(wxRibbonGallery, IsHovered_gurax, "IsHovered")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, IsHovered_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsHovered();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonGallery#ScrollLines(lines as Number)
Gurax_DeclareMethodAlias(wxRibbonGallery, ScrollLines_gurax, "ScrollLines")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("lines", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, ScrollLines_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxRibbonGallery::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int lines = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->ScrollLines(lines);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonGallery#ScrollPixels(pixels as Number)
Gurax_DeclareMethodAlias(wxRibbonGallery, ScrollPixels_gurax, "ScrollPixels")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("pixels", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, ScrollPixels_gurax, processor_gurax, argument_gurax)
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

// wx.RibbonGallery#EnsureVisible(item as wx.RibbonGalleryItem)
Gurax_DeclareMethodAlias(wxRibbonGallery, EnsureVisible_gurax, "EnsureVisible")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_wxRibbonGalleryItem, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxRibbonGallery, EnsureVisible_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonGalleryItem& value_item = args_gurax.Pick<Value_wxRibbonGalleryItem>();
	const wxRibbonGalleryItem* item = value_item.GetEntityPtr();
	// Function body
	pEntity_gurax->EnsureVisible(item);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonGallery
//------------------------------------------------------------------------------
VType_wxRibbonGallery VTYPE_wxRibbonGallery("RibbonGallery");

void VType_wxRibbonGallery::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable, Gurax_CreateConstructor(RibbonGallery_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonGallery, Create_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, Clear_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, IsEmpty_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetCount_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, Append_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, SetItemClientObject_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetItemClientObject_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, SetItemClientData_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetHoveredItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetActiveItem_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetUpButtonState_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetDownButtonState_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, GetExtensionButtonState_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, IsHovered_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, ScrollLines_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, ScrollPixels_gurax));
	Assign(Gurax_CreateMethod(wxRibbonGallery, EnsureVisible_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonGallery
//------------------------------------------------------------------------------
VType& Value_wxRibbonGallery::vtype = VTYPE_wxRibbonGallery;

String Value_wxRibbonGallery::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonGallery");
}

//------------------------------------------------------------------------------
// Value_wxRibbonGallery::EntityT
//------------------------------------------------------------------------------
bool Value_wxRibbonGallery::EntityT::ScrollLines(int lines)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("ScrollLines");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(core_gurax.GetProcessor(), new Gurax::Value_Number(lines))) {
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
		if (!pValueRtn->IsInstanceOf(VTYPE_Bool)) {
			Error::IssueWith(ErrorType::TypeError, pFunc_gurax->GetDeclCallable().GetExprSrc(),
				"the function ScrollLines is expected to return a value of %s or its derived class",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_ScrollLines(lines);
}

Gurax_EndModuleScope(wx)
