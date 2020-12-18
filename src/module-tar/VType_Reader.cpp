//==============================================================================
// VType_Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

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
// tar.Reader(stream:Stream) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `tar.Reader` instance.");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	// Function body
	RefPtr<Reader> pReader(new Reader(streamSrc.Reference()));
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// tar.Reader#EachEntry():[all] {block?}
Gurax_DeclareMethod(Reader, EachEntry)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(all));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Reader, EachEntry)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Reader& reader = valueThis.GetReader();
	// Attribute
	bool skipDirFlag = !argument.IsSet(Gurax_Symbol(all));
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Entry(reader.Reference(), skipDirFlag));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of class property
//-----------------------------------------------------------------------------
// tar.Reader.codec
Gurax_DeclareClassProperty_RW(Reader, codec)
{
	Declare(VTYPE_Codec, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementClassPropertyGetter(Reader, codec)
{
	RefPtr<Codec> pCodec(Reader::pCodec.Reference());
	if (pCodec->IsDumb()) return Value::nil();
	return new Value_Codec(pCodec.release());
}

Gurax_ImplementClassPropertySetter(Reader, codec)
{
	if (value.IsValid()) {
		Reader::pCodec.reset(Value_Codec::GetCodec(value).Reference());
	} else {
		Reader::pCodec.reset(Codec::CreateDumb());
	}
}

//------------------------------------------------------------------------------
// VType_Reader
//------------------------------------------------------------------------------
VType_Reader VTYPE_Reader("Reader");

void VType_Reader::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Reader));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reader, EachEntry));
	// Assignment of property
	Assign(Gurax_CreateClassProperty(Reader, codec));
}

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
VType& Value_Reader::vtype = VTYPE_Reader;

String Value_Reader::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetReader().ToString(ss));
}

Gurax_EndModuleScope(tar)
