//==============================================================================
// VType_Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(zip)

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
// zip.Reader(stream:Stream:r) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `zip.Reader` instance from the specified stream.");
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
	AddHelp(
		Gurax_Symbol(en),
		"Seeks entry in the zip file that matches the specified name\n"
		"and returns a `stream` instance associated with the entry.\n");
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
	if (pStatEx->IsFolder()) {
		Error::Issue(ErrorType::PathError, "the specified entry is a folder");
		return Value::nil();
	}
	RefPtr<Stream> pStream(CreateStream(reader.GetStreamSrc(), *pStatEx));
	if (!pStream) return nullptr;
	return new Value_Stream(pStream.release());
}

// zip.Reader#Entries() {block?}
Gurax_DeclareMethod(Reader, Entries)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an `iterator` instance that returns `stream` instances\n"
		"associated with each entry in the ZIP file.\n");
}

Gurax_ImplementMethod(Reader, Entries)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Reader& reader = valueThis.GetReader();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Entry(reader.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// zip.Reader#propSkeleton
Gurax_DeclareProperty_R(Reader, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Reader, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
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
	Assign(Gurax_CreateMethod(Reader, Entry));
	Assign(Gurax_CreateMethod(Reader, Entries));
	// Assignment of property
	Assign(Gurax_CreateProperty(Reader, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
VType& Value_Reader::vtype = VTYPE_Reader;

Gurax_EndModuleScope(zip)
