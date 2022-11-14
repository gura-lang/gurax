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

${help.ComposePropertyHelp(String, `en)}

# Operator

`String + String` ...

`String + Any` ...

`Any + String` ...

`String == String` ...

`String >= String` ...

`String > String` ...

`String <= String` ...

`String < String` ...

`String <=> String` ...

`String * Number` ...

`String != String` ...

# Cast Operation

${help.ComposeConstructorHelp(String, `en)}

${help.ComposeMethodHelp(String, `en)}
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates a `String` instance converted from `src`. If the argument is omitted, an empty string is created.
)**");
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
// String#Align(width as Number, align as Symbol, padding? as String):map as String
Gurax_DeclareMethod(String, Align)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("align", VTYPE_Symbol, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Align the string to the position specified by a symbol given to the argument `align`
and returns the result.
The symbol involves: ` ``left` for left, ` ``center` for center and ` ``right` for right alignment.

If the string width is narrower than the specified `width`, nothing would be done.

It uses a string specified by the argument `padding` to fill lacking spaces.
If omitted, a white space is used for padding.

This method takes into account the character width based on the specification
of East Asian Width. A kanji-character occupies two characters in width.
)**");
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

// String#Capitalize() as String {block?}
Gurax_DeclareMethod(String, Capitalize)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string that capitalizes the first character.
)**");
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

// String#Center(width as Number, padding? as String):map as String
Gurax_DeclareMethod(String, Center)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Align the string to the center within the specified `width`
and returns the result.

If the string width is narrower than the specified `width`, nothing would be done.

It uses a string specified by the argument `padding` to fill lacking spaces.
If omitted, a white space is used for padding.

This method takes into account the character width based on the specification
of East Asian Width. A kanji-character occupies two characters in width.
)**");
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

// String#Chop():[eol] as String
Gurax_DeclareMethod(String, Chop)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(eol));
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string that removes a last character.

If an attribute `:eol` is specified, only the end-of-line character shall be
removed. In this case, if the end-of-line has a sequence of CR-LF, CR code
shall be removed as well.
)**");
}

Gurax_ImplementMethod(String, Chop)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	bool eolOnlyFlag = argument.IsSet(Gurax_Symbol(eol));
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Chop(eolOnlyFlag));
}

// String#DecodeURI() as String
Gurax_DeclareMethod(String, DecodeURI)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string in which percent-encoded characters are decoded.
)**");
}

Gurax_ImplementMethod(String, DecodeURI)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.DecodeURI());
}

// String#Each():[utf8,utf32] as Iterator {block?}
Gurax_DeclareMethod(String, Each)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(utf8));
	DeclareAttrOpt(Gurax_Symbol(utf32));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns each character in the string.
)**");
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


// String#EachLine():[chop] as Iterator {block?}
// conrresponding to stream#ReadLines()
Gurax_DeclareMethod(String, EachLine)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(chop));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that returns each line of the string.

In default, end-of-line characters are included in the result.
You can eliminates them by specifying `:chop` attribute.
)**");
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

// String#Encode(codec as Codec):Binary {block?}
Gurax_DeclareMethod(String, Encode)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareArg("codec", VTYPE_Codec, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Encodes the string with the given `codec` and return the result as a `Binary`.
)**");
}

Gurax_ImplementMethod(String, Encode)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Codec& codec = args.Pick<Value_Codec>().GetCodec();
	// Function body
	const String& str = valueThis.GetStringSTL();
	Binary dst;
	if (!codec.Encode(dst, str)) return Value::nil();
	return new Value_Binary(dst);
}

// String#EncodeURI() as String
Gurax_DeclareMethod(String, EncodeURI)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string in which non-URIC characters are percent-encoded.
)**");
}

Gurax_ImplementMethod(String, EncodeURI)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.EncodeURI());
}

// String#EndsWith(sub as String, posEnd? as Number):map:[rest,icase]
Gurax_DeclareMethod(String, EndsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rest));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the string ends with the specified suffix `sub`.

The optional argument `posEnd` specifies the bottom position of the string where the matching starts.

If the attribute `:rest` is specified,
it returns the rest part if the string ends with the specified suffix, and `nil` otherewise.

When the attribute `:icase` is specified, character cases are ignored.
)**");
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

// String#Enquote():[auto,q,qq] as String {block?}
Gurax_DeclareMethod(String, Enquote)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(auto_));
	DeclareAttrOpt(Gurax_Symbol(q));
	DeclareAttrOpt(Gurax_Symbol(qq));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Surrounds the given string with quotation marks. Following attributes control
what character is used as the mark:

- `` `auto`` .. double-quote character if the string contains any single-quote and no double-quote characters,
                or single-quote character otherwise.
- `` `q`` .. single-quote character
- `` `qq`` .. double-quote character
)**");
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

// String#EscapeHTML():[quote] as String
Gurax_DeclareMethod(String, EscapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(quote));
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts some characters into HTML entity symbols.
If attribute `:quote` is specified, a double-quotation character would be converted to
an entity symbol \"&quot;\".
)**");
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

