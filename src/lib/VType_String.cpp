//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// String#Align(width:Number, padding?:String):String:map:[center,left,right] {block?}
Gurax_DeclareMethod(String, Align)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("padding", VTYPE_String, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
#if 0
	DeclareAttr(Gurax_Symbol(center));
	DeclareAttr(Gurax_Symbol(left));
	DeclareAttr(Gurax_Symbol(right));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Align the string to the left, right or center within the specified `width`\n"
		"and returns the result.\n"
		"\n"
		"The following attributes specify the alignment position:\n"
		"\n"
		"- `:center` .. Aligns to the center. This is the default.\n"
		"- `:left` .. Aligns to the left\n"
		"- `:right` .. Aligns to the right\n"
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
	return Value::nil();
}

// String#Capitalize():String {block?}
Gurax_DeclareMethod(String, Capitalize)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string that capitalizes the first character.\n");
}

Gurax_ImplementMethod(String, Capitalize)
{
	return Value::nil();
}

// String#Chop(suffix*:String):String:[eol,icase] {block?}
Gurax_DeclareMethod(String, Chop)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "suffix", VTYPE_String, OCCUR_ZeroOrMore);
	DeclareAttr(Gurax_Symbol(eol));
	DeclareAttr(Gurax_Symbol(icase));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	return Value::nil();
}

// String#DecodeURI():String {block?}
Gurax_DeclareMethod(String, DecodeURI)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which percent-encoded characters are decoded.");
}

Gurax_ImplementMethod(String, DecodeURI)
{
	return Value::nil();
}

// String#Each():Iterator:[utf8,utf32] {block?}
Gurax_DeclareMethod(String, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareAttr(Gurax_Symbol(utf8));
	DeclareAttr(Gurax_Symbol(utf32));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating strings of each character in the original one.\n");
}

Gurax_ImplementMethod(String, Each)
{
	return Value::nil();
}

// String#EachLine(nLines?:Number):Iterator:[chop] {block?}
// conrresponding to file#readlines()
Gurax_DeclareMethod(String, EachLine)
{
	Declare(VTYPE_Iterator, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "nLines", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(chop));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating strings of each line in the original one.\n"
		"\n"
		"In default, end-of-line characters are involved in the result.\n"
		"You can eliminates them by specifying `:chop` attribute.\n");
}

Gurax_ImplementMethod(String, EachLine)
{
	return Value::nil();
}

// String#Embed(dst?:Stream:w):String:[noindent,lasteol]
Gurax_DeclareMethod(String, Embed)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "dst", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
	DeclareAttr(Gurax_Symbol(noindent));
	DeclareAttr(Gurax_Symbol(lasteol));
#endif
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
	return Value::nil();
}

// String#Encode(codec:Codec):String {block?}
Gurax_DeclareMethod(String, Encode)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "codec", VTYPE_codec);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Encodes the string with the given `codec` and return the result as a `binary`.\n");
}

Gurax_ImplementMethod(String, Encode)
{
	return Value::nil();
}

// String#EncodeURI():String {block?}
Gurax_DeclareMethod(String, EncodeURI)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Returns a string in which non-URIC characters are percent-encoded.\n");
}

Gurax_ImplementMethod(String, EncodeURI)
{
	return Value::nil();
}

// String#EndsWith(sub:String, posEnd?:Number):map:[rest,icase]
Gurax_DeclareMethod(String, EndsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("posEnd", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
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
	int endpos = args.IsValid()? args.PickInt() : -1;
	// Function body
	const char* str = valueThis.GetString();
	const char* rtn = nullptr;
	if (endpos < 0) {
		rtn = argument.IsSet(Gurax_Symbol(icase))?
			String::EndsWith<CharICase>(str, sub) :
			String::EndsWith<CharCase>(str, sub);
	} else {
		rtn = argument.IsSet(Gurax_Symbol(icase))?
			String::EndsWith<CharICase>(str, endpos, sub) :
			String::EndsWith<CharCase>(str, endpos, sub);
	}
	return !argument.IsSet(Gurax_Symbol(rest))? Value::Bool(rtn) :
		rtn? new Value_String(rtn) : Value::nil();
}

// String#Escape():String:[surround] {block?}
Gurax_DeclareMethod(String, Escape)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(surround));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Applies backslash escaping on characters in the string.\n"
		"If attribute `:surround` is specified, the result contains a pair of single- or double-\n"
		"quotation characters surrounding the string.\n");
}

