//==============================================================================
// module-zip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(zip)

//------------------------------------------------------------------------------
// Global variable
//------------------------------------------------------------------------------
RefPtr<Codec> g_pCodec;

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// zip.Directory(stream as Stream) {block?}
Gurax_DeclareFunction(Directory)
{
	Declare(VTYPE_Directory, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a `Directory` instance that browses the contents in a ZIP stream.
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

// zip.Inspect(stream as Stream)
Gurax_DeclareFunction(Inspect)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints all descriptors in the ZIP-format file.
)""");
}

Gurax_ImplementFunction(Inspect)
{
	// Arguments
	ArgPicker args(argument);
	RefPtr<Stream> pStream(args.PickStream().CreateBwdSeekable());
	if (!pStream) return nullptr;
	// Function body
	InspectDescriptor(Basement::Inst.GetStreamCOut(), *pStream);
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of module property
//-----------------------------------------------------------------------------
// zip.codec:nil
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
	Assign(VTYPE_Writer);
	Assign(VTYPE_StatEx);
	Assign(VTYPE_bzip2);
	Assign(VTYPE_gzip);
	// Assignment of function
	Assign(Gurax_CreateFunction(Directory));
	Assign(Gurax_CreateFunction(Inspect));
	// Assignment of property
	Assign(Gurax_CreateModuleProperty(codec));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(zip)
