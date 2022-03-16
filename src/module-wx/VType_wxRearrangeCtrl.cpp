//==============================================================================
// VType_wxRearrangeCtrl.cpp
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
// wx.RearrangeCtrl(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, order[] as Number, items[] as String, style? as Number, validator? as wx.Validator, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(RearrangeCtrl_gurax, "RearrangeCtrl")
{
	Declare(VTYPE_wxRearrangeCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.RearrangeCtrl.");
}

Gurax_ImplementConstructorEx(RearrangeCtrl_gurax, processor_gurax, argument_gurax)
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
	wxArrayInt order = Util::CreateArrayInt(args_gurax.PickList());
	wxArrayString items = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxRearrangeListNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxRearrangeCtrl::EntityT(parent, id, pos, size, order, items, style, validator, name);
	RefPtr<Value_wxRearrangeCtrl> pValue_gurax(new Value_wxRearrangeCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.RearrangeCtrl#Create(parent as wx.Window, id as Number, pos as wx.Point, size as wx.Size, order[] as Number, items[] as String, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxRearrangeCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::Once, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::Once, ArgFlag::None);
	DeclareArg("order", VTYPE_Number, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("items", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeCtrl, Create_gurax, processor_gurax, argument_gurax)
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
	wxArrayInt order = Util::CreateArrayInt(args_gurax.PickList());
	wxArrayString items = Util::CreateArrayString(args_gurax.PickList());
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxRearrangeListNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, order, items, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.RearrangeCtrl#GetList() {block?}
Gurax_DeclareMethodAlias(wxRearrangeCtrl, GetList_gurax, "GetList")
{
	Declare(VTYPE_wxRearrangeList, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxRearrangeCtrl, GetList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxRearrangeList(
		pEntity_gurax->GetList()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxRearrangeCtrl
//------------------------------------------------------------------------------
VType_wxRearrangeCtrl VTYPE_wxRearrangeCtrl("RearrangeCtrl");

void VType_wxRearrangeCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable, Gurax_CreateConstructor(RearrangeCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxRearrangeCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxRearrangeCtrl, GetList_gurax));
}

//------------------------------------------------------------------------------
// Value_wxRearrangeCtrl
//------------------------------------------------------------------------------
VType& Value_wxRearrangeCtrl::vtype = VTYPE_wxRearrangeCtrl;

String Value_wxRearrangeCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.RearrangeCtrl");
}

//------------------------------------------------------------------------------
// Value_wxRearrangeCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