// String#Find(sub as String, pos? as Number):map:[icase]
Gurax_DeclareMethod(String, Find)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns the position where the specified sub-string is found in the string.
In the case the sub-string is not found, it returns `nil`.

The argument `pos` specifies the position where the search starts.

With the attribute `:icase`, character cases are ignored while matching.
)**");
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

// String#Fold(len as Number, step? as Number):[neat] as Iterator {block?}
Gurax_DeclareMethod(String, Fold)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("step", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(neat));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that folds the source string by the specified length.

The argument `step` specifies the length of advancement for the next folding point.
If omitted, it would be the same amount as `len`.
)**");
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

// String#Foldw(width as Number, padding? as String) as Iterator {block?}
Gurax_DeclareMethod(String, Foldw)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator that folds the source string by the specified width.

This method takes into account the character width based on the specification
of East Asian Width.
)**");
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

// String#IsAlnum() as Bool
Gurax_DeclareMethod(String, IsAlnum)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if all the characters in the string are alphabet and digit.
)**");
}

Gurax_ImplementMethod(String, IsAlnum)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsAlnum());
}

// String#IsAlpha() as Bool
Gurax_DeclareMethod(String, IsAlpha)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if all the characters in the string are alphabet.
)**");
}

Gurax_ImplementMethod(String, IsAlpha)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsAlpha());
}

// String#IsDigit() as Bool
Gurax_DeclareMethod(String, IsDigit)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if all the characters in the string are digit.
)**");
}

Gurax_ImplementMethod(String, IsDigit)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsDigit());
}

// String#IsEmpty() as Bool
Gurax_DeclareMethod(String, IsEmpty)
{
	Declare(VTYPE_Bool, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the string is empty.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if all the characters in the string are space.
)**");
}

Gurax_ImplementMethod(String, IsSpace)
{
	auto& valueThis = GetValueThis(argument);
	const String& str = valueThis.GetStringSTL();
	return new Value_Bool(str.IsSpace());
}

// String#Left(len? as Number):map as String
Gurax_DeclareMethod(String, Left)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Extracts the specified length of string from left of the source string.

If the argument is omitted, it would return whole the source string.
)**");
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

// String#LJust(width as Number, padding? as String):map as String
Gurax_DeclareMethod(String, LJust)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Align the string to the left within the specified `width`
and returns the result.

If the string width is narrower than the specified `width`, nothing would be done.

It uses a string specified by the argument `padding` to fill lacking spaces.
If omitted, a white space is used for padding.

This method takes into account the character width based on the specification
of East Asian Width. A kanji-character occupies two characters in width.
)**");
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

// String#Lower() as String
Gurax_DeclareMethod(String, Lower)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts each alphabetical character to lower case.
)**");
}

