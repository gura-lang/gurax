//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// Chr(code:number):map
Gurax_DeclareFunction(Chr)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("code", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts a UTF-32 code into a string.\n");
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

// dir(value)
Gurax_DeclareFunction(dir)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("value", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
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

// Format(format:String, values*):String:map
Gurax_DeclareFunction(Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts `values` into string depending on formatter specifications\n"
		"specified in `format` and returns the result in string.\n"
		"\n"
		"The format specifier has a format of `%[flags][width][.precision]specifier`.\n"
		"The `specifier` takes one of the following characters:\n"
		"\n"
		"- `d`, `i` .. decimal integer number with a sign mark\n"
		"- `u` .. decimal integer number wihout a sign mark\n"
		"- `b` .. binary integer number without a sign mark\n"
		"- `o` .. octal integer number without a sign mark\n"
		"- `x` .. hexadecimal integer number in lower character without a sign mark\n"
		"- `X` .. hexadecimal integer number in upper character without a sign mark\n"
		"- `e` .. floating number in exponential form\n"
		"- `E` .. floating number in exponential form (in upper character)\n"
		"- `f` .. floating number in decimal form\n"
		"- `F` .. floating number in decimal form (in upper character)\n"
		"- `g` .. better form between `e` and `f`\n"
		"- `G` .. better form between `E` and `F`\n"
		"- `s` .. string\n"
		"- `c` .. character\n"
		"\n"
		"The `flags` takes one of the following characters.\n"
		"\n"
		"- `+` .. Appends a character \"`+`\" before a positive number.\n"
		"- `-` .. Adjust a string to left.\n"
		"- `[SPC]` .. Appends a space character before a positive number.\n"
		"- `#` .. Appends a prefix before a numbers \"`0b`\" for a binary,\n"
		"         \"`0`\" for an octal and \"`0x`\" for a hexadecimal number.\n"
		"- `0` .. Fills lacking columns with \"`0`\" instead of space characters.`\n"
		"\n"
		"The `width` is a decimal number that specifies a minimum character.\n"
		"If the width of the corresponding field is less than this number,\n"
		"the lacking part will be filled with space characters or \"`0`\".\n"
		"If the width is equal to or more than this number, there's nothing to be processed.\n"
		"If an asterisk character \"`*`\" is specified for `width`,\n"
		"the minimum character width will be retrieved from the argument list.\n"
		"\n"
		"The `width` it a character width that appears on a console,\n"
		"and it takes into account each character width based on the specification\n"
		"of East Asian Width. This means that a kanji-character occupies two characters in width.\n"
		"\n"
		"The `precision` is a decimal number and has different effects depending on `specifier`.\n"
		"\n"
		"For specifiers that formats integer numbers, it specifies a minimum character width\n"
		"and fills `0` for the lacking column.\n"
		"Format specifiers \"`%03d`\" and \"`%.3d`\" have the same effect.\n"
		"When it works in combination with `width`,\n"
		"`precision` fills `0` in the lacking space before `width` does padding.\n"
		"An example is shown below:\n"
		"\n"
		"    Format('%5.3d', 23) .. returns \"  023\"\n"
		"\n"
		"For specifiers `e`, `f` and `g`, it specifies a digit number after a decimal point.\n"
		"Examples are shown below:\n"
		"\n"
		"    Format('%.3f', 1 / 3) .. returns \"0.333\"\n"
		"    Format('%.5f', 1 / 3) .. returns \"0.33333\"\n"
		"\n"
		"It has no effect with other specifiers.\n");
}

Gurax_ImplementFunction(Format)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	String str;
	str.PrintFmt(format, values);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(str);
}

// Ord(str:String):map
Gurax_DeclareFunction(Ord)
{
	Declare(VTYPE_Number, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts the first character of a string into a number of UTF-32 code.\n"
		"If the string contains more than one characters, it simply neglects trailing ones.\n");
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
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` to standard output.");
}

Gurax_ImplementFunction(Print)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& valueList = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.Print(valueList);
	return Value::nil();
}

// Printf(format:String, values*):void:map
Gurax_DeclareFunction(Printf)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("format", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` to standard output according to formatter specifiers specified in `format`.\n"
		"\n"
		"For detail information about formatter specications,\n"
		"refer to the help or document of `Format()` function.");
}

Gurax_ImplementFunction(Printf)
{
	// Arguments
	ArgPicker args(argument);
	const char* format = args.PickString();
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.PrintFmt(format, values);
	return Value::nil();
}

// Println(values*):void:map
Gurax_DeclareFunction(Println)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out `values` and an end-of-line character to the standard output.\n");
}

Gurax_ImplementFunction(Println)
{
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	Stream& stream = *Stream::COut;
	stream.Println(values);
	return Value::nil();
}

// Range(num:Number, numEnd?:Number, step?:Number):map {block?}
Gurax_DeclareFunction(Range)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("num", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("numEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("step", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that generates a sequence of number that increases or decreases by a specified step.\n"
		"\n"
		"- `Range(num:Number)`\n"
		"- `Range(num:Number, numEnd:Number)`\n"
		"- `Range(num:Number, numEnd:Number, step:Number)`\n");
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
		numEnd = num / step * step;
		if (numEnd * step < 0) numEnd = 0;
		pIterator.reset(new Iterator_Range(0, numEnd, step));
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

// ReadLines(stream:Stream):[chop] {block?}
Gurax_DeclareFunction(ReadLines)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that reads each line from the `Stream` and returns it as a `String` instance.");
}

