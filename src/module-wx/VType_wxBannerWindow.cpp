//==============================================================================
// VType_wxBannerWindow.cpp
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
// wx.BannerWindow(args* as Any) {block?}
Gurax_DeclareConstructorAlias(BannerWindow_gurax, "BannerWindow")
{
	Declare(VTYPE_wxBannerWindow, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.BannerWindow.");
}

Gurax_ImplementConstructorEx(BannerWindow_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wxBannerWindow(parent as Window_p, dir as Direction = wxLEFT)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("parent", VTYPE_wxWindow);
			pDeclCallable->DeclareArg("dir", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxWindow* parent = args.Pick<Value_wxWindow>().GetEntityPtr();
		wxDirection dir = args.IsValid()? args.PickNumber<wxDirection>() : wxLEFT;
		return new Value_wxBannerWindow(new wxBannerWindow(parent, dir));
	} while (0);
	Error::ClearIssuedFlag();
	// wxBannerWindow(parent as Window_p, winid as WindowID, dir as Direction = wxLEFT, pos as const_Point_r = wxDefaultPosition, size as const_Size_r = wxDefaultSize, style as long = 0, name as const_String_r = wxBannerWindowNameStr)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("parent", VTYPE_wxWindow);
			pDeclCallable->DeclareArg("winid", VTYPE_Number);
			pDeclCallable->DeclareArg("dir", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("pos", VTYPE_wxPoint, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("size", VTYPE_wxSize, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("style", VTYPE_Number, DeclArg::Occur::ZeroOrOnce);
			pDeclCallable->DeclareArg("name", VTYPE_String, DeclArg::Occur::ZeroOrOnce);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		wxWindow* parent = args.Pick<Value_wxWindow>().GetEntityPtr();
		wxWindowID winid = args.PickNumber<wxWindowID>();
		wxDirection dir = args.IsValid()? args.PickNumber<wxDirection>() : wxLEFT;
		const wxPoint& pos = args.IsValid()? args.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
		const wxSize& size = args.IsValid()? args.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
		long style = args.IsValid()? args.PickNumber<long>() : 0;
		wxString name = args.IsValid()? args.PickString() : wxBannerWindowNameStr;
		return new Value_wxBannerWindow(new wxBannerWindow(parent, winid, dir, pos, size, style, name));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.BannerWindow#Create(parent as wx.Window, winid as Number, dir? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxBannerWindow, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("winid", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("dir", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBannerWindow, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID winid = args_gurax.PickNumber<wxWindowID>();
	bool dir_validFlag = args_gurax.IsValid();
	wxDirection dir = dir_validFlag? args_gurax.PickNumber<wxDirection>() : wxLEFT;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxBannerWindowNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, winid, dir, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.BannerWindow#SetBitmap(bmp as wx.Bitmap)
Gurax_DeclareMethodAlias(wxBannerWindow, SetBitmap_gurax, "SetBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBannerWindow, SetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_bmp = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& bmp = value_bmp.GetEntity();
	// Function body
	pEntity_gurax->SetBitmap(bmp);
	return Gurax::Value::nil();
}

// wx.BannerWindow#SetText(title as String, message as String)
Gurax_DeclareMethodAlias(wxBannerWindow, SetText_gurax, "SetText")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("title", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBannerWindow, SetText_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* title = args_gurax.PickString();
	const char* message = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetText(title, message);
	return Gurax::Value::nil();
}

// wx.BannerWindow#SetGradient(start as wx.Colour, end as wx.Colour)
Gurax_DeclareMethodAlias(wxBannerWindow, SetGradient_gurax, "SetGradient")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("start", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	DeclareArg("end", VTYPE_wxColour, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxBannerWindow, SetGradient_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxColour& value_start = args_gurax.Pick<Value_wxColour>();
	const wxColour& start = value_start.GetEntity();
	Value_wxColour& value_end = args_gurax.Pick<Value_wxColour>();
	const wxColour& end = value_end.GetEntity();
	// Function body
	pEntity_gurax->SetGradient(start, end);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxBannerWindow
//------------------------------------------------------------------------------
VType_wxBannerWindow VTYPE_wxBannerWindow("BannerWindow");

void VType_wxBannerWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(BannerWindow_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxBannerWindow, Create_gurax));
	Assign(Gurax_CreateMethod(wxBannerWindow, SetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxBannerWindow, SetText_gurax));
	Assign(Gurax_CreateMethod(wxBannerWindow, SetGradient_gurax));
}

//------------------------------------------------------------------------------
// Value_wxBannerWindow
//------------------------------------------------------------------------------
VType& Value_wxBannerWindow::vtype = VTYPE_wxBannerWindow;

String Value_wxBannerWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.BannerWindow");
}

//------------------------------------------------------------------------------
// Value_wxBannerWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
