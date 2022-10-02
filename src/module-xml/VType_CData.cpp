//==============================================================================
// VType_CData.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(xml)

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
// xml.CData() {block?}
Gurax_DeclareConstructor(CData)
{
	Declare(VTYPE_CData, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `xml.CData` instance.");
}

Gurax_ImplementConstructor(CData)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<CData> pCData(new CData());
	return argument.ReturnValue(processor, new Value_CData(pCData.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// xml.CData#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(CData, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(CData, MethodSkeleton)
{
	// Target
	//auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Double num1 = args.PickNumber<Double>();
	Double num2 = args.PickNumber<Double>();
	// Function body
	return new Value_Number(num1 + num2);
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// xml.CData#propSkeleton
Gurax_DeclareProperty_R(CData, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(CData, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_CData
//------------------------------------------------------------------------------
VType_CData VTYPE_CData("CData");

void VType_CData::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Node, Flag::Immutable, Gurax_CreateConstructor(CData));
	// Assignment of method
	Assign(Gurax_CreateMethod(CData, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(CData, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_CData
//------------------------------------------------------------------------------
VType& Value_CData::vtype = VTYPE_CData;

String Value_CData::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCData().ToString(ss));
}

Gurax_EndModuleScope(xml)
