//==============================================================================
// VType_Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

${help.ComposePropertyHelp(Stream, `en)}

# Operator

The operator `<<` writes a value to the `Stream`.
This works in the same way as `Stream#Print()` method if a `String` value is specified, and `Stream#Write()` method otherwise.

- `Stream << String` ... Writes the content of the `String` to the `Stream`. 
- `Stream << Binary` ... Writes the content of the `Binary` to the `Stream`.
- `Stream << Pointer` ... Writes the content pointed by the `Pointer` to the `Stream`.
- `Stream << Stream` ... Writes the data read from the left-sided `Stream` into the right-sided `Stream`. 

# Cast Operation

The following cast operations are prepared:

- `String as Stream` ... Creates a `Stream` from a path name specified by the `String`.
- `Binary as Stream` ... Creates a `Stream` that scans data on the `Binary`.

${help.ComposeConstructorHelp(Stream, `en)}

${help.ComposeMethodHelp(Stream, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// Stream(pathName as String, mode? as String, codec? as Codec) {block?}
Gurax_DeclareConstructor(Stream)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("pathName", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("mode", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `Stream` instance.
)""");
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
// Implementation of class method
//------------------------------------------------------------------------------
// Stream.Pipe(streamSrc:r as Stream, streamDst:w as Stream):void:[cooked]
Gurax_DeclareClassMethod(Stream, Pipe)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("streamSrc", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("streamDst", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(cooked));
	AddHelp(Gurax_Symbol(en), u8R"""(
Writes data read from `streamSrc` into `streamDst`.
)""");
}

Gurax_ImplementClassMethod(Stream, Pipe)
{
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	Stream& streamDst = args.PickStream();
	bool cookedFlag = argument.IsSet(Gurax_Symbol(cooked));
	// Function body
	if (streamSrc.IsInfinite()) {
		Error::Issue(ErrorType::StreamError,
					 "can't read data from inifinite stream without specifying the length");
		return Value::nil();
	}
	if (cookedFlag) {
		streamSrc.PipeToStreamCooked(streamDst);
	} else {
		streamSrc.PipeToStream(streamDst);
	}
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// Stream#Addcr(flag as Bool):reduce
Gurax_DeclareMethod(Stream, Addcr)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Indicates the stream to add carriage return code when putting strings.
)""");
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

// Stream#Delcr(flag as Bool):reduce
Gurax_DeclareMethod(Stream, Delcr)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("flag", VTYPE_Bool, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Indicates the stream to add carriage return code when putting strings.
)""");
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
	AddHelp(Gurax_Symbol(en), u8R"""(
Flush the stream.
)""");
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

// Stream#PipeFrom(streamSrc as Stream):reduce:[cooked] as Stream
Gurax_DeclareMethod(Stream, PipeFrom)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("streamSrc", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareAttrOpt(Gurax_Symbol(cooked));
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads data from the `streamSrc` and writes it into the target `Stream` instance.
)""");
}

Gurax_ImplementMethod(Stream, PipeFrom)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	Stream& streamSrc = args.PickStream();
	bool cookedFlag = argument.IsSet(Gurax_Symbol(cooked));
	// Function body
	if (stream.IsInfinite()) {
		Error::Issue(ErrorType::StreamError,
					 "can't read data from inifinite stream without specifying the length");
		return Value::nil();
	}
	if (cookedFlag) {
		if (!stream.PipeFromStreamCooked(streamSrc)) return Value::nil();
	} else {
		if (!stream.PipeFromStream(streamSrc)) return Value::nil();
	}
	return valueThis.Reference();
}

// Stream#PipeTo(streamDst:w as Stream):reduce:[cooked] as Stream
Gurax_DeclareMethod(Stream, PipeTo)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("streamDst", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(cooked));
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads data from the target `Stream` instance and writes it into `streamDst`.
)""");
}

Gurax_ImplementMethod(Stream, PipeTo)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	Stream& streamDst = args.PickStream();
	bool cookedFlag = argument.IsSet(Gurax_Symbol(cooked));
	// Function body
	if (stream.IsInfinite()) {
		Error::Issue(ErrorType::StreamError,
					 "can't read data from inifinite stream without specifying the length");
		return Value::nil();
	}
	if (cookedFlag) {
		if (!stream.PipeToStreamCooked(streamDst)) return Value::nil();
	} else {
		if (!stream.PipeToStream(streamDst)) return Value::nil();
	}
	return valueThis.Reference();
}

// Stream#Print(values*):void:map
Gurax_DeclareMethod(Stream, Print)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` to the specified stream.
)""");
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
	stream.Print(valueList, StringStyle::Empty);
	return Value::nil();
}

// Stream#Printf(format as String, values*):void:map
Gurax_DeclareMethod(Stream, Printf)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` to the specified stream according to formatter specifiers specified in `format`.

For detail information about formatter specications,
refer to the help or document of `Format()` function.
)""");
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
	stream.PrintValueList(format, values);
	return Value::nil();
}

// Stream#Println(values*):void:map
Gurax_DeclareMethod(Stream, Println)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` and an end-of-line character to the specified stream.
)""");
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
	stream.Println(values, StringStyle::Empty);
	return Value::nil();
}

// Stream#Read(bytes? as Number)
Gurax_DeclareMethod(Stream, Read)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads data from the `Stream` and returns it as a `Binary` instance.
)""");
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
		Binary buff(stream.Read(bytes));
		if (buff.empty() || Error::IsIssued()) return Value::nil();
		_pValue.reset(new Value_Binary(buff));
	} else if (stream.IsInfinite()) {
		Error::Issue(ErrorType::StreamError,
					 "can't read data from inifinite stream without specifying the length");
		return Value::nil();
	} else {
		RefPtr<BinaryReferable> pBuff(new BinaryReferable());
		if (!stream.ReadToBinary(pBuff->GetBinary())) return Value::nil();
		_pValue.reset(new Value_Binary(pBuff.release()));
	}
	return _pValue.release();
}

// Stream#ReadLine():[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLine)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads one line from the `Stream` and returns it as a `String` instance.
)""");
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
	return argument.ReturnValue(processor, new Value_String(std::move(str)));
}

// Stream#ReadLines(nLines? as Number):[chop] {block?}
Gurax_DeclareMethod(Stream, ReadLines)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("nLines", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that reads each line from the `Stream` and returns it as a `String` instance.
)""");
}

Gurax_ImplementMethod(Stream, ReadLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	size_t nLines = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	bool includeEOLFlag = !argument.IsSet(Gurax_Symbol(chop));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnIterator(processor, stream.ReadLines(nLines, includeEOLFlag));
}

// Stream#ReadText() {block?}
Gurax_DeclareMethod(Stream, ReadText)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads whole text from the `Stream` and returns it as a `String` instance.
)""");
}

Gurax_ImplementMethod(Stream, ReadText)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Function body
	String str = stream.ReadText();
	if (Error::IsIssued()) return Value::nil();
	return argument.ReturnValue(processor, new Value_String(std::move(str)));
}

// Stream#Seek(offset as Number, whence? as Symbol):reduce
Gurax_DeclareMethod(Stream, Seek)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("offset", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("whence", VTYPE_Symbol, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Seeks the current file position to the specified `offset`.

The argument `whence` specifies the meaning of `offset` value as follows:

- `` `set`` ... `offset` is an absolute offset from the begining of the stream.
- `` `cur`` ... `offset` is a relative offset from the current position.

It returns `this` stream instance.
)""");
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

// Stream#SkipLine()
Gurax_DeclareMethod(Stream, SkipLine)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads a line and discards it.

It returns `this` stream instance.
)""");
}

Gurax_ImplementMethod(Stream, SkipLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	valueThis.GetStream().SkipLines(1);
	return valueThis.Reference();
}

// Stream#SkipLines(nLines as Number)
Gurax_DeclareMethod(Stream, SkipLines)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("nLines", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Reads specified number of lines and discards them.

It returns `this` stream instance.
)""");
}

Gurax_ImplementMethod(Stream, SkipLines)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t nLines = args.PickNumberNonNeg<size_t>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	valueThis.GetStream().SkipLines(nLines);
	return valueThis.Reference();
}

// Stream#Write(ptr as Pointer, bytes? as Number):reduce
Gurax_DeclareMethod(Stream, Write)
{
	Declare(VTYPE_Stream, Flag::Reduce);
	DeclareArg("ptr", VTYPE_Pointer, ArgOccur::Once, ArgFlag::None);
	DeclareArg("bytes", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Writes data pointed by the specified `Pointer` instance to the `Stream`.
)""");
}

Gurax_ImplementMethod(Stream, Write)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Stream& stream = valueThis.GetStream();
	// Arguments
	ArgPicker args(argument);
	const Pointer& ptr = args.PickPointer();
	bool validFlag_bytes = false;
	size_t bytes = (validFlag_bytes = args.IsValid())? args.PickNumberNonNeg<size_t>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	size_t bytesAvail = ptr.GetBytesAvailable();
	if (!validFlag_bytes) {
		if (!stream.Write(ptr.GetPointerC<void>(), bytesAvail)) return Value::nil();
	} else if (bytes <= bytesAvail) {
		if (!stream.Write(ptr.GetPointerC<void>(), bytes)) return Value::nil();
	} else {
		Error::Issue(ErrorType::RangeError, "exceeds the memory size pointed by the pointer");
		return Value::nil();
	}
	return valueThis.Reference();
}

//-----------------------------------------------------------------------------
// Implementation of properties
//-----------------------------------------------------------------------------
// Stream#codec
Gurax_DeclareProperty_RW(Stream, codec)
{
	Declare(VTYPE_Codec, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Stream, codec)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Codec> pCodec(valueThis.GetStream().GetCodec().Reference());
	if (pCodec->IsDumb()) return Value::nil();
	return new Value_Codec(pCodec.release());
}

Gurax_ImplementPropertySetter(Stream, codec)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (value.IsValid()) {
		valueThis.GetStream().SetCodec(Value_Codec::GetCodec(value).Reference());
	} else {
		valueThis.GetStream().SetCodec(Codec::CreateDumb());
	}
}

// Stream#identifier
Gurax_DeclareProperty_R(Stream, identifier)
{
	Declare(VTYPE_String, Flag::Nil);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementPropertyGetter(Stream, identifier)
{
	auto& valueThis = GetValueThis(valueTarget);
	if (!valueThis.GetStream().HasIdentifier()) return Value::nil();
	return new Value_String(valueThis.GetStream().GetIdentifier());
}

// Stream#stat
Gurax_DeclareProperty_R(Stream, stat)
{
	Declare(VTYPE_Stat, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
An instance that provides status information of the Stream.
)""");
}

Gurax_ImplementPropertyGetter(Stream, stat)
{
	auto& valueThis = GetValueThis(valueTarget);
	RefPtr<Value_Stat> pValue(valueThis.GetStream().CreateStatValue());
	if (!pValue) return Value::nil();
	return pValue.release();
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// Stream << Binary
Gurax_ImplementOpBinary(Shl, Stream, Binary)
{
	Stream& stream = Value_Stream::GetStream(valueL);
	Binary& binary = Value_Binary::GetBinary(valueR);
	size_t bytes = binary.size();
	if (!stream.Write(binary.data(), bytes)) return Value::nil();
	return valueL.Reference();
}

// Stream << Pointer
Gurax_ImplementOpBinary(Shl, Stream, Pointer)
{
	Stream& stream = Value_Stream::GetStream(valueL);
	Pointer& ptr = Value_Pointer::GetPointer(valueR);
	size_t bytesAvail = ptr.GetBytesAvailable();
	if (!stream.Write(ptr.GetPointerC<void>(), bytesAvail)) return Value::nil();
	return valueL.Reference();
}

// Stream << Stream
Gurax_ImplementOpBinary(Shl, Stream, Stream)
{
	Stream& stream = Value_Stream::GetStream(valueL);
	Stream& streamSrc = Value_Stream::GetStream(valueR);
	if (!stream.PipeFromStream(streamSrc)) return Value::nil();
	return valueL.Reference();
}

// Stream << String
Gurax_ImplementOpBinary(Shl, Stream, String)
{
	Stream& stream = Value_Stream::GetStream(valueL);
	const char* str = Value_String::GetString(valueR);
	stream.Print(str);
	return valueL.Reference();
}

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
VType_Stream VTYPE_Stream("Stream");

void VType_Stream::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Stream));
	// Assignment of function
	frameOuter.Assign(Gurax_CreateConstructorAlias(Stream, "Open"));
	// Assignment of class method
	Assign(Gurax_CreateClassMethod(Stream, Pipe));
	// Assignment of method
	Assign(Gurax_CreateMethod(Stream, Addcr));
	Assign(Gurax_CreateMethod(Stream, Delcr));
	Assign(Gurax_CreateMethod(Stream, Flush));
	Assign(Gurax_CreateMethod(Stream, PipeFrom));
	Assign(Gurax_CreateMethod(Stream, PipeTo));
	Assign(Gurax_CreateMethod(Stream, Print));
	Assign(Gurax_CreateMethod(Stream, Printf));
	Assign(Gurax_CreateMethod(Stream, Println));
	Assign(Gurax_CreateMethod(Stream, Read));
	Assign(Gurax_CreateMethod(Stream, ReadLine));
	Assign(Gurax_CreateMethod(Stream, ReadLines));
	Assign(Gurax_CreateMethod(Stream, ReadText));
	Assign(Gurax_CreateMethod(Stream, Seek));
	Assign(Gurax_CreateMethod(Stream, SkipLine));
	Assign(Gurax_CreateMethod(Stream, SkipLines));
	Assign(Gurax_CreateMethod(Stream, Write));
	// Assignment of property
	Assign(Gurax_CreateProperty(Stream, codec));
	Assign(Gurax_CreateProperty(Stream, identifier));
	Assign(Gurax_CreateProperty(Stream, stat));
	// Assignment of operator
	Gurax_AssignOpBinary(Shl, Stream, Binary);
	Gurax_AssignOpBinary(Shl, Stream, Pointer);
	Gurax_AssignOpBinary(Shl, Stream, Stream);
	Gurax_AssignOpBinary(Shl, Stream, String);
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
			if (!binary.GetBinary().IsWritable()) {
				Error::Issue(ErrorType::StreamError, "the binary is not writable");
				return nullptr;
			}
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

String Value_Stream::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetStream().ToString(ss));
}

}
