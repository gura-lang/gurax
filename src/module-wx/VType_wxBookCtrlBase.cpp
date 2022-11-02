//==============================================================================
// VType_wxBookCtrlBase.cpp
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

${help.ComposePropertyHelp(wxBookCtrlBase)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxBookCtrlBase)}

${help.ComposeMethodHelp(wxBookCtrlBase)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BookCtrlBase#SetPageSize(size as wx.Size)
Gurax_DeclareMethodAlias(wxBookCtrlBase, SetPageSize_gurax, "SetPageSize")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, SetPageSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	// Function body
	pEntity_gurax->SetPageSize(size);
	return Gurax::Value::nil();
}

// wx.BookCtrlBase#HitTest(pt as wx.Point)
Gurax_DeclareMethodAlias(wxBookCtrlBase, HitTest_gurax, "HitTest")
{
	Declare(VTYPE_Tuple, Flag::None);
	DeclareArg("pt", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, HitTest_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxPoint& value_pt = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pt = value_pt.GetEntity();
	// Function body
	long flags;
	int rtn = pEntity_gurax->HitTest(pt, &flags);
	if (rtn == wxNOT_FOUND) return Value::nil();
	return Value_Tuple::Create(new Value_Number(rtn), new Value_Number(flags));
}

// wx.BookCtrlBase#GetPageImage(nPage as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetPageImage_gurax, "GetPageImage")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("nPage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetPageImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t nPage = args_gurax.PickNumber<size_t>();
	// Function body
	int rtn = pEntity_gurax->GetPageImage(nPage);
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#SetPageImage(page as Number, image as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, SetPageImage_gurax, "SetPageImage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("image", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, SetPageImage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	int image = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->SetPageImage(page, image);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#GetPageText(nPage as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetPageText_gurax, "GetPageText")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("nPage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetPageText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t nPage = args_gurax.PickNumber<size_t>();
	// Function body
	wxString rtn = pEntity_gurax->GetPageText(nPage);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.BookCtrlBase#SetPageText(page as Number, text as String)
Gurax_DeclareMethodAlias(wxBookCtrlBase, SetPageText_gurax, "SetPageText")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, SetPageText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	const char* text = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetPageText(page, text);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#GetSelection()
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#GetCurrentPage() {block?}
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetCurrentPage_gurax, "GetCurrentPage")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetCurrentPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetCurrentPage()));
}

// wx.BookCtrlBase#SetSelection(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	int rtn = pEntity_gurax->SetSelection(page);
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#AdvanceSelection(forward? as Bool)
Gurax_DeclareMethodAlias(wxBookCtrlBase, AdvanceSelection_gurax, "AdvanceSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("forward", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, AdvanceSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool forward = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->AdvanceSelection(forward);
	return Gurax::Value::nil();
}

// wx.BookCtrlBase#ChangeSelection(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, ChangeSelection_gurax, "ChangeSelection")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, ChangeSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	int rtn = pEntity_gurax->ChangeSelection(page);
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#FindPage(page as wx.Window)
Gurax_DeclareMethodAlias(wxBookCtrlBase, FindPage_gurax, "FindPage")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, FindPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_page = args_gurax.Pick<Value_wxWindow>();
	const wxWindow* page = value_page.GetEntityPtr();
	// Function body
	int rtn = pEntity_gurax->FindPage(page);
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#AddPage(page as wx.Window, text as String, select? as Bool, imageId? as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, AddPage_gurax, "AddPage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("select", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("imageId", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, AddPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_page = args_gurax.Pick<Value_wxWindow>();
	wxWindow* page = value_page.GetEntityPtr();
	const char* text = args_gurax.PickString();
	bool select = args_gurax.IsValid()? args_gurax.PickBool() : false;
	bool imageId_validFlag = args_gurax.IsValid();
	int imageId = imageId_validFlag? args_gurax.PickNumber<int>() : wxBookCtrlBase::NO_IMAGE;
	// Function body
	bool rtn = pEntity_gurax->AddPage(page, text, select, imageId);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#DeleteAllPages()
