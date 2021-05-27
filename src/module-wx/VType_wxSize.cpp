//==============================================================================
// VType_wxSize.cpp
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
// wx.Size(width? as Number, height? as Number) {block?}
Gurax_DeclareConstructor(Size)
{
	Declare(VTYPE_wxSize, Flag::None);
	DeclareArg("width", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("height", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `wx.Size` instance.");
}

Gurax_ImplementConstructor(Size)
{
	// Argument
	ArgPicker args(argument);
	int width = args.IsValid()? args.PickNumber<int>() : 0;
	int height = args.IsValid()? args.PickNumber<int>() : 0;
	// Function body
	Value_wxSize::EntityT entity(width, height);
	RefPtr<Value_wxSize> pValue(new Value_wxSize(entity));
	return argument.ReturnValue(processor, pValue.release());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_wxSize
//------------------------------------------------------------------------------
VType_wxSize VTYPE_wxSize("Size");

void VType_wxSize::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Mutable, Gurax_CreateConstructor(Size));
	// Assignment of method
	//Assign(Gurax_CreateMethod(Size, OnInit));
	// Assignment of property
	//Assign(Gurax_CreateProperty(Size, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_wxSize
//------------------------------------------------------------------------------
VType& Value_wxSize::vtype = VTYPE_wxSize;

String Value_wxSize::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "wx.Size");
}

Gurax_EndModuleScope(wx)