Gurax_ImplementMethod(String, Lower)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Lower());
}

// String#Mid(pos as Number, len? as Number):map as String {block?}
Gurax_DeclareMethod(String, Mid)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pos", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Extracts the specified length of string from the position `pos` and returns the result.

If the argument `len` is omitted, it returns a string from `pos` to the end.
The number of an argument `pos` starts from zero.

Below are examples:

    'Hello world'.mid(3, 2) // 'lo'
    'Hello world'.mid(5)    // 'world'
)**");
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

// String#Render(stream?:w as Stream):void
Gurax_DeclareMethod(String, Render)
{
	Declare(VTYPE_Nil, Flag::None);
	DeclareArg("stream", VTYPE_Stream, ArgOccur::ZeroOrOnce, ArgFlag::StreamW);
	AddHelp(Gurax_Symbol(en), u8R"**(
Prints out the string to the specified `stream`.

If the argument is omitted, it would be rendered to the standard output.
)**");
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

// String#Replace(match as String, sub as String, count? as Number):map:[icase] as String {block?}
Gurax_DeclareMethod(String, Replace)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("match", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Replaces sub strings that matches the string `match` with a string specified by `sub`
and returns the result.

The argument `count` limits the maximum number of substitution.
If omitted, there's no limit of the work.

With an attribute `:icase`, character cases are ignored while matching strings.

If `block` is specified, it would be evaluated with a block parameter `|result as String, replaced as Bool|`,
where `result` is the result string and `replaced` indicates if there is any change
between the result and its original string.
In this case, the block's result would become the function's returned value.
)**");
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

// String#ReplaceM(map[] as String, count? as Number):map:[icase] as String {block?}
Gurax_DeclareMethod(String, ReplaceM)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("map", VTYPE_String, ArgOccur::Once, ArgFlag::ListVar);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Replaces string parts according to a list of pairs of a matching and a substituting string
and returns the result.

The argument `map` is a `list` of match-substitution paris like `[match1, sub1, match2, sub2, ..]`
with which a sub string that matches `match`*n* would be replaced with `sub`*n*.

The argument `count` limits the maximum number of substitution.
If omitted, there's no limit of the work.

With an attribute `:icase`, character cases are ignored while matching strings.

If `block` is specified, it would be evaluated with a block parameter `|result as String, replaced as Bool|`,
where `result` is the result string and `replaced` indicates if there is any change
between the result and its original string.
In this case, the block's result would become the function's returned value.
)**");
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

// String#Right(len? as Number):map as String {block?}
Gurax_DeclareMethod(String, Right)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("len", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Extracts the specified length of string from right of the source string.

If the argument is omitted, it would return whole the source string.
)**");
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

// String#RJust(width as Number, padding? as String):map as String
Gurax_DeclareMethod(String, RJust)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("width", VTYPE_Number, ArgOccur::Once, ArgFlag::None);
	DeclareArg("padding", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Align the string to the right within the specified `width`
and returns the result.

If the string width is narrower than the specified `width`, nothing would be done.

It uses a string specified by the argument `padding` to fill lacking spaces.
If omitted, a white space is used for padding.

This method takes into account the character width based on the specification
of East Asian Width. A kanji-character occupies two characters in width.
)**");
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

// String#Split(sep? as String, count? as Number):[icase] as String {block?}
Gurax_DeclareMethod(String, Split)
{
	Declare(VTYPE_String, Flag::None);
	DeclareArg("sep", VTYPE_String, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("count", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Creates an iterator generating sub strings extracted from the original one
separated by a specified string `sep`.
With an attribute `:icase`, character cases are ignored while finding the separator.
)**");
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

// String#StartsWith(sub as String, pos? as Number):map:[rest,icase]
Gurax_DeclareMethod(String, StartsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(rest));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns `true` if the string starts with `sub`.

If attribute `:rest` is specified,
it returns the rest part if the string starts with prefix, or `nil` otherewise.
You can specify a top position for the matching by an argument `pos`.

With an attribute `:icase`, character cases are ignored while matching.
)**");
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

// String#Strip() as String {block?}
Gurax_DeclareMethod(String, Strip)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string that removes space characters on the both side.
)**");
}

