//==============================================================================
// module-base64.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(base64)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// base64.Encode(src:Stream, dst?:Stream:w):[base16,base32,base32hex,base64]
Gurax_DeclareFunction(Encode)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareArg("lineLen", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(base16));
	DeclareAttrOpt(Gurax_Symbol(base32));
	DeclareAttrOpt(Gurax_Symbol(base32hex));
	DeclareAttrOpt(Gurax_Symbol(base64));
	AddHelp(
		Gurax_Symbol(en),
		"Applies base64-encode on data from the stream `src`\n"
		"and puts the result out to the stream `dst`.\n"
		"If `dst` is omitted, the result will be returned as `Binary` value.\n");
}

Gurax_ImplementFunction(Encode)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	Stream* pStreamDst = args.IsValid()? &args.PickStream() : nullptr;
	size_t nCharsPerLine = args.IsValid()? args.PickNumberNonNeg<size_t>() : 72;
	const Info& info =
		argument.IsSet(Gurax_Symbol(base16))? Info::Base16 : 
		argument.IsSet(Gurax_Symbol(base32))? Info::Base32 : 
		argument.IsSet(Gurax_Symbol(base32hex))? Info::Base32hex : 
		Info::Base64; 
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (pStreamDst) {
		RefPtr<Encoder> pEncoder(new Encoder(pStreamDst->Reference(), nCharsPerLine, info));
		pEncoder->EncodeStream(streamSrc);
		pEncoder->Finish();
		return Value::nil();
	} else {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable());
		RefPtr<Stream> pStreamDst(new Stream_Binary(Stream::Flag::Writable, pBuff->Reference()));
		RefPtr<Encoder> pEncoder(new Encoder(pStreamDst->Reference(), nCharsPerLine, info));
		if (!pEncoder->EncodeStream(streamSrc) || !pEncoder->Finish()) return Value::nil();
		return new Value_Binary(pBuff.release());
	}
}

// base64.Decode(src:Stream, dst?:Stream:w):[base16,base32.base32hex,base64]
Gurax_DeclareFunction(Decode)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(base16));
	DeclareAttrOpt(Gurax_Symbol(base32));
	DeclareAttrOpt(Gurax_Symbol(base32hex));
	DeclareAttrOpt(Gurax_Symbol(base64));
	AddHelp(
		Gurax_Symbol(en),
		"Applies base64-decode on data from the stream `src`\n"
		"and puts the result out to the stream `dst`.\n"
		"If `dst` is omitted, the result will be returned as `Binary` value.\n");
}

Gurax_ImplementFunction(Decode)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	Stream* pStreamDst = args.IsValid()? &args.PickStream() : nullptr;
	size_t nCharsPerLine = args.IsValid()? args.PickNumberNonNeg<size_t>() : 72;
	const Info& info =
		argument.IsSet(Gurax_Symbol(base16))? Info::Base16 : 
		argument.IsSet(Gurax_Symbol(base32))? Info::Base32 : 
		argument.IsSet(Gurax_Symbol(base32hex))? Info::Base32hex : 
		Info::Base64; 
	if (Error::IsIssued()) return Value::nil();
	// Function body
	if (pStreamDst) {
		RefPtr<Decoder> pDecoder(new Decoder(pStreamDst->Reference(), info));
		pDecoder->DecodeStream(streamSrc);
		return Value::nil();
	} else {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable());
		RefPtr<Stream> pStreamDst(new Stream_Binary(Stream::Flag::Writable, pBuff->Reference()));
		RefPtr<Decoder> pDecoder(new Decoder(pStreamDst->Reference(), info));
		if (!pDecoder->DecodeStream(streamSrc)) return Value::nil();
		return new Value_Binary(pBuff.release());
	}
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of function
	Assign(Gurax_CreateFunction(Encode));
	Assign(Gurax_CreateFunction(Decode));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(base64)
