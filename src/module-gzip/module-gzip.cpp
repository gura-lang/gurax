//==============================================================================
// module-gzip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gzip)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// gzip.Reader(stream:Stream:r) {block?}
Gurax_DeclareFunction(Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that reads and uncompresses gzip-encoded data stream.
)""");
}

Gurax_ImplementFunction(Reader)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	const int windowBits = 31;
	RefPtr<Value> pValue(GenerateReader(stream.Reference(), windowBits));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// gzip.Writer(stream:Stream:w, level?:Number) {block?}
Gurax_DeclareFunction(Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("level", VTYPE_Number, ArgOccur::ZeroOrOnce);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that compresses data into a gzip-encoded data stream.
)""");
}

Gurax_ImplementFunction(Writer)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	int level = args.IsValid()? args.PickNumber<int>() : Z_DEFAULT_COMPRESSION;
	// Function body
	const int windowBits = 31;
	RefPtr<Value> pValue(GenerateWriter(stream.Reference(), level, windowBits));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
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
	Assign(Gurax_CreateFunction(Reader));
	Assign(Gurax_CreateFunction(Writer));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gzip)
