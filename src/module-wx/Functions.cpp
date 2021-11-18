//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"
Gurax_BeginModuleScope(wx)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// wx.Bell()
Gurax_DeclareFunctionAlias(Bell_gurax, "Bell")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(Bell_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxBell();
	return Gurax::Value::nil();
}

// wx.GetKeyCodeName(keyCode as Number)
Gurax_DeclareFunctionAlias(GetKeyCodeName_gurax, "GetKeyCodeName")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("keyCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(GetKeyCodeName_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int keyCode = args_gurax.PickNumber<int>();
	// Function body
	return new Value_String(Util::GetKeyCodeName(keyCode));
}

// wx.ImplementApp(app as wx.App)
Gurax_DeclareFunctionAlias(ImplementApp_gurax, "ImplementApp")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("app", VTYPE_wxApp, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(ImplementApp_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxApp& value_app = args_gurax.Pick<Value_wxApp>();
	wxApp* app = value_app.GetEntityPtr();
	// Function body
	wxApp::SetInstance(app);
	int argc = 0;
	char* argv[1] = { nullptr };
	::wxEntry(argc, argv);
	return Value::nil();
}

// wx.InitAllImageHandlers()
Gurax_DeclareFunctionAlias(InitAllImageHandlers_gurax, "InitAllImageHandlers")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(InitAllImageHandlers_gurax, processor_gurax, argument_gurax)
{
	// Function body
	wxInitAllImageHandlers();
	return Gurax::Value::nil();
}

// wx.MessageBox(message as String, caption? as String, style? as Number, parent? as wx.Window, x? as Number, y? as Number)
Gurax_DeclareFunctionAlias(MessageBox_gurax, "MessageBox")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("message", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caption", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("x", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("y", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunctionEx(MessageBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* message = args_gurax.PickString();
	const char* caption = args_gurax.IsValid()? args_gurax.PickString() : wxMessageBoxCaptionStr;
	bool style_validFlag = args_gurax.IsValid();
	int style = style_validFlag? args_gurax.PickNumber<int>() : (wxOK | wxCENTRE);
	wxWindow* parent = args_gurax.IsValid()? args_gurax.Pick<Value_wxWindow>().GetEntityPtr() : nullptr;
	bool x_validFlag = args_gurax.IsValid();
	int x = x_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	bool y_validFlag = args_gurax.IsValid();
	int y = y_validFlag? args_gurax.PickNumber<int>() : wxDefaultCoord;
	// Function body
	wxMessageBox(message, caption, style, parent, x, y);
	return Gurax::Value::nil();
}

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void AssignFunctions(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Bell_gurax));
	frame.Assign(Gurax_CreateFunction(GetKeyCodeName_gurax));
	frame.Assign(Gurax_CreateFunction(ImplementApp_gurax));
	frame.Assign(Gurax_CreateFunction(InitAllImageHandlers_gurax));
	frame.Assign(Gurax_CreateFunction(MessageBox_gurax));
}

Gurax_EndModuleScope(wx)
