//==============================================================================
// VType_GLUnurbs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glu.GLUnurbs, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glu.GLUnurbs, `en)}

${help.ComposeMethodHelp(glu.GLUnurbs, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// glu.GLUnurbs#propSkeleton
Gurax_DeclareProperty_R(GLUnurbs, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(GLUnurbs, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLUnurbs
//------------------------------------------------------------------------------
VType_GLUnurbs VTYPE_GLUnurbs("GLUnurbs");

void VType_GLUnurbs::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(GLUnurbs, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLUnurbs
//------------------------------------------------------------------------------
VType& Value_GLUnurbs::vtype = VTYPE_GLUnurbs;

String Value_GLUnurbs::ToString(const StringStyle& ss) const
{
	return "GLUnurbs";
}

Gurax_EndModuleScope(glu)
