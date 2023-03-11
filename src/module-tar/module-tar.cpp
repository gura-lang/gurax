//==============================================================================
// module-tar.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(tar)

//------------------------------------------------------------------------------
// Global variable
//------------------------------------------------------------------------------
RefPtr<Codec> g_pCodec;

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// tar.Directory(stream:Stream) {block?}
Gurax_DeclareFunction(Directory)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a `Directory` instance that browses the contents in a TAR stream.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Adds up the given two numbers and returns the result.
)""");
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

//-----------------------------------------------------------------------------
// Implementation of module property
//-----------------------------------------------------------------------------
// tar.codec:nil
Gurax_DeclareModuleProperty_RW(codec)
{
	Declare(VTYPE_Codec, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementModulePropertyGetter(codec)
{
	RefPtr<Codec> pCodec(g_pCodec.Reference());
	if (pCodec->IsDumb()) return Value::nil();
	return new Value_Codec(pCodec.release());
}

Gurax_ImplementModulePropertySetter(codec)
{
	if (value.IsValid()) {
		g_pCodec.reset(Value_Codec::GetCodec(value).Reference());
	} else {
		g_pCodec.reset(Codec::CreateDumb());
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
	// Initialize Codec
	g_pCodec.reset(Codec::CreateDumb());
	// Assignment of VType
	Assign(VTYPE_Reader);
	Assign(VTYPE_StatEx);
	Assign(VTYPE_Writer);
	Assign(VTYPE_bzip2);
	Assign(VTYPE_gzip);
	// Assignment of function
	Assign(Gurax_CreateFunction(Directory));
	Assign(Gurax_CreateFunction(Test));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(codec));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(tar)
