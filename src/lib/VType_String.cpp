//==============================================================================
// VType_String.cpp
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
// String(src?) {block?}
Gurax_DeclareConstructor(String)
{
	Declare(VTYPE_DateTime, Flag::Map);
	DeclareArg("src", VTYPE_Any, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `String` instance.");
}

Gurax_ImplementConstructor(String)
{
	// Arguments
	ArgPicker args(argument);
	const Value* pValue = args.IsValid()? &args.PickValue() : nullptr;
	// Function body
	String str;
	if (pValue) str = pValue->ToString();
	return argument.ReturnValue(processor, new Value_String(str));
}

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// String#Align(width:Number, align:Symbol, padding?:String):String:map
Gurax_DeclareMethod(String, Align)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("align", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Align the string to the position specified by a symbol given to the argument `align`\n"
		"and returns the result.\n"
		"The symbol involves: ` ``left` for left, ` ``center` for center and ` ``right` for right alignment."
		"\n"
		"If the string width is narrower than the specified `width`, nothing would be done.\n"
		"\n"
		"It uses a string specified by the argument `padding` to fill lacking spaces.\n"
		"If omitted, a white space is used for padding.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width. A kanji-character occupies two characters in width.\n");
}

Gurax_ImplementMethod(String, Align)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int width = args.PickNumberNonNeg<Int>();
	const Symbol* pSymbol = args.PickSymbol();
	const char* padding = args.IsValid()? args.PickString() : " ";
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	String strRtn;
	if (pSymbol->IsIdentical(Gurax_Symbol(left))) {
		strRtn = str.LJust(width, padding);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(center))) {
		strRtn = str.Center(width, padding);
	} else if (pSymbol->IsIdentical(Gurax_Symbol(right))) {
		strRtn = str.RJust(width, padding);
	} else {
		Error::Issue(ErrorType::ValueError, "the argument align takes `left, `center or `right");
		return Value::nil();
	}
	return new Value_String(strRtn);
}

// String#Capitalize():String {block?}
Gurax_DeclareMethod(String, Capitalize)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that capitalizes the first character.\n");
}

Gurax_ImplementMethod(String, Capitalize)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Capitalize());
}

// String#Center(width:Number, padding?:String):String:map
Gurax_DeclareMethod(String, Center)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Align the string to the center within the specified `width`\n"
		"and returns the result.\n"
		"\n"
		"If the string width is narrower than the specified `width`, nothing would be done.\n"
		"\n"
		"It uses a string specified by the argument `padding` to fill lacking spaces.\n"
		"If omitted, a white space is used for padding.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width. A kanji-character occupies two characters in width.\n");
}

Gurax_ImplementMethod(String, Center)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int width = args.PickNumberNonNeg<Int>();
	const char* padding = args.IsValid()? args.PickString() : " ";
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Center(width, padding));
}

// String#Chop(suffix*:String):String:[eol,icase] {block?}
Gurax_DeclareMethod(String, Chop)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("suffix", VTYPE_String, ArgOccur::ZeroOrMore, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(eol));
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that removes a last character.\n"
		"\n"
		"If an attribute `:eol` is specified, only the end-of-line character shall be\n"
		"removed. In this case, if the end-of-line has a sequence of CR-LF, CR code\n"
		"shall be removed as well.");
}

Gurax_ImplementMethod(String, Chop)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#DecodeURI():String
Gurax_DeclareMethod(String, DecodeURI)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which percent-encoded characters are decoded.");
}

Gurax_ImplementMethod(String, DecodeURI)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.DecodeURI());
}

// String#Each():Iterator:[utf8,utf32] {block?}
Gurax_DeclareMethod(String, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(utf8));
	DeclareAttrOpt(Gurax_Symbol(utf32));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that returns each character in the string.\n");
}

Gurax_ImplementMethod(String, Each)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	VType_String::Iterator_Each::Type type =
		argument.IsSet(Gurax_Symbol(utf8))? VType_String::Iterator_Each::Type::UTF8 :
		argument.IsSet(Gurax_Symbol(utf32))? VType_String::Iterator_Each::Type::UTF32 :
		VType_String::Iterator_Each::Type::String;
	// Function body
	const StringReferable& str = valueThis.GetStringReferable();
	return argument.ReturnIterator(processor, new VType_String::Iterator_Each(str.Reference(), type));
}


