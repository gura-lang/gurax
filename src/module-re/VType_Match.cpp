//==============================================================================
// VType_Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// re.Match(pattern:Pattern, str:String):map {block?}
Gurax_DeclareFunction(Match)
{
	Declare(VTYPE_Pattern, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Executes a pattern matching and returns `re.Match` instance as its result.\n");
}

Gurax_ImplementFunction(Match)
{
	// Arguments
	ArgPicker args(argument);
	//const Pattern& pattern = args.PickValue<Value_Pattern>().GetPattern();
	// Function body
	//return ReturnValue(processor, argument, new Value_Pattern(pPattern.release()));
	return Value::nil();
}

//------------------------------------------------------------------------------
// VType_Match
//------------------------------------------------------------------------------
VType_Match VTYPE_Match("Match");

void VType_Match::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
}

//------------------------------------------------------------------------------
// Value_Match
//------------------------------------------------------------------------------
VType& Value_Match::vtype = VTYPE_Match;

Gurax_EndModuleScope(re)
