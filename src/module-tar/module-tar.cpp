//==============================================================================
// module-tar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(tar)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// tar.Test(stream:Stream)
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds up the given two numbers and returns the result.");
}

Gurax_ImplementFunction(Test)
{
#if 0
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().Reference());
	// Function body
	if (String::EndsWith<CharICase>(pStream->GetIdentifier(), ".gz") ||
		String::EndsWith<CharICase>(pStream->GetIdentifier(), ".tgz")) {
		ZLib::GZHeader hdr;
		if (!hdr.Read(*pStream)) return Value::nil();
		RefPtr<ZLib::Stream_Reader> pStreamGZ(new ZLib::Stream_Reader(pStream.release()));
		if (!pStreamGZ->Initialize(-MAX_WBITS)) return Value::nil();
		pStream.reset(pStreamGZ.release());
	} else if (String::EndsWith<CharICase>(pStream->GetIdentifier(), ".bz2")) {
		int verbosity = 0, small = 0;
		RefPtr<BZLib::Stream_Reader> pStreamBZ2(new BZLib::Stream_Reader(pStream.release()));
		if (!pStreamBZ2->Initialize(verbosity, small)) return Value::nil();
		pStream.reset(pStreamBZ2.release());
	}
	for (;;) {
		std::unique_ptr<Header> pHeader(Header::Read(*pStream));
		if (!pHeader) break;
		pHeader->SetOffset(pStream->GetOffset());
		::printf("%s\n", pHeader->GetName());
		pStream->Seek(pHeader->CalcBlocks() * BLOCKSIZE, Stream::SeekMode::Cur);
	}
#endif
	return Value::nil();
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
	Assign(Gurax_CreateFunction(Test));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(tar)
