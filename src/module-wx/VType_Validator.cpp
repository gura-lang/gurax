//==============================================================================
// VType_Validator.cpp
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
	Declare(VTYPE_Validator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Validator` instance.");
}

Gurax_ImplementConstructor(Validator)
{
	// Function body
	auto pEntity = new Value_Validator::EntityT();
	RefPtr<Value_Validator> pValue(new Value_Validator(pEntity));
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
// VType_Validator
//------------------------------------------------------------------------------
VType_Validator VTYPE_Validator("Validator");

void VType_Validator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_EvtHandler, Flag::Mutable, Gurax_CreateConstructor(Validator));
	// Assignment of method
	// Assignment of property
	//Assign(Gurax_CreateProperty(Validator, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Validator
//------------------------------------------------------------------------------
VType& Value_Validator::vtype = VTYPE_Validator;

String Value_Validator::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Validator");
}

//------------------------------------------------------------------------------
// Value_Validator::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
