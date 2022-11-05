//==============================================================================
// VType_wxStaticLine.cpp
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

${help.ComposePropertyHelp(wx.StaticLine, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.StaticLine, `en)}

${help.ComposeMethodHelp(wx.StaticLine, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.StaticLine(parent as wx.Window, id? as Number, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(StaticLine_gurax, "StaticLine")
{
	Declare(VTYPE_wxStaticLine, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("id", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.StaticLine.");
}

Gurax_ImplementConstructorEx(StaticLine_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	bool id_validFlag = args_gurax.IsValid();
	wxWindowID id = id_validFlag? args_gurax.PickNumber<wxWindowID>() : wxID_ANY;
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxLI_HORIZONTAL;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : wxStaticLineNameStr;
	// Function body
	auto pEntity_gurax = new Value_wxStaticLine::EntityT(parent, id, pos, size, style, name);
	RefPtr<Value_wxStaticLine> pValue_gurax(new Value_wxStaticLine(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.StaticLine#IsVertical()
Gurax_DeclareMethodAlias(wxStaticLine, IsVertical_gurax, "IsVertical")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxStaticLine, IsVertical_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsVertical();
	return new Gurax::Value_Bool(rtn);
}

// wx.StaticLine.GetDefaultSize()
Gurax_DeclareClassMethodAlias(wxStaticLine, GetDefaultSize_gurax, "GetDefaultSize")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassMethodEx(wxStaticLine, GetDefaultSize_gurax, processor_gurax, argument_gurax)
{
	// Function body
	int rtn = wxStaticLine::GetDefaultSize();
	return new Gurax::Value_Number(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxStaticLine
//------------------------------------------------------------------------------
VType_wxStaticLine VTYPE_wxStaticLine("StaticLine");

void VType_wxStaticLine::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxControl, Flag::Mutable, Gurax_CreateConstructor(StaticLine_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxStaticLine, IsVertical_gurax));
	Assign(Gurax_CreateMethod(wxStaticLine, GetDefaultSize_gurax));
}

//------------------------------------------------------------------------------
// Value_wxStaticLine
//------------------------------------------------------------------------------
VType& Value_wxStaticLine::vtype = VTYPE_wxStaticLine;

String Value_wxStaticLine::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.StaticLine");
}

//------------------------------------------------------------------------------
// Value_wxStaticLine::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
