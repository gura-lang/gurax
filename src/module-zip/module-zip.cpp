//==============================================================================
// module-zip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(zip)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// zip.Directory(stream:Stream) {block?}
Gurax_DeclareFunction(Directory)
{
	Declare(VTYPE_Directory, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `Directory` instance that browses the contents in a ZIP stream.");
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

// zip.Inspect(stream:Stream)
Gurax_DeclareFunction(Inspect)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Prints all descriptors in the ZIP-format file.");
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
	Assign(VTYPE_Reader);
	Assign(VTYPE_Writer);
	Assign(VTYPE_StatEx);
	// Assignment of function
	Assign(Gurax_CreateFunction(Directory));
	Assign(Gurax_CreateFunction(Inspect));
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(zip)
