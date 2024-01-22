//==============================================================================
// VType_Pointer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

- `p.int8 = 10` .. Writes data into the pointed.
- `p.int32 = 10` .. Writes data into the pointed.
- `x = p.int8` ..  Reads data from the pointed.
- `x = p.int16` ..  Reads data from the pointed.

- `p.int8:fwd = 10` .. Writes data into the pointed memory and increases the address by 1 byte.

${help.ComposePropertyHelp(Pointer, `en)}

# Operator

`Pointer + Number` ... Creates a `Pointer` that increases the left-sided `Pointer` by the right-sided `Number`.

`Number + Pointer` ... Creates a `Pointer` that increases the right-sided `Pointer` by the left-sided `Number`.

`Pointer - Number` ... Creates a `Pointer` that decreases the left-sided `Pointer` by the right-sided `Number`.

`Pointer - Pointer` ... Creates a `Number` of the difference between the left-sided `Pointer` and the right-sided `Pointer`.


# Cast Operation

`Binary` as `Pointer` ... Creates a `Pointer` that scans the data in `Binary`.

`Array` as `Pointer` ... Creates a `Pointer` that scans the data in `Array`.

`Image` as `Pointer` ... Creates a `Pointer` that scans the data in `Image`.


${help.ComposeConstructorHelp(Pointer, `en)}

