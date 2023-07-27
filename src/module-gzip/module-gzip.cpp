//==============================================================================
// module-gzip.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(gzip)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// gzip.Reader(stream as Stream) {block?}
Gurax_DeclareFunction(Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
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

// gzip.Writer(stream:w as Stream, level? as Number) {block?}
Gurax_DeclareFunction(Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareArg("level", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
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
// Implementation of method
//------------------------------------------------------------------------------
// Stream#Reader@gzip() {block?}
Gurax_DeclareMethodAlias(Stream, Reader_at_gzip, "Reader@gzip")
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that reads and uncompresses gzip-encoded data stream.
)""");
}

Gurax_ImplementMethod(Stream, Reader_at_gzip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Function body
	const int windowBits = 31;
	RefPtr<Value> pValue(GenerateReader(stream.Reference(), windowBits));
	if (!pValue) return Value::nil();
	return argument.ReturnValue(processor, pValue.release());
}

// Stream#Writer@gzip(level? as Number) {block?}
Gurax_DeclareMethodAlias(Stream, Writer_at_gzip, "Writer@gzip")
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("level", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that compresses data into a gzip-encoded data stream.
)""");
}

Gurax_ImplementMethod(Stream, Writer_at_gzip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
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
	// Assignment of method
	VTYPE_Stream.Assign(Gurax_CreateMethod(Stream, Reader_at_gzip));
	VTYPE_Stream.Assign(Gurax_CreateMethod(Stream, Writer_at_gzip));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(gzip)
