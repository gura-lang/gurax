//==============================================================================
// VType_wxSlider.cpp
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
// wx.Slider(parent as wx.Window, id as Number, value as Number, minValue as Number, maxValue as Number, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?} {block?}
Gurax_DeclareConstructorAlias(Slider_gurax, "Slider")
{
	Declare(VTYPE_wxSlider, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("value", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("minValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("maxValue", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Slider.");
}

Gurax_ImplementConstructorEx(Slider_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	int value = args_gurax.PickNumber<int>();
	int minValue = args_gurax.PickNumber<int>();
	int maxValue = args_gurax.PickNumber<int>();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxSL_HORIZONTAL;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxSliderNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxSlider::EntityT(parent, id, value, minValue, maxValue, pos, size, style, validator, name);
	RefPtr<Value_wxSlider> pValue_gurax(new Value_wxSlider(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSlider
//------------------------------------------------------------------------------
VType_wxSlider VTYPE_wxSlider("Slider");

void VType_wxSlider::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(Slider_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxSlider
//------------------------------------------------------------------------------
VType& Value_wxSlider::vtype = VTYPE_wxSlider;

String Value_wxSlider::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Slider");
}

//------------------------------------------------------------------------------
// Value_wxSlider::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