// String#EachLine():Iterator:[chop] {block?}
// conrresponding to stream#ReadLines()
Gurax_DeclareMethod(String, EachLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that returns each line of the string.\n"
		"\n"
		"In default, end-of-line characters are included in the result.\n"
		"You can eliminates them by specifying `:chop` attribute.\n");
}

Gurax_ImplementMethod(String, EachLine)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	bool chopFlag = argument.IsSet(Gurax_Symbol(chop));
	// Function body
	const StringReferable& str = valueThis.GetStringReferable();
	return argument.ReturnIterator(processor, new VType_String::Iterator_EachLine(str.Reference(), chopFlag));
}

// String#Encode(codec:Codec):String {block?}
Gurax_DeclareMethod(String, Encode)
{
	Declare(VTYPE_String, Flag::None);
	//DeclareArg("codec", VTYPE_Codec, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Encodes the string with the given `codec` and return the result as a `binary`.\n");
}

Gurax_ImplementMethod(String, Encode)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#EncodeURI():String
Gurax_DeclareMethod(String, EncodeURI)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which non-URIC characters are percent-encoded.\n");
}

Gurax_ImplementMethod(String, EncodeURI)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.EncodeURI());
}

// String#EndsWith(sub:String, posEnd?:Number):map:[rest,icase]
Gurax_DeclareMethod(String, EndsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rest));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string ends with the specified suffix `sub`.\n"
		"\n"
		"The optional argument `posEnd` specifies the bottom position of the string where the matching starts.\n"
		"\n"
		"If the attribute `:rest` is specified,\n"
		"it returns the rest part if the string ends with the specified suffix, and `nil` otherewise.\n"
		"\n"
		"When the attribute `:icase` is specified, character cases are ignored.\n");
}

Gurax_ImplementMethod(String, EndsWith)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* sub = args.PickString();
	Int endPos = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const char* str = valueThis.GetString();
	const char* rtn = nullptr;
	if (endPos < 0) {
		rtn = argument.IsSet(Gurax_Symbol(icase))?
			String::EndsWith<CharICase>(str, sub) :
			String::EndsWith<CharCase>(str, sub);
	} else {
		rtn = argument.IsSet(Gurax_Symbol(icase))?
			String::EndsWith<CharICase>(str, endPos, sub) :
			String::EndsWith<CharCase>(str, endPos, sub);
	}
	return !argument.IsSet(Gurax_Symbol(rest))? Value::Bool(rtn) :
		rtn? new Value_String(rtn) : Value::nil();
}

// String#Enquote():String:[auto,q,qq] {block?}
Gurax_DeclareMethod(String, Enquote)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(auto_));
	DeclareAttrOpt(Gurax_Symbol(q));
	DeclareAttrOpt(Gurax_Symbol(qq));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Surrounds the given string with quotation marks. Following attributes control\n"
		"what character is used as the mark:\n"
		"\n"
		"- `` `auto`` .. double-quote character if the string contains any single-quote and no double-quote characters,\n"
		"                or single-quote character otherwise.\n"
		"- `` `q`` .. single-quote character\n"
		"- `` `qq`` .. double-quote character\n");
}

Gurax_ImplementMethod(String, Enquote)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	char chQuote =
		argument.IsSet(Gurax_Symbol(auto_))? str.DetermineQuote() :
		argument.IsSet(Gurax_Symbol(q))? '\'' :
		argument.IsSet(Gurax_Symbol(qq))? '"' : '\'';
	return new Value_String(str.Enquote(chQuote));
}

// String#EscapeHTML():String:[quote]
Gurax_DeclareMethod(String, EscapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(quote));
	AddHelp(
		Gurax_Symbol(en), 
		"Converts some characters into HTML entity symbols.\n"
		"If attribute `:quote` is specified, a double-quotation character would be converted to\n"
		"an entity symbol \"&quot;\".");
}

Gurax_ImplementMethod(String, EscapeHTML)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	bool quoteFlag = argument.IsSet(Gurax_Symbol(quote));
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.EscapeHTML(quoteFlag));
}

// String#Find(sub:String, pos?:Number):map:[icase,rev]
Gurax_DeclareMethod(String, Find)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rev));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en), 
		"Returns the position where the specified sub-string is found in the string.\n"
		"In the case the sub-string is not found, it returns `nil`.\n"
		"\n"
		"The argument `pos` specifies the position where the search starts.\n"
		"\n"
		"With the attribute `:icase`, character cases are ignored while matching."
		"\n"
		"If the attribute `:rev` is specified, the search starts from the end of the string.");
}

