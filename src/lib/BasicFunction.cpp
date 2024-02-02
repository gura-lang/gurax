//==============================================================================
// BasicFunction.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// BasicFunction
//------------------------------------------------------------------------------
// Chr(code as Number):map
Gurax_DeclareFunction(Chr)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Coverts a UTF-32 character code `code` into a string and returns it.
)""");
	AddHelp(Gurax_Symbol(ja), u8R"""(
UTF-32 キャラクタコード `code` を文字列に変換し、戻り値として返します。
)""");
}

Gurax_ImplementFunction(Chr)
{
	// Arguments
	ArgPicker args(argument);
	UInt32 codeUTF32 = args.PickNumberNonNeg<UInt32>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	String str;
	str.AppendUTF32(codeUTF32);
	return new Value_String(str);
}

// Dim(n+ as Number) {block?}
Gurax_DeclareFunction(Dim)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("n", VTYPE_Number, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Returns a list that contains `n` pieces of elements. The list is filled with `nil` values.
Below is an example of creating a list with three elements:

    x = Dim(3) // x is [nil, nil, nil]

If you pass multiple numbers for the argument `n`, it would create a nested list.
Below is an example of creating a two-dimentional list:

    x = Dim(3, 2) // x is [[nil, nil], [nil, nil], [nil, nil]]

The optional `block` specifies a procedure that is supposed to return element values.
It takes block parameters `|i0 as number, i1 as number, ..|` where `i0` and `i1` represent indices while looping.

Below is an example of creating a one-dimentional list containing a string:

    x = Dim(3) {'Hi'} // x is ['Hi', 'Hi', 'Hi']

Below is an example of creating a two-dimentional list containing strings.

    x = Dim(3, 2) {|i, j| Format('%d-%d', i, j)}
                        // x is [['0-0', '0-1'], ['1-0', '1-1'], ['2-0', '2-1']]
)""");
}

ValueTypedOwner* DimSub(Processor& processor, NumList<Int>& cntList, NumList<Int>::iterator pCnt,
	NumList<Int>& idxList, NumList<Int>::iterator pIdx, const Expr_Block* pExprOfBlock, Argument* pArgSub)
{
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	if (pCnt + 1 != cntList.end()) {
		for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
			RefPtr<ValueTypedOwner> pValueTypedOwnerSub(
				DimSub(processor, cntList, pCnt + 1, idxList, pIdx + 1, pExprOfBlock, pArgSub));
			if (!pValueTypedOwnerSub) return nullptr;
			pValueOwner->push_back(new Value_List(pValueTypedOwnerSub.release()));
		}
		return new ValueTypedOwner(VTYPE_List, pValueOwner.release());
	} else if (pExprOfBlock) {
		Frame& frame = processor.GetFrameCur();
		for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
			pArgSub->ResetAllValues();
			ArgFeeder args(*pArgSub, frame);
			for (Int idx : idxList) {
				if (!args.FeedValue(processor, new Value_Number(idx))) return nullptr;
			}
			RefPtr<Value> pValue(pExprOfBlock->Eval(processor, *pArgSub));
			if (Error::IsIssued()) return nullptr;
			pValueOwner->push_back(pValue.release());
		}
		return new ValueTypedOwner(pValueOwner.release());
	} else {
		for (*pIdx = 0; *pIdx < *pCnt; (*pIdx)++) {
			pValueOwner->push_back(Value::nil());
		}
		return new ValueTypedOwner(VTYPE_Nil, pValueOwner.release());
	}
}

Gurax_ImplementFunction(Dim)
{
	// Arguments
	ArgPicker args(argument);
	NumList<Int> cntList = Value_Number::GetNumListPos<int>(args.PickList());
	if (Error::IsIssued()) return Value::nil();
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	// Function body
	NumList<Int> idxList(cntList.size(), 0);
	auto pCnt = cntList.begin();
	auto pIdx = idxList.begin();
	RefPtr<Argument> pArgSub(pExprOfBlock? Argument::CreateForBlockCall(processor, *pExprOfBlock) : nullptr);
	RefPtr<ValueTypedOwner> pValueTypedOwner(
		DimSub(processor, cntList, pCnt, idxList, pIdx, pExprOfBlock, pArgSub.get()));
	if (!pValueTypedOwner) return Value::nil();
	return new Value_List(pValueTypedOwner.release());
}

// dir(value?)
Gurax_DeclareFunction(dir)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementFunction(dir)
{
	// Arguments
	ArgPicker args(argument);
	SymbolList symbolList;
	if (args.IsValid()) {
		args.PickValue().GatherMemberSymbol(symbolList);
	} else {
		Basement::Inst.GetFrame().GatherSymbol(symbolList);
	}
	// Function body
	symbolList.Sort();
	RefPtr<ValueOwner> pValues(new ValueOwner());
	pValues->reserve(symbolList.size());
	for (const Symbol* pSymbol : symbolList) pValues->push_back(new Value_Symbol(pSymbol));
	return new Value_List(VTYPE_Symbol, pValues.release());
}

