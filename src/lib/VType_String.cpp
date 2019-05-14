//==============================================================================
// VType_String.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Implementation of method
//------------------------------------------------------------------------------
// String#EndsWith(sub:String, endpos?:Number):map:[rest,icase]
Gurax_DeclareMethod(String, EndsWith)
{
	Declare(VTYPE_Any, Flag::Map);
	DeclareArg("sub", VTYPE_String, DeclArg::Occur::Once, DeclArg::Flag::None, nullptr);
	DeclareArg("endpos", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
	DeclareAttrOpt(Gurax_Symbol(rest));
	DeclareAttrOpt(Gurax_Symbol(icase));
	AddHelp(
		Gurax_Symbol(en),
		"Returns `true` if the string ends with suffix.\n"
		"\n"
		"If attribute `:rest` is specified,\n"
		"it returns the rest part if the string ends with suffix, or `nil` otherewise.\n"
		"You can specify a bottom position for the matching by an argument `endpos`.\n"
		"\n"
		"With an attribute `:icase`, character cases are ignored while matching.");
}

Gurax_ImplementMethod(String, EndsWith)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	const char* sub = args.PickString();
	int endpos = args.IsDefined()? args.PickInt() : -1;
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
	DeclareArg("endpos", VTYPE_Number, DeclArg::Occur::ZeroOrOnce, DeclArg::Flag::None, nullptr);
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
	int pos = args.IsDefined()? args.PickInt() : 0;
	// Function body
	const String& str = valueThis.GetStringSTL();
	String::const_iterator pStr = str.Forward(pos);
	String::const_iterator pFound = argument.IsSet(Gurax_Symbol(icase))?
		str.Find<CharICase>(pStr, sub) : str.Find<CharCase>(pStr, sub);
	return (pFound == str.end())? Value::nil() : new Value_Number(str.CalcPos(pFound));
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
	int pos = args.IsDefined()? args.PickInt() : 0;
	// Function body
	const char* str = valueThis.GetString();
	if (pos > 0) str = String::Forward(str, pos);
	const char* rtn = argument.IsSet(Gurax_Symbol(icase))?
		String::StartsWith<CharICase>(str, sub) :
		String::StartsWith<CharCase>(str, sub);
	return !argument.IsSet(Gurax_Symbol(rest))? Value::Bool(rtn) :
		rtn? new Value_String(rtn) : Value::nil();
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
		"Returns the number of characters in the string.");
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
		"Returns the string's width when displayed with a fixed-width font.");
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
	frameOuter.Assign(*this);
	// Assignment of method
	Assign(Gurax_CreateMethod(String, EndsWith));
	Assign(Gurax_CreateMethod(String, Find));
	Assign(Gurax_CreateMethod(String, StartsWith));
	// Assignment of property
	Assign(Gurax_CreateProperty(String, len));
	Assign(Gurax_CreateProperty(String, width));
}

Value* VType_String::DoCastFrom(const Value& value) const
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
