﻿//==============================================================================
// VType_wxAnimationCtrl.cpp
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

${help.ComposePropertyHelp(wx.AnimationCtrl, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AnimationCtrl, `en)}

${help.ComposeMethodHelp(wx.AnimationCtrl, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.AnimationCtrl, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.AnimationCtrl, `ja)}

${help.ComposeMethodHelp(wx.AnimationCtrl, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AnimationCtrl(parent as wx.Window, id as Number, anim? as wx.Animation, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(AnimationCtrl_gurax, "AnimationCtrl")
{
	Declare(VTYPE_wxAnimationCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("anim", VTYPE_wxAnimation, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(AnimationCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxAnimation& anim = args_gurax.IsValid()? args_gurax.Pick<Value_wxAnimation>().GetEntity() : wxNullAnimation;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxAC_DEFAULT_STYLE;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxAnimationCtrlNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxAnimationCtrl::EntityT(parent, id, anim, pos, size, style, name);
	RefPtr<Value_wxAnimationCtrl> pValue_gurax(new Value_wxAnimationCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AnimationCtrl#Create(parent as wx.Window, id as Number, anim? as wx.Animation, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxAnimationCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("anim", VTYPE_wxAnimation, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	const wxAnimation& anim = args_gurax.IsValid()? args_gurax.Pick<Value_wxAnimation>().GetEntity() : wxNullAnimation;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxAC_DEFAULT_STYLE;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxAnimationCtrlNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, anim, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.AnimationCtrl#GetAnimation() {block?}
Gurax_DeclareMethodAlias(wxAnimationCtrl, GetAnimation_gurax, "GetAnimation")
{
	Declare(VTYPE_wxAnimation, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, GetAnimation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAnimation(pEntity_gurax->GetAnimation()));
}

// wx.AnimationCtrl#GetInactiveBitmap() {block?}
Gurax_DeclareMethodAlias(wxAnimationCtrl, GetInactiveBitmap_gurax, "GetInactiveBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, GetInactiveBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(pEntity_gurax->GetInactiveBitmap()));
}

// wx.AnimationCtrl#IsPlaying()
Gurax_DeclareMethodAlias(wxAnimationCtrl, IsPlaying_gurax, "IsPlaying")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, IsPlaying_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsPlaying();
	return new Gurax::Value_Bool(rtn);
}

// wx.AnimationCtrl#LoadFile(file as String, animType? as Number)
Gurax_DeclareMethodAlias(wxAnimationCtrl, LoadFile_gurax, "LoadFile")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("file", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("animType", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, LoadFile_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString file(args_gurax.PickString());
	bool animType_validFlag = args_gurax.IsValid();
	wxAnimationType animType = animType_validFlag? args_gurax.PickNumber<wxAnimationType>() : wxANIMATION_TYPE_ANY;
	// Function body
	bool rtn = pEntity_gurax->LoadFile(file, animType);
	return new Gurax::Value_Bool(rtn);
}

// wx.AnimationCtrl#Load(file as wx.InputStream, animType? as Number)
Gurax_DeclareMethodAlias(wxAnimationCtrl, Load_gurax, "Load")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("file", VTYPE_wxInputStream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("animType", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, Load_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxInputStream& value_file = args_gurax.Pick<Value_wxInputStream>();
	wxInputStream& file = value_file.GetEntity();
	bool animType_validFlag = args_gurax.IsValid();
	wxAnimationType animType = animType_validFlag? args_gurax.PickNumber<wxAnimationType>() : wxANIMATION_TYPE_ANY;
	// Function body
	bool rtn = pEntity_gurax->Load(file, animType);
	return new Gurax::Value_Bool(rtn);
}

// wx.AnimationCtrl#Play()
Gurax_DeclareMethodAlias(wxAnimationCtrl, Play_gurax, "Play")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, Play_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->Play();
	return new Gurax::Value_Bool(rtn);
}

// wx.AnimationCtrl#SetAnimation(anim as wx.Animation)
Gurax_DeclareMethodAlias(wxAnimationCtrl, SetAnimation_gurax, "SetAnimation")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("anim", VTYPE_wxAnimation, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, SetAnimation_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAnimation& value_anim = args_gurax.Pick<Value_wxAnimation>();
	const wxAnimation& anim = value_anim.GetEntity();
	// Function body
	pEntity_gurax->SetAnimation(anim);
	return Gurax::Value::nil();
}

// wx.AnimationCtrl#SetInactiveBitmap(bmp as wx.Bitmap)
Gurax_DeclareMethodAlias(wxAnimationCtrl, SetInactiveBitmap_gurax, "SetInactiveBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("bmp", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, SetInactiveBitmap_gurax, processor_gurax, argument_gurax)
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
	pEntity_gurax->SetInactiveBitmap(bmp);
	return Gurax::Value::nil();
}

// wx.AnimationCtrl#Stop()
Gurax_DeclareMethodAlias(wxAnimationCtrl, Stop_gurax, "Stop")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxAnimationCtrl, Stop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Stop();
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAnimationCtrl
//------------------------------------------------------------------------------
VType_wxAnimationCtrl VTYPE_wxAnimationCtrl("AnimationCtrl");

void VType_wxAnimationCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(AnimationCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAnimationCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, GetAnimation_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, GetInactiveBitmap_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, IsPlaying_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, LoadFile_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, Load_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, Play_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, SetAnimation_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, SetInactiveBitmap_gurax));
	Assign(Gurax_CreateMethod(wxAnimationCtrl, Stop_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAnimationCtrl
//------------------------------------------------------------------------------
VType& Value_wxAnimationCtrl::vtype = VTYPE_wxAnimationCtrl;

String Value_wxAnimationCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AnimationCtrl");
}

//------------------------------------------------------------------------------
// Value_wxAnimationCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
