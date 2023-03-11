//==============================================================================
// VType_Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"""(
# Overview

# Predefined Variable

${help.ComposePropertyHelp(re.Pattern, `en)}

# Operator

# Cast Operation

${help.ComposeConstructorHelp(re.Pattern, `en)}

${help.ComposeMethodHelp(re.Pattern, `en)}
)""";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// re.Pattern(pattern as String):map:[icase,multiLine] {block?}
Gurax_DeclareConstructor(Pattern)
{
	Declare(VTYPE_Pattern, Flag::Map);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareAttrOpt(Gurax_Symbol(icase));
	DeclareAttrOpt(Gurax_Symbol(multiLine));
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates a `re.pattern` instance from the given pattern string.

Following attributes would customize some traits of the pattern:

- `:icase` .. Ignores character cases.
- `:multiLine` .. Matches \"`.`\" with a line break.
)""");
}

Gurax_ImplementConstructor(Pattern)
{
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	bool icaseFlag = argument.IsSet(Gurax_Symbol(icase));
	bool multiLineFlag = argument.IsSet(Gurax_Symbol(multiLine));
	// Function body
	RefPtr<Pattern> pPattern(new Pattern());
	if (!pPattern->Prepare(pattern, icaseFlag, multiLineFlag)) return Value::nil();
	return argument.ReturnValue(processor, new Value_Pattern(pPattern.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// re.Pattern#Match(str as String, pos? as Number, posEnd? as Number):map {block?}
Gurax_DeclareMethod(Pattern, Match)
{
	Declare(VTYPE_Match, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Applies a pattern matching to the given string and returns a `re.Match` instance
if the matching successes. If not, it would return `nil`.

The argument `pos` specifies the starting position for matching process.
If omitted, it starts from the beginning of the string.

The argument `endpos` specifies the ending position for matching process.
If omitted, it would be processed until the end of the string.
)""");
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
	return argument.ReturnValue(processor, new Value_Match(pMatch.release()));
}

// re.Pattern#Sub(str:String, replace, cnt?:Number):map {block?}
Gurax_DeclareMethod(Pattern, Sub)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Substitutes strings that matches `pattern` with the specified replacer.

The argument `replace` takes a `string` or `function`.

If a `string` is specified, it would be used as a substituting string,
in which you can use macros `\\0`, `\\1`, `\\2` .. to refer to matched groups.

If a `function` is specified, it would be called with an argument `m:re.Match`
and is expected to return a string for subsitution.

The argument `count` specifies the maximum number of substitutions.
If omitted, no limit would be applied.
)""");
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
	RefPtr<Value> pValueRtn(new Value_String(strRtn));
	const Expr_Block* pExprOfBlock = argument.GetExprOfBlock();
	return pExprOfBlock?
		pExprOfBlock->EvalEasy(processor, pValueRtn.release(), new Value_Number(nReplaced)) :
		pValueRtn.release();
}

// re.Pattern#Split(str as String, cntMax? as Number):map {block?}
Gurax_DeclareMethod(Pattern, Split)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cntMax", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that splits the source string with the specified pattern.

The argument `cntMax` specifies the maximum number for splitting.
If omitted, no limit would be applied.
)""");
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
	return argument.ReturnIterator(processor, pIterator.release());
}

// re.Pattern#Scan(str as String, pos? as Number, posEnd? as Number):map {block?}
Gurax_DeclareMethod(Pattern, Scan)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(
Creates an iterator that returns strings that match the specified pattern.

The argument `pos` specifies the starting position for matching process.
If omitted, it starts from the beginning of the string.

The argument `posEnd` specifies the ending position for matching process.
If omitted, it would be processed until the end of the string.
)""");
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
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// VType_Pattern
//------------------------------------------------------------------------------
VType_Pattern VTYPE_Pattern("Pattern");

void VType_Pattern::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelp(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Pattern));
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

String Value_Pattern::ToString(const StringStyle& ss) const
{
	return ToStringGeneric(ss, GetPattern().ToString(ss));
}

Gurax_EndModuleScope(re)