Gurax_ImplementMethod(String, Find)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* sub = args.PickString();
	Int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	String::const_iterator pStr = str.Forward(pos);
	String::const_iterator pFound = argument.IsSet(Gurax_Symbol(icase))?
		str.Find<CharICase>(pStr, sub) : str.Find<CharCase>(pStr, sub);
	return (pFound == str.end())? Value::nil() : new Value_Number(str.CalcPos(pFound));
}

// String#Fold(len:Number, step?:Number):String:[neat] {block?}
Gurax_DeclareMethod(String, Fold)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("step", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(neat));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that folds the source string by the specified length.\n"
		"\n"
		"The argument `step` specifies the length of advancement for the next folding point.\n"
		"If omitted, it would be the same amount as `len`.\n");
}

Gurax_ImplementMethod(String, Fold)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t lenPerFold = args.PickNumberPos<size_t>();
	size_t lenStep = args.IsValid()? args.PickNumberPos<size_t>() : lenPerFold;
	bool neatFlag = argument.IsSet(Gurax_Symbol(neat));
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const StringReferable& str = valueThis.GetStringReferable();
	return argument.ReturnIterator(
		processor, new VType_String::Iterator_Fold(str.Reference(), lenPerFold, lenStep, neatFlag));
}

// String#Foldw(width:Number, padding?:String):String {block?}
Gurax_DeclareMethod(String, Foldw)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that folds the source string by the specified width.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width.\n");
}

Gurax_ImplementMethod(String, Foldw)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	size_t widthPerFold = args.PickNumberPos<size_t>();
	const char* padding = args.IsValid()? args.PickString() : nullptr;
	// Function body
	const StringReferable& str = valueThis.GetStringReferable();
	return argument.ReturnIterator(
		processor, new VType_String::Iterator_Foldw(str.Reference(), widthPerFold, padding? *padding : '\0'));
}

// String#Format(values*):String:map
Gurax_DeclareMethod(String, Format)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Taking the string instance as a printf-styled formatter string,\n"
		"it converts `values` into a string depending on formatter specifiers in it.\n");
}

Gurax_ImplementMethod(String, Format)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const ValueList& values = args.PickList();
	// Function body
	String str;
	str.FormatValueList(valueThis.GetString(), values);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(str);
}

// String#IsAlnum()
Gurax_DeclareMethod(String, IsAlnum)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet and digit.");
}

Gurax_ImplementMethod(String, IsAlnum)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsAlnum());
}

// String#IsAlpha()
Gurax_DeclareMethod(String, IsAlpha)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet.");
}

Gurax_ImplementMethod(String, IsAlpha)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsAlpha());
}

// String#IsDigit()
Gurax_DeclareMethod(String, IsDigit)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are digit.");
}

Gurax_ImplementMethod(String, IsDigit)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsDigit());
}

// String#IsEmpty()
Gurax_DeclareMethod(String, IsEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string is empty.");
}

Gurax_ImplementMethod(String, IsEmpty)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsEmpty());
}

// String#IsSpace()
Gurax_DeclareMethod(String, IsSpace)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are space.");
}

Gurax_ImplementMethod(String, IsSpace)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsSpace());
}

// String#Left(len?:Number):String:map
Gurax_DeclareMethod(String, Left)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Extracts the specified length of string from left of the source string.\n"
		"\n"
		"If the argument is omitted, it would return whole the source string.\n");
}

Gurax_ImplementMethod(String, Left)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int len = args.PickNumberNonNeg<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Left(len));
}

// String#LJust(width:Number, padding?:String):String:map
Gurax_DeclareMethod(String, LJust)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Align the string to the left within the specified `width`\n"
		"and returns the result.\n"
		"\n"
		"If the string width is narrower than the specified `width`, nothing would be done.\n"
		"\n"
		"It uses a string specified by the argument `padding` to fill lacking spaces.\n"
		"If omitted, a white space is used for padding.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width. A kanji-character occupies two characters in width.\n");
}

Gurax_ImplementMethod(String, LJust)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int width = args.PickNumberNonNeg<Int>();
	const char* padding = args.IsValid()? args.PickString() : " ";
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.LJust(width, padding));
}

// String#Lower()
Gurax_DeclareMethod(String, Lower)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts each alphabetical character to lower case.\n");
}

Gurax_ImplementMethod(String, Lower)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Lower());
}