// Format(format as String, values*):map
Gurax_DeclareFunction(Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts `values` into string depending on formatter specifications
specified in `format` and returns the result in string.

The format specifier has a format of `%[flags][width][.precision]specifier`.
The `specifier` takes one of the following characters:

- `d`, `i` .. decimal integer number with a sign mark
- `u` .. decimal integer number wihout a sign mark
- `b` .. binary integer number without a sign mark
- `o` .. octal integer number without a sign mark
- `x` .. hexadecimal integer number in lower character without a sign mark
- `X` .. hexadecimal integer number in upper character without a sign mark
- `e` .. floating number in exponential form
- `E` .. floating number in exponential form (in upper character)
- `f` .. floating number in decimal form
- `F` .. floating number in decimal form (in upper character)
- `g` .. better form between `e` and `f`
- `G` .. better form between `E` and `F`
- `s` .. string
- `c` .. character

The `flags` takes one of the following characters.

- `+` .. Appends a character "`+`" before a positive number.
- `-` .. Adjust a string to left.
- `[SPC]` .. Appends a space character before a positive number.
- `#` .. Appends a prefix before a numbers "`0b`" for a binary,
        "`0`" for an octal and "`0x`" for a hexadecimal number.
- `0` .. Fills lacking columns with "`0`" instead of space characters.`

The `width` is a decimal number that specifies a minimum character.
If the width of the corresponding field is less than this number,
the lacking part will be filled with space characters or "`0`".
If the width is equal to or more than this number, there's nothing to be processed.
If an asterisk character "`*`" is specified for `width`,
the minimum character width will be retrieved from the argument list.

The `width` it a character width that appears on a console,
and it takes into account each character width based on the specification
of East Asian Width. This means that a kanji-character occupies two characters in width.

The `precision` is a decimal number and has different effects depending on `specifier`.

For specifiers that formats integer numbers, it specifies a minimum character width
and fills `0` for the lacking column.
Format specifiers "`%03d`" and "`%.3d`" have the same effect.
When it works in combination with `width`,
`precision` fills `0` in the lacking space before `width` does padding.
An example is shown below:

    Format('%5.3d', 23) .. returns "  023"

For specifiers `e`, `f` and `g`, it specifies a digit number after a decimal point.
Examples are shown below:

    Format('%.3f', 1 / 3) .. returns "0.333"
    Format('%.5f', 1 / 3) .. returns "0.33333"

It has no effect with other specifiers.
)""");
}

Gurax_ImplementFunction(Format)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	String str;
	str.FormatValueList(format, values);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(str);
}

// Int(value):map
Gurax_DeclareFunction(Int)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts a value into an integer number like below:

- With a number value, it would be converted into an integer number.
- With a string value, it would be parsed as an integer number.
  An error occurs if it has an invalid format.
- With a value of other types, an error occurs.
)""");
}

Gurax_ImplementFunction(Int)
{
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	if (value.IsType(VTYPE_Number)) {
		return new Value_Number(Value_Number::GetNumber<Int64>(value));
	} else if (value.IsType(VTYPE_String)) {
		bool successFlag;
		Double num = Value_String::GetStringSTL(value).ToDouble(&successFlag);
		if (!successFlag) {
			Error::Issue(ErrorType::ValueError, "failed to convert to a number");
			return Value::nil();
		}
		return new Value_Number(static_cast<Int64>(num));
	}
	Error::Issue(ErrorType::TypeError, "Number or String must be specified");
	return Value::nil();
}

// Max(values+):map:[index]
Gurax_DeclareFunction(Max)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementFunction(Max)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	if (argument.IsSet(Gurax_Symbol(index))) {
		size_t idx = 0;
		valueList.Max(&idx);
		return new Value_Number(idx);
	}
	return valueList.Max().Reference();
}

// Min(values+):map:[index]
Gurax_DeclareFunction(Min)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(index));
	AddHelp(Gurax_Symbol(en), u8R"""(
)""");
}

Gurax_ImplementFunction(Min)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	if (argument.IsSet(Gurax_Symbol(index))) {
		size_t idx = 0;
		valueList.Min(&idx);
		return new Value_Number(idx);
	}
	return valueList.Min().Reference();
}

// Ord(str as String):map
Gurax_DeclareFunction(Ord)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts the first character of a string into a number of UTF-32 code.
If the string contains more than one characters, it simply neglects trailing ones.
)""");
}

Gurax_ImplementFunction(Ord)
{
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	UInt32 codeUTF32 = String::NextUTF32(&str);
	return new Value_Number(codeUTF32);
}

// Print(values*):void:map
Gurax_DeclareFunction(Print)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` to standard output.
)""");
}

Gurax_ImplementFunction(Print)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.Print(valueList, StringStyle::Empty);
	return Value::nil();
}

// Printf(format as String, values*):void:map
Gurax_DeclareFunction(Printf)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` to standard output according to formatter specifiers specified in `format`.

For detail information about formatter specications,
refer to the help or document of `Format()` function.
)""");
}

Gurax_ImplementFunction(Printf)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.PrintValueList(format, values);
	return Value::nil();
}

// Println(values*):void:map
Gurax_DeclareFunction(Println)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"""(
Prints out `values` and an end-of-line character to the standard output.
)""");
}

