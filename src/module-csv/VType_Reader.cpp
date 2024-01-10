//==============================================================================
// VType_Reader.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(csv.Reader, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(csv.Reader, `en)}

${help.ComposeMethodHelp(csv.Reader, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// csv.Reader(stream:r as Stream) {block?}
Gurax_DeclareConstructor(Reader)
{
	Declare(VTYPE_Reader, Flag::None);
	DeclareArg("stream", VTYPE_Stream, DeclArg::Occur::Once, DeclArg::Flag::StreamR);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `csv.Reader` instance.
)""");
}

Gurax_ImplementConstructor(Reader)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	// Function body
	RefPtr<Reader> pReader(new Reader(stream.Reference()));
	return argument.ReturnValue(processor, new Value_Reader(pReader.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// csv.Reader#ReadLine(func? as Function) {block?}
Gurax_DeclareMethod(Reader, ReadLine)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Reader, ReadLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	ArgPicker args(argument);
	const Function* pFunc = args.IsValid()? &args.PickFunction() : nullptr;
	// Function body
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (!valueThis.GetReader().ReadLine(*pValueOwner)) return Value::nil();
	if (!pFunc) {
		return argument.ReturnValue(processor, new Value_Tuple(pValueOwner.release()));
	} else if (pFunc->GetSymbol()->IsIdentical(Gurax_Symbol(List))) {
		return argument.ReturnValue(processor, new Value_List(VTYPE_String, pValueOwner.release()));
	} else {
		return argument.ReturnValue(processor, pFunc->EvalEasy(processor, *pValueOwner));
	}
}

// csv.Reader#ReadLines(func? as Function):[asList,asTuple] {block?}
Gurax_DeclareMethod(Reader, ReadLines)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("func", VTYPE_Function, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Reader, ReadLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	ArgPicker args(argument);
	const Function* pFunc = args.IsValid()? &args.PickFunction() : nullptr;
	// Function body
	if (!pFunc) {
		return argument.ReturnIterator(processor, new Iterator_ReadLineAsTuple(valueThis.GetReader().Reference()));
	} else if (pFunc->GetSymbol()->IsIdentical(Gurax_Symbol(List))) {
		return argument.ReturnIterator(processor, new Iterator_ReadLineAsList(valueThis.GetReader().Reference()));
	} else {
		return argument.ReturnIterator(processor, new Iterator_ReadLineAndEval(valueThis.GetReader().Reference(), processor.Reference(), pFunc->Reference()));
	}
}

//------------------------------------------------------------------------------
// VType_Reader
//------------------------------------------------------------------------------
VType_Reader VTYPE_Reader("Reader");

void VType_Reader::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Reader));
	// Assignment of method
	Assign(Gurax_CreateMethod(Reader, ReadLine));
	Assign(Gurax_CreateMethod(Reader, ReadLines));
}

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
VType& Value_Reader::vtype = VTYPE_Reader;

String Value_Reader::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetReader().ToString(ss));
}

Gurax_EndModuleScope(csv)
