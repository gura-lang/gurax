//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// Format(format:String, values*):String:map
Gurax_DeclareFunction(Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Format)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	String str;
	str.PrintFmt(format, values);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(str);
}

// Print(str*:String):void:map
Gurax_DeclareFunction(Print)
{
	Declare(VTYPE_Nil, Flag::Map);
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

// Printf(format:String, values*):void:map
Gurax_DeclareFunction(Printf)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Printf)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.PrintFmt(format, values);
	return Value::nil();
}

// Println(objs*):void:map
Gurax_DeclareFunction(Println)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(Println)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
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