Gurax_ImplementMethod(String, Escape)
{
	return Value::nil();
}

// String#EscapeHTML():String:[quote] {block?}
Gurax_DeclareMethod(String, EscapeHTML)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(quote));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	DeclareArg("sub", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("pos", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
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
	int pos = args.IsValid()? args.PickInt() : 0;
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
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "len", VTYPE_number);
	DeclareArg(env, "step", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(neat));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that folds the source string by the specified length.\n"
		"\n"
		"The argument `step` specifies the length of advancement for the next folding point.\n"
		"If omitted, it would be the same amount as `len`.\n");
}

Gurax_ImplementMethod(String, Fold)
{
	return Value::nil();
}

// String#Foldw(width:Number):String:[padding] {block?}
Gurax_DeclareMethod(String, Foldw)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "width", VTYPE_number);
	DeclareAttr(Gurax_Symbol(padding));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator that folds the source string by the specified width.\n"
		"\n"
		"This method takes into account the character width based on the specification\n"
		"of East Asian Width.\n");
}

Gurax_ImplementMethod(String, Foldw)
{
	return Value::nil();
}

// String#Format(values*):String:reduce:map
Gurax_DeclareMethod(String, Format)
{
	Declare(VTYPE_String, Flag::Reduce | Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "values", VTYPE_any, OCCUR_ZeroOrMore);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Taking the string instance as a printf-styled formatter string,\n"
		"it converts `values` into a string depending on formatter specifiers in it.\n");
}

Gurax_ImplementMethod(String, Format)
{
	return Value::nil();
}

// String#Left(len?:Number):String:map
Gurax_DeclareMethod(String, Left)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "len", VTYPE_number, OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Extracts the specified length of string from left of the source string.\n"
		"\n"
		"If the argument is omitted, it would return whole the source string.\n");
}

Gurax_ImplementMethod(String, Left)
{
	return Value::nil();
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
	return new Value_String(String::Lower(valueThis.GetString()));
}

// String#Mid(pos:Number, len?:Number):String:map {block?}
Gurax_DeclareMethod(String, Mid)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "pos", VTYPE_number, OCCUR_Once);
	DeclareArg(env, "len", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	return Value::nil();
}

// String#Print(stream?:Stream:w):void
Gurax_DeclareMethod(String, Print)
{
	Declare(VTYPE_Nil, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Prints out the string to the specified `stream`.\n"
		"\n"
		"If the argument is omitted, it would print to the standard output.\n");
}

Gurax_ImplementMethod(String, Print)
{
	return Value::nil();
}

// String#Println(stream?:Stream:w):void
Gurax_DeclareMethod(String, Println)
{
	Declare(VTYPE_Nil, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareArg(env, "stream", VTYPE_stream, OCCUR_ZeroOrOnce, FLAG_Write);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Prints out the string and a line-break to the specified `stream`.\n"
		"\n"
		"If the argument is omitted, it would print to the standard output.\n");
}

Gurax_ImplementMethod(String, Println)
{
	return Value::nil();
}

// String#Replace(match:String, sub:String, count?:number):String:map:[icase] {block?}
Gurax_DeclareMethod(String, Replace)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "match",	VTYPE_string);
	DeclareArg(env, "sub",		VTYPE_string);
	DeclareArg(env, "count",	VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(icase));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	return Value::nil();
}

// String#Replaces(map[]:String, count?:number):String:map:[icase] {block?}
Gurax_DeclareMethod(String, Replaces)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "map",		VTYPE_String, OCCUR_Once, FLAG_ListVar);
	DeclareArg(env, "count",	VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(icase));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	return Value::nil();
}

// String#Right(len?:Number):String:map {block?}
Gurax_DeclareMethod(String, Right)
{
	Declare(VTYPE_String, Flag::Map);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "len", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Extracts the specified length of string from right of the source string.\n"
		"\n"
		"If the argument is omitted, it would return whole the source string.\n");
}

Gurax_ImplementMethod(String, Right)
{
	return Value::nil();
}

// String#Split(sep?:String, count?:number):String:[icase] {block?}
Gurax_DeclareMethod(String, Split)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "sep", VTYPE_String, OCCUR_ZeroOrOnce);
	DeclareArg(env, "count", VTYPE_number, OCCUR_ZeroOrOnce);
	DeclareAttr(Gurax_Symbol(icase));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Creates an iterator generating sub strings extracted from the original one\n"
		"separated by a specified string `sep`.\n"
		"With an attribute `:icase`, character cases are ignored while finding the separator.\n");
}

