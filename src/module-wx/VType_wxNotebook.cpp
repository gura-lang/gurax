//==============================================================================
// VType_wxNotebook.cpp
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
// wx.Notebook(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(Notebook_gurax, "Notebook")
{
	Declare(VTYPE_wxNotebook, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Notebook.");
}

Gurax_ImplementConstructorEx(Notebook_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxNotebookNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxNotebook::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxNotebook> pValue_gurax(new Value_wxNotebook(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Notebook#GetRowCount()
Gurax_DeclareMethodAlias(wxNotebook, GetRowCount_gurax, "GetRowCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, GetRowCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetRowCount();
	return new Gurax::Value_Number(rtn);
}

// wx.Notebook#GetThemeBackgroundColour() {block?}
Gurax_DeclareMethodAlias(wxNotebook, GetThemeBackgroundColour_gurax, "GetThemeBackgroundColour")
{
	Declare(VTYPE_wxColour, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, GetThemeBackgroundColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxColour(
		pEntity_gurax->GetThemeBackgroundColour()));
}

// wx.Notebook#SetPadding(padding as wx.Size)
Gurax_DeclareMethodAlias(wxNotebook, SetPadding_gurax, "SetPadding")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("padding", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, SetPadding_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxSize& value_padding = args_gurax.Pick<Value_wxSize>();
	const wxSize& padding = value_padding.GetEntity();
	// Function body
	pEntity_gurax->SetPadding(padding);
	return Gurax::Value::nil();
}

// wx.Notebook#GetPageImage(nPage as Number)
Gurax_DeclareMethodAlias(wxNotebook, GetPageImage_gurax, "GetPageImage")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("nPage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, GetPageImage_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#SetPageImage(page as Number, image as Number)
Gurax_DeclareMethodAlias(wxNotebook, SetPageImage_gurax, "SetPageImage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("image", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, SetPageImage_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#GetPageText(nPage as Number)
Gurax_DeclareMethodAlias(wxNotebook, GetPageText_gurax, "GetPageText")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("nPage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, GetPageText_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#SetPageText(page as Number, text as String)
Gurax_DeclareMethodAlias(wxNotebook, SetPageText_gurax, "SetPageText")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, SetPageText_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#GetSelection()
Gurax_DeclareMethodAlias(wxNotebook, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.Notebook#SetSelection(page as Number)
Gurax_DeclareMethodAlias(wxNotebook, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, SetSelection_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#ChangeSelection(page as Number)
Gurax_DeclareMethodAlias(wxNotebook, ChangeSelection_gurax, "ChangeSelection")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxNotebook, ChangeSelection_gurax, processor_gurax, argument_gurax)
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

// wx.Notebook#InsertPage(index as Number, page as wx.Window, text as String, select? as Bool, imageId? as Number)
Gurax_DeclareMethodAlias(wxNotebook, InsertPage_gurax, "InsertPage")
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

Gurax_ImplementMethodEx(wxNotebook, InsertPage_gurax, processor_gurax, argument_gurax)
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
	int imageId = imageId_validFlag? args_gurax.PickNumber<int>() : wxNotebook::NO_IMAGE;
	// Function body
	bool rtn = pEntity_gurax->InsertPage(index, page, text, select, imageId);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxNotebook
//------------------------------------------------------------------------------
VType_wxNotebook VTYPE_wxNotebook("Notebook");

void VType_wxNotebook::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlBase, Flag::Mutable, Gurax_CreateConstructor(Notebook_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxNotebook, GetRowCount_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, GetThemeBackgroundColour_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, SetPadding_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, GetPageImage_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, SetPageImage_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, GetPageText_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, SetPageText_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, ChangeSelection_gurax));
	Assign(Gurax_CreateMethod(wxNotebook, InsertPage_gurax));
}

//------------------------------------------------------------------------------
// Value_wxNotebook
//------------------------------------------------------------------------------
VType& Value_wxNotebook::vtype = VTYPE_wxNotebook;

String Value_wxNotebook::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Notebook");
}

//------------------------------------------------------------------------------
// Value_wxNotebook::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
