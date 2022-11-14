﻿//==============================================================================
// VType_wxFileConfig.cpp
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

${help.ComposePropertyHelp(wx.FileConfig, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.FileConfig, `en)}

${help.ComposeMethodHelp(wx.FileConfig, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.FileConfig#SetUmask(mode as Number)
Gurax_DeclareMethodAlias(wxFileConfig, SetUmask_gurax, "SetUmask")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, SetUmask_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int mode = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetUmask(mode);
	return Gurax::Value::nil();
}

// wx.FileConfig#SetPath(strPath as String)
Gurax_DeclareMethodAlias(wxFileConfig, SetPath_gurax, "SetPath")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("strPath", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, SetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* strPath = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetPath(strPath);
	return Gurax::Value::nil();
}

// wx.FileConfig#GetPath()
Gurax_DeclareMethodAlias(wxFileConfig, GetPath_gurax, "GetPath")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, GetPath_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetPath();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileConfig#GetNumberOfEntries(bRecursive? as Bool)
Gurax_DeclareMethodAlias(wxFileConfig, GetNumberOfEntries_gurax, "GetNumberOfEntries")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bRecursive", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, GetNumberOfEntries_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool bRecursive = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	size_t rtn = pEntity_gurax->GetNumberOfEntries(bRecursive);
	return new Gurax::Value_Number(rtn);
}

// wx.FileConfig#GetNumberOfGroups(bRecursive? as Bool)
Gurax_DeclareMethodAlias(wxFileConfig, GetNumberOfGroups_gurax, "GetNumberOfGroups")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("bRecursive", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, GetNumberOfGroups_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool bRecursive = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	size_t rtn = pEntity_gurax->GetNumberOfGroups(bRecursive);
	return new Gurax::Value_Number(rtn);
}

// wx.FileConfig#HasGroup(strName as String)
Gurax_DeclareMethodAlias(wxFileConfig, HasGroup_gurax, "HasGroup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("strName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, HasGroup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* strName = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->HasGroup(strName);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#HasEntry(strName as String)
Gurax_DeclareMethodAlias(wxFileConfig, HasEntry_gurax, "HasEntry")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("strName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, HasEntry_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* strName = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->HasEntry(strName);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#Flush(bCurrentOnly? as Bool)
Gurax_DeclareMethodAlias(wxFileConfig, Flush_gurax, "Flush")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("bCurrentOnly", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, Flush_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool bCurrentOnly = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->Flush(bCurrentOnly);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#RenameEntry(oldName as String, newName as String)
Gurax_DeclareMethodAlias(wxFileConfig, RenameEntry_gurax, "RenameEntry")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("oldName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("newName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, RenameEntry_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* oldName = args_gurax.PickString();
	const char* newName = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->RenameEntry(oldName, newName);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#RenameGroup(oldName as String, newName as String)
Gurax_DeclareMethodAlias(wxFileConfig, RenameGroup_gurax, "RenameGroup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("oldName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("newName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, RenameGroup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* oldName = args_gurax.PickString();
	const char* newName = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->RenameGroup(oldName, newName);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#DeleteEntry(key as String, bGroupIfEmptyAlso? as Bool)
Gurax_DeclareMethodAlias(wxFileConfig, DeleteEntry_gurax, "DeleteEntry")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("key", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bGroupIfEmptyAlso", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, DeleteEntry_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* key = args_gurax.PickString();
	bool bGroupIfEmptyAlso = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	bool rtn = pEntity_gurax->DeleteEntry(key, bGroupIfEmptyAlso);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#DeleteGroup(szKey as String)
Gurax_DeclareMethodAlias(wxFileConfig, DeleteGroup_gurax, "DeleteGroup")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("szKey", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, DeleteGroup_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* szKey = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->DeleteGroup(szKey);
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig#DeleteAll()
Gurax_DeclareMethodAlias(wxFileConfig, DeleteAll_gurax, "DeleteAll")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementMethodEx(wxFileConfig, DeleteAll_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->DeleteAll();
	return new Gurax::Value_Bool(rtn);
}

// wx.FileConfig.GetGlobalFile(basename as String) {block?}
Gurax_DeclareClassMethodAlias(wxFileConfig, GetGlobalFile_gurax, "GetGlobalFile")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareArg("basename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementClassMethodEx(wxFileConfig, GetGlobalFile_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* basename = args_gurax.PickString();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		wxFileConfig::GetGlobalFile(basename)));
}

// wx.FileConfig.GetLocalFile(basename as String, style? as Number) {block?}
Gurax_DeclareClassMethodAlias(wxFileConfig, GetLocalFile_gurax, "GetLocalFile")
{
	Declare(VTYPE_wxFileName, Flag::None);
	DeclareArg("basename", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementClassMethodEx(wxFileConfig, GetLocalFile_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* basename = args_gurax.PickString();
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxFileName(
		wxFileConfig::GetLocalFile(basename, style)));
}

// wx.FileConfig.GetGlobalFileName(szFile as String)
Gurax_DeclareClassMethodAlias(wxFileConfig, GetGlobalFileName_gurax, "GetGlobalFileName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("szFile", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementClassMethodEx(wxFileConfig, GetGlobalFileName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* szFile = args_gurax.PickString();
	// Function body
	wxString rtn = wxFileConfig::GetGlobalFileName(szFile);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.FileConfig.GetLocalFileName(szFile as String, style? as Number)
Gurax_DeclareClassMethodAlias(wxFileConfig, GetLocalFileName_gurax, "GetLocalFileName")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("szFile", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
)**");
}

Gurax_ImplementClassMethodEx(wxFileConfig, GetLocalFileName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* szFile = args_gurax.PickString();
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : 0;
	// Function body
	wxString rtn = wxFileConfig::GetLocalFileName(szFile, style);
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxFileConfig
//------------------------------------------------------------------------------
VType_wxFileConfig VTYPE_wxFileConfig("FileConfig");

void VType_wxFileConfig::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxConfigBase, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxFileConfig, SetUmask_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, SetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetPath_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetNumberOfEntries_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetNumberOfGroups_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, HasGroup_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, HasEntry_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, Flush_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, RenameEntry_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, RenameGroup_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, DeleteEntry_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, DeleteGroup_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, DeleteAll_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetGlobalFile_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetLocalFile_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetGlobalFileName_gurax));
	Assign(Gurax_CreateMethod(wxFileConfig, GetLocalFileName_gurax));
}

//------------------------------------------------------------------------------
// Value_wxFileConfig
//------------------------------------------------------------------------------
VType& Value_wxFileConfig::vtype = VTYPE_wxFileConfig;

String Value_wxFileConfig::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.FileConfig");
}

Gurax_EndModuleScope(wx)
