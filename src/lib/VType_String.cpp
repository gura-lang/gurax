//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// String#Align(width:number, padding:string => ' '):map:[center,left,right] {block?}
Gurax_DeclareMethod(String, Align)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_Map);
	DeclareArg(env, "width", VTYPE_number);
	DeclareArg(env, "padding", VTYPE_string, OCCUR_Once, FLAG_None, 0, new Expr_Value(Value(" ")));
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

// String#Capitalize() {block?}
Gurax_DeclareMethod(String, Capitalize)
{
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

// String#Chop(suffix*:string):[eol,icase] {block?}
Gurax_DeclareMethod(String, Chop)
{
#if 0
	SetFuncAttr(VTYPE_any, RSLTMODE_Normal, FLAG_None);
	DeclareArg(env, "suffix", VTYPE_string, OCCUR_ZeroOrMore);
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

// String#DecodeURI() {block?}
Gurax_DeclareMethod(String, DecodeURI)
{
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

// String#Each():[utf8,utf32] {block?}
Gurax_DeclareMethod(String, Each)
{
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

// String#EachLine(nLines?:number):[chop] {block?}
// conrresponding to file#readlines()
Gurax_DeclareMethod(String, EachLine)
{
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

// String#Embed(dst?:stream:w):[noindent,lasteol]
Gurax_DeclareMethod(String, Embed)
{
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

// String#Encode(codec:Codec) {block?}
Gurax_DeclareMethod(String, Encode)
{
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

// String#EncodeURI() {block?}
Gurax_DeclareMethod(String, EncodeURI)
{
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

// String#ToBinary() {block?}
Gurax_DeclareMethod(String, ToBinary)
{
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

// String#Upper()
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

//------------------------------------------------------------------------------
// Implementation of property
//------------------------------------------------------------------------------
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
	Assign(Gurax_CreateMethod(String, EndsWith));
	Assign(Gurax_CreateMethod(String, Find));
	Assign(Gurax_CreateMethod(String, Lower));
	Assign(Gurax_CreateMethod(String, StartsWith));
	Assign(Gurax_CreateMethod(String, Upper));
	// Assignment of property
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
