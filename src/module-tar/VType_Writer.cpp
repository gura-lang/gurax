//==============================================================================
// VType_Writer.cpp
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
	enum class Compress { None, Gzip, Bzip2 };
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().Reference());
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	Compress compress = Compress::None;
	if (!pSymbol || pSymbol->IsIdentical(Gurax_Symbol(auto_))) {
		const char* identifier = pStream->GetIdentifier();
		if (String::EndsWith<CharICase>(identifier, ".tar.gz") ||
			String::EndsWith<CharICase>(identifier, ".tgz")) {
			compress = Compress::Gzip;
		} else if (String::EndsWith<CharICase>(identifier, ".tar.bz2") ||
			String::EndsWith<CharICase>(identifier, ".tb2") ||
			String::EndsWith<CharICase>(identifier, ".tbz2")) {
			compress = Compress::Bzip2;
		}
	} else if (pSymbol->IsIdentical(Gurax_Symbol(gz)) || pSymbol->IsIdentical(Gurax_Symbol(gzip))) {
		compress = Compress::Gzip;
	} else if (pSymbol->IsIdentical(Gurax_Symbol(bz2)) || pSymbol->IsIdentical(Gurax_Symbol(bzip2))) {
		compress = Compress::Bzip2;
	} else {
		Error::Issue(ErrorType::SymbolError, "invalid symbol to specify compression method");
		return Value::nil();
	}
	if (compress == Compress::Gzip) {
		int level = Z_DEFAULT_COMPRESSION, windowBits = 31, memLevel = 8, strategy = Z_DEFAULT_STRATEGY;
		RefPtr<ZLib::Stream_Writer> pStreamGZ(new ZLib::Stream_Writer(pStream.Reference()));
		if (!pStreamGZ->Initialize(level, windowBits, memLevel, strategy)) return Value::nil();
		pStream.reset(pStreamGZ.release());
	} else if (compress == Compress::Bzip2) {
		int blockSize100k = 9, verbosity = 0, workFactor = 0;
		RefPtr<BZLib::Stream_Writer> pStreamBZ2(new BZLib::Stream_Writer(pStream.Reference()));
		if (!pStreamBZ2->Initialize(blockSize100k, verbosity, workFactor)) return Value::nil();
		pStream.reset(pStreamBZ2.release());
	}
	// Function body
	RefPtr<Writer> pWriter(new Writer(pStream.release()));
	return argument.ReturnValue(processor, new Value_Writer(pWriter.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// tar.Writer#Add(stream:Stream:r, fileName:String):map:reduce
Gurax_DeclareMethod(Writer, Add)
{
	Declare(VTYPE_Writer, Flag::Reduce | Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from `stream` and adds it to the zip file with the specified file name.\n");
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
	} else {
		if (!stream.HasIdentifier()) {
			Error::Issue(ErrorType::StreamError, "the Stream doesn't have identifier information");
			return Value::nil();
		}
		fileName = PathName(stream.GetIdentifier()).ExtractFileName();
	}
	// Function body
	if (!writer.Add(stream, fileName.c_str())) return Value::nil();
	return valueThis.Reference();
}

// tar.Writer#Close():reduce
Gurax_DeclareMethod(Writer, Close)
{
	Declare(VTYPE_Writer, Flag::Reduce);
	AddHelp(
		Gurax_Symbol(en),
		"Close the tar.Writer instance.\n");
}

Gurax_ImplementMethod(Writer, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Writer& writer = valueThis.GetWriter();
	writer.Close();
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// tar.Writer#propSkeleton
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
	// Assignment of property
	Assign(Gurax_CreateProperty(Writer, propSkeleton));
}

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
VType& Value_Writer::vtype = VTYPE_Writer;

String Value_Writer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetWriter().ToString(ss));
}

Gurax_EndModuleScope(tar)
