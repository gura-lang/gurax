//==============================================================================
// module-bzip2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(bzip2)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// bzip2.Reader(stream:Stream:r) {block?}
Gurax_DeclareFunction(Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that reads and uncompresses bzip2-encoded data stream.
)""");
}

Gurax_ImplementFunction(Reader)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Value> pValue(GenerateReader(stream.Reference()));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// bzip2.Writer(stream:Stream:w, blockSize100k?:Number) {block?}
Gurax_DeclareFunction(Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("blockSize100k", VTYPE_Number, ArgOccur::ZeroOrOnce);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that compresses data into a bzip2-encoded data stream.
The argument `blockSize100k` takes a number between 1 and 9
that specifies the block size to be used for compression.
The actual block size is 100000 times of this value.
Nine gives the best compression but takes most memory.
)""");
}

Gurax_ImplementFunction(Writer)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	int blockSize100k = args.IsValid()? args.PickNumberRanged<int>(1, 9) : 9;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Value> pValue(GenerateWriter(stream.Reference(), blockSize100k));
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

Gurax_EndModule(bzip2)
