//==============================================================================
// VType_wxComboBox.cpp
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
// wx.ComboBox(parent as wx.Window, id as Number, value? as String, pos? as wx.Point, size? as wx.Size, choices[]? as String, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(ComboBox_gurax, "ComboBox")
{
	Declare(VTYPE_wxComboBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.ComboBox.");
}

Gurax_ImplementConstructorEx(ComboBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* value = args_gurax.IsValid()? args_gurax.PickString() : "";
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	auto choices = args_gurax.PickListT<const char*>(Gurax::Value_String::ValueForVector);
	long style = args_gurax.IsValid()? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxButtonNameStr;
	// Function body
	wxArrayString choices_;
	for (const char* choice : choices) choices_.Add(choice);
	auto pEntity_gurax = new Value_wxComboBox::EntityT(parent, id, value, pos, size, choices_, style, validator, name);
	RefPtr<Value_wxComboBox> pValue_gurax(new Value_wxComboBox(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ComboBox#GetCount()
Gurax_DeclareMethodAlias(wxComboBox, GetCount_gurax, "GetCount")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, GetCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetCount();
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#GetString(n as Number)
Gurax_DeclareMethodAlias(wxComboBox, GetString_gurax, "GetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, GetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	const char* rtn = pEntity_gurax->GetString(n);
	return new Gurax::Value_String(rtn);
}

// wx.ComboBox#SetString(n as Number, string as String)
Gurax_DeclareMethodAlias(wxComboBox, SetString_gurax, "SetString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, SetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	const char* string = args_gurax.PickString();
	// Function body
	pEntity_gurax->SetString(n, string);
	return Gurax::Value::nil();
}

// wx.ComboBox#FindString(string as String, caseSensitive? as Bool)
Gurax_DeclareMethodAlias(wxComboBox, FindString_gurax, "FindString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("caseSensitive", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, FindString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	bool caseSensitive = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	int rtn = pEntity_gurax->FindString(string, caseSensitive);
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#SetSelection(n as Number)
Gurax_DeclareMethodAlias(wxComboBox, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, SetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetSelection(n);
	return Gurax::Value::nil();
}

// wx.ComboBox#GetSelection()
Gurax_DeclareMethodAlias(wxComboBox, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#SetStringSelection(string as String)
Gurax_DeclareMethodAlias(wxComboBox, SetStringSelection_gurax, "SetStringSelection")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("string", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, SetStringSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* string = args_gurax.PickString();
	// Function body
	bool rtn = pEntity_gurax->SetStringSelection(string);
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboBox#GetStringSelection()
Gurax_DeclareMethodAlias(wxComboBox, GetStringSelection_gurax, "GetStringSelection")
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, GetStringSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	const char* rtn = pEntity_gurax->GetStringSelection();
	return new Gurax::Value_String(rtn);
}

// wx.ComboBox#Select(n as Number)
Gurax_DeclareMethodAlias(wxComboBox, Select_gurax, "Select")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Select_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int n = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->Select(n);
	return Gurax::Value::nil();
}

// wx.ComboBox#Clear()
Gurax_DeclareMethodAlias(wxComboBox, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.ComboBox#Delete(n as Number)
Gurax_DeclareMethodAlias(wxComboBox, Delete_gurax, "Delete")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Delete_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	pEntity_gurax->Delete(n);
	return Gurax::Value::nil();
}

// wx.ComboBox#HasClientData()
Gurax_DeclareMethodAlias(wxComboBox, HasClientData_gurax, "HasClientData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, HasClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboBox#HasClientObjectData()
Gurax_DeclareMethodAlias(wxComboBox, HasClientObjectData_gurax, "HasClientObjectData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, HasClientObjectData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientObjectData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboBox#HasClientUntypedData()
Gurax_DeclareMethodAlias(wxComboBox, HasClientUntypedData_gurax, "HasClientUntypedData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, HasClientUntypedData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientUntypedData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ComboBox#Append(item as String)
Gurax_DeclareMethodAlias(wxComboBox, Append_gurax, "Append")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* item = args_gurax.PickString();
	// Function body
	int rtn = pEntity_gurax->Append(item);
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#AppendItems(items[] as String)
Gurax_DeclareMethodAlias(wxComboBox, AppendItems_gurax, "AppendItems")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, AppendItems_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto items = args_gurax.PickListT<const char*>(Gurax::Value_String::ValueForVector);
	// Function body
	wxArrayString items_;
	for (const char* item : items) items_.Add(item);
	int rtn = pEntity_gurax->Append(items_);
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#Insert(item as String, pos as Number)
Gurax_DeclareMethodAlias(wxComboBox, Insert_gurax, "Insert")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Insert_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* item = args_gurax.PickString();
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	// Function body
	int rtn = pEntity_gurax->Insert(item, pos);
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#InsertItems(items[] as String, pos as Number)
Gurax_DeclareMethodAlias(wxComboBox, InsertItems_gurax, "InsertItems")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, InsertItems_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto items = args_gurax.PickListT<const char*>(Gurax::Value_String::ValueForVector);
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	// Function body
	wxArrayString items_;
	for (const char* item : items) items_.Add(item);
	int rtn = pEntity_gurax->Insert(items_, pos);
	return new Gurax::Value_Number(rtn);
}

// wx.ComboBox#Set(items[] as String)
Gurax_DeclareMethodAlias(wxComboBox, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxComboBox, Set_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	auto items = args_gurax.PickListT<const char*>(Gurax::Value_String::ValueForVector);
	// Function body
	wxArrayString items_;
	for (const char* item : items) items_.Add(item);
	pEntity_gurax->Set(items_);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxComboBox
//------------------------------------------------------------------------------
VType_wxComboBox VTYPE_wxComboBox("ComboBox");

void VType_wxComboBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(ComboBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxComboBox, GetCount_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, GetString_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, SetString_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, FindString_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, SetStringSelection_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, GetStringSelection_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Select_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Clear_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Delete_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, HasClientData_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, HasClientObjectData_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, HasClientUntypedData_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Append_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, AppendItems_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Insert_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, InsertItems_gurax));
	Assign(Gurax_CreateMethod(wxComboBox, Set_gurax));
}

//------------------------------------------------------------------------------
// Value_wxComboBox
//------------------------------------------------------------------------------
VType& Value_wxComboBox::vtype = VTYPE_wxComboBox;

String Value_wxComboBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ComboBox");
}

Gurax_EndModuleScope(wx)
