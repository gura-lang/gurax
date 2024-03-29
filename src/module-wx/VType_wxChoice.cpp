﻿//==============================================================================
// VType_wxChoice.cpp
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

${help.ComposePropertyHelp(wx.Choice, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.Choice, `en)}

${help.ComposeMethodHelp(wx.Choice, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.Choice, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.Choice, `ja)}

${help.ComposeMethodHelp(wx.Choice, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.Choice(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, choices[]? as String, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(Choice_gurax, "Choice")
{
	Declare(VTYPE_wxChoice, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
}

Gurax_ImplementConstructorEx(Choice_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	bool name_validFlag = args_gurax.IsValid();
	wxString name = name_validFlag? wxString(args_gurax.PickString()) : wxChoiceNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxChoice::EntityT(parent, id, pos, size, choices, style, validator, name);
	RefPtr<Value_wxChoice> pValue_gurax(new Value_wxChoice(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Choice#GetColumns()
Gurax_DeclareMethodAlias(wxChoice, GetColumns_gurax, "GetColumns")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetColumns_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetColumns();
	return new Gurax::Value_Number(rtn);
}

// wx.Choice#GetCurrentSelection()
Gurax_DeclareMethodAlias(wxChoice, GetCurrentSelection_gurax, "GetCurrentSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetCurrentSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetCurrentSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.Choice#SetColumns(n? as Number)
Gurax_DeclareMethodAlias(wxChoice, SetColumns_gurax, "SetColumns")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, SetColumns_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool n_validFlag = args_gurax.IsValid();
	int n = n_validFlag? args_gurax.PickNumber<int>() : 1;
	// Function body
	pEntity_gurax->SetColumns(n);
	return Gurax::Value::nil();
}

// wx.Choice#IsSorted()
Gurax_DeclareMethodAlias(wxChoice, IsSorted_gurax, "IsSorted")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, IsSorted_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsSorted();
	return new Gurax::Value_Bool(rtn);
}

// wx.Choice#GetCount()
Gurax_DeclareMethodAlias(wxChoice, GetCount_gurax, "GetCount")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetCount_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	unsigned int rtn = pEntity_gurax->GetCount();
	return new Gurax::Value_Number(rtn);
}

// wx.Choice#GetSelection()
Gurax_DeclareMethodAlias(wxChoice, GetSelection_gurax, "GetSelection")
{
	Declare(VTYPE_Number, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetSelection_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetSelection();
	return new Gurax::Value_Number(rtn);
}

// wx.Choice#SetSelection(n as Number)
Gurax_DeclareMethodAlias(wxChoice, SetSelection_gurax, "SetSelection")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, SetSelection_gurax, processor_gurax, argument_gurax)
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

// wx.Choice#FindString(s as String, bCase? as Bool)
Gurax_DeclareMethodAlias(wxChoice, FindString_gurax, "FindString")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("s", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bCase", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, FindString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxString s(args_gurax.PickString());
	bool bCase = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	int rtn = pEntity_gurax->FindString(s, bCase);
	return new Gurax::Value_Number(rtn);
}

// wx.Choice#GetString(n as Number)
Gurax_DeclareMethodAlias(wxChoice, GetString_gurax, "GetString")
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	wxString rtn = pEntity_gurax->GetString(n);
	return new Gurax::Value_String(rtn.utf8_str().data());
}

// wx.Choice#SetString(pos as Number, s as String)
Gurax_DeclareMethodAlias(wxChoice, SetString_gurax, "SetString")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("s", VTYPE_String, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, SetString_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	wxString s(args_gurax.PickString());
	// Function body
	pEntity_gurax->SetString(pos, s);
	return Gurax::Value::nil();
}

// wx.Choice#Clear()
Gurax_DeclareMethodAlias(wxChoice, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.Choice#Delete(n as Number)
Gurax_DeclareMethodAlias(wxChoice, Delete_gurax, "Delete")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, Delete_gurax, processor_gurax, argument_gurax)
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

// wx.Choice#HasClientData()
Gurax_DeclareMethodAlias(wxChoice, HasClientData_gurax, "HasClientData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, HasClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientData();
	return new Gurax::Value_Bool(rtn);
}

// wx.Choice#HasClientObjectData()
Gurax_DeclareMethodAlias(wxChoice, HasClientObjectData_gurax, "HasClientObjectData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, HasClientObjectData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientObjectData();
	return new Gurax::Value_Bool(rtn);
}

// wx.Choice#HasClientUntypedData()
Gurax_DeclareMethodAlias(wxChoice, HasClientUntypedData_gurax, "HasClientUntypedData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxChoice, HasClientUntypedData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientUntypedData();
	return new Gurax::Value_Bool(rtn);
}

// wx.Choice#Append(item as Any, clientData? as Any)
Gurax_DeclareMethodAlias(wxChoice, Append_gurax, "Append")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, Append_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::Value& item = args_gurax.PickValue();
	const Gurax::Value& clientData = args_gurax.IsValid()? args_gurax.PickValue() : Value::C_nil();
	// Function body
	int rtn = 0;
	if (item.IsType(VTYPE_String)) {
		if (clientData.IsInvalid()) {
			rtn = pEntity_gurax->Append(Value_String::GetString(item));
		} else {
			rtn = pEntity_gurax->Append(Value_String::GetString(item), ClientData::Create(clientData));
		}
	} else if (item.IsType(VTYPE_List)) {
		const ValueOwner& items = Value_List::GetValueOwner(item);
		if (!items.IsElemInstanceOf(VTYPE_String)) {
			Error::Issue(ErrorType::TypeError, "The list must contain values of String");
			return Value::nil();
		}
		if (clientData.IsInvalid()) {
			rtn = pEntity_gurax->Append(Util::CreateArrayString(items));
		} else if (clientData.IsType(VTYPE_List)) {
			const ValueOwner& clientDataTbl = Value_List::GetValueOwner(clientData);
			if (items.size() != clientDataTbl.size()) {
				Error::Issue(ErrorType::ValueError, "The lists for item and clientData must have the same length");
				return Value::nil();
			}
			rtn = pEntity_gurax->Append(Util::CreateArrayString(items), ClientData::Create(clientDataTbl).data());
		} else {
			Error::Issue(ErrorType::TypeError, "The argument clientData takes a value of List");
			return Value::nil();
		}
	} else {
		Error::Issue(ErrorType::TypeError, "The argument item takes a value of String or List");
		return Value::nil();
	}
	return new Value_Number(rtn);
}

// wx.Choice#GetClientData(n as Number)
Gurax_DeclareMethodAlias(wxChoice, GetClientData_gurax, "GetClientData")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	auto pClientData = dynamic_cast<ClientData*>(pEntity_gurax->GetClientObject(n));
	if (!pClientData) return Value::nil();
	return pClientData->GetValue().Reference();
}

// wx.Choice#GetClientObject(n as Number)
Gurax_DeclareMethodAlias(wxChoice, GetClientObject_gurax, "GetClientObject")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, GetClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	// Function body
	auto pClientData = dynamic_cast<ClientData*>(pEntity_gurax->GetClientObject(n));
	if (!pClientData) return Value::nil();
	return pClientData->GetValue().Reference();
}

