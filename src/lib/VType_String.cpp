//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
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

// String#DecodeURI():String {block?}
Gurax_DeclareMethod(String, DecodeURI)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which percent-encoded characters are decoded.");
}

Gurax_ImplementMethod(String, DecodeURI)
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

// String#Each():Iterator:[utf8,utf32] {block?}
Gurax_DeclareMethod(String, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(utf8));
	DeclareAttrOpt(Gurax_Symbol(utf32));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating strings of each character in the original one.\n");
}

Gurax_ImplementMethod(String, Each)
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

// String#EachLine(nLines?:Number):Iterator:[chop] {block?}
// conrresponding to file#readlines()
Gurax_DeclareMethod(String, EachLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("nLines", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating strings of each line in the original one.\n"
		"\n"
		"In default, end-of-line characters are involved in the result.\n"
		"You can eliminates them by specifying `:chop` attribute.\n");
}

Gurax_ImplementMethod(String, EachLine)
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

// String#Embed(dst?:Stream:w):String:[noindent,lasteol]
Gurax_DeclareMethod(String, Embed)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("dst", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	DeclareAttrOpt(Gurax_Symbol(noindent));
	DeclareAttrOpt(Gurax_Symbol(lasteol));
	AddHelp(
		Gurax_Symbol(en),
		"Evaluates a string that contains embedded scripts\n"
		"and renders the result to the specified stream.\n"
		"\n"
		"If the stream is omitted, the function returns the rendered result as a string.\n"
		"\n"
		"Calling this method is equivalent to calling a method `String#template()` to\n"
		"create a `template` instance on which a method `template#render()` is applied afterward.\n");
}

Gurax_ImplementMethod(String, Embed)
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

// String#EncodeURI():String {block?}
Gurax_DeclareMethod(String, EncodeURI)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which non-URIC characters are percent-encoded.\n");
}

Gurax_ImplementMethod(String, EncodeURI)
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

// String#Escape():String:[surround] {block?}
Gurax_DeclareMethod(String, Escape)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(surround));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Applies backslash escaping on characters in the string.\n"
		"If attribute `:surround` is specified, the result contains a pair of single- or double-\n"
		"quotation characters surrounding the string.\n");
}

Gurax_ImplementMethod(String, Escape)
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

// String#EscapeHTML():String:[quote] {block?}
Gurax_DeclareMethod(String, EscapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(quote));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts some characters into HTML entity symbols.\n"
		"If attribute `:quote` is specified, a double-quotation character would be converted to\n"
		"an entity symbol \"&quot;\".");
}

Gurax_ImplementMethod(String, EscapeHTML)
{
	return Value::nil();
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
	Declare(VTYPE_String, Flag::None);
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

// String#Foldw(width:Number):String:[padding] {block?}
Gurax_DeclareMethod(String, Foldw)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(padding));
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

// String#Format(values*):String:reduce:map
Gurax_DeclareMethod(String, Format)
{
	Declare(VTYPE_String, Flag::Reduce | Flag::Map);
	DeclareArg("values", VTYPE_Any, ArgOccur::ZeroOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Taking the string instance as a printf-styled formatter string,\n"
		"it converts `values` into a string depending on formatter specifiers in it.\n");
}

Gurax_ImplementMethod(String, Format)
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

// String#Print(stream?:Stream:w):void
Gurax_DeclareMethod(String, Print)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out the string to the specified `stream`.\n"
		"\n"
		"If the argument is omitted, it would print to the standard output.\n");
}

Gurax_ImplementMethod(String, Print)
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

// String#Println(stream?:Stream:w):void
Gurax_DeclareMethod(String, Println)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(
		Gurax_Symbol(en),
		"Prints out the string and a line-break to the specified `stream`.\n"
		"\n"
		"If the argument is omitted, it would print to the standard output.\n");
}

Gurax_ImplementMethod(String, Println)
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

// String#Replaces(map[]:String, count?:number):String:map:[icase] {block?}
Gurax_DeclareMethod(String, Replaces)
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

Gurax_ImplementMethod(String, Replaces)
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

// String#Split(sep?:String, count?:number):String:[icase] {block?}
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

// String#Strip():String:[both,left,right] {block?}
Gurax_DeclareMethod(String, Strip)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(both));
	DeclareAttrOpt(Gurax_Symbol(left));
	DeclareAttrOpt(Gurax_Symbol(right));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that removes space characters on the left, the right or the both sides\n"
		"of the original string.\n"
		"\n"
		"The following attributes would specify which side of spaces should be removed:\n"
		"\n"
		"- `:both` .. Removes spaces on both sides. This is the default.\n"
		"- `:left` .. Removes spaces on the left side.\n"
		"- `:right` .. Removes spaces on the right side.\n");
}

Gurax_ImplementMethod(String, Strip)
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

// String#ToTemplate():Template:[noindent,lasteol] {block?}
Gurax_DeclareMethod(String, ToTemplate)
{
	Declare(VTYPE_Template, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(noindent));
	DeclareAttrOpt(Gurax_Symbol(lasteol));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Parses the content of the string as a text containing embedded scripts\n"
		"and returns a `template` instance.\n");
}

