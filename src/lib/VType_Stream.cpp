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
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
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
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
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

// Stream#Read(bytes?:Number)
Gurax_DeclareMethod(Stream, Read)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from the `Stream` and returns it as a `Binary` instance.");
}

Gurax_ImplementMethod(Stream, Read)
{
	return Value::nil();
}

// Stream#ReadLine():[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLine)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	AddHelp(
		Gurax_Symbol(en),
		"Reads one line from the `Stream` and returns it as a `String` instance.");
}

Gurax_ImplementMethod(Stream, ReadLine)
{
	return Value::nil();
}

// Stream#ReadLines(nLines?:Number):[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLines)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("nLines", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that reads each line from the `Stream` and returns it as a `String` instance.");
}

Gurax_ImplementMethod(Stream, ReadLines)
{
	return Value::nil();
}

// Stream#Write(ptr:Pointer, bytes?:Number)
Gurax_DeclareMethod(Stream, Write)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Writes data pointed by the specified `Pointer` instance to the `Stream`.");
}

Gurax_ImplementMethod(Stream, Write)
{
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
	Assign(Gurax_CreateMethod(Stream, Read));
	Assign(Gurax_CreateMethod(Stream, ReadLine));
	Assign(Gurax_CreateMethod(Stream, ReadLines));
	Assign(Gurax_CreateMethod(Stream, Write));
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
VType& Value_Stream::vtype = VTYPE_Stream;

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
