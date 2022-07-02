//==============================================================================
// VType_wxFileDialog.cpp
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
// wx.FileDialog(parent as wx.Window, message? as String, defaultDir? as String, defaultFile? as String, wildcard? as String, style? as Number, pos? as wx.Point, size? as wx.Size, name? as String) {block?}
Gurax_DeclareConstructorAlias(FileDialog_gurax, "FileDialog")
{
	Declare(VTYPE_wxFileDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultDir", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("defaultFile", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildcard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.FileDialog.");
}

Gurax_ImplementConstructorEx(FileDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* message = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorPromptStr;
	const char* defaultDir = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* defaultFile = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* wildcard = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorDefaultWildcardStr;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFD_DEFAULT_STYLE;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFileDialogNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFileDialog::EntityT(parent, message, defaultDir, defaultFile, wildcard, style, pos, size, name);
	RefPtr<Value_wxFileDialog> pValue_gurax(new Value_wxFileDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FileDialog#GetCurrentlySelectedFilename()
Gurax_DeclareMethodAlias(wxFileDialog, GetCurrentlySelectedFilename_gurax, "GetCurrentlySelectedFilename")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetCurrentlySelectedFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetCurrentlySelectedFilename();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#GetDirectory()
Gurax_DeclareMethodAlias(wxFileDialog, GetDirectory_gurax, "GetDirectory")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDirectory();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#GetExtraControl() {block?}
Gurax_DeclareMethodAlias(wxFileDialog, GetExtraControl_gurax, "GetExtraControl")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetExtraControl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetExtraControl()));
}

// wx.FileDialog#GetFilename()
Gurax_DeclareMethodAlias(wxFileDialog, GetFilename_gurax, "GetFilename")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetFilename();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#GetFilterIndex()
Gurax_DeclareMethodAlias(wxFileDialog, GetFilterIndex_gurax, "GetFilterIndex")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetFilterIndex_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFilterIndex();
	return new Gurax::Value_Number(rtn);
}

// wx.FileDialog#GetMessage()
Gurax_DeclareMethodAlias(wxFileDialog, GetMessage_gurax, "GetMessage")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetMessage();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#GetPath()
Gurax_DeclareMethodAlias(wxFileDialog, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#GetPaths()
Gurax_DeclareMethodAlias(wxFileDialog, GetPaths_gurax, "GetPaths")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetPaths_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayString paths;
	pEntity_gurax->GetPaths(paths);
	return Util::CreateList(paths);
}

// wx.FileDialog#GetWildcard()
Gurax_DeclareMethodAlias(wxFileDialog, GetWildcard_gurax, "GetWildcard")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, GetWildcard_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetWildcard();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileDialog#SetDirectory(directory as String)
Gurax_DeclareMethodAlias(wxFileDialog, SetDirectory_gurax, "SetDirectory")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("directory", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* directory = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetDirectory(directory);
	return Gurax::Value::nil();
}

// wx.FileDialog#SetFilename(setfilename as String)
Gurax_DeclareMethodAlias(wxFileDialog, SetFilename_gurax, "SetFilename")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("setfilename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetFilename_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* setfilename = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetFilename(setfilename);
	return Gurax::Value::nil();
}

// wx.FileDialog#SetFilterIndex(filterIndex as Number)
Gurax_DeclareMethodAlias(wxFileDialog, SetFilterIndex_gurax, "SetFilterIndex")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filterIndex", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetFilterIndex_gurax, processor_gurax, argument_gurax)
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

// wx.FileDialog#SetMessage(message as String)
Gurax_DeclareMethodAlias(wxFileDialog, SetMessage_gurax, "SetMessage")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetMessage_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* message = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetMessage(message);
	return Gurax::Value::nil();
}

// wx.FileDialog#SetPath(path as String)
Gurax_DeclareMethodAlias(wxFileDialog, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* path = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetPath(path);
	return Gurax::Value::nil();
}

// wx.FileDialog#SetWildcard(wildCard as String)
Gurax_DeclareMethodAlias(wxFileDialog, SetWildcard_gurax, "SetWildcard")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("wildCard", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, SetWildcard_gurax, processor_gurax, argument_gurax)
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

// wx.FileDialog#ShowModal()
Gurax_DeclareMethodAlias(wxFileDialog, ShowModal_gurax, "ShowModal")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFileDialog, ShowModal_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->ShowModal();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFileDialog
//------------------------------------------------------------------------------
VType_wxFileDialog VTYPE_wxFileDialog("FileDialog");

void VType_wxFileDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(FileDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFileDialog, GetCurrentlySelectedFilename_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetExtraControl_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetFilename_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetFilterIndex_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetMessage_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetPaths_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, GetWildcard_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetFilename_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetFilterIndex_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetMessage_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, SetWildcard_gurax));
	Assign(Gurax_CreateMethod(wxFileDialog, ShowModal_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFileDialog
//------------------------------------------------------------------------------
VType& Value_wxFileDialog::vtype = VTYPE_wxFileDialog;

String Value_wxFileDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileDialog");
}

//------------------------------------------------------------------------------
// Value_wxFileDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