Gurax_ImplementMethod(String, Strip)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(true, true));
}

// String#StripLeft() as String {block?}
Gurax_DeclareMethod(String, StripLeft)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string that removes space characters on the left side.
)**");
}

Gurax_ImplementMethod(String, StripLeft)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(true, false));
}

// String#StripRight() as String {block?}
Gurax_DeclareMethod(String, StripRight)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a string that removes space characters on the right side.
)**");
}

Gurax_ImplementMethod(String, StripRight)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Strip(false, true));
}

// String#Template():[noIndent,lastEol] as Template {block?}
Gurax_DeclareMethod(String, Template)
{
	//Declare(VTYPE_Template, Flag::None);
	DeclareAttrOpt(Gurax_Symbol(noIndent));
	DeclareAttrOpt(Gurax_Symbol(lastEol));
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Parses the content of the string as a text containing embedded scripts
and returns a `Template` instance.
)**");
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
	if (!pTmpl->ParseString(str, autoIndentFlag, appendLastEOLFlag) ||
		!pTmpl->PrepareAndCompose()) return Value::nil();
	return argument.ReturnValue(processor, new Value_Template(pTmpl.release()));
}

// String#ToBinary() as Binary {block?}
Gurax_DeclareMethod(String, ToBinary)
{
	Declare(VTYPE_Binary, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts the string into `binary` instance.
)**");
}

Gurax_ImplementMethod(String, ToBinary)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_Binary(Binary(str.data(), str.size()));
}

// String#ToNumber() as Number {block?}
Gurax_DeclareMethod(String, ToNumber)
{
	Declare(VTYPE_Number, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts the string into `Number` instance.
)**");
}

Gurax_ImplementMethod(String, ToNumber)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	Bool successFlag;
	Double num = str.ToDouble(&successFlag);
	if (!successFlag) {
		Error::Issue(ErrorType::FormatError, "invalid format of a number");
		return Value::nil();
	}
	return new Value_Number(num);
}

// String#ToReader() as Stream {block?}
Gurax_DeclareMethod(String, ToReader)
{
	Declare(VTYPE_Stream, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a `Stream` instance that reads the string content as a binary sequence.
)**");
}

Gurax_ImplementMethod(String, ToReader)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	RefPtr<Stream> pStream(new Stream_StringReader(valueThis.GetStringReferable().Reference()));
	return argument.ReturnValue(processor, new Value_Stream(pStream.release()));
}

// String#ToSymbol() as Symbol {block?}
Gurax_DeclareMethod(String, ToSymbol)
{
	Declare(VTYPE_Symbol, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Convers the string into a symbol.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
Register a procedure evaluated when a string literal
appears with a suffix symbol \"`$`\",
which is meant to translate the string into another language.

The procedure is described in `block` takes a block parameter `|str as String|`
where `str` is the original String, and is expected to return a string
translated from the original.
)**");
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

// String#UnescapeHTML() as String
Gurax_DeclareMethod(String, UnescapeHTML)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts escape sequences into readable characters.
)**");
}

Gurax_ImplementMethod(String, UnescapeHTML)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.UnescapeHTML());
}

// String#Upper() as String
Gurax_DeclareMethod(String, Upper)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts each alphabetical character to upper case.
)**");
}

Gurax_ImplementMethod(String, Upper)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Function body
	const String& str = valueThis.GetStringSTL();
	return new Value_String(str.Upper());
}

