//==============================================================================
// VType_MenuItem.cpp
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
// wx.MenuItem() {block?}
Gurax_DeclareConstructor(MenuItem)
{
	Declare(VTYPE_MenuItem, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.MenuItem` instance.");
}

Gurax_ImplementConstructor(MenuItem)
{
	// Function body
	//auto pEntity = new Value_MenuItem::EntityT();
	//RefPtr<Value_MenuItem> pValue(new Value_MenuItem(pEntity));
	//pEntity->core.SetInfo(processor.Reference(), *pValue);
	//return argument.ReturnValue(processor, pValue.release());
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_MenuItem
//------------------------------------------------------------------------------
VType_MenuItem VTYPE_MenuItem("MenuItem");

void VType_MenuItem::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(MenuItem));
	// Assignment of method
	//Assign(Gurax_CreateMethod(MenuItem, Show));
	// Assignment of property
	//Assign(Gurax_CreateProperty(MenuItem, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_MenuItem
//------------------------------------------------------------------------------
VType& Value_MenuItem::vtype = VTYPE_MenuItem;

String Value_MenuItem::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.MenuItem");
}

//------------------------------------------------------------------------------
// Value_MenuItem::EntityT
//------------------------------------------------------------------------------

Gurax_EndModuleScope(wx)
