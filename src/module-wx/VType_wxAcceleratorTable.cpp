﻿//==============================================================================
// VType_wxAcceleratorTable.cpp
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

${help.ComposePropertyHelp(wx.AcceleratorTable, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.AcceleratorTable, `en)}

${help.ComposeMethodHelp(wx.AcceleratorTable, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// wx.AcceleratorTable(args* as Any) {block?}
Gurax_DeclareConstructorAlias(AcceleratorTable_gurax, "AcceleratorTable")
{
	Declare(VTYPE_wxAcceleratorTable, Flag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an instance of wx.AcceleratorTable.
)**");
}

Gurax_ImplementConstructorEx(AcceleratorTable_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const Gurax::ValueList& args = args_gurax.PickList();
	// Function body
	// wxAcceleratorTable(resource as String)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("resource", VTYPE_String);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const char* resource = args.PickString();
		return new Value_wxAcceleratorTable(wxAcceleratorTable(resource));
	} while (0);
	Error::ClearIssuedFlag();
	// wxAcceleratorTable(entries[] as AcceleratorEntry)
	do {
		static DeclCallable* pDeclCallable = nullptr;
		if (!pDeclCallable) {
			pDeclCallable = new DeclCallable();
			pDeclCallable->DeclareArg("entries", VTYPE_wxAcceleratorEntry, DeclArg::Occur::Once, DeclArg::Flag::ListVar);
		}
		RefPtr<Argument> pArgument(new Argument(processor_gurax, pDeclCallable->Reference()));
		if (!pArgument->FeedValuesAndComplete(processor_gurax, args)) break;
		Error::Clear();
		ArgPicker args(*pArgument);
		const ValueList& values = args.PickList();
		std::unique_ptr<wxAcceleratorEntry> entries(new wxAcceleratorEntry[values.size()]);
		size_t i = 0;
		for (const Value* pValue : values) entries.get()[i++] = Value_wxAcceleratorEntry::GetEntity(*pValue);
		return new Value_wxAcceleratorTable(wxAcceleratorTable(values.size(), entries.get()));
	} while (0);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.AcceleratorTable#IsOk()
Gurax_DeclareMethodAlias(wxAcceleratorTable, IsOk_gurax, "IsOk")
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxAcceleratorTable, IsOk_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	bool rtn = pEntity_gurax->IsOk();
	return new Gurax::Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxAcceleratorTable
//------------------------------------------------------------------------------
VType_wxAcceleratorTable VTYPE_wxAcceleratorTable("AcceleratorTable");

void VType_wxAcceleratorTable::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(AcceleratorTable_gurax));
	// Assignment of method
	Assign(Gurax_CreateMethod(wxAcceleratorTable, IsOk_gurax));
}

//------------------------------------------------------------------------------
// Value_wxAcceleratorTable
//------------------------------------------------------------------------------
VType& Value_wxAcceleratorTable::vtype = VTYPE_wxAcceleratorTable;

String Value_wxAcceleratorTable::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.AcceleratorTable");
}

Gurax_EndModuleScope(wx)
