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
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	const char* str = args.PickString();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(str));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

//-----------------------------------------------------------------------------
// Implementation of method
//-----------------------------------------------------------------------------
// Match#Group(index):map {block?}
Gurax_DeclareMethod(Match, Group)
{
	Declare(VTYPE_Group, Flag::Map);
	DeclareArg("index", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Match, Group)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Match& match = valueThis.GetMatch();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	return Value::nil();
}

// Match#Groups() {block?}
Gurax_DeclareMethod(Match, Groups)
{
	Declare(VTYPE_Iterator, Flag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementMethod(Match, Groups)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	Match& match = valueThis.GetMatch();
	// Arguments
	ArgPicker args(argument);
	const Value& value = args.PickValue();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Group(match.Reference()));
	return ReturnIterator(processor, argument, pIterator.release());
}

//------------------------------------------------------------------------------
// VType_Match
//------------------------------------------------------------------------------
VType_Match VTYPE_Match("Match");

void VType_Match::DoPrepare(Frame& frameOuter)
{
	// VType settings
	SetAttrs(VTYPE_Object, Flag::Immutable);
	SetConstructor(Gurax_CreateFunction(Match));
	// Assignment of method
	Assign(Gurax_CreateMethod(Match, Group));
	Assign(Gurax_CreateMethod(Match, Groups));
}

//------------------------------------------------------------------------------
// Value_Match
//------------------------------------------------------------------------------
VType& Value_Match::vtype = VTYPE_Match;

Value* Value_Match::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		const Value* pValueIndex = valuesIndex.front();
		if (pValueIndex->IsType(VTYPE_Number)) {
			int iGroup = Value_Number::GetNumber<Int>(*pValueIndex);
			if (iGroup < 0 || iGroup >= GetMatch().CountGroups()) {
				Error::Issue(ErrorType::IndexError, "index is out of range");
				return nullptr;
			}
			return new Value_Group(GetMatch().CreateGroup(iGroup));
		} else if (pValueIndex->IsType(VTYPE_String)) {
			
		} else {
			Error::Issue(ErrorType::ValueError, "string or number value must be specified");
			return nullptr;
		}
	} else {
	}
	return Value::nil();
}

Gurax_EndModuleScope(re)
