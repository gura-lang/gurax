//==============================================================================
// VType_OLE.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(mswin)

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

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// mswin.OLE#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(OLE, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Skeleton.\n");
}

Gurax_ImplementMethod(OLE, MethodSkeleton)
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
// mswin.OLE#propSkeleton
Gurax_DeclareProperty_R(OLE, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(OLE, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_OLE
//------------------------------------------------------------------------------
VType_OLE VTYPE_OLE("OLE");

void VType_OLE::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(OLE, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(OLE, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_OLE
//------------------------------------------------------------------------------
VType& Value_OLE::vtype = VTYPE_OLE;

Value* Value_OLE::DoGetProperty(const Symbol* pSymbol, const Attribute& attr, bool notFoundErrorFlag)
{
	return nullptr;
}

String Value_OLE::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetOLE().ToString(ss));
}

	Gurax_EndModuleScope(mswin)
