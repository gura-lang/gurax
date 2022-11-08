//==============================================================================
// VType_wxEditableListBox.cpp
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

${help.ComposePropertyHelp(wx.EditableListBox, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.EditableListBox, `en)}

${help.ComposeMethodHelp(wx.EditableListBox, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.EditableListBox(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(EditableListBox_gurax, "EditableListBox")
{
	Declare(VTYPE_wxEditableListBox, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.EditableListBox.");
}

Gurax_ImplementConstructorEx(EditableListBox_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const char* label = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxEL_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxEditableListBoxNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxEditableListBox::EntityT(parent, id, label, pos, size, style, name);
	RefPtr<Value_wxEditableListBox> pValue_gurax(new Value_wxEditableListBox(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.EditableListBox#Create(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxEditableListBox, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEditableListBox, Create_gurax, processor_gurax, argument_gurax)
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
	const char* label = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxEL_DEFAULT_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxEditableListBoxNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, label, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.EditableListBox#SetStrings(strings[] as String)
Gurax_DeclareMethodAlias(wxEditableListBox, SetStrings_gurax, "SetStrings")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("strings", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEditableListBox, SetStrings_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	wxArrayString strings = Util::CreateArrayString(args_gurax.PickList());
	// Function body
	pEntity_gurax->SetStrings(strings);
	return Gurax::Value::nil();
}

// wx.EditableListBox#GetStrings()
Gurax_DeclareMethodAlias(wxEditableListBox, GetStrings_gurax, "GetStrings")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxEditableListBox, GetStrings_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	wxArrayString strings;
	pEntity_gurax->GetStrings(strings);
	return Util::CreateList(strings);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxEditableListBox
//------------------------------------------------------------------------------
VType_wxEditableListBox VTYPE_wxEditableListBox("EditableListBox");

void VType_wxEditableListBox::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxPanel, Flag::Mutable, Gurax_CreateConstructor(EditableListBox_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxEditableListBox, Create_gurax));
	Assign(Gurax_CreateMethod(wxEditableListBox, SetStrings_gurax));
	Assign(Gurax_CreateMethod(wxEditableListBox, GetStrings_gurax));
}

//------------------------------------------------------------------------------
// Value_wxEditableListBox
//------------------------------------------------------------------------------
VType& Value_wxEditableListBox::vtype = VTYPE_wxEditableListBox;

String Value_wxEditableListBox::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EditableListBox");
}

//------------------------------------------------------------------------------
// Value_wxEditableListBox::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
