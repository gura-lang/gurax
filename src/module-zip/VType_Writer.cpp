//==============================================================================
// VType_Writer.cpp
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
// zip.Writer(stream:Stream:w, compression?:Symbol) {block?}
Gurax_DeclareConstructor(Writer)
{
	Declare(VTYPE_Writer, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("compression", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Writer` instance from the speicifed stream.");
}

Gurax_ImplementConstructor(Writer)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	UInt16 compressionMethod = args.IsValid()?
		SymbolToCompressionMethod(args.PickSymbol()) : CompressionMethod::Deflate;
	if (compressionMethod == CompressionMethod::Invalid) {
		Error::Issue(ErrorType::ValueError, "invalid compression method");
		return Value::nil();
	}
	// Function body
	RefPtr<Writer> pWriter(new Writer(stream.Reference(), compressionMethod));
	return argument.ReturnValue(processor, new Value_Writer(pWriter.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// zip.Writer#Add(stream:Stream:r, fileName?:String, compression?:Symbol):map:reduce
Gurax_DeclareMethod(Writer, Add)
{
	Declare(VTYPE_Writer, Flag::Reduce | Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("compression", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from `stream` and adds it to the zip file.\n"
		"Entry name is decided by the file name associated with the stream\n"
		"unless it's specified by argument `filename`.\n"
		"\n"
		"Argument `compression` specifies the compression method and takes one of the following symbols:\n"
		"\n"
		"- `` `store``\n"
		"- `` `deflate``\n"
		"- `` `bzip2``\n");
}

Gurax_ImplementMethod(Writer, Add)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Writer& writer = valueThis.GetWriter();
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	String fileName;
	if (args.IsValid()) {
		fileName = args.PickString();
	} else {
		const char*identifier = stream.GetIdentifier();
		if (!identifier) {
			Error::Issue(ErrorType::ValueError, "stream doesn't have an identifier");
			return Value::nil();
		}
		fileName = PathName(identifier).ExtractFileName();
	}
	UInt16 compressionMethod = args.IsValid()?
		SymbolToCompressionMethod(args.PickSymbol()) : writer.GetCompressionMethod();
	if (compressionMethod == CompressionMethod::Invalid) {
		Error::Issue(ErrorType::ValueError, "invalid compression method");
		return Value::nil();
	}
	// Function body
	if (!writer.Add(stream, fileName.c_str(), compressionMethod)) return Value::nil();
	return valueThis.Reference();
}

// zip.Writer#Close():void
Gurax_DeclareMethod(Writer, Close)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Closes the zip file after flushing cached data.");
}

Gurax_ImplementMethod(Writer, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Writer& writer = valueThis.GetWriter();
	writer.Finish();
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// zip.Writer#propSkeleton
Gurax_DeclareProperty_R(Writer, propSkeleton)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Writer, propSkeleton)
{
	//auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(3);
}

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
VType_Writer VTYPE_Writer("Writer");

void VType_Writer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Writer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Writer, Add));
	Assign(Gurax_CreateMethod(Writer, Close));
	// Assignment of property
	Assign(Gurax_CreateProperty(Writer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
VType& Value_Writer::vtype = VTYPE_Writer;

Gurax_EndModuleScope(zip)
