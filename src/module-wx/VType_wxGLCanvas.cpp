﻿//==============================================================================
// VType_wxGLCanvas.cpp
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

${help.ComposePropertyHelp(wx.GLCanvas, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GLCanvas, `en)}

${help.ComposeMethodHelp(wx.GLCanvas, `en)}
)**";

static const char* g_docHelp_ja = u8R"**(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GLCanvas, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GLCanvas, `ja)}

${help.ComposeMethodHelp(wx.GLCanvas, `ja)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GLCanvas(parent as wx.Window, id? as Number, attribList[]? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String, palette? as wx.Palette) {block?}
Gurax_DeclareConstructorAlias(GLCanvas_gurax, "GLCanvas")
{
	Declare(VTYPE_wxGLCanvas, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("attribList", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("palette", VTYPE_wxPalette, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(GLCanvas_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	auto attribList = args_gurax.PickNumList<int>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "GLCanvas";
	const wxPalette& palette = args_gurax.IsValid()? args_gurax.Pick<Value_wxPalette>().GetEntity() : wxNullPalette;
	// Function body
	auto pEntity_gurax = new Value_wxGLCanvas::EntityT(parent, id, attribList, pos, size, style, name, palette);
	RefPtr<Value_wxGLCanvas> pValue_gurax(new Value_wxGLCanvas(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GLCanvas#SetColour(colour as String)
Gurax_DeclareMethodAlias(wxGLCanvas, SetColour_gurax, "SetColour")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("colour", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGLCanvas, SetColour_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* colour = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetColour(colour);
	return new Gurax::Value_Bool(rtn);
}

// wx.GLCanvas#SetCurrent(context as wx.GLContext)
Gurax_DeclareMethodAlias(wxGLCanvas, SetCurrent_gurax, "SetCurrent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("context", VTYPE_wxGLContext, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGLCanvas, SetCurrent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGLContext& value_context = args_gurax.Pick<Value_wxGLContext>();
	const wxGLContext& context = value_context.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetCurrent(context);
	return new Gurax::Value_Bool(rtn);
}

// wx.GLCanvas#SwapBuffers()
Gurax_DeclareMethodAlias(wxGLCanvas, SwapBuffers_gurax, "SwapBuffers")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxGLCanvas, SwapBuffers_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->SwapBuffers();
	return new Gurax::Value_Bool(rtn);
}

// wx.GLCanvas.IsExtensionSupported(extension as String)
Gurax_DeclareClassMethodAlias(wxGLCanvas, IsExtensionSupported_gurax, "IsExtensionSupported")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("extension", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementClassMethodEx(wxGLCanvas, IsExtensionSupported_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* extension = args_gurax.PickString();
	// Function body
	bool rtn = wxGLCanvas::IsExtensionSupported(extension);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGLCanvas
//------------------------------------------------------------------------------
VType_wxGLCanvas VTYPE_wxGLCanvas("GLCanvas");

void VType_wxGLCanvas::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxWindow, Flag::Mutable, Gurax_CreateConstructor(GLCanvas_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGLCanvas, SetColour_gurax));
	Assign(Gurax_CreateMethod(wxGLCanvas, SetCurrent_gurax));
	Assign(Gurax_CreateMethod(wxGLCanvas, SwapBuffers_gurax));
	Assign(Gurax_CreateMethod(wxGLCanvas, IsExtensionSupported_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGLCanvas
//------------------------------------------------------------------------------
VType& Value_wxGLCanvas::vtype = VTYPE_wxGLCanvas;

String Value_wxGLCanvas::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GLCanvas");
}

//------------------------------------------------------------------------------
// Value_wxGLCanvas::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
