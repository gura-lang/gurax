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

${help.ComposePropertyHelp(zip.Writer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(zip.Writer, `en)}

${help.ComposeMethodHelp(zip.Writer, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Writer` instance from the speicifed stream.
)**");
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
// zip.Writer#Add(stream:Stream:r, fileName?:String, compression?:Symbol, timeStamp?:DateTime):map:reduce
Gurax_DeclareMethod(Writer, Add)
{
	Declare(VTYPE_Writer, Flag::Reduce | Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("compression", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("timeStamp", VTYPE_DateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Reads data from `stream` and adds it to the zip file with the specified file name.

Argument `compression` specifies the compression method and takes one of the following symbols:

- `` `store``
- `` `deflate``
- `` `bzip2``
)**");
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
		fileName = args.PickStringSTL();
	} else if (!stream.HasIdentifier()) {
		Error::Issue(ErrorType::StreamError, "the Stream doesn't have identifier information");
		return Value::nil();
	} else {
		fileName = PathName(stream.GetIdentifier()).ExtractFileName();
	}
	UInt16 compressionMethod = args.IsValid()?
		SymbolToCompressionMethod(args.PickSymbol()) : writer.GetCompressionMethod();
	if (compressionMethod == CompressionMethod::Invalid) {
		Error::Issue(ErrorType::ValueError, "invalid compression method");
		return Value::nil();
	}
	RefPtr<DateTime> pTimeStamp(args.IsValid()? args.PickDateTime().Reference() : nullptr);
	// Function body
	if (!writer.Add(stream, fileName.c_str(), compressionMethod, pTimeStamp.release())) return Value::nil();
	return valueThis.Reference();
}

// zip.Writer#Close():void
Gurax_DeclareMethod(Writer, Close)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Closes the zip file after flushing cached data.
)**");
}

Gurax_ImplementMethod(Writer, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Writer& writer = valueThis.GetWriter();
	// Function body
	writer.Finish();
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
VType_Writer VTYPE_Writer("Writer");

void VType_Writer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Writer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Writer, Add));
	Assign(Gurax_CreateMethod(Writer, Close));
}

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
VType& Value_Writer::vtype = VTYPE_Writer;

String Value_Writer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetWriter().ToString(ss));
}

Gurax_EndModuleScope(zip)
