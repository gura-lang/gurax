//==============================================================================
// VType_wxAcceleratorEntry.cpp
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

${help.ComposePropertyHelp(wxAcceleratorEntry, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxAcceleratorEntry, `en)}

${help.ComposeMethodHelp(wxAcceleratorEntry, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AcceleratorEntry(flags? as Number, keyCode? as Number, cmd? as Number, item? as wx.MenuItem) {block?}
Gurax_DeclareConstructorAlias(AcceleratorEntry_gurax, "AcceleratorEntry")
{
	Declare(VTYPE_wxAcceleratorEntry, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("keyCode", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("cmd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("item", VTYPE_wxMenuItem, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.AcceleratorEntry.");
}

Gurax_ImplementConstructorEx(AcceleratorEntry_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool flags_validFlag = args_gurax.IsValid();
	int flags = flags_validFlag? args_gurax.PickNumber<int>() : 0;
	bool keyCode_validFlag = args_gurax.IsValid();
	int keyCode = keyCode_validFlag? args_gurax.PickNumber<int>() : 0;
	bool cmd_validFlag = args_gurax.IsValid();
	int cmd = cmd_validFlag? args_gurax.PickNumber<int>() : 0;
	wxMenuItem* item = args_gurax.IsValid()? args_gurax.Pick<Value_wxMenuItem>().GetEntityPtr() : nullptr;
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxAcceleratorEntry(
		wxAcceleratorEntry(flags, keyCode, cmd, item)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AcceleratorEntry#GetCommand()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, GetCommand_gurax, "GetCommand")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, GetCommand_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCommand();
	return new Gurax::Value_Number(rtn);
}

// wx.AcceleratorEntry#GetFlags()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, GetFlags_gurax, "GetFlags")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, GetFlags_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetFlags();
	return new Gurax::Value_Number(rtn);
}

// wx.AcceleratorEntry#GetKeyCode()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, GetKeyCode_gurax, "GetKeyCode")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, GetKeyCode_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetKeyCode();
	return new Gurax::Value_Number(rtn);
}

// wx.AcceleratorEntry#GetMenuItem() {block?}
Gurax_DeclareMethodAlias(wxAcceleratorEntry, GetMenuItem_gurax, "GetMenuItem")
{
	Declare(VTYPE_wxMenuItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, GetMenuItem_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMenuItem(
		*pEntity_gurax->GetMenuItem()));
}

// wx.AcceleratorEntry#Set(flags as Number, keyCode as Number, cmd as Number, item? as wx.MenuItem)
Gurax_DeclareMethodAlias(wxAcceleratorEntry, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("flags", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("keyCode", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cmd", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("item", VTYPE_wxMenuItem, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, Set_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int flags = args_gurax.PickNumber<int>();
	int keyCode = args_gurax.PickNumber<int>();
	int cmd = args_gurax.PickNumber<int>();
	wxMenuItem* item = args_gurax.IsValid()? args_gurax.Pick<Value_wxMenuItem>().GetEntityPtr() : nullptr;
	// Function body
	pEntity_gurax->Set(flags, keyCode, cmd, item);
	return Gurax::Value::nil();
}

// wx.AcceleratorEntry#IsOk()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

// wx.AcceleratorEntry#ToString()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, ToString_gurax, "ToString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, ToString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->ToString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.AcceleratorEntry#ToRawString()
Gurax_DeclareMethodAlias(wxAcceleratorEntry, ToRawString_gurax, "ToRawString")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, ToRawString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxString rtn = pEntity_gurax->ToRawString();
	return new Gurax::Value_String(static_cast<const char*>(rtn.c_str()));
}

// wx.AcceleratorEntry#FromString(str as String)
Gurax_DeclareMethodAlias(wxAcceleratorEntry, FromString_gurax, "FromString")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxAcceleratorEntry, FromString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* str = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->FromString(str);
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAcceleratorEntry
//------------------------------------------------------------------------------
VType_wxAcceleratorEntry VTYPE_wxAcceleratorEntry("AcceleratorEntry");

void VType_wxAcceleratorEntry::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(AcceleratorEntry_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, GetCommand_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, GetFlags_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, GetKeyCode_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, GetMenuItem_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, Set_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, IsOk_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, ToString_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, ToRawString_gurax));
	Assign(Gurax_CreateMethod(wxAcceleratorEntry, FromString_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAcceleratorEntry
//------------------------------------------------------------------------------
VType& Value_wxAcceleratorEntry::vtype = VTYPE_wxAcceleratorEntry;

String Value_wxAcceleratorEntry::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AcceleratorEntry");
}

Gurax_EndModuleScope(wx)
