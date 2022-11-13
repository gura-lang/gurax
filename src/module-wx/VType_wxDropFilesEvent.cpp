﻿//==============================================================================
// VType_wxDropFilesEvent.cpp
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

${help.ComposePropertyHelp(wx.DropFilesEvent, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(wx.DropFilesEvent, `en)}

${help.ComposeMethodHelp(wx.DropFilesEvent, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// wx.DropFilesEvent#GetNumberOfFiles()
Gurax_DeclareMethodAlias(wxDropFilesEvent, GetNumberOfFiles_gurax, "GetNumberOfFiles")
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxDropFilesEvent, GetNumberOfFiles_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	int rtn = pEntity_gurax->GetNumberOfFiles();
	return new Gurax::Value_Number(rtn);
}

// wx.DropFilesEvent#GetPosition() {block?}
Gurax_DeclareMethodAlias(wxDropFilesEvent, GetPosition_gurax, "GetPosition")
{
	Declare(VTYPE_wxPoint, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementMethodEx(wxDropFilesEvent, GetPosition_gurax, processor_gurax, argument_gurax)
{
	// Target
	auto& valueThis_gurax = GetValueThis(argument_gurax);
	auto pEntity_gurax = valueThis_gurax.GetEntityPtr();
	if (!pEntity_gurax) return Value::nil();
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxPoint(
		pEntity_gurax->GetPosition()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxDropFilesEvent
//------------------------------------------------------------------------------
VType_wxDropFilesEvent VTYPE_wxDropFilesEvent("DropFilesEvent");

void VType_wxDropFilesEvent::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp("en", g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvent, Flag::Mutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(wxDropFilesEvent, GetNumberOfFiles_gurax));
	Assign(Gurax_CreateMethod(wxDropFilesEvent, GetPosition_gurax));
}

//------------------------------------------------------------------------------
// Value_wxDropFilesEvent
//------------------------------------------------------------------------------
VType& Value_wxDropFilesEvent::vtype = VTYPE_wxDropFilesEvent;
EventValueFactoryDeriv<Value_wxDropFilesEvent> Value_wxDropFilesEvent::eventValueFactory;

String Value_wxDropFilesEvent::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.DropFilesEvent");
}

Gurax_EndModuleScope(wx)
