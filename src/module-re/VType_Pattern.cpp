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

//------------------------------------------------------------------------------
// VType_Pattern
//------------------------------------------------------------------------------
VType_Pattern VTYPE_Pattern("Pattern");

void VType_Pattern::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Pattern));
}

//------------------------------------------------------------------------------
// Value_Pattern
//------------------------------------------------------------------------------
VType& Value_Pattern::vtype = VTYPE_Pattern;

Gurax_EndModuleScope(re)
