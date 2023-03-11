//==============================================================================
// VType_Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(zip.Reader, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(zip.Reader, `en)}

${help.ComposeMethodHelp(zip.Reader, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// zip.Reader(stream:Stream:r) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `zip.Reader` instance from the specified stream.
)""");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().CreateBwdSeekable());
	if (!pStream) return Value::nil();
	// Function body
	RefPtr<Reader> pReader(new Reader(pStream.release()));
	if (!pReader->ReadCentralDirectory()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Reader#Entry(name:String) {block?}
Gurax_DeclareMethod(Reader, Entry)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("name", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Seeks entry in the zip file that matches the specified name
and returns a `stream` instance associated with the entry.
)""");
}

Gurax_ImplementMethod(Reader, Entry)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Reader& reader = valueThis.GetReader();
	// Arguments
	ArgPicker args(argument);
	const char* name = args.PickString();
	// Function body
	StatEx* pStatEx = reader.GetStatExOwner().FindByName(name);
	if (!pStatEx) {
		Error::Issue(ErrorType::PathError, "can't find an entry with the specified name");
		return Value::nil();
	}
	if (pStatEx->IsDir()) {
		Error::Issue(ErrorType::PathError, "the specified entry is a folder");
		return Value::nil();
	}
	RefPtr<Stream> pStream(Stream_Reader::Create(reader.GetStreamSrc(), *pStatEx));
	return pStream? new Value_Stream(pStream.release()) : nullptr;
}

// zip.Reader#EachEntry():[all] {block?}
Gurax_DeclareMethod(Reader, EachEntry)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(all));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an `iterator` instance that returns `stream` instances
associated with each entry in the ZIP file.

In default, entries that represent directories are skipped.
Specify `:all` attribute to include them.
)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Reader));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reader, Entry));
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

Gurax_EndModuleScope(zip)
