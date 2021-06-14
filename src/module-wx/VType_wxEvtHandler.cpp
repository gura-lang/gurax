//==============================================================================
// VType_wxEvtHandler.cpp
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
// wx.EvtHandler() {block?}
Gurax_DeclareConstructorAlias(EvtHandler_gurax, "EvtHandler")
{
	Declare(VTYPE_wxEvtHandler, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.EvtHandler.");
}

Gurax_ImplementConstructorEx(EvtHandler_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxEvtHandler::EntityT();
	RefPtr<Value_wxEvtHandler> pValue_gurax(new Value_wxEvtHandler(pEntity_gurax));
	pEntity_gurax->core.SetInfo(processor_gurax.Reference(), *pValue_gurax);
	return argument_gurax.ReturnValue(processor_gurax, pValue_gurax.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxEvtHandler
//------------------------------------------------------------------------------
VType_wxEvtHandler VTYPE_wxEvtHandler("EvtHandler");

void VType_wxEvtHandler::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(EvtHandler_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxEvtHandler
//------------------------------------------------------------------------------
VType& Value_wxEvtHandler::vtype = VTYPE_wxEvtHandler;

String Value_wxEvtHandler::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.EvtHandler");
}

Gurax_EndModuleScope(wx)