// String#Mid(pos:Number, len?:Number):String:map {block?}
Gurax_DeclareMethod(String, Mid)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Extracts the specified length of string from the position `pos` and returns the result.\n"
		"\n"
		"If the argument `len` is omitted, it returns a string from `pos` to the end.\n"
		"The number of an argument `pos` starts from zero.\n"
		"\n"
		"Below are examples:\n"
		"\n"
		"    'Hello world'.mid(3, 2) // 'lo'\n"
		"    'Hello world'.mid(5)    // 'world'\n");
}

Gurax_ImplementMethod(String, Mid)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int pos = args.PickNumber<Int>();
	size_t len = args.IsValid()? args.PickNumberNonNeg<size_t>() : static_cast<size_t>(-1);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	if (!str.FixPosition(&pos)) return Value::nil();
	return new Value_String(str.Mid(pos, len));
}

// String#Render(stream?:Stream:w):void
Gurax_DeclareMethod(String, Render)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out the string to the specified `stream`.\n"
		"\n"
		"If the argument is omitted, it would be rendered to the standard output.\n");
}

Gurax_ImplementMethod(String, Render)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Stream& streamDst = args.IsValid()? args.PickStream() : Basement::Inst.GetStreamCOut();
	// Function body
	const char* str = valueThis.GetString();
	streamDst.Print(str);
	return Value::nil();
}

// String#Replace(match:String, sub:String, count?:number):String:map:[icase] {block?}
Gurax_DeclareMethod(String, Replace)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("match", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Replaces sub strings that matches the string `match` with a string specified by `sub`\n"
		"and returns the result.\n"
		"\n"
		"The argument `count` limits the maximum number of substitution.\n"
		"If omitted, there's no limit of the work.\n"
		"\n"
		"With an attribute `:icase`, character cases are ignored while matching strings.\n"
		"\n"
		"If `block` is specified, it would be evaluated with a block parameter `|result:String, replaced:boolean|`,\n"
		"where `result` is the result string and `replaced` indicates if there is any change\n"
		"between the result and its original string.\n"
		"In this case, the block's result would become the function's returned value.\n");
}

Gurax_ImplementMethod(String, Replace)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* match = args.PickString();
	const char* sub = args.PickString();
	bool validFlag_count = false;
	Int count = (validFlag_count = args.IsValid())? args.PickNumberNonNeg<Int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	String strRtn = argument.IsSet(Gurax_Symbol(icase))?
		(validFlag_count? str.Replace<CharICase>(match, sub, count) : str.Replace<CharICase>(match, sub)) :
		(validFlag_count? str.Replace<CharCase>(match, sub, count) : str.Replace<CharCase>(match, sub));
	return new Value_String(strRtn);
}

// String#ReplaceM(map[]:String, count?:number):String:map:[icase] {block?}
Gurax_DeclareMethod(String, ReplaceM)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("map", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Replaces string parts according to a list of pairs of a matching and a substituting string\n"
		"and returns the result.\n"
		"\n"
		"The argument `map` is a `list` of match-substitution paris like `[match1, sub1, match2, sub2, ..]`\n"
		"with which a sub string that matches `match`*n* would be replaced with `sub`*n*.\n"
		"\n"
		"The argument `count` limits the maximum number of substitution.\n"
		"If omitted, there's no limit of the work.\n"
		"\n"
		"With an attribute `:icase`, character cases are ignored while matching strings.\n"
		"\n"
		"If `block` is specified, it would be evaluated with a block parameter `|result:String, replaced:boolean|`,\n"
		"where `result` is the result string and `replaced` indicates if there is any change\n"
		"between the result and its original string.\n"
		"In this case, the block's result would become the function's returned value.\n");
}

Gurax_ImplementMethod(String, ReplaceM)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	StringList map = Value_String::GetStringList(args.PickList());
	bool validFlag_count = false;
	Int count = (validFlag_count = args.IsValid())? args.PickNumberNonNeg<Int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	String strRtn = argument.IsSet(Gurax_Symbol(icase))?
		(validFlag_count? str.ReplaceM<CharICase>(map, count) : str.ReplaceM<CharICase>(map)) :
		(validFlag_count? str.ReplaceM<CharCase>(map, count) : str.ReplaceM<CharCase>(map));
	return new Value_String(strRtn);
}

