//==============================================================================
// VType_wxApp.cpp
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
// wx.App() {block?}
Gurax_DeclareConstructorAlias(App_gurax, "App")
{
	Declare(VTYPE_wxApp, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.App.");
}

Gurax_ImplementConstructorEx(App_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxApp::EntityT();
	RefPtr<Value_wxApp> pValue_gurax(new Value_wxApp(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.App#OnCmdLineError(parser as wx.CmdLineParser)
Gurax_DeclareMethodAlias(wxApp, OnCmdLineError_gurax, "OnCmdLineError")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parser", VTYPE_wxCmdLineParser, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnCmdLineError_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCmdLineParser& value_parser = args_gurax.Pick<Value_wxCmdLineParser>();
	wxCmdLineParser& parser = value_parser.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->OnCmdLineError(parser);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#OnCmdLineHelp(parser as wx.CmdLineParser)
Gurax_DeclareMethodAlias(wxApp, OnCmdLineHelp_gurax, "OnCmdLineHelp")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parser", VTYPE_wxCmdLineParser, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnCmdLineHelp_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCmdLineParser& value_parser = args_gurax.Pick<Value_wxCmdLineParser>();
	wxCmdLineParser& parser = value_parser.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->OnCmdLineHelp(parser);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#OnCmdLineParsed(parser as wx.CmdLineParser)
Gurax_DeclareMethodAlias(wxApp, OnCmdLineParsed_gurax, "OnCmdLineParsed")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parser", VTYPE_wxCmdLineParser, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnCmdLineParsed_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxCmdLineParser& value_parser = args_gurax.Pick<Value_wxCmdLineParser>();
	wxCmdLineParser& parser = value_parser.GetEntity();
	// Function body
	bool rtn = pEntity_gurax->OnCmdLineParsed(parser);
	return new Gurax::Value_Bool(rtn);
}

// wx.App#OnExceptionInMainLoop()
Gurax_DeclareMethodAlias(wxApp, OnExceptionInMainLoop_gurax, "OnExceptionInMainLoop")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnExceptionInMainLoop_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->OnExceptionInMainLoop();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#OnExit()
Gurax_DeclareMethodAlias(wxApp, OnExit_gurax, "OnExit")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnExit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->OnExit();
	return new Gurax::Value_Number(rtn);
}

// wx.App#OnFatalException()
Gurax_DeclareMethodAlias(wxApp, OnFatalException_gurax, "OnFatalException")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnFatalException_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnFatalException();
	return Gurax::Value::nil();
}

// wx.App#OnInit()
Gurax_DeclareMethodAlias(wxApp, OnInit_gurax, "OnInit")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnInit_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->OnInit();
	return new Gurax::Value_Bool(rtn);
}

// wx.App#OnUnhandledException()
Gurax_DeclareMethodAlias(wxApp, OnUnhandledException_gurax, "OnUnhandledException")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxApp, OnUnhandledException_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = dynamic_cast<Value_wxApp::EntityT*>(valueThis_gurax.GetEntityPtr());
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->OnUnhandledException();
	return Gurax::Value::nil();
}

// wx.App.SetInstance(app as wx.AppConsole)
Gurax_DeclareClassMethodAlias(wxApp, SetInstance_gurax, "SetInstance")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("app", VTYPE_wxAppConsole, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxApp, SetInstance_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxAppConsole& value_app = args_gurax.Pick<Value_wxAppConsole>();
	wxAppConsole* app = value_app.GetEntityPtr();
	// Function body
	wxApp::SetInstance(app);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxApp
//------------------------------------------------------------------------------
VType_wxApp VTYPE_wxApp("App");

void VType_wxApp::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxAppConsole, Flag::Mutable, Gurax_CreateConstructor(App_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxApp, OnCmdLineError_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnCmdLineHelp_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnCmdLineParsed_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnExceptionInMainLoop_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnExit_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnFatalException_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnInit_gurax));
	Assign(Gurax_CreateMethod(wxApp, OnUnhandledException_gurax));
	Assign(Gurax_CreateMethod(wxApp, SetInstance_gurax));
}

//------------------------------------------------------------------------------
// Value_wxApp
//------------------------------------------------------------------------------
VType& Value_wxApp::vtype = VTYPE_wxApp;

String Value_wxApp::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.App");
}

//------------------------------------------------------------------------------
// Value_wxApp::EntityT
//------------------------------------------------------------------------------
bool Value_wxApp::EntityT::OnCmdLineError(wxCmdLineParser& parser)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnCmdLineError");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxCmdLineParser(parser))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnCmdLineError(parser);
}

bool Value_wxApp::EntityT::OnCmdLineHelp(wxCmdLineParser& parser)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnCmdLineHelp");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxCmdLineParser(parser))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnCmdLineHelp(parser);
}

bool Value_wxApp::EntityT::OnCmdLineParsed(wxCmdLineParser& parser)
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnCmdLineParsed");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		Gurax::ArgFeeder args_gurax(*pArgument_gurax, core_gurax.GetProcessor().GetFrameCur());
		if (!args_gurax.FeedValue(new Value_wxCmdLineParser(parser))) {
			Util::ExitMainLoop();
			break;
		}
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnCmdLineParsed(parser);
}

bool Value_wxApp::EntityT::OnExceptionInMainLoop()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnExceptionInMainLoop");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnExceptionInMainLoop();
}

int Value_wxApp::EntityT::OnExit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnExit");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Number.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Number::GetNumber<int>(*pValueRtn);
	} while (0);
	return public_OnExit();
}

void Value_wxApp::EntityT::OnFatalException()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnFatalException");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_OnFatalException();
}

bool Value_wxApp::EntityT::OnInit()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnInit");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		// Return Value
		if (!pValueRtn->IsType(VTYPE_Bool)) {
			Error::Issue(ErrorType::TypeError, "the function is expected to return a value of %s",
				VTYPE_Bool.MakeFullName().c_str());
			Util::ExitMainLoop();
			break;
		}
		return Value_Bool::GetBool(*pValueRtn);
	} while (0);
	return public_OnInit();
}

void Value_wxApp::EntityT::OnUnhandledException()
{
	static const Symbol* pSymbolFunc = nullptr;
	if (!pSymbolFunc) pSymbolFunc = Symbol::Add("OnUnhandledException");
	do {
		Gurax::Function* pFunc_gurax;
		RefPtr<Gurax::Argument> pArgument_gurax;
		if (!core_gurax.PrepareOverrideMethod(pSymbolFunc, &pFunc_gurax, pArgument_gurax)) break;
		// Argument
		// (none)
		// Evaluation
		RefPtr<Value> pValueRtn(pFunc_gurax->Eval(core_gurax.GetProcessor(), *pArgument_gurax));
		if (Error::IsIssued()) {
			Util::ExitMainLoop();
			break;
		}
		return;
	} while (0);
	public_OnUnhandledException();
}

Gurax_EndModuleScope(wx)
