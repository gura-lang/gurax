//==============================================================================
// VType_wxChoicebook.cpp
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
// wx.Choicebook(parent as wx.Window, id as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(Choicebook_gurax, "Choicebook")
{
	Declare(VTYPE_wxChoicebook, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Choicebook.");
}

Gurax_ImplementConstructorEx(Choicebook_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	auto pEntity_gurax = new Value_wxChoicebook::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxChoicebook> pValue_gurax(new Value_wxChoicebook(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Choicebook#GetChoiceCtrl() {block?}
Gurax_DeclareMethodAlias(wxChoicebook, GetChoiceCtrl_gurax, "GetChoiceCtrl")
{
	Declare(VTYPE_wxChoice, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxChoicebook, GetChoiceCtrl_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxChoice(
		pEntity_gurax->GetChoiceCtrl()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxChoicebook
//------------------------------------------------------------------------------
VType_wxChoicebook VTYPE_wxChoicebook("Choicebook");

void VType_wxChoicebook::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxBookCtrlBase, Flag::Mutable, Gurax_CreateConstructor(Choicebook_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxChoicebook, GetChoiceCtrl_gurax));
}

//------------------------------------------------------------------------------
// Value_wxChoicebook
//------------------------------------------------------------------------------
VType& Value_wxChoicebook::vtype = VTYPE_wxChoicebook;

String Value_wxChoicebook::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Choicebook");
}

//------------------------------------------------------------------------------
// Value_wxChoicebook::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