// String#Right(len?:Number):String:map {block?}
Gurax_DeclareMethod(String, Right)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Extracts the specified length of string from right of the source string.\n"
		"\n"
		"If the argument is omitted, it would return whole the source string.\n");
}

Gurax_ImplementMethod(String, Right)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int len = args.PickNumberNonNeg<Int>();
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Right(len));
}

// String#RJust(width:Number, padding?:String):String:map
Gurax_DeclareMethod(String, RJust)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Align the string to the right within the specified `width`\n"
		"and returns the result.\n"
		"\n"
		"If the string width is narrower than the specified `width`, nothing would be done.\n"
		"\n"
		"It uses a string specified by the argument `padding` to fill lacking spaces.\n"
		"If omitted, a white space is used for padding.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width. A kanji-character occupies two characters in width.\n");
}

Gurax_ImplementMethod(String, RJust)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Int width = args.PickNumberNonNeg<Int>();
	const char* padding = args.IsValid()? args.PickString() : " ";
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.RJust(width, padding));
}

// String#Split(sep?:String, count?:Number):String:[icase] {block?}
Gurax_DeclareMethod(String, Split)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("sep", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating sub strings extracted from the original one\n"
		"separated by a specified string `sep`.\n"
		"With an attribute `:icase`, character cases are ignored while finding the separator.\n");
}

Gurax_ImplementMethod(String, Split)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* sep = args.IsValid()? args.PickString() : "";
	Int cntMax = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const StringReferable& str = valueThis.GetStringReferable();
	RefPtr<Iterator> pIterator;
	if (*sep == '\0') {
		pIterator.reset(new VType_String::Iterator_Each(str.Reference(), VType_String::Iterator_Each::Type::String));
	} else if (argument.IsSet(Gurax_Symbol(icase))) {
		pIterator.reset(new VType_String::Iterator_Split<CharICase>(str.Reference(), sep, cntMax));
	} else {
		pIterator.reset(new VType_String::Iterator_Split<CharCase>(str.Reference(), sep, cntMax));
	}
	return argument.ReturnIterator(processor, pIterator.release());
}

// String#StartsWith(sub:String, pos?:Number):map:[rest,icase]
Gurax_DeclareMethod(String, StartsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rest));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string starts with `sub`.\n"
		"\n"
		"If attribute `:rest` is specified,\n"
		"it returns the rest part if the string starts with prefix, or `nil` otherewise.\n"
		"You can specify a top position for the matching by an argument `pos`.\n"
		"\n"
		"With an attribute `:icase`, character cases are ignored while matching.");
}

Gurax_ImplementMethod(String, StartsWith)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* sub = args.PickString();
	Int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const char* str = valueThis.GetString();
	if (pos > 0) str = String::Forward(str, pos);
	const char* rtn = argument.IsSet(Gurax_Symbol(icase))?
		String::StartsWith<CharICase>(str, sub) :
		String::StartsWith<CharCase>(str, sub);
	return !argument.IsSet(Gurax_Symbol(rest))? Value::Bool(rtn) :
		rtn? new Value_String(rtn) : Value::nil();
}

// String#Strip():String {block?}
Gurax_DeclareMethod(String, Strip)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that removes space characters on the both side.\n");
}

Gurax_ImplementMethod(String, Strip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(true, true));
}

// String#StripLeft():String {block?}
Gurax_DeclareMethod(String, StripLeft)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that removes space characters on the left side.\n");
}

Gurax_ImplementMethod(String, StripLeft)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(true, false));
}

// String#StripRight():String {block?}
Gurax_DeclareMethod(String, StripRight)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that removes space characters on the right side.\n");
}

Gurax_ImplementMethod(String, StripRight)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(false, true));
}

// String#Template():Template:[noIndent,lastEol] {block?}
Gurax_DeclareMethod(String, Template)
{
	//Declare(VTYPE_Template, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(noIndent));
	DeclareAttrOpt(Gurax_Symbol(lastEol));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Parses the content of the string as a text containing embedded scripts\n"
		"and returns a `Template` instance.\n");
}

Gurax_ImplementMethod(String, Template)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	bool autoIndentFlag = !argument.IsSet(Gurax_Symbol(noIndent));
	bool appendLastEOLFlag = argument.IsSet(Gurax_Symbol(lastEol));
	// Function body
	const char* str = valueThis.GetString();
	RefPtr<Template> pTmpl(new Template());
	if (!pTmpl->ParseString_(str, autoIndentFlag, appendLastEOLFlag) ||
		!pTmpl->PrepareAndCompose()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Template(pTmpl.release()));
}

