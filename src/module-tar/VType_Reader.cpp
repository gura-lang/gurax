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

${help.ComposePropertyHelp(tar.Reader, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(tar.Reader, `en)}

${help.ComposeMethodHelp(tar.Reader, `en)}
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// tar.Reader(stream:Stream, compression?:Symbol) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareArg("compression", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(
Creates a `tar.Reader` instance.
)**");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().Reference());
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	Compress compress = DetermineCompress(pStream->GetIdentifier(), pSymbol);
	// Function body
	if (compress == Compress::Invalid) {
		return Value::nil();
	} else if (compress == Compress::Gzip) {
		ZLib::GZHeader hdr;
		if (!hdr.Read(*pStream)) return Value::nil();
		RefPtr<ZLib::Stream_Reader> pStreamGZ(new ZLib::Stream_Reader(pStream.Reference()));
		if (!pStreamGZ->Initialize(-MAX_WBITS)) return Value::nil();
		pStream.reset(pStreamGZ.release());
	} else if (compress == Compress::Bzip2) {
		int verbosity = 0, small = 0;
		RefPtr<BZLib::Stream_Reader> pStreamBZ2(new BZLib::Stream_Reader(pStream.Reference()));
		if (!pStreamBZ2->Initialize(verbosity, small)) return Value::nil();
		pStream.reset(pStreamBZ2.release());
	}
	RefPtr<Reader> pReader(new Reader(pStream.release()));
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// tar.Reader#Close():reduce
Gurax_DeclareMethod(Reader, Close)
{
	Declare(VTYPE_Reader, Flag::Reduce);
	AddHelp("en", u8R"**(
Close the tar.Reader instance.
)**");
}

Gurax_ImplementMethod(Reader, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Reader& reader = valueThis.GetReader();
	reader.Close();
	return valueThis.Reference();
}

// tar.Reader#EachEntry():[all] {block?}
Gurax_DeclareMethod(Reader, EachEntry)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(all));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp("en", u8R"**(

)**");
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
	Assign(Gurax_CreateMethod(Reader, Close));
	Assign(Gurax_CreateMethod(Reader, EachEntry));
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
