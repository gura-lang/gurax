//==============================================================================
// VType_gzip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

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
// Implementation of class property
//-----------------------------------------------------------------------------
// tar.gzip.propSkeleton
Gurax_DeclareClassProperty_RW(gzip, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(gzip, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

Gurax_ImplementClassPropertySetter(gzip, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
}

//------------------------------------------------------------------------------
// VType_gzip
//------------------------------------------------------------------------------
VType_gzip VTYPE_gzip("gzip");

void VType_gzip::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(gzip, propSkeleton));
}

Gurax_EndModuleScope(tar)