Gurax_ImplementFunction(Println)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.Println(values, StringStyle::Empty);
	return Value::nil();
}

// Range(num as Number, numEnd? as Number, step? as Number):map {block?}
Gurax_DeclareFunction(Range)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("step", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that generates a sequence of number that increases or decreases by a specified step.

- `Range(num as Number)` .. finite sequence of n where `0 <= n < num` or `num < n <= 0`
- `Range(num as Number, numEnd as Number)` .. finite sequence of n where `num <= n < numEnd` or `numEnd < n <= num`
- `Range(num as Number, numEnd as Number, step as Number)` .. finite sequence of n
   where `num <= n < numEnd` or `numEnd < n <= num` with an increment of `step`
- `Range(num as Number, nil, step as Number)` .. infinite sequence that starts at `num` with an increment of `step`
)""");
}

Gurax_ImplementFunction(Range)
{
	// Arguments
	bool validFlag_numEnd = false, validFlag_step = false;
	ArgPicker args(argument);
	Int num = args.PickNumber<Int>();
	Int numEnd = (validFlag_numEnd = args.IsValid())? args.PickNumber<Int>() : 0;
	Int step = (validFlag_step = args.IsValid())? args.PickNumber<Int>() : 1;
	// Function body
	RefPtr<Iterator> pIterator;
	if (!validFlag_numEnd && !validFlag_step) {
		pIterator.reset(new Iterator_Range(0, num, (num >= 0)? 1 : -1));
	} else if (validFlag_numEnd && !validFlag_step) {
		pIterator.reset(new Iterator_Range(num, numEnd, (numEnd >= num)? 1 : -1));
	} else if (!validFlag_numEnd && validFlag_step) {
		if (step == 0) {
			Error::Issue(ErrorType::RangeError, "step must not be zero");
			return Value::nil();
		}
		pIterator.reset(new Iterator_Counter(num, step));
	} else { // validFlag_numEnd && validFlag_step
		if (step == 0) {
			Error::Issue(ErrorType::RangeError, "step must not be zero");
			return Value::nil();
		}
		numEnd = num + (numEnd - num) / step * step;
		if ((numEnd - num) * step < 0) numEnd = num;
		pIterator.reset(new Iterator_Range(num, numEnd, step));
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// ReadLines(stream:Stream, nLines? as Number):[chop] {block?}
Gurax_DeclareFunction(ReadLines)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::StreamR);
	DeclareArg("nLines", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that reads each line from the `Stream` and returns it as a `String` instance.

The argument `nLines` limits the number of lines to be read. If omitted, all the lines are read.

If the attribute `:chop` is specified, the end-of-line character of each line is eliminated.
)""");
}

Gurax_ImplementFunction(ReadLines)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.PickStream();
	size_t nLines = args.IsValid()? args.PickNumberNonNeg<size_t>() : -1;
	bool includeEOLFlag = !argument.IsSet(Gurax_Symbol(chop));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	return argument.ReturnIterator(processor, stream.ReadLines(nLines, includeEOLFlag));
}

#if 0
// hex(num as number, digits? as number):map:[upper]
Gurax_DeclareFunction(hex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "num", VTYPE_number);
	DeclareArg(env, "digits", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(upper));
	AddHelp(Gurax_Symbol(en), u8R"""(
Converts a number into a hexadecimal string.
Argument `digits` specifies a minimum columns of the converted result
and fills `0` in the lacking space.

In default, it uses lower-case characters in its conversion,
while it uses upper-case ones when `:upper` attribute is specified.
)""");
}

Gurax_ImplementFunction(hex)
{
	Signal &sig = env.GetSignal();
	int digits = arg.Is_number(1)? arg.GetInt(1) : 0;
	bool upperFlag = arg.IsSet(Gurax_Symbol(upper));
	String str;
	if (digits <= 0) {
		str = Formatter::FormatValueList(sig, upperFlag? "%X" : "%x",
						ValueList(arg.GetValue(0)));
	} else {
		str = Formatter::FormatValueList(sig, upperFlag? "%0*X" : "%0*x",
						ValueList(Value(digits), arg.GetValue(0)));
	}
	if (sig.IsSignalled()) return Value::Nil;
	return Value(str);
}

#endif

//------------------------------------------------------------------------------
// BasicFunction
//------------------------------------------------------------------------------
void BasicFunction::Prepare(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Chr));
	frame.Assign(Gurax_CreateFunction(Dim));
	frame.Assign(Gurax_CreateFunction(dir));
	frame.Assign(Gurax_CreateFunction(Format));
	frame.Assign(Gurax_CreateFunction(Int));
	frame.Assign(Gurax_CreateFunction(Max));
	frame.Assign(Gurax_CreateFunction(Min));
	frame.Assign(Gurax_CreateFunction(Ord));
	frame.Assign(Gurax_CreateFunction(Print));
	frame.Assign(Gurax_CreateFunction(Printf));
	frame.Assign(Gurax_CreateFunction(Println));
	frame.Assign(Gurax_CreateFunction(Range));
	frame.Assign(Gurax_CreateFunction(ReadLines));
}

}
