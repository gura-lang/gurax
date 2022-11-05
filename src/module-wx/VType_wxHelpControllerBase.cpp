//==============================================================================
// VType_wxHelpControllerBase.cpp
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

${help.ComposePropertyHelp(wxHelpControllerBase, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxHelpControllerBase, `en)}

${help.ComposeMethodHelp(wxHelpControllerBase, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.HelpControllerBase#DisplayBlock(blockNo as Number)
Gurax_DeclareMethodAlias(wxHelpControllerBase, DisplayBlock_gurax, "DisplayBlock")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("blockNo", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, DisplayBlock_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	long blockNo = args_gurax.PickNumber<long>();
	// Function body
	bool rtn = pEntity_gurax->DisplayBlock(blockNo);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#DisplayContents()
Gurax_DeclareMethodAlias(wxHelpControllerBase, DisplayContents_gurax, "DisplayContents")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, DisplayContents_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DisplayContents();
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#DisplayContextPopup(contextId as Number)
Gurax_DeclareMethodAlias(wxHelpControllerBase, DisplayContextPopup_gurax, "DisplayContextPopup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("contextId", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, DisplayContextPopup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int contextId = args_gurax.PickNumber<int>();
	// Function body
	bool rtn = pEntity_gurax->DisplayContextPopup(contextId);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#DisplaySection(section as String)
Gurax_DeclareMethodAlias(wxHelpControllerBase, DisplaySection_gurax, "DisplaySection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("section", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, DisplaySection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* section = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->DisplaySection(section);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#DisplayTextPopup(text as String, pos as wx.Point)
Gurax_DeclareMethodAlias(wxHelpControllerBase, DisplayTextPopup_gurax, "DisplayTextPopup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("text", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, DisplayTextPopup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* text = args_gurax.PickString();
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->DisplayTextPopup(text, pos);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#GetParentWindow() {block?}
Gurax_DeclareMethodAlias(wxHelpControllerBase, GetParentWindow_gurax, "GetParentWindow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, GetParentWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetParentWindow()));
}

// wx.HelpControllerBase#KeywordSearch(keyWord as String, mode? as Number)
Gurax_DeclareMethodAlias(wxHelpControllerBase, KeywordSearch_gurax, "KeywordSearch")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("keyWord", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, KeywordSearch_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* keyWord = args_gurax.PickString();
	bool mode_validFlag = args_gurax.IsValid();
	wxHelpSearchMode mode = mode_validFlag? args_gurax.PickNumber<wxHelpSearchMode>() : wxHELP_SEARCH_ALL;
	// Function body
	bool rtn = pEntity_gurax->KeywordSearch(keyWord, mode);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#LoadFile(file? as String)
Gurax_DeclareMethodAlias(wxHelpControllerBase, LoadFile_gurax, "LoadFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, LoadFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	bool rtn = pEntity_gurax->LoadFile(file);
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#OnQuit()
Gurax_DeclareMethodAlias(wxHelpControllerBase, OnQuit_gurax, "OnQuit")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, OnQuit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnQuit();
	return Gurax::Value::nil();
}

// wx.HelpControllerBase#Quit()
Gurax_DeclareMethodAlias(wxHelpControllerBase, Quit_gurax, "Quit")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, Quit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Quit();
	return new Gurax::Value_Bool(rtn);
}

// wx.HelpControllerBase#SetFrameParameters(titleFormat as String, size as wx.Size, pos? as wx.Point, newFrameEachTime? as Bool)
Gurax_DeclareMethodAlias(wxHelpControllerBase, SetFrameParameters_gurax, "SetFrameParameters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("titleFormat", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("newFrameEachTime", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, SetFrameParameters_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* titleFormat = args_gurax.PickString();
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	bool newFrameEachTime = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	pEntity_gurax->SetFrameParameters(titleFormat, size, pos, newFrameEachTime);
	return Gurax::Value::nil();
}

// wx.HelpControllerBase#SetParentWindow(parentWindow as wx.Window)
Gurax_DeclareMethodAlias(wxHelpControllerBase, SetParentWindow_gurax, "SetParentWindow")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("parentWindow", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, SetParentWindow_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parentWindow = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parentWindow = value_parentWindow.GetEntityPtr();
	// Function body
	pEntity_gurax->SetParentWindow(parentWindow);
	return Gurax::Value::nil();
}

// wx.HelpControllerBase#SetViewer(viewer as String, flags? as Number)
Gurax_DeclareMethodAlias(wxHelpControllerBase, SetViewer_gurax, "SetViewer")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("viewer", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, SetViewer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* viewer = args_gurax.PickString();
	bool flags_validFlag = args_gurax.IsValid();
	long flags = flags_validFlag? args_gurax.PickNumber<long>() : wxHELP_NETSCAPE;
	// Function body
	pEntity_gurax->SetViewer(viewer, flags);
	return Gurax::Value::nil();
}

// wx.HelpControllerBase#Initialize(file as String)
Gurax_DeclareMethodAlias(wxHelpControllerBase, Initialize_gurax, "Initialize")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxHelpControllerBase, Initialize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* file = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->Initialize(file);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxHelpControllerBase
//------------------------------------------------------------------------------
VType_wxHelpControllerBase VTYPE_wxHelpControllerBase("HelpControllerBase");

void VType_wxHelpControllerBase::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxHelpControllerBase, DisplayBlock_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, DisplayContents_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, DisplayContextPopup_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, DisplaySection_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, DisplayTextPopup_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, GetParentWindow_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, KeywordSearch_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, LoadFile_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, OnQuit_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, Quit_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, SetFrameParameters_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, SetParentWindow_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, SetViewer_gurax));
	Assign(Gurax_CreateMethod(wxHelpControllerBase, Initialize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxHelpControllerBase
//------------------------------------------------------------------------------
VType& Value_wxHelpControllerBase::vtype = VTYPE_wxHelpControllerBase;

String Value_wxHelpControllerBase::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.HelpControllerBase");
}

Gurax_EndModuleScope(wx)
