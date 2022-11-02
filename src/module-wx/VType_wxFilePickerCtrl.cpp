//==============================================================================
// VType_wxFilePickerCtrl.cpp
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

${help.ComposePropertyHelp(wxFilePickerCtrl)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxFilePickerCtrl)}

${help.ComposeMethodHelp(wxFilePickerCtrl)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.FilePickerCtrl(parent as wx.Window, id as Number, path? as String, message? as String, wildcard? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(FilePickerCtrl_gurax, "FilePickerCtrl")
{
	Declare(VTYPE_wxFilePickerCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildcard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.FilePickerCtrl.");
}

Gurax_ImplementConstructorEx(FilePickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* path = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* message = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorPromptStr;
	const char* wildcard = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorDefaultWildcardStr;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFLP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFilePickerCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxFilePickerCtrl::EntityT(parent, id, path, message, wildcard, pos, size, style, validator, name);
	RefPtr<Value_wxFilePickerCtrl> pValue_gurax(new Value_wxFilePickerCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FilePickerCtrl#Create(parent as wx.Window, id as Number, path? as String, message? as String, wildcard? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxFilePickerCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("wildcard", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	const char* path = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* message = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorPromptStr;
	const char* wildcard = args_gurax.IsValid()? args_gurax.PickString() : wxFileSelectorDefaultWildcardStr;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxFLP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxFilePickerCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, path, message, wildcard, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.FilePickerCtrl#GetFileName() {block?}
Gurax_DeclareMethodAlias(wxFilePickerCtrl, GetFileName_gurax, "GetFileName")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, GetFileName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		pEntity_gurax->GetFileName()));
}

// wx.FilePickerCtrl#GetPath()
Gurax_DeclareMethodAlias(wxFilePickerCtrl, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FilePickerCtrl#SetFileName(filename as wx.FileName)
Gurax_DeclareMethodAlias(wxFilePickerCtrl, SetFileName_gurax, "SetFileName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filename", VTYPE_wxFileName, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, SetFileName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFileName& value_filename = args_gurax.Pick<Value_wxFileName>();
	const wxFileName& filename = value_filename.GetEntity();
	// Function body
	pEntity_gurax->SetFileName(filename);
	return Gurax::Value::nil();
}

// wx.FilePickerCtrl#SetInitialDirectory(dir as String)
Gurax_DeclareMethodAlias(wxFilePickerCtrl, SetInitialDirectory_gurax, "SetInitialDirectory")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dir", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, SetInitialDirectory_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* dir = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetInitialDirectory(dir);
	return Gurax::Value::nil();
}

// wx.FilePickerCtrl#SetPath(filename as String)
Gurax_DeclareMethodAlias(wxFilePickerCtrl, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxFilePickerCtrl, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetPath(filename);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFilePickerCtrl
//------------------------------------------------------------------------------
VType_wxFilePickerCtrl VTYPE_wxFilePickerCtrl("FilePickerCtrl");

void VType_wxFilePickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable, Gurax_CreateConstructor(FilePickerCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, GetFileName_gurax));
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, SetFileName_gurax));
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, SetInitialDirectory_gurax));
	Assign(Gurax_CreateMethod(wxFilePickerCtrl, SetPath_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFilePickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxFilePickerCtrl::vtype = VTYPE_wxFilePickerCtrl;

String Value_wxFilePickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FilePickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxFilePickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
