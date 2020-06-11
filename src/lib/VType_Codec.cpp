//==============================================================================
// VType_Codec.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Codec(encoding:name):map {block?}
Gurax_DeclareConstructor(Codec)
{
	Declare(VTYPE_Codec, Flag::Map);
	DeclareArg("encoding", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Searches a `Codec` instance that has been registered with the specified encoding name.");
}

Gurax_ImplementConstructor(Codec)
{
	// Arguments
	ArgPicker args(argument);
	const char* encoding = args.PickString();
	// Function body
	bool delcrFlag = true;
	bool addcrFlag = false;
	RefPtr<Codec> pCodec(Codec::Create(encoding, delcrFlag, addcrFlag));
	if (!pCodec) return Value::nil();
	return argument.ReturnValue(processor, new Value_Codec(pCodec.release()));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// VType_Codec
//------------------------------------------------------------------------------
VType_Codec VTYPE_Codec("Codec");

void VType_Codec::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Codec));
}

Value* VType_Codec::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* encoding = Value_String::GetString(value);
		bool delcrFlag = true;
		bool addcrFlag = false;
		RefPtr<Codec> pCodec(Codec::Create(encoding, delcrFlag, addcrFlag));
		if (!pCodec) return Value::nil();
		return new Value_Codec(pCodec.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Codec
//------------------------------------------------------------------------------
VType& Value_Codec::vtype = VTYPE_Codec;

String Value_Codec::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetCodec().ToString(ss));
}


}
