﻿//==============================================================================
// VType_wxMediaCtrl.cpp
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

${help.ComposePropertyHelp(wx.MediaCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.MediaCtrl, `en)}

${help.ComposeMethodHelp(wx.MediaCtrl, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.MediaCtrl, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.MediaCtrl, `ja)}

${help.ComposeMethodHelp(wx.MediaCtrl, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.MediaCtrl(parent as wx.Window, id as Number, fileName? as String, pos? as wx.Point, size? as wx.Size, style? as Number, szBackend? as String, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(MediaCtrl_gurax, "MediaCtrl")
{
	Declare(VTYPE_wxMediaCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("szBackend", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(MediaCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	bool fileName_validFlag = args_gurax.IsValid();
	wxString fileName = fileName_validFlag? wxString(args_gurax.PickString()) : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	bool szBackend_validFlag = args_gurax.IsValid();
	wxString szBackend = szBackend_validFlag? wxString(args_gurax.PickString()) : "";
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : "mediaCtrl";
	// Function body
	auto pEntity_gurax = new Value_wxMediaCtrl::EntityT(parent, id, fileName, pos, size, style, szBackend, validator, name);
	RefPtr<Value_wxMediaCtrl> pValue_gurax(new Value_wxMediaCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.MediaCtrl#Create(parent as wx.Window, id as Number, fileName? as String, pos? as wx.Point, size? as wx.Size, style? as Number, szBackend? as String, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxMediaCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("szBackend", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	bool fileName_validFlag = args_gurax.IsValid();
	wxString fileName = fileName_validFlag? wxString(args_gurax.PickString()) : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	bool szBackend_validFlag = args_gurax.IsValid();
	wxString szBackend = szBackend_validFlag? wxString(args_gurax.PickString()) : "";
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : "mediaCtrl";
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, fileName, pos, size, style, szBackend, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#GetBestSize() {block?}
Gurax_DeclareMethodAlias(wxMediaCtrl, GetBestSize_gurax, "GetBestSize")
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxMediaCtrl, GetBestSize_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(pEntity_gurax->GetBestSize()));
}

// wx.MediaCtrl#GetPlaybackRate()
Gurax_DeclareMethodAlias(wxMediaCtrl, GetPlaybackRate_gurax, "GetPlaybackRate")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, GetPlaybackRate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetPlaybackRate();
	return new Gurax::Value_Number(rtn);
}

// wx.MediaCtrl#GetState()
Gurax_DeclareMethodAlias(wxMediaCtrl, GetState_gurax, "GetState")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, GetState_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxMediaState rtn = pEntity_gurax->GetState();
	return new Gurax::Value_Number(rtn);
}

// wx.MediaCtrl#GetVolume()
Gurax_DeclareMethodAlias(wxMediaCtrl, GetVolume_gurax, "GetVolume")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, GetVolume_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	double rtn = pEntity_gurax->GetVolume();
	return new Gurax::Value_Number(rtn);
}

// wx.MediaCtrl#Length()
Gurax_DeclareMethodAlias(wxMediaCtrl, Length_gurax, "Length")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Length_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFileOffset rtn = pEntity_gurax->Length();
	return new Gurax::Value_Number(rtn);
}

// wx.MediaCtrl#Load(fileName as String)
Gurax_DeclareMethodAlias(wxMediaCtrl, Load_gurax, "Load")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("fileName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Load_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString fileName(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->Load(fileName);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#LoadURI(uri as String)
Gurax_DeclareMethodAlias(wxMediaCtrl, LoadURI_gurax, "LoadURI")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("uri", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, LoadURI_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString uri(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->LoadURI(uri);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#LoadURIWithProxy(uri as String, proxy as String)
Gurax_DeclareMethodAlias(wxMediaCtrl, LoadURIWithProxy_gurax, "LoadURIWithProxy")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("uri", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("proxy", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, LoadURIWithProxy_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString uri(args_gurax.PickString());
	wxString proxy(args_gurax.PickString());
	// Function body
	bool rtn = pEntity_gurax->LoadURIWithProxy(uri, proxy);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#Pause()
Gurax_DeclareMethodAlias(wxMediaCtrl, Pause_gurax, "Pause")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Pause_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Pause();
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#Play()
Gurax_DeclareMethodAlias(wxMediaCtrl, Play_gurax, "Play")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Play_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Play();
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#Seek(where as Number, mode? as Number)
Gurax_DeclareMethodAlias(wxMediaCtrl, Seek_gurax, "Seek")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("where", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Seek_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxFileOffset where = args_gurax.PickNumber<wxFileOffset>();
	bool mode_validFlag = args_gurax.IsValid();
	wxSeekMode mode = mode_validFlag? args_gurax.PickNumber<wxSeekMode>() : wxFromStart;
	// Function body
	wxFileOffset rtn = pEntity_gurax->Seek(where, mode);
	return new Gurax::Value_Number(rtn);
}

// wx.MediaCtrl#SetPlaybackRate(dRate as Number)
Gurax_DeclareMethodAlias(wxMediaCtrl, SetPlaybackRate_gurax, "SetPlaybackRate")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("dRate", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, SetPlaybackRate_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double dRate = args_gurax.PickNumber<double>();
	// Function body
	bool rtn = pEntity_gurax->SetPlaybackRate(dRate);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#SetVolume(dVolume as Number)
Gurax_DeclareMethodAlias(wxMediaCtrl, SetVolume_gurax, "SetVolume")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("dVolume", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, SetVolume_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	double dVolume = args_gurax.PickNumber<double>();
	// Function body
	bool rtn = pEntity_gurax->SetVolume(dVolume);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#ShowPlayerControls(flags? as Number)
Gurax_DeclareMethodAlias(wxMediaCtrl, ShowPlayerControls_gurax, "ShowPlayerControls")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, ShowPlayerControls_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	wxMediaCtrlPlayerControls flags = flags_validFlag? args_gurax.PickNumber<wxMediaCtrlPlayerControls>() : wxMEDIACTRLPLAYERCONTROLS_DEFAULT;
	// Function body
	bool rtn = pEntity_gurax->ShowPlayerControls(flags);
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#Stop()
Gurax_DeclareMethodAlias(wxMediaCtrl, Stop_gurax, "Stop")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Stop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Stop();
	return new Gurax::Value_Bool(rtn);
}

// wx.MediaCtrl#Tell()
Gurax_DeclareMethodAlias(wxMediaCtrl, Tell_gurax, "Tell")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxMediaCtrl, Tell_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxFileOffset rtn = pEntity_gurax->Tell();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMediaCtrl
//------------------------------------------------------------------------------
VType_wxMediaCtrl VTYPE_wxMediaCtrl("MediaCtrl");

void VType_wxMediaCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(MediaCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxMediaCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, GetBestSize_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, GetPlaybackRate_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, GetState_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, GetVolume_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Length_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Load_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, LoadURI_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, LoadURIWithProxy_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Pause_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Play_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Seek_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, SetPlaybackRate_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, SetVolume_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, ShowPlayerControls_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Stop_gurax));
	Assign(Gurax_CreateMethod(wxMediaCtrl, Tell_gurax));
}

//------------------------------------------------------------------------------
// Value_wxMediaCtrl
//------------------------------------------------------------------------------
VType& Value_wxMediaCtrl::vtype = VTYPE_wxMediaCtrl;

String Value_wxMediaCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MediaCtrl");
}

//------------------------------------------------------------------------------
// Value_wxMediaCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
