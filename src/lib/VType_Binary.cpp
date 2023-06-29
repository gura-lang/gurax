//==============================================================================
// VType_Binary.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

- `b'...' .. read-only binary literal`
- `B'...' .. modifiable binary literal`

${help.ComposePropertyHelp(Binary, `en)}

# Operator

- `Binary + Binary` ... 
- `Binary * Number` ... 
- `Binary == Binary` ...
- `Binary != Binary` ... 

${help.ComposeConstructorHelp(Binary, `en)}

${help.ComposeMethodHelp(Binary, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
Gurax_DeclareConstructor(Binary)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Binary` instance.
)""");
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
// Binary#Clear():reduce
Gurax_DeclareMethod(Binary, Clear)
{
	Declare(VTYPE_Binary, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Clear the content of the Binary.
)""");
}

Gurax_ImplementMethod(Binary, Clear)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Binary& buff = valueThis.GetBinary();
	// Function body
	if (!buff.CheckWritable()) return Value::nil();
	buff.clear();
	return argument.GetValueThis().Reference();
}

// Binary#Decode(codec:Codec):String {block?}
Gurax_DeclareMethod(Binary, Decode)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Decodes the binary with the given `codec` and return the result as a `String`.
)""");
}

Gurax_ImplementMethod(Binary, Decode)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Codec& codec = args.Pick<Value_Codec>().GetCodec();
	// Function body
	const Binary& buff = valueThis.GetBinary();
	String dst;
	if (!codec.Decode(dst, buff)) return Value::nil();
	return new Value_String(dst);
}

// Binary#Dump(stream?:Stream:w, addrOffset?:Number):void:[addr,upper]
Gurax_DeclareMethod(Binary, Dump)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareArg("addrOffset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DumpStyle::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints a hexadecimal dump of the `Binary` to the standard output.
If the argument `stream` is specified, the result would be output to the stream.

In default, hexadecimal digit are printed with lower-case characters.
Specifying an attribute `:upper` would output them with upper-case characters instead.

Specifying `:addr` attribute will apppend the current address number on each line.

Example:
    >>> b'A quick brown fox jumps over the lazy dog.'.Dump():upper
    41 20 71 75 69 63 6B 20 62 72 6F 77 6E 20 66 6F  A quick brown fo
    78 20 6A 75 6D 70 73 20 6F 76 65 72 20 74 68 65  x jumps over the
    20 6C 61 7A 79 20 64 6F 67 2E                     lazy dog.
)""");
}

Gurax_ImplementMethod(Binary, Dump)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Binary& binary = valueThis.GetBinaryReferable().GetBinary();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	size_t addrOffset = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	DumpStyle ds(argument, addrOffset);
	// Function body
	stream.Dump(binary.data(), binary.size(), ds);
	return Value::nil();
}

// Binary#Pointer(offset?:Number) {block?}
Gurax_DeclareMethod(Binary, Pointer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("offset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Pointer` instance that points memory in the `Binary`.
)""");
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

// Binary#Reader(codec?:Codec) {block?}
Gurax_DeclareMethod(Binary, Reader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that reads data from the `Binary`.
)""");
}

Gurax_ImplementMethod(Binary, Reader)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	// Argument
	ArgPicker args(argument);
	RefPtr<Codec> pCodec(args.IsValid()? args.PickCodec().Reference() : Codec::CreateDumb());
	// Function body
	size_t offset = 0;
	RefPtr<Value> pValue(new Value_Stream(new Stream_Binary(
			Stream::Flag::Readable, pCodec.release(), binary.Reference(), offset)));
	return argument.ReturnValue(processor, pValue.release());
}

// Binary#Writer(codec?:Codec) {block?}
Gurax_DeclareMethod(Binary, Writer)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance that writes data into the `Binary`.
)""");
}

Gurax_ImplementMethod(Binary, Writer)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const BinaryReferable& binary = valueThis.GetBinaryReferable();
	// Argument
	ArgPicker args(argument);
	RefPtr<Codec> pCodec(args.IsValid()? args.PickCodec().Reference() : Codec::CreateDumb());
	// Function body
	if (!binary.GetBinary().CheckWritable()) return Value::nil();
	size_t offset = binary.GetBinary().size();
	RefPtr<Value> pValue(new Value_Stream(new Stream_Binary(
			Stream::Flag::Writable, pCodec.release(), binary.Reference(), offset)));
	return argument.ReturnValue(processor, pValue.release());
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// Binary#bytes
Gurax_DeclareProperty_R(Binary, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
The binary's size in bytes.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a `pointer` instance that accesses the binary.
This result is equivalent to that of calling the method `binary#Pointer()`
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns `true` if the binary data can be modified.
)""");
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaretion of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Binary));
	// Assignment of method
	Assign(Gurax_CreateMethod(Binary, Clear));
	Assign(Gurax_CreateMethod(Binary, Decode));
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

bool Value_Binary::DoEmptyIndexGet(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return Value::undefined();
}

bool Value_Binary::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_Binary::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const Binary& buff = GetBinary();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, buff.size(), &idx)) return false;
	*ppValue = new Value_Binary(Binary(buff.data() + idx, 1));
	return true;
}

bool Value_Binary::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "modification by index access is not permitted");
	return false;
}

String Value_Binary::ToString(const StringStyle& ss) const
{
	const Binary& buff = _pBinary->GetBinary();
	if (ss.IsBracket()) {
		return ToStringGeneric(ss, String().Format(":%dbytes:%s",
				buff.size(), buff.IsWritable()? "writrable" : "readOnly"));
	}
	return buff.ToString(ss);
}

bool Value_Binary::DoSerialize(Stream& stream) const
{
	return stream.SerializeBinary(GetBinary());
}

Value* VType_Binary::DoDeserialize(Stream& stream) const
{
	Binary binary;
	return stream.DeserializeBinary(binary)? new Value_Binary(binary) : Value::nil();
}

}