Gurax_ImplementMethod(String, ToTemplate)
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

// String#UnescapeHTML():String {block?}
Gurax_DeclareMethod(String, UnescapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en), 
		"Converts escape sequences into readable characters.");
}

Gurax_ImplementMethod(String, UnescapeHTML)
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
// String#isAlnum
Gurax_DeclareProperty_R(String, isAlnum)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet and digit.");
}

Gurax_ImplementPropertyGetter(String, isAlnum)
{
#if 0
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#isAlpha
Gurax_DeclareProperty_R(String, isAlpha)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet.");
}

Gurax_ImplementPropertyGetter(String, isAlpha)
{
#if 0
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#isDigit()
Gurax_DeclareProperty_R(String, isDigit)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are digit.");
}

Gurax_ImplementPropertyGetter(String, isDigit)
{
#if 0
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#isEmpty()
Gurax_DeclareProperty_R(String, isEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string is empty.");
}

Gurax_ImplementPropertyGetter(String, isEmpty)
{
#if 0
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
}

// String#isSpace()
Gurax_DeclareProperty_R(String, isSpace)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are space.");
}

Gurax_ImplementPropertyGetter(String, isSpace)
{
#if 0
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
#endif
	return Value::nil();
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
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
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
	auto& valueThis = GetValueThis(valueTarget);
	const String& str = valueThis.GetStringSTL();
	return new Value_Number(str.Width());
}

//------------------------------------------------------------------------------
// Implementation of operator
//------------------------------------------------------------------------------
// String + String
Gurax_ImplementOpBinary(Add, String, String)
{
	String strL = Value_String::GetStringSTL(valueL);
	const char* strR = Value_String::GetString(valueR);
	strL += strR;
	return new Value_String(strL);
}

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
VType_String VTYPE_String("String");

void VType_String::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	// Assignment of method
	Assign(Gurax_CreateMethod(String, Capitalize));
	Assign(Gurax_CreateMethod(String, Center));
	Assign(Gurax_CreateMethod(String, Chop));
	Assign(Gurax_CreateMethod(String, DecodeURI));
	Assign(Gurax_CreateMethod(String, Each));
	Assign(Gurax_CreateMethod(String, EachLine));
	Assign(Gurax_CreateMethod(String, Embed));
	Assign(Gurax_CreateMethod(String, Encode));
	Assign(Gurax_CreateMethod(String, EncodeURI));
	Assign(Gurax_CreateMethod(String, EndsWith));
	Assign(Gurax_CreateMethod(String, Escape));
	Assign(Gurax_CreateMethod(String, EscapeHTML));
	Assign(Gurax_CreateMethod(String, Find));
	Assign(Gurax_CreateMethod(String, Fold));
	Assign(Gurax_CreateMethod(String, Foldw));
	Assign(Gurax_CreateMethod(String, Format));
	Assign(Gurax_CreateMethod(String, Left));
	Assign(Gurax_CreateMethod(String, LJust));
	Assign(Gurax_CreateMethod(String, Lower));
	Assign(Gurax_CreateMethod(String, Mid));
	Assign(Gurax_CreateMethod(String, Print));
	Assign(Gurax_CreateMethod(String, Println));
	Assign(Gurax_CreateMethod(String, Replace));
	Assign(Gurax_CreateMethod(String, Replaces));
	Assign(Gurax_CreateMethod(String, Right));
	Assign(Gurax_CreateMethod(String, RJust));
	Assign(Gurax_CreateMethod(String, Split));
	Assign(Gurax_CreateMethod(String, StartsWith));
	Assign(Gurax_CreateMethod(String, Strip));
	Assign(Gurax_CreateMethod(String, ToBinary));
	Assign(Gurax_CreateMethod(String, ToReader));
	Assign(Gurax_CreateMethod(String, ToSymbol));
	Assign(Gurax_CreateMethod(String, ToTemplate));
	Assign(Gurax_CreateMethod(String, Translator));
	Assign(Gurax_CreateMethod(String, UnescapeHTML));
	Assign(Gurax_CreateMethod(String, Upper));
	Assign(Gurax_CreateMethod(String, ZenToHan));
	// Assignment of property
	Assign(Gurax_CreateProperty(String, isAlnum));
	Assign(Gurax_CreateProperty(String, isAlpha));
	Assign(Gurax_CreateProperty(String, isDigit));
	Assign(Gurax_CreateProperty(String, isEmpty));
	Assign(Gurax_CreateProperty(String, isSpace));
	Assign(Gurax_CreateProperty(String, len));
	Assign(Gurax_CreateProperty(String, width));
	// Assignment of operator
	Gurax_AssignOpBinary(Add, String, String);
}

Value* VType_String::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return new Value_String(value.ToString());
}

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
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

String Value_String::ToStringDigest(const StringStyle& ss) const
{
	String str;
	_ToStringDigest(str, ss);
	str += ":";
	str += GetStringSTL().MakeQuoted(true);
	str += ">";
	return str;
}

String Value_String::ToStringDetail(const StringStyle& ss) const
{
	return GetStringSTL().MakeQuoted(true);
}

bool Value_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

}
