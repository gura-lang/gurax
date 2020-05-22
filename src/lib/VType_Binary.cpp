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

- `b'...' .. read-only binary literal`
- `B'...' .. writable binary literal`

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
	RefPtr<BinaryReferable> pBinary(new BinaryReferable());
	return argument.ReturnValue(processor, new Value_Binary(pBinary.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Binary#Dump(stream?:Stream:w):void:[addr,upper]
Gurax_DeclareMethod(Binary, Dump)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(addr));
	DeclareAttrOpt(Gurax_Symbol(upper));
	AddHelp(
		Gurax_Symbol(en),
		"Prints a hexadecimal dump of the `Binary` to the standard output.\n"
		"If the argument `stream` is specified, the result would be output to the stream.\n"
		"\n"
		"In default, hexadecimal digit are printed with lower-case characters.\n"
		"Specifying an attribute `:upper` would output them with upper-case characters instead.\n"
		"\n"
		"Specifying `:addr` attribute will apppend the current address number on each line.\n"
		"\n"
		"Example:\n"
		"    >>> b'A quick brown fox jumps over the lazy dog.'.Dump():upper\n"
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
	StringStyle ss;
	if (argument.IsSet(Gurax_Symbol(addr))) ss.SetAddressInfo();
	if (argument.IsSet(Gurax_Symbol(upper))) ss.SetUpperCase();
	// Function body
	binary.GetBinary().Dump(stream, ss);
	return Value::nil();
}

// Binary#Pointer(offset?:Number) {block?}
Gurax_DeclareMethod(Binary, Pointer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Pointer` instance that points memory in the `Binary`.");
}

Gurax_ImplementMethod(Binary, Pointer)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Argument
	ArgPicker args(argument);
	size_t offset = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Value> pValue(new Value_Pointer(new Pointer_Binary(valueThis.GetBinaryReferable().Reference(), offset)));
	return argument.ReturnValue(processor, pValue.release());
}

// Binary#Reader() {block?}
Gurax_DeclareMethod(Binary, Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
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
	RefPtr<Value> pValue(new Value_Stream(new Stream_Binary(Stream::Flag::Readable, binary.Reference(), offset)));
	return argument.ReturnValue(processor, pValue.release());
}

// Binary#Writer() {block?}
Gurax_DeclareMethod(Binary, Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
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
	RefPtr<Value> pValue(new Value_Stream(new Stream_Binary(Stream::Flag::Writable, binary.Reference(), offset)));
	return argument.ReturnValue(processor, pValue.release());
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
		"The binary's size in bytes.");
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
	return new Value_Pointer(new Pointer_Binary(valueThis.GetBinaryReferable().Reference()));
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
// Implementation of operator
//------------------------------------------------------------------------------
// Binary + Binary
Gurax_ImplementOpBinary(Add, Binary, Binary)
{
	Binary binaryL = Value_Binary::GetBinary(valueL);
	const Binary& binaryR = Value_Binary::GetBinary(valueR);
	binaryL += binaryR;
	return new Value_Binary(binaryL);
}

// Binary * Number
Gurax_ImplementOpBinary(Mul, Binary, Number)
{
	const Binary& binaryL = Value_Binary::GetBinary(valueL);
	size_t numR = Value_Number::GetNumberNonNeg<size_t>(valueR);
	if (Error::IsIssued()) return Value::nil();
	return new Value_Binary(binaryL.Repeat(true, numR));
}

// Binary == Binary
Gurax_ImplementOpBinary(Eq, Binary, Binary)
{
	const Binary& binaryL = Value_Binary::GetBinary(valueL);
	const Binary& binaryR = Value_Binary::GetBinary(valueR);
	return new Value_Bool(binaryL == binaryR);
}

// Binary != Binary
Gurax_ImplementOpBinary(Ne, Binary, Binary)
{
	const Binary& binaryL = Value_Binary::GetBinary(valueL);
	const Binary& binaryR = Value_Binary::GetBinary(valueR);
	return new Value_Bool(binaryL != binaryR);
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
	Assign(Gurax_CreateMethod(Binary, Pointer));
	Assign(Gurax_CreateMethod(Binary, Reader));
	Assign(Gurax_CreateMethod(Binary, Writer));
	// Assignment of property
	Assign(Gurax_CreateProperty(Binary, bytes));
	Assign(Gurax_CreateProperty(Binary, p));
	Assign(Gurax_CreateProperty(Binary, writable));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, Binary, Binary);
	Gurax_AssignOpBinary(Mul, Binary, Number);
	Gurax_AssignOpBinary(Eq, Binary, Binary);
	Gurax_AssignOpBinary(Ne, Binary, Binary);
}

//------------------------------------------------------------------------------
// Value_Binary
//------------------------------------------------------------------------------
VType& Value_Binary::vtype = VTYPE_Binary;

String Value_Binary::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str.Format(":%dbytes", _pBinary->GetBinary().size());
	str += _pBinary->GetBinary().IsWritable()? "writrable" : "constant";
	str += ">";
	return str;
}

String Value_Binary::ToStringDetail(const StringStyle& ss) const
{
	const Binary& binary = _pBinary->GetBinary();
	String str = binary.IsWritable()? "B" : "b";
	str += binary.Enquote();
	return str;
}

}
