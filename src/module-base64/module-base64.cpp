//==============================================================================
// module-base64.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(base64)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// base64.Encode(src:Stream, dst?:Stream:w)
Gurax_DeclareFunction(Encode)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("src", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
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
	// Function body
	RefPtr<Stream> pStream(new Stream_ReaderBase64(streamSrc.Reference()));
	if (pStreamDst) {
		pStream->ReadToStream(*pStreamDst);
		return Value::nil();
	} else {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable());
		if (!pStream->ReadToBinary(pBuff->GetBinary())) return Value::nil();
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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(base64)
