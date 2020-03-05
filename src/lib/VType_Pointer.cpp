//==============================================================================
// VType_Pointer.cpp
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

- `p.int8 = 10` .. Writes data into the pointed memory and increments the address by 1 byte.
- `p.int32 = 10` .. Writes data into the pointed memory and increments the address by 4 byte.
- `x = p.int8` ..  Reads data from the pointed memory and increments the address by 1 byte.
- `x = p.int16` ..  Reads data from the pointed memory and increments the address by 2 byte.

- `p.int8:stay = 10` .. Writes data into the pointed memory and keeps the address intact.

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Template function
//------------------------------------------------------------------------------
template<typename T_Num>
Value* PointerGetTmpl(Value_Pointer& valueTarget, const Attribute& attr)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	bool exceedErrorFlag = false;
	Pointer& pointer = valueTarget.GetPointer();
	T_Num num;
	size_t offset = pointer.GetOffset();
	bool rtn = bigEndianFlag?
		pointer.Get<T_Num, true>(&num, exceedErrorFlag) :
		pointer.Get<T_Num, false>(&num, exceedErrorFlag);
	if (stayFlag) pointer.SetOffset(offset);
	return rtn? new Value_Number(num) : Value::nil();
}

template<typename T_Num>
void PointerPutTmpl(Value_Pointer& valueTarget, const Attribute& attr, const Value& value)
{
	bool stayFlag = attr.IsSet(Gurax_Symbol(stay));
	bool bigEndianFlag = attr.IsSet(Gurax_Symbol(be));
	Pointer& pointer = valueTarget.GetPointer();
	T_Num num = Value_Number::GetNumber<T_Num>(value);
	size_t offset = pointer.GetOffset();
	if (bigEndianFlag) { pointer.Put<T_Num, true>(num); } else { pointer.Put<T_Num, false>(num); }
	if (stayFlag) pointer.SetOffset(offset);
}

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Pointer() {block?}
Gurax_DeclareConstructor(Pointer)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Pointer` instance.");
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
// Implementation of method
//-----------------------------------------------------------------------------
// Pointer#Dump(stream?:Stream:w):void:[upper]
Gurax_DeclareMethod(Pointer, Dump)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(upper));
	AddHelp(
		Gurax_Symbol(en),
		"Prints a hexadecimal dump of the `Pointer` to the standard output.\n"
		"If the argument `stream` is specified, the result would be output to the stream.\n"
		"\n"
		"In default, hexadecimal digit are printed with lower-case characters.\n"
		"Specifying an attribute `:upper` would output them with upper-case characters instead.\n"
		"\n"
		"Example:\n"
		"    >>> b'A quick brown fox jumps over the lazy dog.'.p.Dump():upper\n"
		"    41 20 71 75 69 63 6B 20 62 72 6F 77 6E 20 66 6F  A quick brown fo\n"
		"    78 20 6A 75 6D 70 73 20 6F 76 65 72 20 74 68 65  x jumps over the\n"
		"    20 6C 61 7A 79 20 64 6F 67 2E                     lazy dog.\n");
}

Gurax_ImplementMethod(Pointer, Dump)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const Pointer& pointer = valueThis.GetPointer();
	// Argument
	ArgPicker args(argument);
	Stream& stream = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	bool upperFlag = argument.IsSet(Gurax_Symbol(upper));
	// Function body
	StringStyle ss;
	if (upperFlag) ss.UpperCase();
	stream.Dump(pointer.GetPointerC<UInt8>(), pointer.GetBytesAvailable(), ss);
	return Value::nil();
}

// Pointer#Pack(format:String, args*):reduce:[stay]
Gurax_DeclareMethod(Pointer, Pack)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(
		Gurax_Symbol(en),
		"Packs values in the argument list according to specifiers in the `format`\n"
		"into a binary and adds it to where the pointer points.\n"
		"The pointer offset is automatically incremented by the added length\n"
		"unless `:stay` attribute is specified.\n"
		"\n"
		"This method returns a reference to the target instance itself.\n"
		"\n"
		"A specifier has a format of \"`nX`\" where `X` is a format character\n"
		"that represents a packing format and `n` is a number of packing size.\n"
		"The number can be omitted, and it would be treated as `1` in that case.\n"
		"\n"
		"Following format characters would take a `number` value from the argument list\n"
		"and pack them into a binary sequence.\n"
		"\n"
		"- `b` .. One-byte signed number.\n"
		"- `B` .. One-byte unsigned number.\n"
		"- `h` .. Two-byte signed number.\n"
		"- `H` .. Two-byte unsigned number.\n"
		"- `i` .. Four-byte signed number.\n"
		"- `I` .. Four-byte unsigned number.\n"
		"- `l` .. Four-byte signed number.\n"
		"- `L` .. Four-byte unsigned number.\n"
		"- `q` .. Eight-byte signed number.\n"
		"- `Q` .. Eight-byte unsigned number.\n"
		"- `f` .. Float-typed number occupying four bytes.\n"
		"- `d` .. Double-typed number occupying eight bytes.\n"
		"\n"
		"As for them, the packing size `n` means the number of values to be packed.\n"
		"\n"
		"Following format characters would take a `string` value from the argument list\n"
		"and pack them into a binary sequence.\n"
		"\n"
		"- `s` .. Packs a sequence of UTF-8 codes in the string.\n"
		"         The packing size `n` means the size of the room in bytes\n"
		"         where the character codes are to be packed.\n"
		"         Only the sequence within the allocated room would be packed.\n"
		"         If the string length is smaller than the room,\n"
		"         the lacking part would be filled with zero.\n"
		"- `c` .. Picks the first byte of the string and packs it as a one-byte unsigned number.\n"
		"         The packing size `n` means the number of values to be packed.\n"
		"\n"
		"Following format character would take no value from the argument list.\n"
		"\n"
		"- `x` .. Fills the binary with zero.\n"
		"         The packing size `n` means the size of the room in bytes\n"
		"         to be filled with zero.\n"
		"\n"
		"The default byte-order for numbers of two-byte, four-byte and eight-byte\n"
		"depends on the system the interpreter is currently running.\n"
		"You can change it by the following specifiers:\n"
		"\n"
		"- `@` .. System-dependent order.\n"
		"- `=` .. System-dependent order.\n"
		"- `<` .. Little endian\n"
		"- `>` .. Big endian\n"
		"- `!` .. Big endian\n"
		"\n"
		"You can specify an asterisk character \"`*`\" for the number of packing size\n"
		"that picks that number from the argument list.\n"
		"\n"
		"You can specify encoding name embraced with \"`{`\" and \"`}`\" in the format\n"
		"to change coding character set from UTF-8\n"
		"while packing a string with format character \"`s`\".\n");
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

// Pointer#Put(elemType:Symbol, args*):reduce:[be,stay]
Gurax_DeclareMethod(Pointer, Put)
{
	Declare(VTYPE_Pointer, Flag::Reduce);
	DeclareArg("elemType", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(be));
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Pointer, Put)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const Pointer::ElemType elemType = Pointer::SymbolToElemType(args.PickSymbol());
	if (elemType == Pointer::ElemType::None) {
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

// Pointer#Unpack(format:String):[raise,stay]
Gurax_DeclareMethod(Pointer, Unpack)
{
	Declare(VTYPE_Pointer, Flag::None);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("args", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(raise));
	DeclareAttrOpt(Gurax_Symbol(stay));
	AddHelp(
		Gurax_Symbol(en),
		"Extracts values from data sequence pointed by the `pointer` instance according to specifiers in the `format`\n"
		"and returns a list containing the values.\n"
		"\n"
		"A specifier has a format of \"`nX`\" where `X` is a format character\n"
		"that represents a packing format and `n` is a number of packing size.\n"
		"The number can be omitted, and it would be treated as `1` in that case.\n"
		"\n"
		"Following format characters would extract an integer or float value of specified size\n"
		"from the binary and returns a `number` value.\n"
		"\n"
		"- `b` .. One-byte signed number.\n"
		"- `B` .. One-byte unsigned number.\n"
		"- `h` .. Two-byte signed number.\n"
		"- `H` .. Two-byte unsigned number.\n"
		"- `i` .. Four-byte signed number.\n"
		"- `I` .. Four-byte unsigned number.\n"
		"- `l` .. Four-byte signed number.\n"
		"- `L` .. Four-byte unsigned number.\n"
		"- `q` .. Eight-byte signed number.\n"
		"- `Q` .. Eight-byte unsigned number.\n"
		"- `f` .. Float-typed number occupying four bytes.\n"
		"- `d` .. Double-typed number occupying eight bytes.\n"
		"\n"
		"As for them, the packing size `n` means the number of values to be extracted.\n"
		"\n"
		"Following format characters would extract a string sequence from the binary\n"
		"and returns a `string` value.\n"
		"\n"
		"- `s` .. Extracts a sequence of UTF-8 codes and returns `string` instance containing it.\n"
		"         The unpacking size `n` means the size of the room in bytes\n"
		"         where the character codes are to be unpacked.\n"
		"- `c` .. Extracts a one-byte unsigned number and returns a `string` instance containing it.\n"
		"         The unpacking size `n` means the number of values to be extracted.\n"
		"\n"
		"Following format character would not return any value.\n"
		"\n"
		"- `x` .. Advances the address by one byte.\n"
		"         If the unpacking size `n` is specifies,\n"
		"         it would advance the address by `n` bytes.\n"
		"\n"
		"The default byte-order for numbers of two-byte, four-byte and eight-byte\n"
		"depends on the system the interpreter is currently running.\n"
		"You can change it by the following specifiers:\n"
		"\n"
		"- `@` .. System-dependent order.\n"
		"- `=` .. System-dependent order.\n"
		"- `<` .. Little endian\n"
		"- `>` .. Big endian\n"
		"- `!` .. Big endian\n"
		"\n"
		"You can specify an asterisk character \"`*`\" for the number of unpacking size\n"
		"that picks that number from the argument list.\n"
		"\n"
		"You can specify encoding name embraced with \"`{`\" and \"`}`\" in the format\n"
		"to change coding character set from UTF-8\n"
		"while extracting a string with format character \"`s`\".\n"
		"\n"
		"An error occurs if the binary size is smaller than the format reqeusts.\n"
		"If the attribute `:nil` is specified, `nil` value would be returned for such a case.\n");
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
// Pointer#bytesAvail
Gurax_DeclareProperty_R(Pointer, bytesAvail)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"the data size available from the current pointer position.");
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
	AddHelp(
		Gurax_Symbol(en),
		"the entire size of the memory that the pointer covers.");
}

Gurax_ImplementPropertyGetter(Pointer, bytesEntire)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Number(valueThis.GetPointer().GetBytesEntire());
}

// Pointer#offset
Gurax_DeclareProperty_RW(Pointer, offset)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"the offset of the pointer.");
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

// Pointer#int8:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int8)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 8-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int8)
{
	return PointerGetTmpl<Int8>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int8)
{
	PointerPutTmpl<Int8>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int16:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int16)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 16-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int16)
{
	return PointerGetTmpl<Int16>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int16)
{
	PointerPutTmpl<Int16>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int32:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int32)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 32-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int32)
{
	return PointerGetTmpl<Int32>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int32)
{
	PointerPutTmpl<Int32>(GetValueThis(valueTarget), attr, value);
}

// Pointer#int64:[be,stay]
Gurax_DeclareProperty_RW(Pointer, int64)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of signed 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, int64)
{
	return PointerGetTmpl<Int64>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, int64)
{
	PointerPutTmpl<Int64>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint8:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint8)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 8-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint8)
{
	return PointerGetTmpl<UInt8>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint8)
{
	PointerPutTmpl<UInt8>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint16:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint16)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 16-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint16)
{
	return PointerGetTmpl<UInt16>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint16)
{
	PointerPutTmpl<UInt16>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint32:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint32)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 32-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint32)
{
	return PointerGetTmpl<UInt32>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint32)
{
	PointerPutTmpl<UInt32>(GetValueThis(valueTarget), attr, value);
}

// Pointer#uint64:[be,stay]
Gurax_DeclareProperty_RW(Pointer, uint64)
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, uint64)
{
	return PointerGetTmpl<UInt64>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, uint64)
{
	PointerPutTmpl<UInt64>(GetValueThis(valueTarget), attr, value);
}

// Pointer#float:[be,stay]
Gurax_DeclarePropertyAlias_RW(Pointer, float_, "float")
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, float_)
{
	return PointerGetTmpl<Float>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, float_)
{
	PointerPutTmpl<Float>(GetValueThis(valueTarget), attr, value);
}

// Pointer#double:[be,stay]
Gurax_DeclarePropertyAlias_RW(Pointer, double_, "double")
{
	Declare(VTYPE_Number, Flag::None);
	//DeclareAttrOpt(Gurax_Symbol(be));
	AddHelp(
		Gurax_Symbol(en),
		"read or write a number stored in a format of unsigned 64-bit integer.");
}

Gurax_ImplementPropertyGetter(Pointer, double_)
{
	return PointerGetTmpl<Double>(GetValueThis(valueTarget), attr);
}

Gurax_ImplementPropertySetter(Pointer, double_)
{
	PointerPutTmpl<Double>(GetValueThis(valueTarget), attr, value);
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
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Pointer));
	// Assignment of method
	Assign(Gurax_CreateMethod(Pointer, Dump));
	Assign(Gurax_CreateMethod(Pointer, Pack));
	Assign(Gurax_CreateMethod(Pointer, Put));
	Assign(Gurax_CreateMethod(Pointer, Unpack));
	// Assignment of property
	Assign(Gurax_CreateProperty(Pointer, bytesAvail));
	Assign(Gurax_CreateProperty(Pointer, bytesEntire));
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
		return new Value_Pointer(
			new Pointer_Binary(dynamic_cast<const Value_Binary&>(value).GetBinaryReferable().Reference()));
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Pointer
//------------------------------------------------------------------------------
VType& Value_Pointer::vtype = VTYPE_Pointer;

String Value_Pointer::ToStringDigest(const StringStyle& ss) const
{
	String str;
	str += "<";
	str += GetPointer().ToString(ss);
	str += ">";
	return str;
}

String Value_Pointer::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
