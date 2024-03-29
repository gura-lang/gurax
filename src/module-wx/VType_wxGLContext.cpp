﻿//==============================================================================
// VType_wxGLContext.cpp
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

${help.ComposePropertyHelp(wx.GLContext, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.GLContext, `en)}

${help.ComposeMethodHelp(wx.GLContext, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.GLContext, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.GLContext, `ja)}

${help.ComposeMethodHelp(wx.GLContext, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.GLContext(win as wx.GLCanvas, other? as wx.GLContext) {block?}
Gurax_DeclareConstructorAlias(GLContext_gurax, "GLContext")
{
	Declare(VTYPE_wxGLContext, Flag::None);
	DeclareArg("win", VTYPE_wxGLCanvas, ArgOccur::Once, ArgFlag::None);
	DeclareArg("other", VTYPE_wxGLContext, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(GLContext_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGLCanvas& value_win = args_gurax.Pick<Value_wxGLCanvas>();
	wxGLCanvas* win = value_win.GetEntityPtr();
	wxGLContext* other = args_gurax.IsValid()? args_gurax.Pick<Value_wxGLContext>().GetEntityPtr() : nullptr;
	// Function body
	auto pEntity_gurax = new wxGLContext(win, other);
	RefPtr<Value_wxGLContext> pValue_gurax(new Value_wxGLContext(pEntity_gurax));
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.GLContext#SetCurrent(win as wx.GLCanvas)
Gurax_DeclareMethodAlias(wxGLContext, SetCurrent_gurax, "SetCurrent")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("win", VTYPE_wxGLCanvas, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxGLContext, SetCurrent_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGLCanvas& value_win = args_gurax.Pick<Value_wxGLCanvas>();
	const wxGLCanvas& win = value_win.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->SetCurrent(win);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxGLContext
//------------------------------------------------------------------------------
VType_wxGLContext VTYPE_wxGLContext("GLContext");

void VType_wxGLContext::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(GLContext_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxGLContext, SetCurrent_gurax));
}

//------------------------------------------------------------------------------
// Value_wxGLContext
//------------------------------------------------------------------------------
VType& Value_wxGLContext::vtype = VTYPE_wxGLContext;

String Value_wxGLContext::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.GLContext");
}

Gurax_EndModuleScope(wx)
