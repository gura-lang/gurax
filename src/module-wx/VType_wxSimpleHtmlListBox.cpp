//==============================================================================
// VType_wxSimpleHtmlListBox.cpp
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
// wx.SimpleHtmlListBox(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, choices[] as String, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(SimpleHtmlListBox_gurax, "SimpleHtmlListBox")
{
	Declare(VTYPE_wxSimpleHtmlListBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.SimpleHtmlListBox.");
}

Gurax_ImplementConstructorEx(SimpleHtmlListBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	Value_wxPoint& value_pos = args_gurax.Pick<Value_wxPoint>();
	const wxPoint& pos = value_pos.GetEntity();
	Value_wxSize& value_size = args_gurax.Pick<Value_wxSize>();
	const wxSize& size = value_size.GetEntity();
	wxArrayString choices = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxHLB_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxSimpleHtmlListBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxSimpleHtmlListBox::EntityT(parent, id, pos, size, choices, style, validator, name);
	RefPtr<Value_wxSimpleHtmlListBox> pValue_gurax(new Value_wxSimpleHtmlListBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.SimpleHtmlListBox#Clear()
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Clear();
	return Gurax::Value::nil();
}

// wx.SimpleHtmlListBox#Delete(n as Number)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, Delete_gurax, "Delete")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, Delete_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#HasClientData()
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, HasClientData_gurax, "HasClientData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, HasClientData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientData();
	return new Gurax::Value_Bool(rtn);
}

// wx.SimpleHtmlListBox#HasClientObjectData()
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, HasClientObjectData_gurax, "HasClientObjectData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, HasClientObjectData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientObjectData();
	return new Gurax::Value_Bool(rtn);
}

// wx.SimpleHtmlListBox#HasClientUntypedData()
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, HasClientUntypedData_gurax, "HasClientUntypedData")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, HasClientUntypedData_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->HasClientUntypedData();
	return new Gurax::Value_Bool(rtn);
}

// wx.SimpleHtmlListBox#Append(item as Any, clientData? as Any)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, Append_gurax, "Append")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, Append_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#GetClientData(n as Number)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, GetClientData_gurax, "GetClientData")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, GetClientData_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#GetClientObject(n as Number)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, GetClientObject_gurax, "GetClientObject")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, GetClientObject_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#SetClientData(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, SetClientData_gurax, "SetClientData")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, SetClientData_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#SetClientObject(n as Number, data as Any)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, SetClientObject_gurax, "SetClientObject")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("data", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, SetClientObject_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#Insert(item as Any, pos as Number, clientData? as Any)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, Insert_gurax, "Insert")
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, Insert_gurax, processor_gurax, argument_gurax)
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

// wx.SimpleHtmlListBox#Set(items[] as String, clientData? as Any)
Gurax_DeclareMethodAlias(wxSimpleHtmlListBox, Set_gurax, "Set")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("clientData", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSimpleHtmlListBox, Set_gurax, processor_gurax, argument_gurax)
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
// VType_wxSimpleHtmlListBox
//------------------------------------------------------------------------------
VType_wxSimpleHtmlListBox VTYPE_wxSimpleHtmlListBox("SimpleHtmlListBox");

void VType_wxSimpleHtmlListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxHtmlListBox, Flag::Mutable, Gurax_CreateConstructor(SimpleHtmlListBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, Clear_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, Delete_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, HasClientData_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, HasClientObjectData_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, HasClientUntypedData_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, Append_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, GetClientData_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, GetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, SetClientData_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, SetClientObject_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, Insert_gurax));
	Assign(Gurax_CreateMethod(wxSimpleHtmlListBox, Set_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSimpleHtmlListBox
//------------------------------------------------------------------------------
VType& Value_wxSimpleHtmlListBox::vtype = VTYPE_wxSimpleHtmlListBox;

String Value_wxSimpleHtmlListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.SimpleHtmlListBox");
}

//------------------------------------------------------------------------------
// Value_wxSimpleHtmlListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
