//==============================================================================
// VType_curl_slist.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.curl_slist, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.curl_slist, `en)}

${help.ComposeMethodHelp(curl.curl_slist, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.curl_slist(src:Iterator) {block?}
Gurax_DeclareConstructor(curl_slist)
{
	Declare(VTYPE_curl_slist, Flag::None);
	DeclareArg("src", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `curl.curl_slist` instance.
)**");
}

Gurax_ImplementConstructor(curl_slist)
{
	// Arguments
	ArgPicker args(argument);
	Iterator& iter = args.PickIterator();
	// Function body
	curl_slist* slist = nullptr;
	for (;;) {
		RefPtr<Value> pValue(iter.NextValue());
		if (!pValue) break;
		if (!pValue->IsInstanceOf(VTYPE_String)) {
			Error::Issue(ErrorType::TypeError, "the elements must be String values");
			return Value::nil();
		}
		slist = curl_slist_append(slist, Value_String::GetString(*pValue));
	}
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, new Value_curl_slist(slist));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// curl.curl_slist#MethodSkeleton(num1:Number, num2:Number)
Gurax_DeclareMethod(curl_slist, MethodSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("num1", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("num2", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp("en", u8R"**(
Skeleton.
)**");
}

Gurax_ImplementMethod(curl_slist, MethodSkeleton)
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
// curl.curl_slist#propSkeleton
Gurax_DeclareProperty_R(curl_slist, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp("en", u8R"**(

)**");
}

Gurax_ImplementPropertyGetter(curl_slist, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_curl_slist
//------------------------------------------------------------------------------
VType_curl_slist VTYPE_curl_slist("curl_slist");

void VType_curl_slist::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(curl_slist));
	// Assignment of method
	Assign(Gurax_CreateMethod(curl_slist, MethodSkeleton));
	// Assignment of property
	Assign(Gurax_CreateProperty(curl_slist, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_curl_slist
//------------------------------------------------------------------------------
VType& Value_curl_slist::vtype = VTYPE_curl_slist;

String Value_curl_slist::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, "curl.curl_slist");
}

Gurax_EndModuleScope(curl)
