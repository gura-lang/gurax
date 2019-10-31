//==============================================================================
// VType_Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// re.Pattern(pattern:String):map:[icase,multiline] {block?}
Gurax_DeclareFunction(Pattern)
{
	Declare(VTYPE_Pattern, Flag::Map);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareAttrOpt(Gurax_Symbol(multiline));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `re.pattern` instance from the given pattern string.\n"
		"\n"
		"Following attributes would customize some traits of the pattern:\n"
		"\n"
		"- `:icase` .. Ignores character cases.\n"
		"- `:multiline` .. Matches \"`.`\" with a line break.\n");
}

Gurax_ImplementFunction(Pattern)
{
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	bool multilineFlag = argument.IsSet(Gurax_Symbol(multiline));
	// Function body
	RefPtr<Pattern> pPattern(new Pattern());
	if (!pPattern->Prepare(pattern, icaseFlag, multilineFlag)) return Value::nil();
	return ReturnValue(processor, argument, new Value_Pattern(pPattern.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Pattern#Match(str:String, pos?:Number, posEnd?:Number):map {block?}
Gurax_DeclareMethod(Pattern, Match)
{
	Declare(VTYPE_Match, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Applies a pattern matching to the given string and returns a `re.Match` instance\n"
		"if the matching successes. If not, it would return `nil`.\n"
		"\n"
		"The argument `pos` specifies the starting position for matching process.\n"
		"If omitted, it starts from the beginning of the string.\n"
		"\n"
		"The argument `endpos` specifies the ending position for matching process.\n"
		"If omitted, it would be processed until the end of the string.\n");
}

Gurax_ImplementMethod(Pattern, Match)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Pattern& pattern = valueThis.GetPattern();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	int posEnd = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(str, pos, posEnd));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

// Pattern#Sub(pattern:Pattern, replace, cnt?:Number):map {block?}
Gurax_DeclareMethod(Pattern, Sub)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Substitutes strings that matches `pattern` with the specified replacer.\n"
		"\n"
		"The argument `replace` takes a `string` or `function`.\n"
		"\n"
		"If a `string` is specified, it would be used as a substituting string,\n"
		"in which you can use macros `\\0`, `\\1`, `\\2` .. to refer to matched groups.\n"
		"\n"
		"If a `function` is specified, it would be called with an argument `m:re.Match`\n"
		"and is expected to return a string for subsitution.\n"
		"\n"
		"The argument `count` specifies the maximum number of substitutions.\n"
		"If omitted, no limit would be applied.\n");
}

Gurax_ImplementMethod(Pattern, Sub)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Pattern& pattern = valueThis.GetPattern();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	Value& replace = args.PickValue();
	int cnt = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	// Function body
	String strRtn;
	int nReplaced = 0;
	if (replace.IsType(VTYPE_String)) {
		strRtn = pattern.ReplaceByString(str, Value_String::GetString(replace), cnt, nReplaced);
	} else if (replace.IsType(VTYPE_Function)) {
		strRtn = pattern.ReplaceByFunction(str, processor, Value_Function::GetFunction(replace), cnt, nReplaced);
	} else {
		Error::Issue(ErrorType::ValueError, "string or function must be specified");
		return Value::nil();
	}
	return ReturnValue(processor, argument, new Value_String(strRtn), new Value_Bool(nReplaced > 0));
}

// Pattern#Split(str:String, cntMax?:Number):map {block?}
Gurax_DeclareMethod(Pattern, Split)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cntMax", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that splits the source string with the specified pattern.\n"
		"\n"
		"The argument `cntMax` specifies the maximum number for splitting.\n"
		"If omitted, no limit would be applied.\n");
}

Gurax_ImplementMethod(Pattern, Split)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Pattern& pattern = valueThis.GetPattern();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	int cntMax = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Split(pattern.Reference(), str, cntMax));
	return ReturnIterator(processor, argument, pIterator.release());
}

// Pattern#Scan(str:String, pos?:Number, posEnd?:Number):map {block?}
Gurax_DeclareMethod(Pattern, Scan)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns strings that match the specified pattern.\n"
		"\n"
		"The argument `pos` specifies the starting position for matching process.\n"
		"If omitted, it starts from the beginning of the string.\n"
		"\n"
		"The argument `posEnd` specifies the ending position for matching process.\n"
		"If omitted, it would be processed until the end of the string.\n");
}

Gurax_ImplementMethod(Pattern, Scan)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Pattern& pattern = valueThis.GetPattern();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	int posEnd = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Scan(pattern.Reference(), new StringReferable(str), pos, posEnd));
	return ReturnIterator(processor, argument, pIterator.release());
}

//------------------------------------------------------------------------------
// VType_Pattern
//------------------------------------------------------------------------------
VType_Pattern VTYPE_Pattern("Pattern");

void VType_Pattern::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Pattern));
	// Assignment of method
	Assign(Gurax_CreateMethod(Pattern, Match));
	Assign(Gurax_CreateMethod(Pattern, Sub));
	Assign(Gurax_CreateMethod(Pattern, Split));
	Assign(Gurax_CreateMethod(Pattern, Scan));
}

Value* VType_Pattern::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* pattern = Value_String::GetString(value);
		RefPtr<Pattern> pPattern(new Pattern());
		if (!pPattern->Prepare(pattern, false, false)) return nullptr;
		return new Value_Pattern(pPattern.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Pattern
//------------------------------------------------------------------------------
VType& Value_Pattern::vtype = VTYPE_Pattern;

Gurax_EndModuleScope(re)