Gurax_DeclareMethodAlias(wxBookCtrlBase, DeleteAllPages_gurax, "DeleteAllPages")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, DeleteAllPages_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DeleteAllPages();
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#DeletePage(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, DeletePage_gurax, "DeletePage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, DeletePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->DeletePage(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#InsertPage(index as Number, page as wx.Window, text as String, select? as Bool, imageId? as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, InsertPage_gurax, "InsertPage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("index", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("page", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("select", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("imageId", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, InsertPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t index = args_gurax.PickNumber<size_t>();
	Value_wxWindow& value_page = args_gurax.Pick<Value_wxWindow>();
	wxWindow* page = value_page.GetEntityPtr();
	const char* text = args_gurax.PickString();
	bool select = args_gurax.IsValid()? args_gurax.PickBool() : false;
	bool imageId_validFlag = args_gurax.IsValid();
	int imageId = imageId_validFlag? args_gurax.PickNumber<int>() : wxBookCtrlBase::NO_IMAGE;
	// Function body
	bool rtn = pEntity_gurax->InsertPage(index, page, text, select, imageId);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#RemovePage(page as Number)
Gurax_DeclareMethodAlias(wxBookCtrlBase, RemovePage_gurax, "RemovePage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, RemovePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->RemovePage(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.BookCtrlBase#GetPageCount()
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetPageCount_gurax, "GetPageCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetPageCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetPageCount();
	return new Gurax::Value_Number(rtn);
}

// wx.BookCtrlBase#GetPage(page as Number) {block?}
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetPage_gurax, "GetPage")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetPage(page)));
}

// wx.BookCtrlBase#AssignImageList(imageList as wx.ImageList)
Gurax_DeclareMethodAlias(wxBookCtrlBase, AssignImageList_gurax, "AssignImageList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("imageList", VTYPE_wxImageList, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, AssignImageList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxImageList& value_imageList = args_gurax.Pick<Value_wxImageList>();
	wxImageList* imageList = value_imageList.GetEntityPtr();
	// Function body
	pEntity_gurax->AssignImageList(imageList);
	return Gurax::Value::nil();
}

// wx.BookCtrlBase#SetImageList(imageList as wx.ImageList)
Gurax_DeclareMethodAlias(wxBookCtrlBase, SetImageList_gurax, "SetImageList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("imageList", VTYPE_wxImageList, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, SetImageList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxImageList& value_imageList = args_gurax.Pick<Value_wxImageList>();
	wxImageList* imageList = value_imageList.GetEntityPtr();
	// Function body
	pEntity_gurax->SetImageList(imageList);
	return Gurax::Value::nil();
}

// wx.BookCtrlBase#GetImageList() {block?}
Gurax_DeclareMethodAlias(wxBookCtrlBase, GetImageList_gurax, "GetImageList")
{
	Declare(VTYPE_wxImageList, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBookCtrlBase, GetImageList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxImageList(
		pEntity_gurax->GetImageList()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBookCtrlBase
//------------------------------------------------------------------------------
VType_wxBookCtrlBase VTYPE_wxBookCtrlBase("BookCtrlBase");

void VType_wxBookCtrlBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBookCtrlBase, SetPageSize_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, HitTest_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetPageImage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, SetPageImage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetPageText_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, SetPageText_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetCurrentPage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, AdvanceSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, ChangeSelection_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, FindPage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, AddPage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, DeleteAllPages_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, DeletePage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, InsertPage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, RemovePage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetPageCount_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetPage_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, AssignImageList_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, SetImageList_gurax));
	Assign(Gurax_CreateMethod(wxBookCtrlBase, GetImageList_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBookCtrlBase
//------------------------------------------------------------------------------
VType& Value_wxBookCtrlBase::vtype = VTYPE_wxBookCtrlBase;

String Value_wxBookCtrlBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BookCtrlBase");
}

//------------------------------------------------------------------------------
// Value_wxBookCtrlBase::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