${help.ComposeMethodHelp(Pointer, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Pointer() {block?}
Gurax_DeclareConstructor(Pointer)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Pointer` instance.
)""");
}

Gurax_ImplementConstructor(Pointer)
{
	// Arguments
	//ArgPicker args(argument);
	// Function body
	//RefPtr<Pointer> pPointer(new Pointer(0));
	//return argument.ReturnValue(processor, new Value_Pointer(pPointer.release()));
	return Value::nil();
}

//-----------------------------------------------------------------------------
// Implementation of class method
//-----------------------------------------------------------------------------
// Pointer.HasSame(p1 as Pointer, p2 as Pointer)
Gurax_DeclareClassMethod(Pointer, HasSame)
{
	Declare(VTYPE_Bool, Flag::None);
	DeclareArg("p1", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("p2", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Compares contents pointed by the specified by the two given pointers and returns
`true` if they are identical and `false` otherwise.
)""");
}

Gurax_ImplementClassMethod(Pointer, HasSame)
{
	// Arguments
	ArgPicker args(argument);
	const Pointer& p1 = args.PickPointer();
	const Pointer& p2 = args.PickPointer();
	// Function body
	bool rtn = (p1.GetBytesAvailable() == p2.GetBytesAvailable()) &&
		(::memcmp(p1.GetPointerC<void>(), p2.GetPointerC<void>(), p1.GetBytesAvailable()) == 0);
	return new Value_Bool(rtn);
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Pointer#Append(pointer as Pointer, bytes? as Number):reduce:[stay]
Gurax_DeclareMethod(Pointer, Append)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("pointer", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Pointer, Append)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Pointer& pointerSrc = args.Pick<Value_Pointer>().GetPointer();
	size_t bytes = args.IsValid()?
		std::min(args.PickNumberNonNeg<size_t>(), pointerSrc.GetBytesAvailable()) :
		pointerSrc.GetBytesAvailable();
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	Pointer& pointer = valueThis.GetPointer();
	size_t offset = pointer.GetOffset();
	if (!pointer.PutPointer(pointerSrc, bytes)) {
		Error::Issue(ErrorType::MemoryError, "failed to write data into the pointer");
		return Value::nil();
	}
	if (stayFlag) pointer.SetOffset(offset);
	return valueThis.Reference();
}

// Pointer#Decode(codec as Codec) as String {block?}
Gurax_DeclareMethod(Pointer, Decode)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Decodes the data pointed by the pointer with the given `codec` and return the result as a `String`.
)""");
}

Gurax_ImplementMethod(Pointer, Decode)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Codec& codec = args.Pick<Value_Codec>().GetCodec();
	// Function body
	const Pointer& ptr = valueThis.GetPointer();
	String dst;
	if (!codec.Decode(dst, ptr.GetPointerC<void>(), ptr.GetBytesAvailable())) return Value::nil();
	return new Value_String(dst);
}

// Pointer#Dump(stream:w? as Stream, addrOffset? as Number):void:[addr,upper]
Gurax_DeclareMethod(Pointer, Dump)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareArg("addrOffset", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DumpStyle::DeclareAttrOpt(*this);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints a hexadecimal dump of the `Pointer` to the standard output.
If the argument `stream` is specified, the result would be output to the stream.

In default, hexadecimal digit are printed with lower-case characters.
Specifying an attribute `:upper` would output them with upper-case characters instead.

Specifying `:addr` attribute will apppend the current address number on each line.

Example:
    >>> b'A quick brown fox jumps over the lazy dog.'.p.Dump():upper
    41 20 71 75 69 63 6B 20 62 72 6F 77 6E 20 66 6F  A quick brown fo
    78 20 6A 75 6D 70 73 20 6F 76 65 72 20 74 68 65  x jumps over the
    20 6C 61 7A 79 20 64 6F 67 2E                     lazy dog.
)""");
}

Gurax_ImplementMethod(Pointer, Dump)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Pointer& pointer = valueThis.GetPointer();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	size_t addrOffset = args.IsValid()? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	DumpStyle ds(argument, addrOffset);
	// Function body
	stream.Dump(pointer.GetPointerC<UInt8>(), pointer.GetBytesAvailable(), ds);
	return Value::nil();
}

// Pointer#Pack(format as String, args*):reduce:[stay]
Gurax_DeclareMethod(Pointer, Pack)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(Gurax_Symbol(en), u8R"""(
Packs values in the argument list according to specifiers in the `format`
into a binary and adds it to where the pointer points.
The pointer offset is automatically incremented by the added length
unless `:stay` attribute is specified.

This method returns a reference to the target instance itself.

A specifier has a format of \"`nX`\" where `X` is a format character
that represents a packing format and `n` is a number of packing size.
The number can be omitted, and it would be treated as `1` in that case.

Following format characters would take a `number` value from the argument list
and pack them into a binary sequence.

- `b` .. One-byte signed number.
- `B` .. One-byte unsigned number.
- `h` .. Two-byte signed number.
- `H` .. Two-byte unsigned number.
- `i` .. Four-byte signed number.
- `I` .. Four-byte unsigned number.
- `l` .. Four-byte signed number.
- `L` .. Four-byte unsigned number.
- `q` .. Eight-byte signed number.
- `Q` .. Eight-byte unsigned number.
- `f` .. Float-typed number occupying four bytes.
- `d` .. Double-typed number occupying eight bytes.

As for them, the packing size `n` means the number of values to be packed.

Following format characters would take a `string` value from the argument list
and pack them into a binary sequence.

- `s` .. Packs a sequence of UTF-8 codes in the string.
        The packing size `n` means the size of the room in bytes
        where the character codes are to be packed.
        Only the sequence within the allocated room would be packed.
        If the string length is smaller than the room,
        the lacking part would be filled with zero.
- `c` .. Picks the first byte of the string and packs it as a one-byte unsigned number.
        The packing size `n` means the number of values to be packed.

Following format character would take no value from the argument list.

- `x` .. Fills the binary with zero.
        The packing size `n` means the size of the room in bytes
        to be filled with zero.

The default byte-order for numbers of two-byte, four-byte and eight-byte
depends on the system the interpreter is currently running.
You can change it by the following specifiers:

- `@` .. System-dependent order.
- `=` .. System-dependent order.
- `<` .. Little endian
- `>` .. Big endian
- `!` .. Big endian

You can specify an asterisk character \"`*`\" for the number of packing size
that picks that number from the argument list.

You can specify encoding name embraced with \"`{`\" and \"`}`\" in the format
to change coding character set from UTF-8
while packing a string with format character \"`s`\".
)""");
}

Gurax_ImplementMethod(Pointer, Pack)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& valListArg = args.PickList();
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	// Function body
	Pointer& pointer = valueThis.GetPointer();
	size_t offset = pointer.GetOffset();
	pointer.Pack(format, valListArg);
	if (stayFlag) pointer.SetOffset(offset);
	return valueThis.Reference();
}

// Pointer#Put(elemType as Symbol, args*):reduce:[be,stay]
Gurax_DeclareMethod(Pointer, Put)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Pointer, Put)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Pointer::ElemType& elemType = Pointer::SymbolToElemType(args.PickSymbol());
	if (elemType.IsNone()) {
		Error::Issue(ErrorType::ValueError, "invalid symbol for elemType");
		return Value::nil();
	}
	const ValueList& valListArg = args.PickList();
	bool bigEndianFlag = argument.IsSet(Gurax_Symbol(be));
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	// Function body
	Pointer& pointer = valueThis.GetPointer();
	size_t offset = pointer.GetOffset();
	pointer.PutValues(elemType, bigEndianFlag, valListArg);
	if (stayFlag) pointer.SetOffset(offset);
	return valueThis.Reference();
}

// Pointer#Unpack(format as String):[raise,stay]
Gurax_DeclareMethod(Pointer, Unpack)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(Gurax_Symbol(en), u8R"""(
Extracts values from data sequence pointed by the `pointer` instance according to specifiers in the `format`
and returns a list containing the values.

A specifier has a format of \"`nX`\" where `X` is a format character
that represents a packing format and `n` is a number of packing size.
The number can be omitted, and it would be treated as `1` in that case.

Following format characters would extract an integer or float value of specified size
from the binary and returns a `number` value.

- `b` .. One-byte signed number.
- `B` .. One-byte unsigned number.
- `h` .. Two-byte signed number.
- `H` .. Two-byte unsigned number.
- `i` .. Four-byte signed number.
- `I` .. Four-byte unsigned number.
- `l` .. Four-byte signed number.
- `L` .. Four-byte unsigned number.
- `q` .. Eight-byte signed number.
- `Q` .. Eight-byte unsigned number.
- `f` .. Float-typed number occupying four bytes.
- `d` .. Double-typed number occupying eight bytes.

As for them, the packing size `n` means the number of values to be extracted.

Following format characters would extract a string sequence from the binary
and returns a `string` value.

- `s` .. Extracts a sequence of UTF-8 codes and returns `string` instance containing it.
        The unpacking size `n` means the size of the room in bytes
        where the character codes are to be unpacked.
- `c` .. Extracts a one-byte unsigned number and returns a `string` instance containing it.
        The unpacking size `n` means the number of values to be extracted.

Following format character would not return any value.

- `x` .. Advances the address by one byte.
        If the unpacking size `n` is specifies,
        it would advance the address by `n` bytes.

The default byte-order for numbers of two-byte, four-byte and eight-byte
depends on the system the interpreter is currently running.
You can change it by the following specifiers:

- `@` .. System-dependent order.
- `=` .. System-dependent order.
- `<` .. Little endian
- `>` .. Big endian
- `!` .. Big endian

You can specify an asterisk character \"`*`\" for the number of unpacking size
that picks that number from the argument list.

You can specify encoding name embraced with \"`{`\" and \"`}`\" in the format
to change coding character set from UTF-8
while extracting a string with format character \"`s`\".

An error occurs if the binary size is smaller than the format reqeusts.
If the attribute `:nil` is specified, `nil` value would be returned for such a case.
)""");
}

Gurax_ImplementMethod(Pointer, Unpack)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& valListArg = args.PickList();
	bool stayFlag = argument.IsSet(Gurax_Symbol(stay));
	bool exceedErrorFlag = argument.IsSet(Gurax_Symbol(raise));
	// Function body
	Pointer& pointer = valueThis.GetPointer();
	size_t offset = pointer.GetOffset();
	RefPtr<Value> pValue(pointer.Unpack(format, valListArg, exceedErrorFlag));
	if (stayFlag) pointer.SetOffset(offset);
	return pValue.release();
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// Pointer#@:[be,fwd]
Gurax_DeclarePropertyAlias_RW(Pointer, at, "@")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(Pointer, at)
{
	Pointer& pointer = GetValueThis(valueTarget).GetPointer();
	RefPtr<Value> pValue;
	pointer.Get(pointer.GetElemType(), pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, at)
{
	Pointer& pointer = GetValueThis(valueTarget).GetPointer();
	pointer.Put(pointer.GetElemType(), value, attr);
}

// Pointer#bytesAvail
Gurax_DeclareProperty_R(Pointer, bytesAvail)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
the data size available from the current pointer position.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, bytesAvail)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetBytesAvailable());
}

// Pointer#bytesEntire
Gurax_DeclareProperty_R(Pointer, bytesEntire)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
the entire size of the memory that the pointer covers.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, bytesEntire)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetBytesEntire());
}

// Pointer#elemType
Gurax_DeclareProperty_R(Pointer, elemType)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementPropertyGetter(Pointer, elemType)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Symbol(valueThis.GetPointer().GetElemType().pSymbol);
}

// Pointer#offset
Gurax_DeclareProperty_RW(Pointer, offset)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
the offset of the pointer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, offset)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetOffset());
}

Gurax_ImplementPropertySetter(Pointer, offset)
{
	auto& valueThis = GetValueThis(valueTarget);
	size_t offset = Value_Number::GetNumberNonNeg<size_t>(value);
	if (Error::IsIssued()) return;
	valueThis.GetPointer().SetOffset(offset);
}

// Pointer#int8:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, int8)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of signed 8-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, int8)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Int8, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, int8)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Int8, value, attr);
}

// Pointer#int16:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, int16)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of signed 16-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, int16)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Int16, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, int16)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Int16, value, attr);
}

// Pointer#int32:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, int32)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of signed 32-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, int32)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Int32, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, int32)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Int32, value, attr);
}

// Pointer#int64:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, int64)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of signed 64-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, int64)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Int64, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, int64)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Int64, value, attr);
}

// Pointer#uint8:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, uint8)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 8-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, uint8)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::UInt8, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, uint8)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::UInt8, value, attr);
}

// Pointer#uint16:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, uint16)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 16-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, uint16)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::UInt16, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, uint16)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::UInt16, value, attr);
}

// Pointer#uint32:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, uint32)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 32-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, uint32)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::UInt32, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, uint32)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::UInt32, value, attr);
}

// Pointer#uint64:[be,fwd]
Gurax_DeclareProperty_RW(Pointer, uint64)
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 64-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, uint64)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::UInt64, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, uint64)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::UInt64, value, attr);
}

// Pointer#float:[be,fwd]
Gurax_DeclarePropertyAlias_RW(Pointer, float_, "float")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 64-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, float_)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Float, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, float_)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Float, value, attr);
}

// Pointer#double:[be,fwd]
Gurax_DeclarePropertyAlias_RW(Pointer, double_, "double")
{
	Declare(VTYPE_Any, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(fwd));
	AddHelp(Gurax_Symbol(en), u8R"""(
read or write a number stored in a format of unsigned 64-bit integer.
)""");
}

Gurax_ImplementPropertyGetter(Pointer, double_)
{
	RefPtr<Value> pValue;
	GetValueThis(valueTarget).GetPointer().Get(Pointer::ElemType::Double, pValue, attr);
	return pValue.release();
}

Gurax_ImplementPropertySetter(Pointer, double_)
{
	GetValueThis(valueTarget).GetPointer().Put(Pointer::ElemType::Double, value, attr);
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Pointer + Number
Gurax_ImplementOpBinary(Add, Pointer, Number)
{
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueL).Clone());
	long offset = Value_Number::GetNumber<long>(valueR);
	if (!pPointer->Advance(offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Number + Pointer
Gurax_ImplementOpBinary(Add, Number, Pointer)
{
	long offset = Value_Number::GetNumber<long>(valueL);
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueR).Clone());
	if (!pPointer->Advance(offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Pointer - Number
Gurax_ImplementOpBinary(Sub, Pointer, Number)
{
	RefPtr<Pointer> pPointer(Value_Pointer::GetPointer(valueL).Clone());
	long offset = Value_Number::GetNumber<long>(valueR);
	if (!pPointer->Advance(-offset)) return Value::nil();
	return new Value_Pointer(pPointer.release());
}

// Pointer - Pointer
Gurax_ImplementOpBinary(Sub, Pointer, Pointer)
{
	const Pointer& pointerL = Value_Pointer::GetPointer(valueL);
	const Pointer& pointerR = Value_Pointer::GetPointer(valueR);
	if (!pointerL.IsTargetIdentical(pointerR)) {
		Error::Issue(ErrorType::ValueError,
					"pointers must have the same target when the offset difference is calculated");
		return Value::nil();
	}
	return new Value_Number(static_cast<Int64>(pointerL.GetOffset()) - static_cast<Int64>(pointerR.GetOffset()));
}

//------------------------------------------------------------------------------
// VType_Pointer
//------------------------------------------------------------------------------
VType_Pointer VTYPE_Pointer("Pointer");

void VType_Pointer::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Pointer));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Pointer, HasSame));
	// Assignment of method
	Assign(Gurax_CreateMethod(Pointer, Append));
	Assign(Gurax_CreateMethod(Pointer, Decode));
	Assign(Gurax_CreateMethod(Pointer, Dump));
	Assign(Gurax_CreateMethod(Pointer, Pack));
	Assign(Gurax_CreateMethod(Pointer, Put));
	Assign(Gurax_CreateMethod(Pointer, Unpack));
	// Assignment of property
	Assign(Gurax_CreateProperty(Pointer, at));
	Assign(Gurax_CreateProperty(Pointer, bytesAvail));
	Assign(Gurax_CreateProperty(Pointer, bytesEntire));
	Assign(Gurax_CreateProperty(Pointer, elemType));
	Assign(Gurax_CreateProperty(Pointer, offset));
	Assign(Gurax_CreateProperty(Pointer, int8));
	Assign(Gurax_CreateProperty(Pointer, int16));
	Assign(Gurax_CreateProperty(Pointer, int32));
	Assign(Gurax_CreateProperty(Pointer, int64));
	Assign(Gurax_CreateProperty(Pointer, uint8));
	Assign(Gurax_CreateProperty(Pointer, uint16));
	Assign(Gurax_CreateProperty(Pointer, uint32));
	Assign(Gurax_CreateProperty(Pointer, uint64));
	Assign(Gurax_CreateProperty(Pointer, float_));
	Assign(Gurax_CreateProperty(Pointer, double_));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, Pointer, Number);
	Gurax_AssignOpBinary(Add, Number, Pointer);
	Gurax_AssignOpBinary(Sub, Pointer, Number);
	Gurax_AssignOpBinary(Sub, Pointer, Pointer);
}

Value* VType_Pointer::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_Binary)) {
		const BinaryReferable& buff = Value_Binary::GetBinaryReferable(value);
		return new Value_Pointer(new Pointer_Binary(buff.Reference()));
	} else if (value.IsType(VTYPE_Array)) {
		RefPtr<Pointer> pPointer(Value_Array::GetArray(value).CreatePointer());
		return new Value_Pointer(pPointer.release());
	} else if (value.IsType(VTYPE_Image)) {
		RefPtr<Pointer> pPointer(Value_Image::GetImage(value).CreatePointer());
		if (!pPointer) return Value::nil();
		return new Value_Pointer(pPointer.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Pointer
//------------------------------------------------------------------------------
VType& Value_Pointer::vtype = VTYPE_Pointer;

String Value_Pointer::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPointer().ToString(ss));
}

bool Value_Pointer::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	if (!valueIndex.IsInstanceOf(VTYPE_Number)) {
		Error::Issue(ErrorType::IndexError,
			"invalid value for indexing");
		return false;
	}
	const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
	Int idx = valueIndexEx.GetNumber<Int>();
	RefPtr<Pointer> pPointer(GetPointer().Clone());
	if (!pPointer->Advance(idx)) return false;
	RefPtr<Value> pValue;
	pPointer->Get(pPointer->GetElemType(), pValue, *Attribute::Empty);
	*ppValue = pValue.release();
	return true;
}

bool Value_Pointer::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	if (!valueIndex.IsInstanceOf(VTYPE_Number)) {
		Error::Issue(ErrorType::IndexError,
			"invalid value for indexing");
		return false;
	}
	const Value_Number& valueIndexEx = dynamic_cast<const Value_Number&>(valueIndex);
	Int idx = valueIndexEx.GetNumber<Int>();
	RefPtr<Pointer> pPointer(GetPointer().Clone());
	if (!pPointer->Advance(idx)) return false;
	pPointer->Put(pPointer->GetElemType(), *pValue, *Attribute::Empty);
	return true;
}

}
