//==============================================================================
// VType_wxMetafileDC.cpp
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
// wx.MetafileDC(filename? as String) {block?}
Gurax_DeclareConstructorAlias(MetafileDC_gurax, "MetafileDC")
{
	Declare(VTYPE_wxMetafileDC, Flag::None);
	DeclareArg("filename", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an instance of wx.MetafileDC.");
}

Gurax_ImplementConstructorEx(MetafileDC_gurax, processor_gurax, argument_gurax)
{
	// Arguments
	Gurax::ArgPicker args_gurax(argument_gurax);
	const char* filename = args_gurax.IsValid()? args_gurax.PickString() : "";
	// Function body
	return argument_gurax.ReturnValue(processor_gurax, new Value_wxMetafileDC(
		wxMetafileDC(filename)));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxMetafileDC
//------------------------------------------------------------------------------
VType_wxMetafileDC VTYPE_wxMetafileDC("MetafileDC");

void VType_wxMetafileDC::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_wxDC, Flag::Mutable, Gurax_CreateConstructor(MetafileDC_gurax));
	// Assignment of method
}

//------------------------------------------------------------------------------
// Value_wxMetafileDC
//------------------------------------------------------------------------------
VType& Value_wxMetafileDC::vtype = VTYPE_wxMetafileDC;

String Value_wxMetafileDC::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MetafileDC");
}

Gurax_EndModuleScope(wx)