// String#ToBinary():Binary {block?}
Gurax_DeclareMethod(String, ToBinary)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Converts the string into `binary` instance.");
}

Gurax_ImplementMethod(String, ToBinary)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#ToReader():Stream {block?}
Gurax_DeclareMethod(String, ToReader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `stream` instance that reads the string content as a binary sequence.\n");
}

Gurax_ImplementMethod(String, ToReader)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#ToSymbol():Symbol {block?}
Gurax_DeclareMethod(String, ToSymbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Convers the string into a symbol.\n");
}

Gurax_ImplementMethod(String, ToSymbol)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_Symbol(Symbol::Add(str));
}

// String.Translator():void {block}
Gurax_DeclareClassMethod(String, Translator)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareBlock(BlkOccur::Once);
	AddHelp(
		Gurax_Symbol(en),
		"Register a procedure evaluated when a string literal\n"
		"appears with a suffix symbol \"`$`\",\n"
		"which is meant to translate the string into another language.\n"
		"\n"
		"The procedure is described in `block` takes a block parameter `|str:string|`\n"
		"where `str` is the original String, and is expected to return a string\n"
		"translated from the original.\n");
}

Gurax_ImplementClassMethod(String, Translator)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#UnescapeHTML():String
Gurax_DeclareMethod(String, UnescapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts escape sequences into readable characters.");
}

Gurax_ImplementMethod(String, UnescapeHTML)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.UnescapeHTML());
}

// String#Upper():String
Gurax_DeclareMethod(String, Upper)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Converts each alphabetical character to upper case.\n");
}

Gurax_ImplementMethod(String, Upper)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Upper());
}

// String#ZenToHan():String {block?}
Gurax_DeclareMethod(String, ZenToHan)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Converts zenkaku to hankaku characters.");
}

Gurax_ImplementMethod(String, ZenToHan)
{
#if 0
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	if (Error::IsIssued()) return Value::nil();
	// Function body
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// String#first
Gurax_DeclareProperty_R(String, first)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The first character in the string. Returns an empty string if the string is empty.");
}

Gurax_ImplementPropertyGetter(String, first)
{
	const char* str = GetValueThis(valueTarget).GetString();
	const char* p = String::Forward(str);
	return new Value_String(String(str, p));
}

// String#last
Gurax_DeclareProperty_R(String, last)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The last character in the string. Returns an empty string if the string is empty.");
}

Gurax_ImplementPropertyGetter(String, last)
{
	const char* str = GetValueThis(valueTarget).GetString();
	const char* pBtm = String::ForwardToTerminal(str);
	const char* p = String::Backward(pBtm, str);
	return new Value_String(String(p, pBtm));
}

// String#len
Gurax_DeclareProperty_R(String, len)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The number of characters in the string.");
}

Gurax_ImplementPropertyGetter(String, len)
{
	const String& str = GetValueThis(valueTarget).GetStringSTL();
	return new Value_Number(str.Length());
}

// String#width
Gurax_DeclareProperty_R(String, width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"The string's width when displayed with a fixed-width font.");
}

Gurax_ImplementPropertyGetter(String, width)
{
	const String& str = GetValueThis(valueTarget).GetStringSTL();
	return new Value_Number(str.Width());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// String + String
Gurax_ImplementOpBinary(Add, String, String)
{
	String strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	strL += strR;
	return new Value_String(strL);
}

// String + Any
Gurax_ImplementOpBinary(Add, String, Any)
{
	String strL = Value_String::GetStringSTL(valueL);
	const String strR = valueR.ToString();
	strL += strR;
	return new Value_String(strL);
}

// Any + String
Gurax_ImplementOpBinary(Add, Any, String)
{
	String strL = valueL.ToString();
	const String& strR = Value_String::GetStringSTL(valueR);
	strL += strR;
	return new Value_String(strL);
}

// String == String
Gurax_ImplementOpBinary(Eq, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL == strR);
}

// String >= String
Gurax_ImplementOpBinary(Ge, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL >= strR);
}

// String > String
Gurax_ImplementOpBinary(Gt, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL > strR);
}

// String <= String
Gurax_ImplementOpBinary(Le, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL <= strR);
}

// String < String
Gurax_ImplementOpBinary(Lt, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL < strR);
}

