//==============================================================================
// VType_GLUtesselator.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(glu)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(glu.GLUtesselator, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(glu.GLUtesselator, `en)}

${help.ComposeMethodHelp(glu.GLUtesselator, `en)}
)""";

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// glu.GLUtesselator#propSkeleton
Gurax_DeclareProperty_R(GLUtesselator, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(GLUtesselator, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_GLUtesselator
//------------------------------------------------------------------------------
VType_GLUtesselator VTYPE_GLUtesselator("GLUtesselator");

void VType_GLUtesselator::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of property
	Assign(Gurax_CreateProperty(GLUtesselator, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_GLUtesselator
//------------------------------------------------------------------------------
VType& Value_GLUtesselator::vtype = VTYPE_GLUtesselator;

String Value_GLUtesselator::ToString(const StringStyle& ss) const
{
	return "GLUtesselator";
}

Gurax_EndModuleScope(glu)
