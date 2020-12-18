//==============================================================================
// module-tar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(tar)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// tar.Directory(stream:Stream) {block?}
Gurax_DeclareFunction(Directory)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `Directory` instance that browses the contents in a TAR stream.");
}

Gurax_ImplementFunction(Directory)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().CreateBwdSeekable());
	if (!pStream) return nullptr;
	// Function body
	RefPtr<Directory> pDirectory(DirectoryEx::CreateTop(*pStream));
	if (!pDirectory) return Value::nil();
	return argument.ReturnValue(processor, new Value_Directory(pDirectory.release()));
}

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
	// Initialize Codec
	Reader::pCodec.reset(Codec::CreateDumb());
	Writer::pCodec.reset(Codec::CreateDumb());
	// Assignment of VType
	Assign(VTYPE_Reader);
	Assign(VTYPE_StatEx);
	Assign(VTYPE_Writer);
	Assign(VTYPE_bzip2);
	Assign(VTYPE_gzip);
	// Assignment of function
	Assign(Gurax_CreateFunction(Directory));
	Assign(Gurax_CreateFunction(Test));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(tar)