Gurax_ImplementFunction(ReadLines)
{
	// Arguments
	ArgPicker args(argument);
	Stream& stream = args.Pick<Value_Stream>().GetStream();
	bool includeEOLFlag = !argument.IsSet(Gurax_Symbol(chop));
	// Function body
	return argument.ReturnIterator(processor, stream.ReadLines(includeEOLFlag));
}

#if 0
// hex(num:number, digits?:number):map:[upper]
Gurax_DeclareFunction(hex)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "num", VTYPE_number);
	DeclareArg(env, "digits", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(upper));
	AddHelp(
		Gurax_Symbol(en),
		"Converts a number into a hexadecimal string.\n"
		"Argument `digits` specifies a minimum columns of the converted result\n"
		"and fills `0` in the lacking space.\n"
		"\n"
		"In default, it uses lower-case characters in its conversion,\n"
		"while it uses upper-case ones when `:upper` attribute is specified.\n");
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

// int(value):map
Gurax_DeclareFunctionAlias(int_, "int")
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	AddHelp(
		Gurax_Symbol(en),
		"Converts a value into an integer number like below:\n"
		"\n"
		"- For a number value, it would be converted into an integer number.\n"
		"- For a compex value, its absolute number would be converted into an integer number.\n"
		"- For a string value, it would be parsed as an integer number.\n"
		"  An error occurs if it has an invalid format.\n"
		"- For other values, an error occurs.\n");
}

Gurax_ImplementFunction(int_)
{
	Signal &sig = env.GetSignal();
	const Value &value = arg.GetValue(0);
	Value result;
	if (value.Is_number()) {
		result.SetNumber(value.GetLong());
	} else if (value.Is_complex()) {
		result.SetNumber(static_cast<long>(std::abs(value.GetComplex())));
	} else if (value.Is_string()) {
		bool successFlag;
		Number num = value.ToNumber(true, successFlag);
		if (!successFlag) {
			sig.SetError(ERR_ValueError, "failed to convert to a number");
			return Value::Nil;
		}
		result.SetNumber(static_cast<long>(num));
	} else if (value.IsValid()) {
		SetError_InvalidValType(sig, value);
	}
	return result;
}

// tonumber(value):map:[strict,raise,zero,nil]
Gurax_DeclareFunction(tonumber)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	DeclareAttr(Gurax_Symbol(strict));
	DeclareAttr(Gurax_Symbol(raise));
	DeclareAttr(Gurax_Symbol(zero));
	DeclareAttr(Gurax_Symbol(nil));
	AddHelp(
		Gurax_Symbol(en),
		"Converts a string value into a number by a lexical parsing.\n"
		"If the value is not a string, it first tries to convert the value into a string.\n"
		"\n"
		"If the string starts with a sequence of characters that can be parsed as a number literal,\n"
		"it's not a failure even when it contains other characters following them.\n"
		"Specifying an attribute `:strict` doesn't allow such a case and fails the process.\n"
		"\n"
		"If it fails the conversion, it would return `nil` value.\n"
		"Attributes described below are prepared to customize the behaviour in the case of a failure.\n"
		"\n"
		"- `:raise` .. raises an error\n"
		"- `:zero` .. returns zero value\n"
		"- `:nil` .. returns `nil` value (default)\n");
}

Gurax_ImplementFunction(tonumber)
{
	Signal &sig = env.GetSignal();
	bool allowPartFlag = !arg.IsSet(Gurax_Symbol(strict));
	bool successFlag;
	Number num = arg.GetValue(0).ToNumber(allowPartFlag, successFlag);
	if (successFlag) {
		return Value(num);
	} else if (arg.IsSet(Gurax_Symbol(raise))) {
		sig.SetError(ERR_ValueError, "failed to convert to a number");
		return Value::Nil;
	} else if (arg.IsSet(Gurax_Symbol(zero))) {
		return Value(0.);
	} else { // arg.IsSet(Gurax_UserSymbol(nil)
		return Value::Nil;
	}
}

// tostring(value):map
Gurax_DeclareFunction(tostring)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "value", VTYPE_any);
	AddHelp(
		Gurax_Symbol(en),
		"Converts a value into a string.");
}

Gurax_ImplementFunction(tostring)
{
	return Value(arg.GetValue(0).ToString(false));
}

// tosymbol(str:string):map
Gurax_DeclareFunction(tosymbol)
{
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "str", VTYPE_string);
	AddHelp(
		Gurax_Symbol(en),
		"Converts a string into a symbol.");
}

Gurax_ImplementFunction(tosymbol)
{
	return Value(Symbol::Add(arg.GetString(0)));
}
#endif

//------------------------------------------------------------------------------
// Assignment
//------------------------------------------------------------------------------
void Functions::AssignToBasement(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(Chr));
	frame.Assign(Gurax_CreateFunction(dir));
	frame.Assign(Gurax_CreateFunction(Format));
	frame.Assign(Gurax_CreateFunction(Ord));
	frame.Assign(Gurax_CreateFunction(Print));
	frame.Assign(Gurax_CreateFunction(Printf));
	frame.Assign(Gurax_CreateFunction(Println));
	frame.Assign(Gurax_CreateFunction(Range));
	frame.Assign(Gurax_CreateFunction(ReadLines));
}

}