Gurax_ImplementMethod(String, Split)
{
	return Value::nil();
}

// String#StartsWith(sub:String, pos?:Number):map:[rest,icase]
Gurax_DeclareMethod(String, StartsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("pos", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
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
	int pos = args.IsValid()? args.PickInt() : 0;
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
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(both));
	DeclareAttr(Gurax_Symbol(left));
	DeclareAttr(Gurax_Symbol(right));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
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
	return Value::nil();
}

// String#ToBinary():Binary {block?}
Gurax_DeclareMethod(String, ToBinary)
{
	Declare(VTYPE_Binary, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Converts the string into `binary` instance.");
}

Gurax_ImplementMethod(String, ToBinary)
{
	return Value::nil();
}

// String#ToReader():Stream {block?}
Gurax_DeclareMethod(String, ToReader)
{
	Declare(VTYPE_Stream, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns a `stream` instance that reads the string content as a binary sequence.\n");
}

Gurax_ImplementMethod(String, ToReader)
{
	return Value::nil();
}

// String#ToSymbol():Symbol {block?}
Gurax_DeclareMethod(String, ToSymbol)
{
	Declare(VTYPE_Symbol, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Convers the string into a symbol.\n");
}

Gurax_ImplementMethod(String, ToSymbol)
{
	return Value::nil();
}

// String#ToTemplate():Template:[noindent,lasteol] {block?}
Gurax_DeclareMethod(String, ToTemplate)
{
	Declare(VTYPE_Template, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareAttr(Gurax_Symbol(noindent));
	DeclareAttr(Gurax_Symbol(lasteol));
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Parses the content of the string as a text containing embedded scripts\n"
		"and returns a `template` instance.\n");
}

Gurax_ImplementMethod(String, ToTemplate)
{
	return Value::nil();
}

// String.Translator():void {block}
Gurax_DeclareClassMethod(String, Translator)
{
	Declare(VTYPE_Nil, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Void, FLAG_None);
	DeclareBlock(OCCUR_Once);
#endif
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
	return Value::nil();
}

// String#UnescapeHTML():String {block?}
Gurax_DeclareMethod(String, UnescapeHTML)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en), 
		"Converts escape sequences into readable characters.");
}

Gurax_ImplementMethod(String, UnescapeHTML)
{
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
	return new Value_String(String::Upper(valueThis.GetString()));
}

// String#ZenToHan():String {block?}
Gurax_DeclareMethod(String, ZenToHan)
{
	Declare(VTYPE_String, Flag::None);
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareBlock(OCCUR_ZeroOrOnce);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Converts zenkaku to hankaku characters.");
}

Gurax_ImplementMethod(String, ZenToHan)
{
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
// String#isAlnum
Gurax_DeclareProperty_R(String, isAlnum)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet and digit.");
}

Gurax_ImplementPropertyGetter(String, isAlnum)
{
	return Value::nil();
}

// String#isAlpha
Gurax_DeclareProperty_R(String, isAlpha)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are alphabet.");
}

Gurax_ImplementPropertyGetter(String, isAlpha)
{
	return Value::nil();
}

// String#isDigit()
Gurax_DeclareProperty_R(String, isDigit)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are digit.");
}

Gurax_ImplementPropertyGetter(String, isDigit)
{
	return Value::nil();
}

// String#isEmpty()
Gurax_DeclareProperty_R(String, isEmpty)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string is empty.");
}

Gurax_ImplementPropertyGetter(String, isEmpty)
{
	return Value::nil();
}

// String#isSpace()
Gurax_DeclareProperty_R(String, isSpace)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
#endif
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if all the characters in the string are space.");
}

Gurax_ImplementPropertyGetter(String, isSpace)
{
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
	return new Value_Number(valueThis.GetStringSTL().Length());
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
	return new Value_Number(valueThis.GetStringSTL().Width());
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
	Assign(Gurax_CreateMethod(String, Align));
	Assign(Gurax_CreateMethod(String, Capitalize));
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
	Assign(Gurax_CreateMethod(String, Lower));
	Assign(Gurax_CreateMethod(String, Mid));
	Assign(Gurax_CreateMethod(String, Print));
	Assign(Gurax_CreateMethod(String, Println));
	Assign(Gurax_CreateMethod(String, Replace));
	Assign(Gurax_CreateMethod(String, Replaces));
	Assign(Gurax_CreateMethod(String, Right));
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
}

Value* VType_String::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	return new Value_String(value.ToString());
}

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
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
