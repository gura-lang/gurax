//==============================================================================
// VType_Info.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(bmp)

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
// bmp.Info() {block?}
Gurax_DeclareConstructor(Info)
{
	Declare(VTYPE_Info, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Info` instance.");
}

Gurax_ImplementConstructor(Info)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Info> pInfo(new Info());
	return argument.ReturnValue(processor, new Value_Info(pInfo.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// bmp.Info#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(Info, MethodSkeleton)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(Info, MethodSkeleton)
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
// bmp.Info#propSkeleton
Gurax_DeclareProperty_R(Info, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Info, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Info
//------------------------------------------------------------------------------
VType_Info VTYPE_Info("Info");

void VType_Info::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Info));
	// Assignment of method
	Assign(Gurax_CreateMethod(Info, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Info, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Info
//------------------------------------------------------------------------------
VType& Value_Info::vtype = VTYPE_Info;

Gurax_EndModuleScope(bmp)
