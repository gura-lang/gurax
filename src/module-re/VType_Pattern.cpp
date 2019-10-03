//==============================================================================
// VType_Pattern.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// re.Pattern(pattern:String):map {block?}
Gurax_DeclareFunction(Pattern)
{
	Declare(VTYPE_Pattern, Flag::Map);
	DeclareArg("pattern", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Creates a `re.Pattern` instance from a pattern string.\n");
}

Gurax_ImplementFunction(Pattern)
{
	// Arguments
	ArgPicker args(argument);
	const char* pattern = args.PickString();
	// Function body
	RefPtr<Pattern> pPattern(new Pattern());
	if (!pPattern->Prepare(pattern)) return Value::nil();
	return ReturnValue(processor, argument, new Value_Pattern(pPattern.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Pattern#Match(str:String):map {block?}
Gurax_DeclareMethod(Pattern, Match)
{
	Declare(VTYPE_List, Flag::Map);
	DeclareArg("value", VTYPE_Any, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Adds values to the list.");
}

Gurax_ImplementMethod(Pattern, Match)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Pattern& pattern = valueThis.GetPattern();
	// Arguments
	ArgPicker args(argument);
	const char* str = args.PickString();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(str));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
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
}

Value* VType_Pattern::DoCastFrom(const Value& value, DeclArg::Flags flags) const
{
	if (value.IsType(VTYPE_String)) {
		const char* pattern = Value_String::GetString(value);
		RefPtr<Pattern> pPattern(new Pattern());
		if (!pPattern->Prepare(pattern)) return nullptr;
		return new Value_Pattern(pPattern.release());
	}
	return nullptr;
}

//------------------------------------------------------------------------------
// Value_Pattern
//------------------------------------------------------------------------------
VType& Value_Pattern::vtype = VTYPE_Pattern;

Gurax_EndModuleScope(re)
