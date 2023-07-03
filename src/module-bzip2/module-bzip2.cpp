//==============================================================================
// module-bzip2.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(bzip2)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// Stream#Reader@bzip2() {block?}
Gurax_DeclareMethodAlias(Stream, Reader_at_bzip2, "Reader@bzip2")
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that reads and uncompresses bzip2-encoded data stream.
)""");
}

Gurax_ImplementMethod(Stream, Reader_at_bzip2)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Function body
	RefPtr<Value> pValue(GenerateReader(stream.Reference()));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// Stream#Writer@bzip2(blockSize100k? as Number) {block?}
Gurax_DeclareMethodAlias(Stream, Writer_at_bzip2, "Writer@bzip2")
{
	Declare(VTYPE_Stream, Flag::None);
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

Gurax_ImplementMethod(Stream, Writer_at_bzip2)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
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
	// Assignment of method
	VTYPE_Stream.Assign(Gurax_CreateMethod(Stream, Reader_at_bzip2));
	VTYPE_Stream.Assign(Gurax_CreateMethod(Stream, Writer_at_bzip2));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(bzip2)
