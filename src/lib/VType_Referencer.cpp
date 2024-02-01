//==============================================================================
// VType_Referencer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(Referencer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Referencer, `en)}

${help.ComposeMethodHelp(Referencer, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
#if 0
// Referencer() {block?}
Gurax_DeclareConstructor(Referencer)
{
	Declare(VTYPE_Referencer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Referencer` instance.
)""");
}

Gurax_ImplementConstructor(Referencer)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	RefPtr<Referencer> pReferencer(new Referencer());
	return argument.ReturnValue(processor, new Value_Referencer(pReferencer.release()));
}
#endif

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
#if 0
// Referencer#MethodSkeleton(num1 as Number, num2 as Number)
Gurax_DeclareMethod(Referencer, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Referencer, MethodSkeleton)
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
#endif

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Referencer#@
Gurax_DeclarePropertyAlias_RW(Referencer, at_, "@")
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementPropertyGetter(Referencer, at_)
{
	auto& valueThis = GetValueThis(valueTarget);
	return valueThis.GetReferencer().GetValue().Reference();
}

Gurax_ImplementPropertySetter(Referencer, at_)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetReferencer().SetValue(processor, value.Reference());
}

//------------------------------------------------------------------------------
// VType_Referencer
//------------------------------------------------------------------------------
VType_Referencer VTYPE_Referencer("Referencer");

void VType_Referencer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	//Assign(Gurax_CreateMethod(Referencer, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(Referencer, at_));
}

//------------------------------------------------------------------------------
// Value_Referencer
//------------------------------------------------------------------------------
VType& Value_Referencer::vtype = VTYPE_Referencer;

String Value_Referencer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetReferencer().ToString(ss));
}

}
