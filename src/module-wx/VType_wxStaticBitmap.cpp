//==============================================================================
// VType_wxStaticBitmap.cpp
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

${help.ComposePropertyHelp(wxStaticBitmap)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxStaticBitmap)}

${help.ComposeMethodHelp(wxStaticBitmap)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StaticBitmap(parent as wx.Window, id as Number, label as wx.Bitmap, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(StaticBitmap_gurax, "StaticBitmap")
{
	Declare(VTYPE_wxStaticBitmap, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.StaticBitmap.");
}

Gurax_ImplementConstructorEx(StaticBitmap_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	wxWindowID id = args_gurax.PickNumber<wxWindowID>();
	Value_wxBitmap& value_label = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& label = value_label.GetEntity();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStaticBitmapNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxStaticBitmap::EntityT(parent, id, label, pos, size, style, name);
	RefPtr<Value_wxStaticBitmap> pValue_gurax(new Value_wxStaticBitmap(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StaticBitmap#Create(parent as wx.Window, id as Number, label as wx.Bitmap, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String)
Gurax_DeclareMethodAlias(wxStaticBitmap, Create_gurax, "Create")
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("label", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticBitmap, Create_gurax, processor_gurax, argument_gurax)
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
	Value_wxBitmap& value_label = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& label = value_label.GetEntity();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : 0;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStaticBitmapNameStr;
	// Function body
	bool rtn = pEntity_gurax->Create(parent, id, label, pos, size, style, name);
	return new Gurax::Value_Bool(rtn);
}

// wx.StaticBitmap#GetBitmap() {block?}
Gurax_DeclareMethodAlias(wxStaticBitmap, GetBitmap_gurax, "GetBitmap")
{
	Declare(VTYPE_wxBitmap, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticBitmap, GetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxBitmap(
		pEntity_gurax->GetBitmap()));
}

// wx.StaticBitmap#GetIcon() {block?}
Gurax_DeclareMethodAlias(wxStaticBitmap, GetIcon_gurax, "GetIcon")
{
	Declare(VTYPE_wxIcon, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticBitmap, GetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxIcon(
		pEntity_gurax->GetIcon()));
}

// wx.StaticBitmap#SetBitmap(label as wx.Bitmap)
Gurax_DeclareMethodAlias(wxStaticBitmap, SetBitmap_gurax, "SetBitmap")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_wxBitmap, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticBitmap, SetBitmap_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxBitmap& value_label = args_gurax.Pick<Value_wxBitmap>();
	const wxBitmap& label = value_label.GetEntity();
	// Function body
	pEntity_gurax->SetBitmap(label);
	return Gurax::Value::nil();
}

// wx.StaticBitmap#SetIcon(label as wx.Icon)
Gurax_DeclareMethodAlias(wxStaticBitmap, SetIcon_gurax, "SetIcon")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("label", VTYPE_wxIcon, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticBitmap, SetIcon_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxIcon& value_label = args_gurax.Pick<Value_wxIcon>();
	const wxIcon& label = value_label.GetEntity();
	// Function body
	pEntity_gurax->SetIcon(label);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStaticBitmap
//------------------------------------------------------------------------------
VType_wxStaticBitmap VTYPE_wxStaticBitmap("StaticBitmap");

void VType_wxStaticBitmap::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StaticBitmap_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStaticBitmap, Create_gurax));
	Assign(Gurax_CreateMethod(wxStaticBitmap, GetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxStaticBitmap, GetIcon_gurax));
	Assign(Gurax_CreateMethod(wxStaticBitmap, SetBitmap_gurax));
	Assign(Gurax_CreateMethod(wxStaticBitmap, SetIcon_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStaticBitmap
//------------------------------------------------------------------------------
VType& Value_wxStaticBitmap::vtype = VTYPE_wxStaticBitmap;

String Value_wxStaticBitmap::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StaticBitmap");
}

//------------------------------------------------------------------------------
// Value_wxStaticBitmap::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