// String#ZenToHan() as String {block?}
Gurax_DeclareMethod(String, ZenToHan)
{
	Declare(VTYPE_String, Flag::None);
	DeclareBlock(BlkOccur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"**(
Converts zenkaku to hankaku characters.
)**");
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
// String#bytes
Gurax_DeclareProperty_R(String, bytes)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The string's memory size in bytes.
)**");
}

Gurax_ImplementPropertyGetter(String, bytes)
{
	const String& str = GetValueThis(valueTarget).GetStringSTL();
	return new Value_Number(str.size());
}

// String#first
Gurax_DeclareProperty_R(String, first)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The first character in the string. Returns an empty string if the string is empty.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
The last character in the string. Returns an empty string if the string is empty.
)**");
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
	AddHelp(Gurax_Symbol(en), u8R"**(
The number of characters in the string.
)**");
}

Gurax_ImplementPropertyGetter(String, len)
{
	const String& str = GetValueThis(valueTarget).GetStringSTL();
	return new Value_Number(str.Length());
}

// String#p
Gurax_DeclareProperty_R(String, p)
{
	Declare(VTYPE_Pointer, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
Returns a `pointer` instance that accesses the string.
)**");
}

Gurax_ImplementPropertyGetter(String, p)
{
	auto& valueThis = GetValueThis(valueTarget);
	return new Value_Pointer(new Pointer_String(valueThis.GetStringReferable().Reference()));
}

// String#width
Gurax_DeclareProperty_R(String, width)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(
The string's width when displayed with a fixed-width font.
)**");
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

// String <=> String
Gurax_ImplementOpBinary(Cmp, String, String)
{
	const String& strL = Value_String::GetStringSTL(valueL);
	const String& strR = Value_String::GetStringSTL(valueR);
	return new Value_Number(strL.Compare(strR));
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
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
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
	Assign(Gurax_CreateMethod(String, ToNumber));
	Assign(Gurax_CreateMethod(String, ToReader));
	Assign(Gurax_CreateMethod(String, ToSymbol));
	Assign(Gurax_CreateMethod(String, Translator));
	Assign(Gurax_CreateMethod(String, UnescapeHTML));
	Assign(Gurax_CreateMethod(String, Upper));
	Assign(Gurax_CreateMethod(String, ZenToHan));
	// Assignment of property
	Assign(Gurax_CreateProperty(String, bytes));
	Assign(Gurax_CreateProperty(String, first));
	Assign(Gurax_CreateProperty(String, last));
	Assign(Gurax_CreateProperty(String, len));
	Assign(Gurax_CreateProperty(String, p));
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
	Gurax_AssignOpBinary(Cmp, String, String);
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
	String strEntity = GetStringSTL();
	if (ss.IsBracket()) return ToStringGeneric(ss, strEntity.EnquoteAuto());
	if (ss.IsQuoteString()) strEntity = strEntity.EnquoteAuto();
	if (ss.IsDQuoteString()) strEntity = strEntity.Enquote('"');
	return strEntity;
}

bool Value_String::Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const
{
	return formatter.PutAlignedString(formatterFlags, GetString(), formatterFlags.precision);
}

bool Value_String::DoEmptyIndexGet(Value** ppValue) const
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return Value::undefined();
}

bool Value_String::DoEmptyIndexSet(RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "empty-indexing access is not supported");
	return false;
}

bool Value_String::DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const
{
	const String& str = GetString();
	size_t idx = 0;
	if (!Index::GetIndexNumber(valueIndex, str.size(), &idx)) return false;
	*ppValue = new Value_String(str.PickChar(idx));
	return true;
}

bool Value_String::DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue)
{
	Error::Issue(ErrorType::IndexError, "modification by index access is not permitted");
	return false;
}

Iterator* Value_String::DoGenIterator() const
{
	// Arguments
	VType_String::Iterator_Each::Type type = VType_String::Iterator_Each::Type::String;
	// Function body
	const StringReferable& str = GetStringReferable();
	return new VType_String::Iterator_Each(str.Reference(), type);
}

}
