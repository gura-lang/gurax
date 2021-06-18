//==============================================================================
// VType_wxSizer.cpp
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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.Sizer#Add(item as Any, flags as wx.SizerFlags)
Gurax_DeclareMethodAlias(wxSizer, Add_gurax, "Add")
{
	Declare(VTYPE_wxSizerItem, Flag::None);
	DeclareArg("item", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("flags", VTYPE_wxSizerFlags, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSizer, Add_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Gurax::Value& item = args_gurax.PickValue();
	const wxSizerFlags& flags = args_gurax.Pick<Value_wxSizerFlags>().GetEntity();
	// Function body
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable->DeclareArg("", VTYPE_wxWindow);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, *pDeclCallable));
	} while (0);
	wxSizerItem* rtn;
	if (item.IsInstanceOf(VTYPE_wxWindow)) {
		rtn = pEntity_gurax->Add(Value_wxWindow::GetEntityPtr(item), flags);
	} else if (item.IsInstanceOf(VTYPE_wxSizer)) {
		rtn = pEntity_gurax->Add(Value_wxSizer::GetEntityPtr(item), flags);
	} else {
		Error::Issue(ErrorType::TypeError, "item must be an instance of wx.Window or wx.Sizer");
		return Value::nil();
	}
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerItem(*rtn));
}

// wx.Sizer#AddSpacer(size as Number)
Gurax_DeclareMethodAlias(wxSizer, AddSpacer_gurax, "AddSpacer")
{
	Declare(VTYPE_wxSizerItem, Flag::None);
	DeclareArg("size", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSizer, AddSpacer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int size = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerItem(
		*pEntity_gurax->AddSpacer(size)));
}

// wx.Sizer#AddStretchSpacer(prop as Number)
Gurax_DeclareMethodAlias(wxSizer, AddStretchSpacer_gurax, "AddStretchSpacer")
{
	Declare(VTYPE_wxSizerItem, Flag::None);
	DeclareArg("prop", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSizer, AddStretchSpacer_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int prop = args_gurax.PickNumber<int>();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSizerItem(
		*pEntity_gurax->AddStretchSpacer(prop)));
}

// wx.Sizer#CalcMin()
Gurax_DeclareMethodAlias(wxSizer, CalcMin_gurax, "CalcMin")
{
	Declare(VTYPE_wxSize, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSizer, CalcMin_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxSize(
		pEntity_gurax->CalcMin()));
}

// wx.Sizer#Clear(delete_windows? as Bool)
Gurax_DeclareMethodAlias(wxSizer, Clear_gurax, "Clear")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("delete_windows", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxSizer, Clear_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	bool delete_windows = args_gurax.IsValid()? args_gurax.PickBool() : false;
	// Function body
	pEntity_gurax->Clear(delete_windows);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSizer
//------------------------------------------------------------------------------
VType_wxSizer VTYPE_wxSizer("Sizer");

void VType_wxSizer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxObject, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxSizer, Add_gurax));
	Assign(Gurax_CreateMethod(wxSizer, AddSpacer_gurax));
	Assign(Gurax_CreateMethod(wxSizer, AddStretchSpacer_gurax));
	Assign(Gurax_CreateMethod(wxSizer, CalcMin_gurax));
	Assign(Gurax_CreateMethod(wxSizer, Clear_gurax));
}

//------------------------------------------------------------------------------
// Value_wxSizer
//------------------------------------------------------------------------------
VType& Value_wxSizer::vtype = VTYPE_wxSizer;

String Value_wxSizer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Sizer");
}

Gurax_EndModuleScope(wx)
