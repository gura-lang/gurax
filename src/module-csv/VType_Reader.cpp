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
// csv.Reader#ReadLine():[asList,asTuple] {block?}
Gurax_DeclareMethod(Reader, ReadLine)
{
	Declare(VTYPE_List, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(asList));
	DeclareAttrOpt(Gurax_Symbol(asTuple));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Reader, ReadLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	bool asListFlag = argument.IsSet(Gurax_Symbol(asList));
	// Function body
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (!valueThis.GetReader().ReadLine(*pValueOwner)) return Value::nil();
	return asListFlag?
		argument.ReturnValue(processor, new Value_List(VTYPE_String, pValueOwner.release())) :
		argument.ReturnValue(processor, new Value_Tuple(pValueOwner.release()));
}

// csv.Reader#ReadLines():[asList,asTuple] {block?}
Gurax_DeclareMethod(Reader, ReadLines)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	DeclareAttrOpt(Gurax_Symbol(asList));
	DeclareAttrOpt(Gurax_Symbol(asTuple));
	AddHelp(Gurax_Symbol(en), u8R"""(
Skeleton.
)""");
}

Gurax_ImplementMethod(Reader, ReadLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	bool asListFlag = argument.IsSet(Gurax_Symbol(asList));
	// Function body
	return asListFlag?
		argument.ReturnIterator(processor, new Iterator_ReadLineAsList(valueThis.GetReader().Reference())) :
		argument.ReturnIterator(processor, new Iterator_ReadLineAsTuple(valueThis.GetReader().Reference()));
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
