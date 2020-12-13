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
// Codec(name:String, delcr?:Bool, addcr?:Bool):map {block?}
Gurax_DeclareConstructor(Codec)
{
	Declare(VTYPE_Codec, Flag::Map);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("delcr", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("addcr", VTYPE_Bool, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Searches a `Codec` instance that has been registered with the specified encoding name.");
}

Gurax_ImplementConstructor(Codec)
{
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	bool delcrFlag = args.IsValid()? args.PickBool() : true;
	bool addcrFlag = args.IsValid()? args.PickBool() : false;
	// Function body
	RefPtr<Codec> pCodec(Codec::Create(name, delcrFlag, addcrFlag));
	if (!pCodec) return Value::nil();
	return argument.ReturnValue(processor, new Value_Codec(pCodec.release()));
}

//------------------------------------------------------------------------------
// Implementation of class method
//------------------------------------------------------------------------------
// Codec.names
Gurax_DeclareClassProperty_R(Codec, names)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(Codec, names)
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	for (CodecFactory* pCodecFactory : CodecFactory::GetList()) {
		pValues->push_back(new Value_String(pCodecFactory->GetName()));
	}
	return new Value_List(pValues.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Codec#addcr
Gurax_DeclareProperty_RW(Codec, addcr)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Codec, addcr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetCodec().GetAddcrFlag());
}

Gurax_ImplementPropertySetter(Codec, addcr)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetCodec().SetAddcrFlag(value.GetBool());
}

// Codec#delcr
Gurax_DeclareProperty_RW(Codec, delcr)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Codec, delcr)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetCodec().GetDelcrFlag());
}

Gurax_ImplementPropertySetter(Codec, delcr)
{
	auto& valueThis = GetValueThis(valueTarget);
	valueThis.GetCodec().SetDelcrFlag(value.GetBool());
}

// Codec#name
Gurax_DeclareProperty_R(Codec, name)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Codec, name)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_String(valueThis.GetCodec().GetName());
}

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
	// Assignment of class property
	Assign(Gurax_CreateProperty(Codec, names));
	// Assignment of property
	Assign(Gurax_CreateProperty(Codec, addcr));
	Assign(Gurax_CreateProperty(Codec, delcr));
	Assign(Gurax_CreateProperty(Codec, name));
}

Value* VType_Codec::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* name = Value_String::GetString(value);
		bool delcrFlag = true;
		bool addcrFlag = false;
		RefPtr<Codec> pCodec(Codec::Create(name, delcrFlag, addcrFlag));
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
