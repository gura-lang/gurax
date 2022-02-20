//==============================================================================
// VType_wxCheckListBox.cpp
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
// wx.CheckListBox(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, choices[] as String, style? as Number, validator? as wx.Validator, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(CheckListBox_gurax, "CheckListBox")
{
	Declare(VTYPE_wxCheckListBox, Flag::None);
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
		"Creates an instance of wx.CheckListBox.");
}

Gurax_ImplementConstructorEx(CheckListBox_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "listBox";
	// Function body
	auto pEntity_gurax = new Value_wxCheckListBox::EntityT(parent, id, pos, size, choices, style, validator, name);
	RefPtr<Value_wxCheckListBox> pValue_gurax(new Value_wxCheckListBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CheckListBox#Create(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, choices[] as String, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxCheckListBox, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("choices", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCheckListBox, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxListBoxNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, choices, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckListBox#Check(item as Number, check? as Bool)
Gurax_DeclareMethodAlias(wxCheckListBox, Check_gurax, "Check")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("check", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCheckListBox, Check_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	bool check = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Check(item, check);
	return Gurax::Value::nil();
}

// wx.CheckListBox#IsChecked(item as Number)
Gurax_DeclareMethodAlias(wxCheckListBox, IsChecked_gurax, "IsChecked")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("item", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCheckListBox, IsChecked_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	unsigned int item = args_gurax.PickNumber<unsigned int>();
	// Function body
	bool rtn = pEntity_gurax->IsChecked(item);
	return new Gurax::Value_Bool(rtn);
}

// wx.CheckListBox#GetCheckedItems()
Gurax_DeclareMethodAlias(wxCheckListBox, GetCheckedItems_gurax, "GetCheckedItems")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCheckListBox, GetCheckedItems_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayInt checkedItems;
	pEntity_gurax->GetCheckedItems(checkedItems);
	return Util::CreateList(checkedItems);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCheckListBox
//------------------------------------------------------------------------------
VType_wxCheckListBox VTYPE_wxCheckListBox("CheckListBox");

void VType_wxCheckListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxListBox, Flag::Mutable, Gurax_CreateConstructor(CheckListBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCheckListBox, Create_gurax));
	Assign(Gurax_CreateMethod(wxCheckListBox, Check_gurax));
	Assign(Gurax_CreateMethod(wxCheckListBox, IsChecked_gurax));
	Assign(Gurax_CreateMethod(wxCheckListBox, GetCheckedItems_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCheckListBox
//------------------------------------------------------------------------------
VType& Value_wxCheckListBox::vtype = VTYPE_wxCheckListBox;

String Value_wxCheckListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CheckListBox");
}

//------------------------------------------------------------------------------
// Value_wxCheckListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
