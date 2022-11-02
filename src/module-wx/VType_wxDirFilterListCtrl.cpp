//==============================================================================
// VType_wxDirFilterListCtrl.cpp
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

${help.ComposePropertyHelp(wxDirFilterListCtrl)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxDirFilterListCtrl)}

${help.ComposeMethodHelp(wxDirFilterListCtrl)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.DirFilterListCtrl(parent as wx.GenericDirCtrl, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number) {block?}
Gurax_DeclareConstructorAlias(DirFilterListCtrl_gurax, "DirFilterListCtrl")
{
	Declare(VTYPE_wxDirFilterListCtrl, Flag::None);
	DeclareArg("parent", VTYPE_wxGenericDirCtrl, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.DirFilterListCtrl.");
}

Gurax_ImplementConstructorEx(DirFilterListCtrl_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGenericDirCtrl& value_parent = args_gurax.Pick<Value_wxGenericDirCtrl>();
	wxGenericDirCtrl* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	auto pEntity_gurax = new Value_wxDirFilterListCtrl::EntityT(parent, id, pos, size, style);
	RefPtr<Value_wxDirFilterListCtrl> pValue_gurax(new Value_wxDirFilterListCtrl(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DirFilterListCtrl#Create(parent as wx.GenericDirCtrl, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number)
Gurax_DeclareMethodAlias(wxDirFilterListCtrl, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxGenericDirCtrl, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirFilterListCtrl, Create_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxGenericDirCtrl& value_parent = args_gurax.Pick<Value_wxGenericDirCtrl>();
	wxGenericDirCtrl* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, pos, size, style);
	return new Gurax::Value_Bool(rtn);
}

// wx.DirFilterListCtrl#Init()
Gurax_DeclareMethodAlias(wxDirFilterListCtrl, Init_gurax, "Init")
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirFilterListCtrl, Init_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	pEntity_gurax->Init();
	return Gurax::Value::nil();
}

// wx.DirFilterListCtrl#FillFilterList(filter as String, defaultFilter as Number)
Gurax_DeclareMethodAlias(wxDirFilterListCtrl, FillFilterList_gurax, "FillFilterList")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("filter", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("defaultFilter", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxDirFilterListCtrl, FillFilterList_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filter = args_gurax.PickString();
	int defaultFilter = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->FillFilterList(filter, defaultFilter);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDirFilterListCtrl
//------------------------------------------------------------------------------
VType_wxDirFilterListCtrl VTYPE_wxDirFilterListCtrl("DirFilterListCtrl");

void VType_wxDirFilterListCtrl::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxChoice, Flag::Mutable, Gurax_CreateConstructor(DirFilterListCtrl_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDirFilterListCtrl, Create_gurax));
	Assign(Gurax_CreateMethod(wxDirFilterListCtrl, Init_gurax));
	Assign(Gurax_CreateMethod(wxDirFilterListCtrl, FillFilterList_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDirFilterListCtrl
//------------------------------------------------------------------------------
VType& Value_wxDirFilterListCtrl::vtype = VTYPE_wxDirFilterListCtrl;

String Value_wxDirFilterListCtrl::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DirFilterListCtrl");
}

//------------------------------------------------------------------------------
// Value_wxDirFilterListCtrl::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
