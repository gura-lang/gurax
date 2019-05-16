//==============================================================================
// Functions.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------
// dir(frame?:Frame)
Gurax_DeclareFunction(dir)
{
	Declare(VTYPE_List, Flag::None);
	DeclareArg("frame", VTYPE_Frame, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
}

Gurax_ImplementFunction(dir)
{
	// Arguments
	ArgPicker args(argument);
	const Frame& frame = args.IsDefined()? Value_Frame::GetFrame(args.PickValue()) : Basement::Inst.GetFrame();
	// Function body
	SymbolList symbolList;
	frame.GatherSymbol(symbolList);
	symbolList.Sort();
	RefPtr<ValueTypedOwner> pValues(new ValueTypedOwner());
	pValues->Reserve(symbolList.size());
	for (const Symbol* pSymbol : symbolList) pValues->Add(new Value_Symbol(pSymbol));
	return new Value_List(pValues.release());
}

// Format(format:String, values*):String:map
Gurax_DeclareFunction(Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
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

// Print(values*):void:map
Gurax_DeclareFunction(Print)
{
	Declare(VTYPE_Nil, Flag::Map);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
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
	DeclareArg("format", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
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
	DeclareArg("values", VTYPE_Any, DeclArg::Occur::ZeroOrMore, DeclArg::Flag::None, nullptr);
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

void Functions::AssignToBasement(Frame& frame)
{
	frame.Assign(Gurax_CreateFunction(dir));
	frame.Assign(Gurax_CreateFunction(Format));
	frame.Assign(Gurax_CreateFunction(Print));
	frame.Assign(Gurax_CreateFunction(Printf));
	frame.Assign(Gurax_CreateFunction(Println));
}

}
