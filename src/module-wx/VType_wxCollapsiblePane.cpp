//==============================================================================
// VType_wxCollapsiblePane.cpp
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

${help.ComposePropertyHelp(wx.CollapsiblePane, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.CollapsiblePane, `en)}

${help.ComposeMethodHelp(wx.CollapsiblePane, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.CollapsiblePane(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String) {block?}
Gurax_DeclareConstructorAlias(CollapsiblePane_gurax, "CollapsiblePane")
{
	Declare(VTYPE_wxCollapsiblePane, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.CollapsiblePane.");
}

Gurax_ImplementConstructorEx(CollapsiblePane_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxCP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxCollapsiblePaneNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxCollapsiblePane::EntityT(parent, id, label, pos, size, style, validator, name);
	RefPtr<Value_wxCollapsiblePane> pValue_gurax(new Value_wxCollapsiblePane(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.CollapsiblePane#Create(parent as wx.Window, id as Number, label as String, pos? as wx.Point, size? as wx.Size, style? as Number, validator? as wx.Validator, name? as String)
Gurax_DeclareMethodAlias(wxCollapsiblePane, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("validator", VTYPE_wxValidator, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, Create_gurax, processor_gurax, argument_gurax)
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
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxCP_DEFAULT_STYLE;
	const wxValidator& validator = args_gurax.IsValid()? args_gurax.Pick<Value_wxValidator>().GetEntity() : wxDefaultValidator;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxCollapsiblePaneNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, label, pos, size, style, validator, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.CollapsiblePane#Collapse(collapse? as Bool)
Gurax_DeclareMethodAlias(wxCollapsiblePane, Collapse_gurax, "Collapse")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("collapse", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, Collapse_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool collapse = args_gurax.IsValid()? args_gurax.PickBool() : true;
	// Function body
	pEntity_gurax->Collapse(collapse);
	return Gurax::Value::nil();
}

// wx.CollapsiblePane#Expand()
Gurax_DeclareMethodAlias(wxCollapsiblePane, Expand_gurax, "Expand")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, Expand_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Expand();
	return Gurax::Value::nil();
}

// wx.CollapsiblePane#GetPane() {block?}
Gurax_DeclareMethodAlias(wxCollapsiblePane, GetPane_gurax, "GetPane")
{
	Declare(VTYPE_wxWindow, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, GetPane_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxWindow(
		pEntity_gurax->GetPane()));
}

// wx.CollapsiblePane#IsCollapsed()
Gurax_DeclareMethodAlias(wxCollapsiblePane, IsCollapsed_gurax, "IsCollapsed")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, IsCollapsed_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsCollapsed();
	return new Gurax::Value_Bool(rtn);
}

// wx.CollapsiblePane#IsExpanded()
Gurax_DeclareMethodAlias(wxCollapsiblePane, IsExpanded_gurax, "IsExpanded")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxCollapsiblePane, IsExpanded_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsExpanded();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxCollapsiblePane
//------------------------------------------------------------------------------
VType_wxCollapsiblePane VTYPE_wxCollapsiblePane("CollapsiblePane");

void VType_wxCollapsiblePane::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(CollapsiblePane_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxCollapsiblePane, Create_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePane, Collapse_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePane, Expand_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePane, GetPane_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePane, IsCollapsed_gurax));
	Assign(Gurax_CreateMethod(wxCollapsiblePane, IsExpanded_gurax));
}

//------------------------------------------------------------------------------
// Value_wxCollapsiblePane
//------------------------------------------------------------------------------
VType& Value_wxCollapsiblePane::vtype = VTYPE_wxCollapsiblePane;

String Value_wxCollapsiblePane::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.CollapsiblePane");
}

//------------------------------------------------------------------------------
// Value_wxCollapsiblePane::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
