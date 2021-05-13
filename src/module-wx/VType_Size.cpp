//==============================================================================
// VType_Size.cpp
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
// wx.Size() {block?}
Gurax_DeclareConstructor(Size)
{
	Declare(VTYPE_Size, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Size` instance.");
}

Gurax_ImplementConstructor(Size)
{
	// Function body
	Value_Size::EntityT entity;
	RefPtr<Value_Size> pValue(new Value_Size(entity));
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Size
//------------------------------------------------------------------------------
VType_Size VTYPE_Size("Size");

void VType_Size::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Window, Flag::Mutable, Gurax_CreateConstructor(Size));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Size, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Size, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Size
//------------------------------------------------------------------------------
VType& Value_Size::vtype = VTYPE_Size;

String Value_Size::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Size");
}

Gurax_EndModuleScope(wx)
