//==============================================================================
// VType_wxDirPickerCtrl.cpp
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
// wx.DirPickerCtrl(parent as wx.Window, id as Number, path? as String, message? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(DirPickerCtrl_gurax, "DirPickerCtrl")
{
	Declare(VTYPE_wxDirPickerCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.DirPickerCtrl.");
}

Gurax_ImplementConstructorEx(DirPickerCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* path = args_gurax.IsValid()? args_gurax.PickString() : "";
	const char* message = args_gurax.IsValid()? args_gurax.PickString() : wxDirSelectorPromptStr;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDIRP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxDirPickerCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxDirPickerCtrl::EntityT(parent, id, path, message, pos, size, style, validator, name);
	RefPtr<Value_wxDirPickerCtrl> pValue_gurax(new Value_wxDirPickerCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DirPickerCtrl#Create(parent as wx.Window, id as Number, path? as String, message? as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxDirPickerCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("path", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	const char* message = args_gurax.IsValid()? args_gurax.PickString() : wxDirSelectorPromptStr;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDIRP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxDirPickerCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, path, message, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.DirPickerCtrl#GetDirName() {block?}
Gurax_DeclareMethodAlias(wxDirPickerCtrl, GetDirName_gurax, "GetDirName")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, GetDirName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		pEntity_gurax->GetDirName()));
}

// wx.DirPickerCtrl#GetPath()
Gurax_DeclareMethodAlias(wxDirPickerCtrl, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.DirPickerCtrl#SetDirName(dirname as wx.FileName)
Gurax_DeclareMethodAlias(wxDirPickerCtrl, SetDirName_gurax, "SetDirName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dirname", VTYPE_wxFileName, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, SetDirName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxFileName& value_dirname = args_gurax.Pick<Value_wxFileName>();
	const wxFileName& dirname = value_dirname.GetEntity();
	// Function body
	pEntity_gurax->SetDirName(dirname);
	return Gurax::Value::nil();
}

// wx.DirPickerCtrl#SetInitialDirectory(dir as String)
Gurax_DeclareMethodAlias(wxDirPickerCtrl, SetInitialDirectory_gurax, "SetInitialDirectory")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dir", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, SetInitialDirectory_gurax, processor_gurax, argument_gurax)
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

// wx.DirPickerCtrl#SetPath(dirname as String)
Gurax_DeclareMethodAlias(wxDirPickerCtrl, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("dirname", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirPickerCtrl, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* dirname = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetPath(dirname);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDirPickerCtrl
//------------------------------------------------------------------------------
VType_wxDirPickerCtrl VTYPE_wxDirPickerCtrl("DirPickerCtrl");

void VType_wxDirPickerCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPickerBase, Flag::Mutable, Gurax_CreateConstructor(DirPickerCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, GetDirName_gurax));
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, SetDirName_gurax));
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, SetInitialDirectory_gurax));
	Assign(Gurax_CreateMethod(wxDirPickerCtrl, SetPath_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDirPickerCtrl
//------------------------------------------------------------------------------
VType& Value_wxDirPickerCtrl::vtype = VTYPE_wxDirPickerCtrl;

String Value_wxDirPickerCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DirPickerCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDirPickerCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
