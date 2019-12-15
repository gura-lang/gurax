//==============================================================================
// VType_Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
Gurax_DeclareConstructor(Binary)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Binary` instance.");
}

Gurax_ImplementConstructor(Binary)
{
	// Function body
	RefPtr<BinaryReferable> pBinary(new BinaryReferable(true));
	return argument.ReturnValue(processor, new Value_Binary(pBinary.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Binary#Dump(stream?:Stream:w):void:[upper]
Gurax_DeclareMethod(Binary, Dump)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(upper));
	AddHelp(
		Gurax_Symbol(en),
		"Prints a hexadecimal dump from the content of the `binary` to the standard output.\n"
		"If the argument `stream` is specified, the result would be output to the stream.\n"
		"\n"
		"In default, hexadecimal digit are printed with lower-case characters.\n"
		"Specifying an attribute `:upper` would output them with upper-case characters instead.\n"
		"\n"
		"Example:\n"
		"    >>> b'A quick brown fox jumps over the lazy dog.'.dump():upper\n"
		"    41 20 71 75 69 63 6B 20 62 72 6F 77 6E 20 66 6F  A quick brown fo\n"
		"    78 20 6A 75 6D 70 73 20 6F 76 65 72 20 74 68 65  x jumps over the\n"
		"    20 6C 61 7A 79 20 64 6F 67 2E                     lazy dog.\n");
}

Gurax_ImplementMethod(Binary, Dump)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	bool upperFlag = argument.IsSet(Gurax_Symbol(upper));
	// Function body
	StringStyle ss;
	if (upperFlag) ss.UpperCase();
	binary.GetBinary().Dump(stream, ss);
	return Value::nil();
}

// Binary#Reader() {block?}
Gurax_DeclareMethod(Binary, Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stream` instance that reads data from the `Binary`.");
}

Gurax_ImplementMethod(Binary, Reader)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	// Function body
	size_t offset = 0;
	return new Value_Stream(new Stream_Binary(Stream::Flag::Readable, binary.Reference(), offset));
}

// Binary#Writer() {block?}
Gurax_DeclareMethod(Binary, Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stream` instance that writes data into the `Binary`.");
}

Gurax_ImplementMethod(Binary, Writer)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	// Function body
	if (!binary.GetBinary().CheckWritable()) return Value::nil();
	size_t offset = binary.GetBinary().size();
	return new Value_Stream(new Stream_Binary(Stream::Flag::Writable, binary.Reference(), offset));
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Binary#bytes
Gurax_DeclareProperty_R(Binary, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The size of the binary in bytes.");
}

Gurax_ImplementPropertyGetter(Binary, bytes)
{
	auto& valueThis = GetValueThis(valueTarget);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	return new Value_Number(binary.GetBinary().size());
}

// Binary#p
Gurax_DeclareProperty_R(Binary, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `pointer` instance that accesses the binary.\n"
		"This result is equivalent to that of calling the method `binary#pointer()`");
}

Gurax_ImplementPropertyGetter(Binary, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Pointer(new Pointer_Binary(0, valueThis.Reference()));
}

// Binary#writable
Gurax_DeclareProperty_R(Binary, writable)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the binary data can be modified.\n");
}

Gurax_ImplementPropertyGetter(Binary, writable)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Bool(valueThis.GetBinary().IsWritable());
}

//------------------------------------------------------------------------------
// VType_Binary
//------------------------------------------------------------------------------
VType_Binary VTYPE_Binary("Binary");

void VType_Binary::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Binary));
	// Assignment of method
	Assign(Gurax_CreateMethod(Binary, Dump));
	Assign(Gurax_CreateMethod(Binary, Reader));
	Assign(Gurax_CreateMethod(Binary, Writer));
	// Assignment of property
	Assign(Gurax_CreateProperty(Binary, bytes));
	Assign(Gurax_CreateProperty(Binary, p));
	Assign(Gurax_CreateProperty(Binary, writable));
}

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
VType& Value_Binary::vtype = VTYPE_Binary;

String Value_Binary::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Printf(":%dbytes", _pBinary->GetBinary().size());
	str += _pBinary->GetBinary().IsWritable()? "writrable" : "constant";
	str += ">";
	return str;
}

String Value_Binary::ToStringDetail(const StringStyle& ss) const
{
	String str = "b";
	str += _pBinary->GetBinary().MakeQuoted(true);
	return str;
}

}
