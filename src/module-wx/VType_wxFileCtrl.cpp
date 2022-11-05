//==============================================================================
// VType_wxFileCtrl.cpp
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

${help.ComposePropertyHelp(wxFileCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxFileCtrl, `en)}

${help.ComposeMethodHelp(wxFileCtrl, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FileCtrl(parent as wx.Window, id as Number, defaultDirectory? as String, defaultFilename? as String, wildCard? as String, style? as Number, pos? as wx.Point, size? as wx.Size, name? as String) {block?}
Gurax_DeclareConstructorAlias(FileCtrl_gurax, "FileCtrl")
{
	Declare(VTYPE_wxFileCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defaultDirectory", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultFilename", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildCard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.FileCtrl.");
}

Gurax_ImplementConstructorEx(FileCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* defaultDirectory = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* defaultFilename = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* wildCard = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorDefaultWildcardStr;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFC_DEFAULT_STYLE;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFileCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFileCtrl::EntityT(parent, id, defaultDirectory, defaultFilename, wildCard, style, pos, size, name);
	RefPtr<Value_wxFileCtrl> pValue_gurax(new Value_wxFileCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FileCtrl#Create(parent as wx.Window, id as Number, defaultDirectory? as String, defaultFilename? as String, wildCard? as String, style? as Number, pos? as wx.Point, size? as wx.Size, name? as String)
Gurax_DeclareMethodAlias(wxFileCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defaultDirectory", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultFilename", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildCard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* defaultDirectory = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* defaultFilename = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* wildCard = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorDefaultWildcardStr;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFC_DEFAULT_STYLE;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFileCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, defaultDirectory, defaultFilename, wildCard, style, pos, size, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileCtrl#GetDirectory()
Gurax_DeclareMethodAlias(wxFileCtrl, GetDirectory_gurax, "GetDirectory")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, GetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDirectory();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileCtrl#GetFilename()
Gurax_DeclareMethodAlias(wxFileCtrl, GetFilename_gurax, "GetFilename")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, GetFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFilename();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileCtrl#GetFilterIndex()
Gurax_DeclareMethodAlias(wxFileCtrl, GetFilterIndex_gurax, "GetFilterIndex")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, GetFilterIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFilterIndex();
	return new Gurax::Value_Number(rtn);
}

// wx.FileCtrl#GetPath()
Gurax_DeclareMethodAlias(wxFileCtrl, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileCtrl#GetWildcard()
Gurax_DeclareMethodAlias(wxFileCtrl, GetWildcard_gurax, "GetWildcard")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, GetWildcard_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetWildcard();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileCtrl#SetDirectory(directory as String)
Gurax_DeclareMethodAlias(wxFileCtrl, SetDirectory_gurax, "SetDirectory")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("directory", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, SetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* directory = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetDirectory(directory);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileCtrl#SetFilename(filename as String)
Gurax_DeclareMethodAlias(wxFileCtrl, SetFilename_gurax, "SetFilename")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, SetFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetFilename(filename);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileCtrl#SetPath(path as String)
Gurax_DeclareMethodAlias(wxFileCtrl, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* path = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetPath(path);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileCtrl#SetFilterIndex(filterIndex as Number)
Gurax_DeclareMethodAlias(wxFileCtrl, SetFilterIndex_gurax, "SetFilterIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filterIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, SetFilterIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int filterIndex = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetFilterIndex(filterIndex);
	return Gurax::Value::nil();
}

// wx.FileCtrl#SetWildcard(wildCard as String)
Gurax_DeclareMethodAlias(wxFileCtrl, SetWildcard_gurax, "SetWildcard")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("wildCard", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, SetWildcard_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* wildCard = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetWildcard(wildCard);
	return Gurax::Value::nil();
}

// wx.FileCtrl#ShowHidden(show as Bool)
Gurax_DeclareMethodAlias(wxFileCtrl, ShowHidden_gurax, "ShowHidden")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileCtrl, ShowHidden_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.PickBool();
	// Function body
	pEntity_gurax->ShowHidden(show);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFileCtrl
//------------------------------------------------------------------------------
VType_wxFileCtrl VTYPE_wxFileCtrl("FileCtrl");

void VType_wxFileCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(FileCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFileCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, GetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, GetFilename_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, GetFilterIndex_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, GetWildcard_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, SetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, SetFilename_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, SetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, SetFilterIndex_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, SetWildcard_gurax));
	Assign(Gurax_CreateMethod(wxFileCtrl, ShowHidden_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFileCtrl
//------------------------------------------------------------------------------
VType& Value_wxFileCtrl::vtype = VTYPE_wxFileCtrl;

String Value_wxFileCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileCtrl");
}

//------------------------------------------------------------------------------
// Value_wxFileCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
