﻿//==============================================================================
// VType_wxAboutDialogInfo.cpp
// Don't edit this file since it's been generated by Generate.gura.
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(wx.AboutDialogInfo, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AboutDialogInfo, `en)}

${help.ComposeMethodHelp(wx.AboutDialogInfo, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.AboutDialogInfo, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.AboutDialogInfo, `ja)}

${help.ComposeMethodHelp(wx.AboutDialogInfo, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AboutDialogInfo() {block?}
Gurax_DeclareConstructorAlias(AboutDialogInfo_gurax, "AboutDialogInfo")
{
	Declare(VTYPE_wxAboutDialogInfo, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(AboutDialogInfo_gurax, processor_gurax, argument_gurax)
{
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAboutDialogInfo(
		wxAboutDialogInfo()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AboutDialogInfo#AddArtist(artist as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, AddArtist_gurax, "AddArtist")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("artist", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds an artist name to be shown in the program credits.
)""");
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, AddArtist_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString artist(args_gurax.PickString());
	// Function body
	pEntity_gurax->AddArtist(artist);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#AddDeveloper(developer as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, AddDeveloper_gurax, "AddDeveloper")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("developer", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds a developer name to be shown in the program credits.
)""");
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, AddDeveloper_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString developer(args_gurax.PickString());
	// Function body
	pEntity_gurax->AddDeveloper(developer);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#AddDocWriter(docwriter as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, AddDocWriter_gurax, "AddDocWriter")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("docwriter", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds a documentation writer name to be shown in the program credits.
)""");
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, AddDocWriter_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString docwriter(args_gurax.PickString());
	// Function body
	pEntity_gurax->AddDocWriter(docwriter);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#AddTranslator(translator as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, AddTranslator_gurax, "AddTranslator")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("translator", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, AddTranslator_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString translator(args_gurax.PickString());
	// Function body
	pEntity_gurax->AddTranslator(translator);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#GetName()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetName_gurax, "GetName")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetName();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#HasDescription()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasDescription_gurax, "HasDescription")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasDescription();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#GetDescription()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetDescription_gurax, "GetDescription")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetDescription();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#HasCopyright()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasCopyright_gurax, "HasCopyright")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasCopyright_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasCopyright();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#GetCopyright()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetCopyright_gurax, "GetCopyright")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetCopyright_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetCopyright();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#SetArtists(artists[] as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetArtists_gurax, "SetArtists")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("artists", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetArtists_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString artists = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetArtists(artists);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetCopyright(copyright as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetCopyright_gurax, "SetCopyright")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("copyright", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetCopyright_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString copyright(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetCopyright(copyright);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetDescription(desc as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetDescription_gurax, "SetDescription")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("desc", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString desc(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetDescription(desc);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetDevelopers(developers[] as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetDevelopers_gurax, "SetDevelopers")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("developers", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetDevelopers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString developers = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetDevelopers(developers);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetDocWriters(docwriters[] as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetDocWriters_gurax, "SetDocWriters")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("docwriters", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetDocWriters_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString docwriters = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetDocWriters(docwriters);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#HasIcon()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasIcon_gurax, "HasIcon")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasIcon();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#GetIcon() {block?}
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIcon(pEntity_gurax->GetIcon()));
}

// wx.AboutDialogInfo#SetIcon(icon as wx.Icon)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetIcon_gurax, "SetIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("icon", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_icon = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& icon = value_icon.GetEntity();
	// Function body
	pEntity_gurax->SetIcon(icon);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#HasLicence()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasLicence_gurax, "HasLicence")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasLicence_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasLicence();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#GetLicence()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetLicence_gurax, "GetLicence")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetLicence_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLicence();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#SetLicence(licence as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetLicence_gurax, "SetLicence")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("licence", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetLicence_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString licence(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetLicence(licence);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetLicense(licence as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetLicense_gurax, "SetLicense")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("licence", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetLicense_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString licence(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetLicense(licence);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetName(name as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetName_gurax, "SetName")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetName_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString name(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetName(name);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetTranslators(translators[] as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetTranslators_gurax, "SetTranslators")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("translators", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetTranslators_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString translators = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetTranslators(translators);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#SetVersion(version as String, longVersion? as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetVersion_gurax, "SetVersion")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("version", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("longVersion", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetVersion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString version(args_gurax.PickString());
	bool longVersion_validFlag = args_gurax.IsValid();
	wxString longVersion = longVersion_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	pEntity_gurax->SetVersion(version, longVersion);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#GetVersion()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetVersion_gurax, "GetVersion")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetVersion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetVersion();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#GetLongVersion()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetLongVersion_gurax, "GetLongVersion")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetLongVersion_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetLongVersion();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#HasWebSite()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasWebSite_gurax, "HasWebSite")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasWebSite_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasWebSite();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#GetWebSiteURL()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetWebSiteURL_gurax, "GetWebSiteURL")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetWebSiteURL_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetWebSiteURL();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#GetWebSiteDescription()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, GetWebSiteDescription_gurax, "GetWebSiteDescription")
{
	Declare(VTYPE_String, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, GetWebSiteDescription_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->GetWebSiteDescription();
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.AboutDialogInfo#SetWebSite(url as String, desc? as String)
Gurax_DeclareMethodAlias(wxAboutDialogInfo, SetWebSite_gurax, "SetWebSite")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("url", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("desc", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, SetWebSite_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString url(args_gurax.PickString());
	bool desc_validFlag = args_gurax.IsValid();
	wxString desc = desc_validFlag? wxString(args_gurax.PickString()) : "";
	// Function body
	pEntity_gurax->SetWebSite(url, desc);
	return Gurax::Value::nil();
}

// wx.AboutDialogInfo#HasDevelopers()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasDevelopers_gurax, "HasDevelopers")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasDevelopers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasDevelopers();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#HasDocWriters()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasDocWriters_gurax, "HasDocWriters")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasDocWriters_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasDocWriters();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#HasArtists()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasArtists_gurax, "HasArtists")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasArtists_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasArtists();
	return new Gurax::Value_Bool(rtn);
}

// wx.AboutDialogInfo#HasTranslators()
Gurax_DeclareMethodAlias(wxAboutDialogInfo, HasTranslators_gurax, "HasTranslators")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAboutDialogInfo, HasTranslators_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasTranslators();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAboutDialogInfo
//------------------------------------------------------------------------------
VType_wxAboutDialogInfo VTYPE_wxAboutDialogInfo("AboutDialogInfo");

void VType_wxAboutDialogInfo::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(AboutDialogInfo_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, AddArtist_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, AddDeveloper_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, AddDocWriter_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, AddTranslator_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetName_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasDescription_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetDescription_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasCopyright_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetCopyright_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetArtists_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetCopyright_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetDescription_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetDevelopers_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetDocWriters_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasIcon_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetIcon_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasLicence_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetLicence_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetLicence_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetLicense_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetName_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetTranslators_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetVersion_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetVersion_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetLongVersion_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasWebSite_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetWebSiteURL_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, GetWebSiteDescription_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, SetWebSite_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasDevelopers_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasDocWriters_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasArtists_gurax));
	Assign(Gurax_CreateMethod(wxAboutDialogInfo, HasTranslators_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAboutDialogInfo
//------------------------------------------------------------------------------
VType& Value_wxAboutDialogInfo::vtype = VTYPE_wxAboutDialogInfo;

String Value_wxAboutDialogInfo::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AboutDialogInfo");
}

Gurax_EndModuleScope(wx)
