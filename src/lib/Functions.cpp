//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// Print(str*:String):void
Gurax_DeclareFunction(Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("str", VTYPE_String, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Print)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.Print(valueList);
	return Value::nil();
}

// Printf(format:String, values*):void
Gurax_DeclareFunction(Printf)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Printf)
{
	Stream& stream = *Stream::COut;
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	stream.PrintFmt(format, values);
	return Value::nil();
}

// Println(objs*):void
Gurax_DeclareFunction(Println)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Println)
{
	Stream& stream = *Stream::COut;
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	stream.Println(values);
	return Value::nil();
}

void Functions::PrepareBasic(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Print));
	frame.Assign(Gurax_CreateFunction(Printf));
	frame.Assign(Gurax_CreateFunction(Println));
}

}