// wx.Choice#SetClientData(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxChoice, SetClientData_gurax, "SetClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, SetClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	const Gurax::Value& data = args_gurax.PickValue();
	// Function body
	pEntity_gurax->SetClientObject(n, ClientData::Create(data));
	return Value::nil();
}

// wx.Choice#SetClientObject(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxChoice, SetClientObject_gurax, "SetClientObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, SetClientObject_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int n = args_gurax.PickNumber<unsigned int>();
	const Gurax::Value& data = args_gurax.PickValue();
	// Function body
	pEntity_gurax->SetClientObject(n, ClientData::Create(data));
	return Value::nil();
}

// wx.Choice#Insert(item as Any, pos as Number, clientData? as Any)
Gurax_DeclareMethodAlias(wxChoice, Insert_gurax, "Insert")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, Insert_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::Value& item = args_gurax.PickValue();
	unsigned int pos = args_gurax.PickNumber<unsigned int>();
	const Gurax::Value& clientData = args_gurax.IsValid()? args_gurax.PickValue() : Value::C_nil();
	// Function body
	int rtn = 0;
	if (item.IsType(VTYPE_String)) {
		if (clientData.IsInvalid()) {
			rtn = pEntity_gurax->Insert(Value_String::GetString(item), pos);
		} else {
			rtn = pEntity_gurax->Insert(Value_String::GetString(item), pos, ClientData::Create(clientData));
		}
	} else if (item.IsType(VTYPE_List)) {
		const ValueOwner& items = Value_List::GetValueOwner(item);
		if (!items.IsElemInstanceOf(VTYPE_String)) {
			Error::Issue(ErrorType::TypeError, "The list must contain values of String");
			return Value::nil();
		}
		if (clientData.IsInvalid()) {
			rtn = pEntity_gurax->Insert(Util::CreateArrayString(items), pos);
		} else if (clientData.IsType(VTYPE_List)) {
			const ValueOwner& clientDataTbl = Value_List::GetValueOwner(clientData);
			if (items.size() != clientDataTbl.size()) {
				Error::Issue(ErrorType::ValueError, "The lists for item and clientData must have the same length");
				return Value::nil();
			}
			rtn = pEntity_gurax->Insert(Util::CreateArrayString(items), pos, ClientData::Create(clientDataTbl).data());
		} else {
			Error::Issue(ErrorType::TypeError, "The argument clientData takes a value of List");
			return Value::nil();
		}
	} else {
		Error::Issue(ErrorType::TypeError, "The argument item takes a value of String or List");
		return Value::nil();
	}
	return new Value_Number(rtn);
}

