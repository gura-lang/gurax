//==============================================================================
// VType_bzip2.cpp
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
// tar.bzip2.propSkeleton
Gurax_DeclareClassProperty_RW(bzip2, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(bzip2, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

Gurax_ImplementClassPropertySetter(bzip2, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
}

//------------------------------------------------------------------------------
// VType_bzip2
//------------------------------------------------------------------------------
VType_bzip2 VTYPE_bzip2("bzip2");

void VType_bzip2::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(bzip2, propSkeleton));
}

Gurax_EndModuleScope(tar)
