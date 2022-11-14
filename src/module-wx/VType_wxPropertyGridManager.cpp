﻿//==============================================================================
// VType_wxPropertyGridManager.cpp
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

${help.ComposePropertyHelp(wx.PropertyGridManager, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.PropertyGridManager, `en)}

${help.ComposeMethodHelp(wx.PropertyGridManager, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PropertyGridManager(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(PropertyGridManager_gurax, "PropertyGridManager")
{
	Declare(VTYPE_wxPropertyGridManager, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.PropertyGridManager.
)**");
}

Gurax_ImplementConstructorEx(PropertyGridManager_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxPGMAN_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPropertyGridManagerNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxPropertyGridManager::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxPropertyGridManager> pValue_gurax(new Value_wxPropertyGridManager(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.PropertyGridManager#AddPage(label? as String, bmp? as wx.Bitmap, pageObj? as wx.PropertyGridPage) {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, AddPage_gurax, "AddPage")
{
	Declare(VTYPE_wxPropertyGridPage, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pageObj", VTYPE_wxPropertyGridPage, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, AddPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxBitmap& bmp = args_gurax.IsValid()? args_gurax.Pick<Value_wxBitmap>().GetEntity() : wxPG_NULL_BITMAP;
	wxPropertyGridPage* pageObj = args_gurax.IsValid()? args_gurax.Pick<Value_wxPropertyGridPage>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPropertyGridPage(
		pEntity_gurax->AddPage(label, bmp, pageObj)));
}

// wx.PropertyGridManager#Clear()
Gurax_DeclareMethodAlias(wxPropertyGridManager, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#ClearPage(page as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, ClearPage_gurax, "ClearPage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, ClearPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->ClearPage(page);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#CommitChangesFromEditor(flags? as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, CommitChangesFromEditor_gurax, "CommitChangesFromEditor")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, CommitChangesFromEditor_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	wxUint32 flags = flags_validFlag? args_gurax.PickNumber<wxUint32>() : 0;
	// Function body
	bool rtn = pEntity_gurax->CommitChangesFromEditor(flags);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxPropertyGridManager, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, Create_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxPGMAN_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxPropertyGridManagerNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#EnableCategories(enable as Bool)
Gurax_DeclareMethodAlias(wxPropertyGridManager, EnableCategories_gurax, "EnableCategories")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("enable", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, EnableCategories_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool enable = args_gurax.PickBool();
	// Function body
	bool rtn = pEntity_gurax->EnableCategories(enable);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#GetColumnCount(page? as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetColumnCount_gurax, "GetColumnCount")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool page_validFlag = args_gurax.IsValid();
	int page = page_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	int rtn = pEntity_gurax->GetColumnCount(page);
	return new Gurax::Value_Number(rtn);
}

// wx.PropertyGridManager#GetDescBoxHeight()
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetDescBoxHeight_gurax, "GetDescBoxHeight")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetDescBoxHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetDescBoxHeight();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertyGridManager#GetGrid() {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetGrid_gurax, "GetGrid")
{
	Declare(VTYPE_wxPropertyGrid, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetGrid_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPropertyGrid(
		pEntity_gurax->GetGrid()));
}

// wx.PropertyGridManager#GetCurrentPage() {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetCurrentPage_gurax, "GetCurrentPage")
{
	Declare(VTYPE_wxPropertyGridPage, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetCurrentPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPropertyGridPage(
		pEntity_gurax->GetCurrentPage()));
}

// wx.PropertyGridManager#GetPage(ind as Number) {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetPage_gurax, "GetPage")
{
	Declare(VTYPE_wxPropertyGridPage, Flag::None);
	DeclareArg("ind", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int ind = args_gurax.PickNumber<unsigned int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPropertyGridPage(
		pEntity_gurax->GetPage(ind)));
}

// wx.PropertyGridManager#GetPageByName(name as String)
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetPageByName_gurax, "GetPageByName")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetPageByName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* name = args_gurax.PickString();
	// Function body
	int rtn = pEntity_gurax->GetPageByName(name);
	return new Gurax::Value_Number(rtn);
}

// wx.PropertyGridManager#GetPageCount()
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetPageCount_gurax, "GetPageCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetPageCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetPageCount();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertyGridManager#GetPageName(index as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetPageName_gurax, "GetPageName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetPageName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	wxString rtn = pEntity_gurax->GetPageName(index);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.PropertyGridManager#GetPageRoot(index as Number) {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetPageRoot_gurax, "GetPageRoot")
{
	Declare(VTYPE_wxPGProperty, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetPageRoot_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPGProperty(
		*pEntity_gurax->GetPageRoot(index)));
}

// wx.PropertyGridManager#GetSelectedPage()
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetSelectedPage_gurax, "GetSelectedPage")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetSelectedPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelectedPage();
	return new Gurax::Value_Number(rtn);
}

// wx.PropertyGridManager#GetSelectedProperty() {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetSelectedProperty_gurax, "GetSelectedProperty")
{
	Declare(VTYPE_wxPGProperty, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetSelectedProperty_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPGProperty(
		*pEntity_gurax->GetSelectedProperty()));
}

// wx.PropertyGridManager#GetSelection() {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_wxPGProperty, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPGProperty(
		*pEntity_gurax->GetSelection()));
}

// wx.PropertyGridManager#GetToolBar() {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, GetToolBar_gurax, "GetToolBar")
{
	Declare(VTYPE_wxToolBar, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, GetToolBar_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxToolBar(
		pEntity_gurax->GetToolBar()));
}

// wx.PropertyGridManager#InsertPage(index as Number, label as String, bmp? as wx.Bitmap, pageObj? as wx.PropertyGridPage) {block?}
Gurax_DeclareMethodAlias(wxPropertyGridManager, InsertPage_gurax, "InsertPage")
{
	Declare(VTYPE_wxPropertyGridPage, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pageObj", VTYPE_wxPropertyGridPage, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, InsertPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	const char* label = args_gurax.PickString();
	const wxBitmap& bmp = args_gurax.IsValid()? args_gurax.Pick<Value_wxBitmap>().GetEntity() : wxNullBitmap;
	wxPropertyGridPage* pageObj = args_gurax.IsValid()? args_gurax.Pick<Value_wxPropertyGridPage>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPropertyGridPage(
		pEntity_gurax->InsertPage(index, label, bmp, pageObj)));
}

// wx.PropertyGridManager#IsAnyModified()
Gurax_DeclareMethodAlias(wxPropertyGridManager, IsAnyModified_gurax, "IsAnyModified")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, IsAnyModified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsAnyModified();
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#IsFrozen()
Gurax_DeclareMethodAlias(wxPropertyGridManager, IsFrozen_gurax, "IsFrozen")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, IsFrozen_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsFrozen();
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#IsPageModified(index as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, IsPageModified_gurax, "IsPageModified")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, IsPageModified_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t index = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsPageModified(index);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#RemovePage(page as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, RemovePage_gurax, "RemovePage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, RemovePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->RemovePage(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.PropertyGridManager#SelectPage(index as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SelectPage_gurax, "SelectPage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SelectPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int index = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SelectPage(index);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetColumnCount(colCount as Number, page? as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetColumnCount_gurax, "SetColumnCount")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("colCount", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetColumnCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int colCount = args_gurax.PickNumber<int>();
	bool page_validFlag = args_gurax.IsValid();
	int page = page_validFlag? args_gurax.PickNumber<int>() : -1;
	// Function body
	pEntity_gurax->SetColumnCount(colCount, page);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetColumnTitle(idx as Number, title as String)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetColumnTitle_gurax, "SetColumnTitle")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("idx", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetColumnTitle_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int idx = args_gurax.PickNumber<int>();
	const char* title = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetColumnTitle(idx, title);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetDescription(label as String, content as String)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetDescription_gurax, "SetDescription")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("content", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* label = args_gurax.PickString();
	const char* content = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetDescription(label, content);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetDescBoxHeight(ht as Number, refresh? as Bool)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetDescBoxHeight_gurax, "SetDescBoxHeight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("ht", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("refresh", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetDescBoxHeight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int ht = args_gurax.PickNumber<int>();
	bool refresh = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetDescBoxHeight(ht, refresh);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetSplitterLeft(subProps? as Bool, allPages? as Bool)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetSplitterLeft_gurax, "SetSplitterLeft")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("subProps", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("allPages", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetSplitterLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool subProps = args_gurax.IsValid()? args_gurax.PickBool() : false;
	bool allPages = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->SetSplitterLeft(subProps, allPages);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetPageSplitterLeft(page as Number, subProps? as Bool)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetPageSplitterLeft_gurax, "SetPageSplitterLeft")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("subProps", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetPageSplitterLeft_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	bool subProps = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	pEntity_gurax->SetPageSplitterLeft(page, subProps);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetPageSplitterPosition(page as Number, pos as Number, column? as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetPageSplitterPosition_gurax, "SetPageSplitterPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetPageSplitterPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int page = args_gurax.PickNumber<int>();
	int pos = args_gurax.PickNumber<int>();
	bool column_validFlag = args_gurax.IsValid();
	int column = column_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->SetPageSplitterPosition(page, pos, column);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#SetSplitterPosition(pos as Number, column? as Number)
Gurax_DeclareMethodAlias(wxPropertyGridManager, SetSplitterPosition_gurax, "SetSplitterPosition")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("column", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, SetSplitterPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int pos = args_gurax.PickNumber<int>();
	bool column_validFlag = args_gurax.IsValid();
	int column = column_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	pEntity_gurax->SetSplitterPosition(pos, column);
	return Gurax::Value::nil();
}

// wx.PropertyGridManager#ShowHeader(show? as Bool)
Gurax_DeclareMethodAlias(wxPropertyGridManager, ShowHeader_gurax, "ShowHeader")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxPropertyGridManager, ShowHeader_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->ShowHeader(show);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPropertyGridManager
//------------------------------------------------------------------------------
VType_wxPropertyGridManager VTYPE_wxPropertyGridManager("PropertyGridManager");

void VType_wxPropertyGridManager::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable, Gurax_CreateConstructor(PropertyGridManager_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPropertyGridManager, AddPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, Clear_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, ClearPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, CommitChangesFromEditor_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, Create_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, EnableCategories_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetDescBoxHeight_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetGrid_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetCurrentPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetPageByName_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetPageCount_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetPageName_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetPageRoot_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetSelectedPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetSelectedProperty_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, GetToolBar_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, InsertPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, IsAnyModified_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, IsFrozen_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, IsPageModified_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, RemovePage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SelectPage_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetColumnCount_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetColumnTitle_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetDescription_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetDescBoxHeight_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetSplitterLeft_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetPageSplitterLeft_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetPageSplitterPosition_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, SetSplitterPosition_gurax));
	Assign(Gurax_CreateMethod(wxPropertyGridManager, ShowHeader_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPropertyGridManager
//------------------------------------------------------------------------------
VType& Value_wxPropertyGridManager::vtype = VTYPE_wxPropertyGridManager;

String Value_wxPropertyGridManager::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PropertyGridManager");
}

//------------------------------------------------------------------------------
// Value_wxPropertyGridManager::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
