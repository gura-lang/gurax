//==============================================================================
// VType_wxValidator.cpp
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
// wx.Validator() {block?}
Gurax_DeclareConstructorAlias(Validator_gurax, "Validator")
{
	Declare(VTYPE_wxValidator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.Validator.");
}

Gurax_ImplementConstructorEx(Validator_gurax, processor_gurax, argument_gurax)
{
	// Function body
	auto pEntity_gurax = new Value_wxValidator::EntityT();
	RefPtr<Value_wxValidator> pValue_gurax(new Value_wxValidator(pEntity_gurax));
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
// VType_wxValidator
//------------------------------------------------------------------------------
VType_wxValidator VTYPE_wxValidator("Validator");

void VType_wxValidator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Validator_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxValidator
//------------------------------------------------------------------------------
VType& Value_wxValidator::vtype = VTYPE_wxValidator;

String Value_wxValidator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Validator");
}

//------------------------------------------------------------------------------
// Value_wxValidator::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
