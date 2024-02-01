//==============================================================================
// VType_LabelSet.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(ml_mnist)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(ml.mnist.LabelSet, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(ml.mnist.LabelSet, `en)}

${help.ComposeMethodHelp(ml.mnist.LabelSet, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// ml.mnist.LabelSet(stream as Stream):map {block?}
Gurax_DeclareConstructor(LabelSet)
{
	Declare(VTYPE_LabelSet, Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `ml.mnist.LabelSet` instance.
)""");
}

Gurax_ImplementConstructor(LabelSet)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<LabelSet> pLabelSet(new LabelSet());
	if (!pLabelSet->Read(stream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_LabelSet(pLabelSet.release()));
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// ml.mnist.LabelSet#nSamples
Gurax_DeclareProperty_R(LabelSet, nSamples)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(LabelSet, nSamples)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLabelSet().GetNSamples());
}

// ml.mnist.LabelSet#nClasses
Gurax_DeclareProperty_R(LabelSet, nClasses)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(LabelSet, nClasses)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetLabelSet().GetNClasses());
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
	Assign(Gurax_CreateProperty(LabelSet, nSamples));
	Assign(Gurax_CreateProperty(LabelSet, nClasses));
}

Value* VType_LabelSet::DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const
{
	RefPtr<Value_Stream> pValueCasted(value.Cast<Value_Stream>(processor, flags));
	if (!pValueCasted) return nullptr;
	RefPtr<LabelSet> pLabelSet(new LabelSet());
	if (!pLabelSet->Read(pValueCasted->GetStream())) return nullptr;
	return new Value_LabelSet(pLabelSet.release());
}

//------------------------------------------------------------------------------
// Value_LabelSet
//------------------------------------------------------------------------------
VType& Value_LabelSet::vtype = VTYPE_LabelSet;

String Value_LabelSet::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetLabelSet().ToString(ss));
}

Gurax_EndModuleScope(ml_mnist)
