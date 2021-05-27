//==============================================================================
// VType_wxValidator.cpp
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
Gurax_DeclareConstructor(Validator)
{
	Declare(VTYPE_wxValidator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Validator` instance.");
}

Gurax_ImplementConstructor(Validator)
{
	// Function body
	auto pEntity = new Value_wxValidator::EntityT();
	RefPtr<Value_wxValidator> pValue(new Value_wxValidator(pEntity));
	pEntity->core.SetInfo(processor.Reference(), *pValue);
	return argument.ReturnValue(processor, pValue.release());
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
	Declare(VTYPE_wxEvtHandler, Flag::Mutable, Gurax_CreateConstructor(Validator));
	// Assignment of method
	// Assignment of property
	//Assign(Gurax_CreateProperty(Validator, propSkeleton));
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
