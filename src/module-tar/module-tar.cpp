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
	// Assignment of VType
	Assign(VTYPE_StatEx);
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
