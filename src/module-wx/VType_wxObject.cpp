//==============================================================================
// VType_wxObject.cpp
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
// wx.Object() {block?}
Gurax_DeclareConstructor(Object)
{
	Declare(VTYPE_Object, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Object` instance.");
}

Gurax_ImplementConstructor(Object)
{
	// Function body
	RefPtr<Value_wxObject> pValue(new Value_wxObject(wxObject()));
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxObject
//------------------------------------------------------------------------------
VType_wxObject VTYPE_wxObject("Object");

void VType_wxObject::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Object));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Object, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Object, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxObject
//------------------------------------------------------------------------------
VType& Value_wxObject::vtype = VTYPE_wxObject;

String Value_wxObject::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Object");
}

Gurax_EndModuleScope(wx)