// String * Number
Gurax_ImplementOpBinary(Mul, String, Number)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	size_t numR = Value_Number::GetNumberNonNeg<size_t>(valueR);
	if (Error::IsIssued()) return Value::nil();
	return new Value_String(strL.Repeat(numR));
}

// String != String
Gurax_ImplementOpBinary(Ne, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Bool(strL != strR);
}

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
VType_String VTYPE_String("String");

void VType_String::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(String));
	// Assignment of method
	Assign(Gurax_CreateMethod(String, Align));
	Assign(Gurax_CreateMethod(String, Capitalize));
	Assign(Gurax_CreateMethod(String, Center));
	Assign(Gurax_CreateMethod(String, Chop));
	Assign(Gurax_CreateMethod(String, DecodeURI));
	Assign(Gurax_CreateMethod(String, Each));
	Assign(Gurax_CreateMethod(String, EachLine));
	Assign(Gurax_CreateMethod(String, Encode));
	Assign(Gurax_CreateMethod(String, EncodeURI));
	Assign(Gurax_CreateMethod(String, EndsWith));
	Assign(Gurax_CreateMethod(String, Enquote));
	Assign(Gurax_CreateMethod(String, EscapeHTML));
	Assign(Gurax_CreateMethod(String, Find));
	Assign(Gurax_CreateMethod(String, Fold));
	Assign(Gurax_CreateMethod(String, Foldw));
	Assign(Gurax_CreateMethod(String, Format));
	Assign(Gurax_CreateMethod(String, IsAlnum));
	Assign(Gurax_CreateMethod(String, IsAlpha));
	Assign(Gurax_CreateMethod(String, IsDigit));
	Assign(Gurax_CreateMethod(String, IsEmpty));
	Assign(Gurax_CreateMethod(String, IsSpace));
	Assign(Gurax_CreateMethod(String, Left));
	Assign(Gurax_CreateMethod(String, LJust));
	Assign(Gurax_CreateMethod(String, Lower));
	Assign(Gurax_CreateMethod(String, Mid));
	Assign(Gurax_CreateMethod(String, Render));
	Assign(Gurax_CreateMethod(String, Replace));
	Assign(Gurax_CreateMethod(String, ReplaceM));
	Assign(Gurax_CreateMethod(String, Right));
	Assign(Gurax_CreateMethod(String, RJust));
	Assign(Gurax_CreateMethod(String, Split));
	Assign(Gurax_CreateMethod(String, StartsWith));
	Assign(Gurax_CreateMethod(String, Strip));
	Assign(Gurax_CreateMethod(String, StripLeft));
	Assign(Gurax_CreateMethod(String, StripRight));
	Assign(Gurax_CreateMethod(String, Template));
	Assign(Gurax_CreateMethod(String, ToBinary));
	Assign(Gurax_CreateMethod(String, ToReader));
	Assign(Gurax_CreateMethod(String, ToSymbol));
	Assign(Gurax_CreateMethod(String, Translator));
	Assign(Gurax_CreateMethod(String, UnescapeHTML));
	Assign(Gurax_CreateMethod(String, Upper));
	Assign(Gurax_CreateMethod(String, ZenToHan));
	// Assignment of property
	Assign(Gurax_CreateProperty(String, first));
	Assign(Gurax_CreateProperty(String, last));
	Assign(Gurax_CreateProperty(String, len));
	Assign(Gurax_CreateProperty(String, width));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, String, String);
	Gurax_AssignOpBinary(Add, String, Any);
	Gurax_AssignOpBinary(Add, Any, String);
	Gurax_AssignOpBinary(Eq, String, String);
	Gurax_AssignOpBinary(Ge, String, String);
	Gurax_AssignOpBinary(Gt, String, String);
	Gurax_AssignOpBinary(Le, String, String);
	Gurax_AssignOpBinary(Lt, String, String);
	Gurax_AssignOpBinary(Mul, String, Number);
	Gurax_AssignOpBinary(Ne, String, String);
}

Value* VType_String::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return new Value_String(value.ToString());
}

//------------------------------------------------------------------------------
// VType_String::Iterator_Each
//------------------------------------------------------------------------------
Value* VType_String::Iterator_Each::DoNextValue()
{
	if (!*_pCurrent) return nullptr;
	RefPtr<Value> pValue;
	switch (_type) {
	case Type::UTF8: {
		pValue.reset(new Value_Number(String::NextUTF8(&_pCurrent)));
		break;
	}
	case Type::UTF32: {
		pValue.reset(new Value_Number(String::NextUTF32(&_pCurrent)));
		break;
	}
	default: { // Type::String
		const char* pEnd = String::Forward(_pCurrent);
		pValue.reset(new Value_String(String(_pCurrent, pEnd)));
		_pCurrent = pEnd;
		break;
	}
	}
	return pValue.release();
}

