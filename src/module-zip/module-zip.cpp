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
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
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
	RefPtr<Directory> pDirectory(CreateDirectory(*pStream, nullptr, nullptr, Directory::Type::None));
	if (!pDirectory) return Value::nil();
	return argument.ReturnValue(processor, new Value_Directory(pDirectory.release()));
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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(zip)
