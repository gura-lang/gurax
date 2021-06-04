//==============================================================================
// VType_wxWindow.cpp
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
// wx.Window() {block?}
Gurax_DeclareConstructorAlias(Window_gurax, "ndow")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wxWindow.");
}

Gurax_ImplementConstructorEx(Window_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxWindow::EntityT();
	RefPtr<Value_wxWindow> pValue_gurax(new Value_wxWindow(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.wxWindow#Close(force? as Bool)
Gurax_DeclareMethodAlias(wxWindow, Close_gurax, "Close")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("force", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWindow, Close_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool force = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->Close(force);
	return new Gurax::Value_Bool(rtn);
}

// wx.wxWindow#Show(show? as Bool)
Gurax_DeclareMethodAlias(wxWindow, Show_gurax, "Show")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxWindow, Show_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool show = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	bool rtn = pEntity_gurax->Show(show);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxWindow
//------------------------------------------------------------------------------
VType_wxWindow VTYPE_wxWindow("Window");

void VType_wxWindow::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Window_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxWindow, Close_gurax));
	Assign(Gurax_CreateMethod(wxWindow, Show_gurax));
}

//------------------------------------------------------------------------------
// Value_wxWindow
//------------------------------------------------------------------------------
VType& Value_wxWindow::vtype = VTYPE_wxWindow;

String Value_wxWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Window");
}

Gurax_EndModuleScope(wx)
