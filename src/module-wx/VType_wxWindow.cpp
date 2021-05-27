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
Gurax_DeclareConstructor(Window)
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Window` instance.");
}

Gurax_ImplementConstructor(Window)
{
	// Function body
	auto pEntity = new Value_wxWindow::EntityT();
	RefPtr<Value_wxWindow> pValue(new Value_wxWindow(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Window#Close(force? as Bool)
Gurax_DeclareMethod(wxWindow, Close)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("force", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(wxWindow, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	Bool force = args.IsValid()? args.PickBool() : false;
	// Function body
	bool rtn = pEntity->Close(force);
	return new Value_Bool(rtn);
}

// wx.Window#Show(show? as Bool)
Gurax_DeclareMethod(wxWindow, Show)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("show", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(wxWindow, Show)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	auto pEntity = valueThis.GetEntity();
	if (!pEntity) return Value::nil();
	// Arguments
	ArgPicker args(argument);
	Bool show = args.IsValid()? args.PickBool() : true;
	// Function body
	bool rtn = pEntity->Show(show);
	return new Value_Bool(rtn);
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
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Window));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxWindow, Close));
	Assign(Gurax_CreateMethod(wxWindow, Show));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Window, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxWindow
//------------------------------------------------------------------------------
VType& Value_wxWindow::vtype = VTYPE_wxWindow;

String Value_wxWindow::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Window");
}

//------------------------------------------------------------------------------
// Value_wxWindow::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
