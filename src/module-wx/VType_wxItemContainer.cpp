﻿//==============================================================================
// VType_wxItemContainer.cpp
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

${help.ComposePropertyHelp(wx.ItemContainer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.ItemContainer, `en)}

${help.ComposeMethodHelp(wx.ItemContainer, `en)}
)""";

static const char* g_docHelp_ja = u8R"""(
# 概要

# 定数

${help.ComposePropertyHelp(wx.ItemContainer, `ja)}

# オペレータ

# キャスト

${help.ComposeConstructorHelp(wx.ItemContainer, `ja)}

${help.ComposeMethodHelp(wx.ItemContainer, `ja)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.ItemContainer#Clear()
Gurax_DeclareMethodAlias(wxItemContainer, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.ItemContainer#Delete(n as Number)
Gurax_DeclareMethodAlias(wxItemContainer, Delete_gurax, "Delete")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, Delete_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#HasClientData()
Gurax_DeclareMethodAlias(wxItemContainer, HasClientData_gurax, "HasClientData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, HasClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ItemContainer#HasClientObjectData()
Gurax_DeclareMethodAlias(wxItemContainer, HasClientObjectData_gurax, "HasClientObjectData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, HasClientObjectData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientObjectData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ItemContainer#HasClientUntypedData()
Gurax_DeclareMethodAlias(wxItemContainer, HasClientUntypedData_gurax, "HasClientUntypedData")
{
	Declare(VTYPE_Bool, Flag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, HasClientUntypedData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientUntypedData();
	return new Gurax::Value_Bool(rtn);
}

// wx.ItemContainer#Append(item as Any, clientData? as Any)
Gurax_DeclareMethodAlias(wxItemContainer, Append_gurax, "Append")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, Append_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#GetClientData(n as Number)
Gurax_DeclareMethodAlias(wxItemContainer, GetClientData_gurax, "GetClientData")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, GetClientData_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#GetClientObject(n as Number)
Gurax_DeclareMethodAlias(wxItemContainer, GetClientObject_gurax, "GetClientObject")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, GetClientObject_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#SetClientData(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxItemContainer, SetClientData_gurax, "SetClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, SetClientData_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#SetClientObject(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxItemContainer, SetClientObject_gurax, "SetClientObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, SetClientObject_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#Insert(item as Any, pos as Number, clientData? as Any)
Gurax_DeclareMethodAlias(wxItemContainer, Insert_gurax, "Insert")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, Insert_gurax, processor_gurax, argument_gurax)
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

// wx.ItemContainer#Set(items[] as String, clientData? as Any)
Gurax_DeclareMethodAlias(wxItemContainer, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
}

Gurax_ImplementMethodEx(wxItemContainer, Set_gurax, processor_gurax, argument_gurax)
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
// VType_wxItemContainer
//------------------------------------------------------------------------------
VType_wxItemContainer VTYPE_wxItemContainer("ItemContainer");

void VType_wxItemContainer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	AddHelp(Gurax_Symbol(ja), g_docHelp_ja);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxItemContainer, Clear_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, Delete_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, HasClientData_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, HasClientObjectData_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, HasClientUntypedData_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, Append_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, GetClientData_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, GetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, SetClientData_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, SetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, Insert_gurax));
	Assign(Gurax_CreateMethod(wxItemContainer, Set_gurax));
}

//------------------------------------------------------------------------------
// Value_wxItemContainer
//------------------------------------------------------------------------------
VType& Value_wxItemContainer::vtype = VTYPE_wxItemContainer;

String Value_wxItemContainer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.ItemContainer");
}

Gurax_EndModuleScope(wx)
