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

${help.ComposePropertyHelp(tar.Writer, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(tar.Writer, `en)}

${help.ComposeMethodHelp(tar.Writer, `en)}
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
	RefPtr<Stream> pStream(args.PickStream().Reference());
	const Symbol* pSymbol = args.IsValid()? args.PickSymbol() : nullptr;
	Compress compress = DetermineCompress(pStream->GetIdentifier(), pSymbol);
#if 0
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
	} else if (pSymbol->IsIdentical(Gurax_Symbol(none))) {
		compress = Compress::None;
	} else {
		Error::Issue(ErrorType::SymbolError, "invalid symbol to specify compression method: %s", pSymbol->GetName());
		return Value::nil();
	}
#endif
	if (compress == Compress::Invalid) {
		return Value::nil();
	} else if (compress == Compress::Gzip) {
		const Writer::GzipInfo& v = Writer::gzipInfo;
		RefPtr<ZLib::Stream_Writer> pStreamGZ(new ZLib::Stream_Writer(pStream.Reference()));
		if (!pStreamGZ->Initialize(v.level, v.windowBits, v.memLevel, v.strategy)) return Value::nil();
		pStream.reset(pStreamGZ.release());
	} else if (compress == Compress::Bzip2) {
		const Writer::Bzip2Info& v = Writer::bzip2Info;
		RefPtr<BZLib::Stream_Writer> pStreamBZ2(new BZLib::Stream_Writer(pStream.Reference()));
		if (!pStreamBZ2->Initialize(v.blockSize100k, v.verbosity, v.workFactor)) return Value::nil();
		pStream.reset(pStreamBZ2.release());
	}
	// Function body
	RefPtr<Writer> pWriter(new Writer(pStream.release()));
	return argument.ReturnValue(processor, new Value_Writer(pWriter.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// tar.Writer#Add(stream:Stream:r, fileName:String, mtime?:DateTime, atime?:DateTime, ctime?:DateTime):map:reduce
Gurax_DeclareMethod(Writer, Add)
{
	Declare(VTYPE_Writer, Flag::Reduce | Flag::Map);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("fileName", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("mtime", VTYPE_DateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("atime", VTYPE_DateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("ctime", VTYPE_DateTime, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Reads data from `stream` and adds it to the zip file with the specified file name.
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
	RefPtr<DateTime> pDateTimeM(args.IsValid()? args.PickDateTime().Reference() : nullptr);
	RefPtr<DateTime> pDateTimeA(args.IsValid()? args.PickDateTime().Reference() : nullptr);
	RefPtr<DateTime> pDateTimeC(args.IsValid()? args.PickDateTime().Reference() : nullptr);
	// Function body
	if (!writer.Add(stream, fileName.c_str(), pDateTimeM.release(), pDateTimeA.release(), pDateTimeC.release())) return Value::nil();
	return valueThis.Reference();
}

// tar.Writer#Close():reduce
Gurax_DeclareMethod(Writer, Close)
{
	Declare(VTYPE_Writer, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Close the tar.Writer instance.
)**");
}

Gurax_ImplementMethod(Writer, Close)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Writer& writer = valueThis.GetWriter();
	writer.Close();
	return valueThis.Reference();
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

Value_Writer::~Value_Writer()
{
	GetWriter().Close();
}

String Value_Writer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetWriter().ToString(ss));
}

Gurax_EndModuleScope(tar)
