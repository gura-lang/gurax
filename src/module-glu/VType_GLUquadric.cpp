//==============================================================================
// VType_GLUquadric.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glu.GLUquadric, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glu.GLUquadric, `en)}

${help.ComposeMethodHelp(glu.GLUquadric, `en)}
)**";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// glu.GLUquadric#propSkeleton
Gurax_DeclareProperty_R(GLUquadric, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Skeleton.
)**");
}

Gurax_ImplementPropertyGetter(GLUquadric, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLUquadric
//------------------------------------------------------------------------------
VType_GLUquadric VTYPE_GLUquadric("GLUquadric");

void VType_GLUquadric::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(GLUquadric, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLUquadric
//------------------------------------------------------------------------------
VType& Value_GLUquadric::vtype = VTYPE_GLUquadric;

String Value_GLUquadric::ToString(const StringStyle& ss) const
{
	return "GLUquadric";
}

Gurax_EndModuleScope(glu)
