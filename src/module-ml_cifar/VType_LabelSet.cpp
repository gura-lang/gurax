//==============================================================================
// VType_LabelSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.cifar.LabelSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.cifar.LabelSet, `en)}

${help.ComposeMethodHelp(ml.cifar.LabelSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.cifar.LabelSet() {block?}
Gurax_DeclareConstructor(LabelSet)
{
	Declare(VTYPE_LabelSet, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.cifar.LabelSet` instance.
)""");
}

Gurax_ImplementConstructor(LabelSet)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<LabelSet> pLabelSet(new LabelSet());
	return argument.ReturnValue(processor, new Value_LabelSet(pLabelSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.cifar.LabelSet#propSkeleton
Gurax_DeclareProperty_R(LabelSet, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(LabelSet, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_LabelSet
//------------------------------------------------------------------------------
VType_LabelSet VTYPE_LabelSet("LabelSet");

void VType_LabelSet::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(LabelSet));
	// Assignment of method
	// Assignment of property
	//Assign(Gurax_CreateProperty(LabelSet, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_LabelSet
//------------------------------------------------------------------------------
VType& Value_LabelSet::vtype = VTYPE_LabelSet;

String Value_LabelSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLabelSet().ToString(ss));
}

Gurax_EndModuleScope(ml_cifar)
