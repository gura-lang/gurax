//==============================================================================
// VType_wxPrintAbortDialog.cpp
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

${help.ComposePropertyHelp(wxPrintAbortDialog)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wxPrintAbortDialog)}

${help.ComposeMethodHelp(wxPrintAbortDialog)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.PrintAbortDialog(parent as wx.Window, documentTitle as String, pos? as wx.Point, size? as wx.Size, style? as Number, name? as String) {block?}
Gurax_DeclareConstructorAlias(PrintAbortDialog_gurax, "PrintAbortDialog")
{
	Declare(VTYPE_wxPrintAbortDialog, Flag::None);
	DeclareArg("parent", VTYPE_wxWindow, ArgOccur::Once, ArgFlag::None);
	DeclareArg("documentTitle", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_wxPoint, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("size", VTYPE_wxSize, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("style", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.PrintAbortDialog.");
}

Gurax_ImplementConstructorEx(PrintAbortDialog_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	Value_wxWindow& value_parent = args_gurax.Pick<Value_wxWindow>();
	wxWindow* parent = value_parent.GetEntityPtr();
	const char* documentTitle = args_gurax.PickString();
	const wxPoint& pos = args_gurax.IsValid()? args_gurax.Pick<Value_wxPoint>().GetEntity() : wxDefaultPosition;
	const wxSize& size = args_gurax.IsValid()? args_gurax.Pick<Value_wxSize>().GetEntity() : wxDefaultSize;
	bool style_validFlag = args_gurax.IsValid();
	long style = style_validFlag? args_gurax.PickNumber<long>() : wxDEFAULT_DIALOG_STYLE;
	const char* name = args_gurax.IsValid()? args_gurax.PickString() : "dialog";
	// Function body
	auto pEntity_gurax = new Value_wxPrintAbortDialog::EntityT(parent, documentTitle, pos, size, style, name);
	RefPtr<Value_wxPrintAbortDialog> pValue_gurax(new Value_wxPrintAbortDialog(pEntity_gurax));
	pEntity_gurax->core_gurax.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.PrintAbortDialog#SetProgress(currentPage as Number, totalPages as Number, currentCopy as Number, totalCopies as Number)
Gurax_DeclareMethodAlias(wxPrintAbortDialog, SetProgress_gurax, "SetProgress")
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("currentPage", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("totalPages", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("currentCopy", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("totalCopies", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethodEx(wxPrintAbortDialog, SetProgress_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	int currentPage = args_gurax.PickNumber<int>();
	int totalPages = args_gurax.PickNumber<int>();
	int currentCopy = args_gurax.PickNumber<int>();
	int totalCopies = args_gurax.PickNumber<int>();
	// Function body
	pEntity_gurax->SetProgress(currentPage, totalPages, currentCopy, totalCopies);
	return Gurax::Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxPrintAbortDialog
//------------------------------------------------------------------------------
VType_wxPrintAbortDialog VTYPE_wxPrintAbortDialog("PrintAbortDialog");

void VType_wxPrintAbortDialog::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDialog, Flag::Mutable, Gurax_CreateConstructor(PrintAbortDialog_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxPrintAbortDialog, SetProgress_gurax));
}

//------------------------------------------------------------------------------
// Value_wxPrintAbortDialog
//------------------------------------------------------------------------------
VType& Value_wxPrintAbortDialog::vtype = VTYPE_wxPrintAbortDialog;

String Value_wxPrintAbortDialog::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.PrintAbortDialog");
}

//------------------------------------------------------------------------------
// Value_wxPrintAbortDialog::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
