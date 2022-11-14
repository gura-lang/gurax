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

${help.ComposePropertyHelp(Codec, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(Codec, `en)}

${help.ComposeMethodHelp(Codec, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Searches a `Codec` instance that has been registered with the specified encoding name.
)**");
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
// Codec.bom@utf8
Gurax_DeclareClassPropertyAlias_R(Codec, bom_at_utf8, "bom@utf8")
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(Codec, bom_at_utf8)
{
	Binary binary(Codec::BOM::UTF8);
	binary.SetWritableFlag(false);
	return new Value_Binary(binary);
}

// Codec.bom@utf16be
Gurax_DeclareClassPropertyAlias_R(Codec, bom_at_utf16be, "bom@utf16be")
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(Codec, bom_at_utf16be)
{
	Binary binary(Codec::BOM::UTF16BE);
	binary.SetWritableFlag(false);
	return new Value_Binary(binary);
}

// Codec.bom@utf16le
Gurax_DeclareClassPropertyAlias_R(Codec, bom_at_utf16le, "bom@utf16le")
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(Codec, bom_at_utf16le)
{
	Binary binary(Codec::BOM::UTF16LE);
	binary.SetWritableFlag(false);
	return new Value_Binary(binary);
}

// Codec.bom@utf32be
Gurax_DeclareClassPropertyAlias_R(Codec, bom_at_utf32be, "bom@utf32be")
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(Codec, bom_at_utf32be)
{
	Binary binary(Codec::BOM::UTF32BE, 4);
	binary.SetWritableFlag(false);
	return new Value_Binary(binary);
}

// Codec.bom@utf32le
Gurax_DeclareClassPropertyAlias_R(Codec, bom_at_utf32le, "bom@utf32le")
{
	Declare(VTYPE_Binary, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

Gurax_ImplementClassPropertyGetter(Codec, bom_at_utf32le)
{
	Binary binary(Codec::BOM::UTF32LE, 4);
	binary.SetWritableFlag(false);
	return new Value_Binary(binary);
}

// Codec.names
Gurax_DeclareClassProperty_R(Codec, names)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Codec));
	// Assignment of class property
	Assign(Gurax_CreateProperty(Codec, bom_at_utf8));
	Assign(Gurax_CreateProperty(Codec, bom_at_utf16be));
	Assign(Gurax_CreateProperty(Codec, bom_at_utf16le));
	Assign(Gurax_CreateProperty(Codec, bom_at_utf32be));
	Assign(Gurax_CreateProperty(Codec, bom_at_utf32le));
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
