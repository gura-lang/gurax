//==============================================================================
// VType_Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Stream#Print(values*):void:map
Gurax_DeclareMethod(Stream, Print)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` to the specified stream.");
}

Gurax_ImplementMethod(Stream, Print)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	stream.Print(valueList);
	return Value::nil();
}

// Stream#Printf(format:String, values*):void:map
Gurax_DeclareMethod(Stream, Printf)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` to the specified stream according to formatter specifiers specified in `format`.\n"
		"\n"
		"For detail information about formatter specications,\n"
		"refer to the help or document of `Format()` function.");
}

Gurax_ImplementMethod(Stream, Printf)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	stream.PrintFmt(format, values);
	return Value::nil();
}

// Stream#Println(values*):void:map
Gurax_DeclareMethod(Stream, Println)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` and an end-of-line character to the specified stream.\n");
}

Gurax_ImplementMethod(Stream, Println)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	stream.Println(values);
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
VType_Stream VTYPE_Stream("Stream");

void VType_Stream::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(Stream, Print));
	Assign(Gurax_CreateMethod(Stream, Printf));
	Assign(Gurax_CreateMethod(Stream, Println));
}

Value* VType_Stream::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Binary)) {
		const BinaryReferable& binary = Value_Binary::GetBinaryReferable(value);
		size_t offset = (flags & DeclArg::Flag::StreamW)? binary.GetBinary().size() : 0;
		return new Value_Stream(new Stream_Binary(binary.Reference(), offset));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Stream
//------------------------------------------------------------------------------
String Value_Stream::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetStream().GetName();
	str += ">";
	return str;
}

String Value_Stream::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