// wx.Choice#Set(items[] as String, clientData? as Any)
Gurax_DeclareMethodAlias(wxChoice, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxChoice, Set_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString items = Util::CreateArrayString(args_gurax.PickList());
	const Gurax::Value& clientData = args_gurax.IsValid()? args_gurax.PickValue() : Value::C_nil();
	// Function body
	if (clientData.IsInvalid()) {
		pEntity_gurax->Set(items);
	} else if (clientData.IsType(VTYPE_List)) {
		const ValueOwner& clientDataTbl = Value_List::GetValueOwner(clientData);
		if (items.size() != clientDataTbl.size()) {
			Error::Issue(ErrorType::ValueError, "The lists for item and clientData must have the same length");
			return Value::nil();
		}
		pEntity_gurax->Set(items, ClientData::Create(clientDataTbl).data());
	} else {
		Error::Issue(ErrorType::TypeError, "The argument clientData takes a value of List");
		return Value::nil();
	}
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxChoice
//------------------------------------------------------------------------------
VType_wxChoice VTYPE_wxChoice("Choice");

void VType_wxChoice::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(Choice_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxChoice, GetColumns_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetCurrentSelection_gurax));
	Assign(Gurax_CreateMethod(wxChoice, SetColumns_gurax));
	Assign(Gurax_CreateMethod(wxChoice, IsSorted_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetCount_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetSelection_gurax));
	Assign(Gurax_CreateMethod(wxChoice, SetSelection_gurax));
	Assign(Gurax_CreateMethod(wxChoice, FindString_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetString_gurax));
	Assign(Gurax_CreateMethod(wxChoice, SetString_gurax));
	Assign(Gurax_CreateMethod(wxChoice, Clear_gurax));
	Assign(Gurax_CreateMethod(wxChoice, Delete_gurax));
	Assign(Gurax_CreateMethod(wxChoice, HasClientData_gurax));
	Assign(Gurax_CreateMethod(wxChoice, HasClientObjectData_gurax));
	Assign(Gurax_CreateMethod(wxChoice, HasClientUntypedData_gurax));
	Assign(Gurax_CreateMethod(wxChoice, Append_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetClientData_gurax));
	Assign(Gurax_CreateMethod(wxChoice, GetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxChoice, SetClientData_gurax));
	Assign(Gurax_CreateMethod(wxChoice, SetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxChoice, Insert_gurax));
	Assign(Gurax_CreateMethod(wxChoice, Set_gurax));
}

//------------------------------------------------------------------------------
// Value_wxChoice
//------------------------------------------------------------------------------
VType& Value_wxChoice::vtype = VTYPE_wxChoice;

String Value_wxChoice::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Choice");
}

//------------------------------------------------------------------------------
// Value_wxChoice::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
