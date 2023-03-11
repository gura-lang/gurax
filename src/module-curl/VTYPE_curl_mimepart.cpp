//==============================================================================
// VType_curl_mimepart.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.curl_mimepart, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.curl_mimepart, `en)}

${help.ComposeMethodHelp(curl.curl_mimepart, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.curl_mimepart() {block?}
Gurax_DeclareConstructor(curl_mimepart)
{
	Declare(VTYPE_curl_mimepart, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `curl.curl_mimepart` instance.
)""");
}

Gurax_ImplementConstructor(curl_mimepart)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<curl_mimepart> curl_mimepart(new curl_mimepart());
	//return argument.ReturnValue(processor, new Value_curl_mimepart(curl_mimepart.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.curl_mimepart#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(curl_mimepart, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(curl_mimepart, MethodSkeleton)
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
// curl.curl_mimepart#propSkeleton
Gurax_DeclareProperty_R(curl_mimepart, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(curl_mimepart, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_curl_mimepart
//------------------------------------------------------------------------------
VType_curl_mimepart VTYPE_curl_mimepart("curl_mimepart");

void VType_curl_mimepart::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(curl_mimepart));
	// Assignment of method
	Assign(Gurax_CreateMethod(curl_mimepart, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(curl_mimepart, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_curl_mimepart
//------------------------------------------------------------------------------
VType& Value_curl_mimepart::vtype = VTYPE_curl_mimepart;

String Value_curl_mimepart::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.curl_mimepart");
}

Gurax_EndModuleScope(curl)
