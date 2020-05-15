//==============================================================================
// module-base64.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(base64)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// base64.Encode(src:Stream, dst?:Stream:w, lineLen?:Number):[base16,base32,base32hex,base64,singleLine] {block?}
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
	DeclareAttrOpt(Gurax_Symbol(singleLine));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from stream `src` and encodes it in a base-n format into the stream `dst`.\n"
		"If `dst` is omitted, the result will be returned as `Binary` value.\n"
		"\n"
		"In default, base64 format is applied. The following attributes can specify the format:\n"
		"\n"
		"- `:base16` .. Base16 format\n"
		"- `:base32` .. Base32 format\n"
		"- `:base32hex` .. Base32hex format\n"
		"- `:base64` .. Base64 format. Default.\n"
		"\n"
		"In default, output characters are folded by the length specified by `lineLen`.\n"
		"If the argument is omitted, pre-defined length for each format is applied:\n"
		"64 characters for base32 and base32hex and 76 for base16 and base64.\n"
		"\n"
		"Specifying the attribute `:singleLine` puts the result in a single line without folding.\n");
}

Gurax_ImplementFunction(Encode)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	Stream* pStreamDst = args.IsValid()? &args.PickStream() : nullptr;
	const Info& info =
		argument.IsSet(Gurax_Symbol(base16))? Info::Base16 : 
		argument.IsSet(Gurax_Symbol(base32))? Info::Base32 : 
		argument.IsSet(Gurax_Symbol(base32hex))? Info::Base32hex : 
		Info::Base64; 
	size_t nCharsPerLine = args.IsValid()?
		args.PickNumberNonNeg<size_t>() : info.nCharsPerLineDefault;
	if (Error::IsIssued()) return Value::nil();
	bool singleLineFlag = argument.IsSet(Gurax_Symbol(singleLine));
	// Function body
	if (pStreamDst) {
		RefPtr<Encoder> pEncoder(new Encoder(pStreamDst->Reference(),
								singleLineFlag? 0 : nCharsPerLine, info));
		pEncoder->EncodeStream(streamSrc);
		pEncoder->Finish();
		return Value::nil();
	} else {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable());
		RefPtr<Stream> pStreamDst(new Stream_Binary(Stream::Flag::Writable, pBuff->Reference()));
		RefPtr<Encoder> pEncoder(new Encoder(pStreamDst->Reference(),
								singleLineFlag? 0 : nCharsPerLine, info));
		if (!pEncoder->EncodeStream(streamSrc) || !pEncoder->Finish()) return Value::nil();
		return argument.ReturnValue(processor, new Value_Binary(pBuff.release()));
	}
}

// base64.Decode(src:Stream, dst?:Stream:w):[base16,base32.base32hex,base64] {block?}
Gurax_DeclareFunction(Decode)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(base16));
	DeclareAttrOpt(Gurax_Symbol(base32));
	DeclareAttrOpt(Gurax_Symbol(base32hex));
	DeclareAttrOpt(Gurax_Symbol(base64));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data formatted in a base-n format from stream `src` and decodes it into the stream `dst`.\n"
		"If `dst` is omitted, the result will be returned as `Binary` value.\n"
		"\n"
		"In default, base64 format is applied. The following attributes can specify the format:\n"
		"\n"
		"- `:base16` .. Base16 format\n"
		"- `:base32` .. Base32 format\n"
		"- `:base32hex` .. Base32hex format\n"
		"- `:base64` .. Base64 format. Default.\n");
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
		return argument.ReturnValue(processor, new Value_Binary(pBuff.release()));
	}
}

//------------------------------------------------------------------------------
// Implementation of suffix manager
//------------------------------------------------------------------------------
Gurax_ImplementSuffixMgr_Compose(Binary, base16)
{
	const String& buff = strRef.GetStringSTL();
	RefPtr<BinaryReferable> pBuffDst(new BinaryReferable());
	if (!Decoder::Decode(*pBuffDst, buff.data(), buff.size(), Info::Base16)) return;
	composer.Add_Value(new Value_Binary(pBuffDst.release()), pExpr);	// [Value]
}

Gurax_ImplementSuffixMgr_Compose(Binary, base32)
{
	const String& buff = strRef.GetStringSTL();
	RefPtr<BinaryReferable> pBuffDst(new BinaryReferable());
	if (!Decoder::Decode(*pBuffDst, buff.data(), buff.size(), Info::Base32)) return;
	composer.Add_Value(new Value_Binary(pBuffDst.release()), pExpr);	// [Value]
}

Gurax_ImplementSuffixMgr_Compose(Binary, base32hex)
{
	const String& buff = strRef.GetStringSTL();
	RefPtr<BinaryReferable> pBuffDst(new BinaryReferable());
	if (!Decoder::Decode(*pBuffDst, buff.data(), buff.size(), Info::Base32hex)) return;
	composer.Add_Value(new Value_Binary(pBuffDst.release()), pExpr);	// [Value]
}

Gurax_ImplementSuffixMgr_Compose(Binary, base64)
{
	const String& buff = strRef.GetStringSTL();
	RefPtr<BinaryReferable> pBuffDst(new BinaryReferable());
	if (!Decoder::Decode(*pBuffDst, buff.data(), buff.size(), Info::Base64)) return;
	composer.Add_Value(new Value_Binary(pBuffDst.release()), pExpr);	// [Value]
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
	// Assignment of suffix manager
	Gurax_AssignSuffixMgr(Binary, base16);
	Gurax_AssignSuffixMgr(Binary, base32);
	Gurax_AssignSuffixMgr(Binary, base32hex);
	Gurax_AssignSuffixMgr(Binary, base64);
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(base64)
