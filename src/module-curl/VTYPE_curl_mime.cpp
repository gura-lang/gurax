//==============================================================================
// VType_curl_mime.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.curl_mime, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.curl_mime, `en)}

${help.ComposeMethodHelp(curl.curl_mime, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.curl_mime() {block?}
Gurax_DeclareConstructor(curl_mime)
{
	Declare(VTYPE_curl_mime, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `curl.curl_mime` instance.
)**");
}

Gurax_ImplementConstructor(curl_mime)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<curl_mime> curl_mime(new curl_mime());
	//return argument.ReturnValue(processor, new Value_curl_mime(curl_mime.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.curl_mime#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(curl_mime, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(curl_mime, MethodSkeleton)
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
// curl.curl_mime#propSkeleton
Gurax_DeclareProperty_R(curl_mime, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(curl_mime, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_curl_mime
//------------------------------------------------------------------------------
VType_curl_mime VTYPE_curl_mime("curl_mime");

void VType_curl_mime::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(curl_mime));
	// Assignment of method
	Assign(Gurax_CreateMethod(curl_mime, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(curl_mime, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_curl_mime
//------------------------------------------------------------------------------
VType& Value_curl_mime::vtype = VTYPE_curl_mime;

String Value_curl_mime::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.curl_mime");
}

Gurax_EndModuleScope(curl)
