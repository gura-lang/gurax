//==============================================================================
// VType_Stream.cpp
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
// Stream(pathName:String, mode?:String, codec?:Codec) {block?}
Gurax_DeclareConstructor(Stream)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `Stream` instance.");
}

Gurax_ImplementConstructor(Stream)
{
	// Arguments
	ArgPicker args(argument);
	const char* pathName = args.PickString();
	Stream::OpenFlags openFlags = args.IsValid()?
		Stream::ModeToOpenFlags(args.PickString()) : Stream::OpenFlag::None;
	const Codec* pCodec = args.IsValid()? &Value_Codec::GetCodec(args.PickValue()) : nullptr;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Stream> pStream(Stream::Open(pathName, openFlags));
	if (!pStream) return Value::nil();
	if (pCodec) pStream->SetCodec(pCodec->Reference());
	return argument.ReturnValue(processor, new Value_Stream(pStream.release()));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Stream#Addcr(flag:Bool):reduce
Gurax_DeclareMethod(Stream, Addcr)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Indicates the stream to add carriage return code when putting strings.");
}

Gurax_ImplementMethod(Stream, Addcr)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	bool flag = args.PickBool();
	// Function body
	stream.GetCodec().SetAddcrFlag(flag);
	return valueThis.Reference();
}

// Stream#Delcr(flag:Bool):reduce
Gurax_DeclareMethod(Stream, Delcr)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Indicates the stream to add carriage return code when putting strings.");
}

Gurax_ImplementMethod(Stream, Delcr)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	bool flag = args.PickBool();
	// Function body
	stream.GetCodec().SetDelcrFlag(flag);
	return valueThis.Reference();
}

// Stream#Flush():reduce
Gurax_DeclareMethod(Stream, Flush)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	AddHelp(
		Gurax_Symbol(en),
		"Flush the stream.");
}

Gurax_ImplementMethod(Stream, Flush)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Function body
	stream.Flush();
	return valueThis.Reference();
}

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
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Reads data from the `Stream` and returns it as a `Binary` instance.");
}

Gurax_ImplementMethod(Stream, Read)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	bool validFlag_bytes = false;
	ArgPicker args(argument);
	size_t bytes = (validFlag_bytes = args.IsValid())? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Value> _pValue;
	if (validFlag_bytes) {
		_pValue.reset(new Value_Binary(stream.Read(bytes)));
		if (Error::IsIssued()) return Value::nil();
	} else if (stream.IsInfinite()) {
		Error::Issue(ErrorType::StreamError,
					 "can't read data from inifinite stream without specifying the length");
		return Value::nil();
	} else {
		_pValue.reset(new Value_Binary(stream.ReadAll()));
		if (Error::IsIssued()) return Value::nil();
	}
	return _pValue.release();
}

// Stream#ReadLine():[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLine)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Reads one line from the `Stream` and returns it as a `String` instance.");
}

Gurax_ImplementMethod(Stream, ReadLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	bool includeEOLFlag = !argument.IsSet(Gurax_Symbol(chop));
	// Function body
	String str;
	if (!stream.ReadLine(str, includeEOLFlag)) return Value::nil();
	return argument.ReturnValue(processor, new Value_String(str));
}

// Stream#ReadLines():[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLines)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that reads each line from the `Stream` and returns it as a `String` instance.");
}

Gurax_ImplementMethod(Stream, ReadLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	bool includeEOLFlag = !argument.IsSet(Gurax_Symbol(chop));
	// Function body
	return argument.ReturnIterator(processor, stream.ReadLines(includeEOLFlag));
}

// Stream#Seek(offset:Number, whence?:Symbol):reduce
Gurax_DeclareMethod(Stream, Seek)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("whence", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Seeks the current file position to the offset specified by the argument `offset`.\n"
		"\n"
		"The argument `whence` specifies the meaning of `offset` value as follows:\n"
		"\n"
		"- ``set` ... `offset` is an absolute offset from the begining of the stream.\n"
		"- ``cur` ... `offset` is a relative offset from the current position.\n"
		"\n"
		"This method returns the target stream instance itself.\n");
}

Gurax_ImplementMethod(Stream, Seek)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	long offset = args.PickNumber<long>();
	const Symbol *pSymbol = args.IsValid()? args.PickSymbol() : Gurax_Symbol(set);
	Stream::SeekMode whence = pSymbol->IsIdentical(Gurax_Symbol(cur))?
		Stream::SeekMode::Cur : Stream::SeekMode::Set;
	// Function body
	if (!stream.Seek(offset, whence)) return Value::nil();
	return valueThis.Reference();
}

// Stream#Write(ptr:Pointer, bytes?:Number):reduce
Gurax_DeclareMethod(Stream, Write)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("ptr", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Writes data pointed by the specified `Pointer` instance to the `Stream`.");
}

Gurax_ImplementMethod(Stream, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const Pointer& ptr = args.Pick<Value_Pointer>().GetPointer();
	bool validFlag_bytes = false;
	size_t bytes = (validFlag_bytes = args.IsValid())? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	size_t bytesAvail = ptr.GetSizeAvailable();
	if (!validFlag_bytes) {
		stream.Write(ptr.GetPointerC(), bytesAvail);
	} else if (bytes <= bytesAvail) {
		stream.Write(ptr.GetPointerC(), bytes);
	} else {
		Error::Issue(ErrorType::RangeError, "exceeds the memory size pointed by the pointer");
		return Value::nil();
	}
	return valueThis.Reference();
}

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
VType_Stream VTYPE_Stream("Stream");

void VType_Stream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Stream));
	// Assignment of function
	frameOuter.Assign(Gurax_CreateConstructorAlias(Stream, "Open"));
	// Assignment of method
	Assign(Gurax_CreateMethod(Stream, Addcr));
	Assign(Gurax_CreateMethod(Stream, Delcr));
	Assign(Gurax_CreateMethod(Stream, Flush));
	Assign(Gurax_CreateMethod(Stream, Print));
	Assign(Gurax_CreateMethod(Stream, Printf));
	Assign(Gurax_CreateMethod(Stream, Println));
	Assign(Gurax_CreateMethod(Stream, Read));
	Assign(Gurax_CreateMethod(Stream, ReadLine));
	Assign(Gurax_CreateMethod(Stream, ReadLines));
	Assign(Gurax_CreateMethod(Stream, Seek));
	Assign(Gurax_CreateMethod(Stream, Write));
}

Value* VType_Stream::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* pathName = Value_String::GetString(value);
		Stream::OpenFlags openFlags = (flags & DeclArg::Flag::StreamW)?
			Stream::OpenFlag::Write : Stream::OpenFlag::None;
		RefPtr<Stream> pStream(Stream::Open(pathName, openFlags));
		if (!pStream) return nullptr;
		return new Value_Stream(pStream.release());
	} else if (value.IsType(VTYPE_Binary)) {
		const BinaryReferable& binary = Value_Binary::GetBinaryReferable(value);
		size_t offset = 0;
		Stream::Flags flagsStream = Stream::Flag::Readable;
		if (flags & DeclArg::Flag::StreamW) {
			offset = binary.GetBinary().size();
			flagsStream = Stream::Flag::Writable;
		}
		return new Value_Stream(new Stream_Binary(flagsStream, binary.Reference(), offset));
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
	str += GetStream().ToString(ss);
	str += ">";
	return str;
}

String Value_Stream::ToStringDetail(const StringStyle& ss) const
{
	return ToStringDigest(ss);
}

}
