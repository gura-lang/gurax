//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// Format(format:String, values*):String
Gurax_DeclareFunction(Format)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Format)
{
	String str;
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	str.PrintFmt(format, values);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(str);
}

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

// Hoge(a:Number, b:Number):map
Gurax_DeclareFunction(Hoge)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("a", VTYPE_Number, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("b", VTYPE_Number, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Hoge)
{
	// Arguments
	ArgPicker args(argument);
	Double a = args.PickDouble();
	Double b = args.PickDouble();
	// Function body
	return new Value_Number(a + b);
}

void Functions::PrepareBasic(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Format));
	frame.Assign(Gurax_CreateFunction(Print));
	frame.Assign(Gurax_CreateFunction(Printf));
	frame.Assign(Gurax_CreateFunction(Println));
	frame.Assign(Gurax_CreateFunction(Hoge));
}

}
