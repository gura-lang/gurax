//==============================================================================
// VType_wxRibbonBar.cpp
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

${help.ComposePropertyHelp(wxRibbonBar)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxRibbonBar)}

${help.ComposeMethodHelp(wxRibbonBar)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.RibbonBar(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(RibbonBar_gurax, "RibbonBar")
{
	Declare(VTYPE_wxRibbonBar, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RibbonBar.");
}

Gurax_ImplementConstructorEx(RibbonBar_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxRIBBON_BAR_DEFAULT_STYLE;
	// Function body
	auto pEntity_gurax = new Value_wxRibbonBar::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxRibbonBar> pValue_gurax(new Value_wxRibbonBar(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RibbonBar#Create(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, Create_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxRIBBON_BAR_DEFAULT_STYLE;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#SetTabCtrlMargins(left as Number, right as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, SetTabCtrlMargins_gurax, "SetTabCtrlMargins")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("left", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("right", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, SetTabCtrlMargins_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int left = args_gurax.PickNumber<int>();
	int right = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetTabCtrlMargins(left, right);
	return Gurax::Value::nil();
}

// wx.RibbonBar#SetArtProvider(art as wx.RibbonArtProvider)
Gurax_DeclareMethodAlias(wxRibbonBar, SetArtProvider_gurax, "SetArtProvider")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("art", VTYPE_wxRibbonArtProvider, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, SetArtProvider_gurax, processor_gurax, argument_gurax)
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

// wx.RibbonBar#SetActivePage(page as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, SetActivePage_gurax, "SetActivePage")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, SetActivePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->SetActivePage(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#GetActivePage()
Gurax_DeclareMethodAlias(wxRibbonBar, GetActivePage_gurax, "GetActivePage")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, GetActivePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetActivePage();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonBar#GetPage(n as Number) {block?}
Gurax_DeclareMethodAlias(wxRibbonBar, GetPage_gurax, "GetPage")
{
	Declare(VTYPE_wxRibbonPage, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, GetPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRibbonPage(
		pEntity_gurax->GetPage(n)));
}

// wx.RibbonBar#GetPageCount()
Gurax_DeclareMethodAlias(wxRibbonBar, GetPageCount_gurax, "GetPageCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, GetPageCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	size_t rtn = pEntity_gurax->GetPageCount();
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonBar#DismissExpandedPanel()
Gurax_DeclareMethodAlias(wxRibbonBar, DismissExpandedPanel_gurax, "DismissExpandedPanel")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, DismissExpandedPanel_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DismissExpandedPanel();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#GetPageNumber(page as wx.RibbonPage)
Gurax_DeclareMethodAlias(wxRibbonBar, GetPageNumber_gurax, "GetPageNumber")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("page", VTYPE_wxRibbonPage, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, GetPageNumber_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxRibbonPage& value_page = args_gurax.Pick<Value_wxRibbonPage>();
	wxRibbonPage* page = value_page.GetEntityPtr();
	// Function body
	int rtn = pEntity_gurax->GetPageNumber(page);
	return new Gurax::Value_Number(rtn);
}

// wx.RibbonBar#DeletePage(n as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, DeletePage_gurax, "DeletePage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, DeletePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t n = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->DeletePage(n);
	return Gurax::Value::nil();
}

// wx.RibbonBar#ClearPages()
Gurax_DeclareMethodAlias(wxRibbonBar, ClearPages_gurax, "ClearPages")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, ClearPages_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->ClearPages();
	return Gurax::Value::nil();
}

// wx.RibbonBar#IsPageShown(page as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, IsPageShown_gurax, "IsPageShown")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, IsPageShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsPageShown(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#ShowPage(page as Number, show_tab? as Bool)
Gurax_DeclareMethodAlias(wxRibbonBar, ShowPage_gurax, "ShowPage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("show_tab", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, ShowPage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	bool show_tab = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->ShowPage(page, show_tab);
	return Gurax::Value::nil();
}

// wx.RibbonBar#HidePage(page as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, HidePage_gurax, "HidePage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, HidePage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->HidePage(page);
	return Gurax::Value::nil();
}

// wx.RibbonBar#IsPageHighlighted(page as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, IsPageHighlighted_gurax, "IsPageHighlighted")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, IsPageHighlighted_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	bool rtn = pEntity_gurax->IsPageHighlighted(page);
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#AddPageHighlight(page as Number, highlight? as Bool)
Gurax_DeclareMethodAlias(wxRibbonBar, AddPageHighlight_gurax, "AddPageHighlight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("highlight", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, AddPageHighlight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	bool highlight = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->AddPageHighlight(page, highlight);
	return Gurax::Value::nil();
}

// wx.RibbonBar#RemovePageHighlight(page as Number)
Gurax_DeclareMethodAlias(wxRibbonBar, RemovePageHighlight_gurax, "RemovePageHighlight")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("page", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, RemovePageHighlight_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	size_t page = args_gurax.PickNumber<size_t>();
	// Function body
	pEntity_gurax->RemovePageHighlight(page);
	return Gurax::Value::nil();
}

// wx.RibbonBar#ShowPanels(show? as Bool)
Gurax_DeclareMethodAlias(wxRibbonBar, ShowPanels_gurax, "ShowPanels")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, ShowPanels_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->ShowPanels(show);
	return Gurax::Value::nil();
}

// wx.RibbonBar#HidePanels()
Gurax_DeclareMethodAlias(wxRibbonBar, HidePanels_gurax, "HidePanels")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, HidePanels_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->HidePanels();
	return Gurax::Value::nil();
}

// wx.RibbonBar#ArePanelsShown()
Gurax_DeclareMethodAlias(wxRibbonBar, ArePanelsShown_gurax, "ArePanelsShown")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, ArePanelsShown_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->ArePanelsShown();
	return new Gurax::Value_Bool(rtn);
}

// wx.RibbonBar#Realize()
Gurax_DeclareMethodAlias(wxRibbonBar, Realize_gurax, "Realize")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRibbonBar, Realize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Realize();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRibbonBar
//------------------------------------------------------------------------------
VType_wxRibbonBar VTYPE_wxRibbonBar("RibbonBar");

void VType_wxRibbonBar::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxRibbonControl, Flag::Mutable, Gurax_CreateConstructor(RibbonBar_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRibbonBar, Create_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, SetTabCtrlMargins_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, SetArtProvider_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, SetActivePage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, GetActivePage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, GetPage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, GetPageCount_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, DismissExpandedPanel_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, GetPageNumber_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, DeletePage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, ClearPages_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, IsPageShown_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, ShowPage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, HidePage_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, IsPageHighlighted_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, AddPageHighlight_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, RemovePageHighlight_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, ShowPanels_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, HidePanels_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, ArePanelsShown_gurax));
	Assign(Gurax_CreateMethod(wxRibbonBar, Realize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRibbonBar
//------------------------------------------------------------------------------
VType& Value_wxRibbonBar::vtype = VTYPE_wxRibbonBar;

String Value_wxRibbonBar::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RibbonBar");
}

//------------------------------------------------------------------------------
// Value_wxRibbonBar::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