String VType_String::Iterator_Each::ToString(const StringStyle& ss) const
{
	return "String#Each";
}

//------------------------------------------------------------------------------
// VType_String::Iterator_EachLine
//------------------------------------------------------------------------------
Value* VType_String::Iterator_EachLine::DoNextValue()
{
	const char* pBegin = _pCurrent;
	if (!*pBegin) return nullptr;
	const char* pEnd = pBegin;
	for ( ; ; _pCurrent++) {
		char ch = *_pCurrent;
		if (ch == '\0') {
			pEnd = _pCurrent;
			break;
		} else if (ch == '\n') {
			pEnd = _chopFlag? _pCurrent : _pCurrent + 1;
			_pCurrent++;
			break;
		}
	}
	return new Value_String(String(pBegin, pEnd));
}

String VType_String::Iterator_EachLine::ToString(const StringStyle& ss) const
{
	return "String#EachLine";
}

//-----------------------------------------------------------------------------
// VType_String::Iterator_Fold
//-----------------------------------------------------------------------------
Value* VType_String::Iterator_Fold::DoNextValue()
{
	if (!*_pCurrent) return nullptr;
	size_t lenForward = 0;
	const char* pNext;
	const char* pTail;
	if (_lenStep <= _lenPerFold) {
		size_t lenForwardSub = 0;
		pNext = String::Forward(_pCurrent, _lenStep, &lenForward);
		pTail = String::Forward(pNext, _lenPerFold - _lenStep, &lenForwardSub);
		lenForward += lenForwardSub;
	} else {
		pTail = String::Forward(_pCurrent, _lenPerFold, &lenForward);
		pNext = String::Forward(pTail, _lenStep - _lenPerFold);
	}
	if (_neatFlag && lenForward < _lenPerFold) return nullptr;
	RefPtr<Value> pValue(new Value_String(String(_pCurrent, pTail)));
	_pCurrent = pNext;
	return pValue.release();
}

String VType_String::Iterator_Fold::ToString(const StringStyle& ss) const
{
	return String("String#Fold");
}

//-----------------------------------------------------------------------------
// VType_String::Iterator_Foldw
//-----------------------------------------------------------------------------
Value* VType_String::Iterator_Foldw::DoNextValue()
{
	size_t width = 0; 
	if (!*_pCurrent) return nullptr;
	const char* pHead = _pCurrent;
	while (*_pCurrent) {
		const char* pNext = _pCurrent;
		UInt32 codeUTF32 = String::NextUTF32(&pNext);
		Codec::WidthProp widthProp = Codec::GetWidthProp(codeUTF32);
		width += (widthProp == Codec::WidthProp::A ||
				  widthProp == Codec::WidthProp::W ||
				  widthProp == Codec::WidthProp::F)? 2 : 1;
		if (width > _widthPerFold) {
			String str(pHead, _pCurrent);
			if (_chPadding) str += _chPadding;
			if (pHead == _pCurrent) _pCurrent = pNext;
			return new Value_String(str);
		}
		_pCurrent = pNext;
		if (width == _widthPerFold) {
			return new Value_String(String(pHead, _pCurrent));
		}
	}
	if (_chPadding && width < _widthPerFold) {
		String str(pHead, _pCurrent);
		for (size_t i = _widthPerFold - width; i > 0; i--) str += _chPadding;
		return new Value_String(str);
	}
	return new Value_String(String(pHead, _pCurrent));
}

String VType_String::Iterator_Foldw::ToString(const StringStyle& ss) const
{
	return String("String#Foldw");
}

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
VType& Value_String::vtype = VTYPE_String;

StringList Value_String::GetStringList(const ValueList& values)
{
	StringList strs;
	strs.reserve(values.size());
	for (Value* pValue : values) {
		const String& str = GetStringSTL(*pValue);
		strs.push_back(str);
	}
	return strs;
}

String Value_String::ToString(const StringStyle& ss) const
{
	String str = GetStringSTL();
	if (ss.IsStringQuoted()) str = str.EnquoteAuto();
	return str;
}

bool Value_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
