//==============================================================================
// module-hash.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(hash)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// hash.CRC32(stream?:Stream) {block?}
Gurax_DeclareFunction(CRC32)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Accumulator` instance.
)**");
}

Gurax_ImplementFunction(CRC32)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_CRC32());
	if (pStream && !pAccumulator->PipeFromStream(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
}

// hash.MD5(stream?:Stream) {block?}
Gurax_DeclareFunction(MD5)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Accumulator` instance.
)**");
}

Gurax_ImplementFunction(MD5)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_MD5());
	if (pStream && !pAccumulator->PipeFromStream(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
}

// hash.SHA1(stream?:Stream) {block?}
Gurax_DeclareFunction(SHA1)
{
	Declare(VTYPE_Accumulator, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `Accumulator` instance.
)**");
}

Gurax_ImplementFunction(SHA1)
{
	// Arguments
	ArgPicker args(argument);
	Stream* pStream = args.IsValid()? &args.PickStream() : nullptr;
	// Function body
	RefPtr<Accumulator> pAccumulator(new Accumulator_SHA1());
	if (pStream && !pAccumulator->PipeFromStream(*pStream)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Accumulator(pAccumulator.release()));
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
	Assign(VTYPE_Accumulator);
	// Assignment of function
	Assign(Gurax_CreateFunction(CRC32));
	Assign(Gurax_CreateFunction(MD5));
	Assign(Gurax_CreateFunction(SHA1));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(hash)
