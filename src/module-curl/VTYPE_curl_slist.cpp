//==============================================================================
// VType_curl_slist.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(curl)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(curl.curl_slist, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(curl.curl_slist, `en)}

${help.ComposeMethodHelp(curl.curl_slist, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// curl.curl_slist(src as Iterator) {block?}
Gurax_DeclareConstructor(curl_slist)
{
	Declare(VTYPE_curl_slist, Flag::None);
	DeclareArg("src", VTYPE_Iterator, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `curl.curl_slist` instance.
)""");
}

Gurax_ImplementConstructor(curl_slist)
{
	// Arguments
	ArgPicker args(argument);
	Iterator& iter = args.PickIterator();
	// Function body
#if 0	
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
#endif
	curl_slist* slist = CreateSListFromIterator(iter);
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, slist? new Value_curl_slist(slist) : Value::nil());
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------

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
	//Assign(Gurax_CreateMethod(curl_slist, MethodSkeleton));
	// Assignment of property
	//Assign(Gurax_CreateProperty(curl_slist, propSkeleton));
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
