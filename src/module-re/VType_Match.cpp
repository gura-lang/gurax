//==============================================================================
// VType_Match.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Help
//------------------------------------------------------------------------------
static const char* g_docHelp_en = u8R"**(
# Overview

# Predefined Variable

# Property

# Operator

# Cast Operation

# Constructor

# Method
)**";

//------------------------------------------------------------------------------
// Implementation of constructor
//------------------------------------------------------------------------------
// re.Match(pattern:Pattern, str:String):map {block?}
Gurax_DeclareConstructor(Match)
{
	Declare(VTYPE_Pattern, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("str", VTYPE_String, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"Executes a pattern matching and returns `re.Match` instance as its result.\n");
}

Gurax_ImplementConstructor(Match)
{
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	const char* str = args.PickString();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(str));
	if (!pMatch) return Value::nil();
	return argument.ReturnValue(processor, new Value_Match(pMatch.release()));
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
	// Arguments
	ArgPicker args(argument);
	const Value& valueIndex = args.PickValue();
	// Function body
	return valueThis.GetValueOfGroup(valueIndex);
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
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Group(match.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//-----------------------------------------------------------------------------
// Implementation of property
//-----------------------------------------------------------------------------
// re.Match#begin
Gurax_DeclareProperty_R(Match, begin)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Match, begin)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Match& match = valueThis.GetMatch();
	return new Value_Number(match.GetPosBegin());
}

// re.Match#end
Gurax_DeclareProperty_R(Match, end)
{
	Declare(VTYPE_Number, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Match, end)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Match& match = valueThis.GetMatch();
	return new Value_Number(match.GetPosEnd());
}

// re.Match#source
Gurax_DeclareProperty_R(Match, source)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Match, source)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Match& match = valueThis.GetMatch();
	return new Value_String(match.GetSourceString());
}

// re.Match#string
Gurax_DeclareProperty_R(Match, string)
{
	Declare(VTYPE_String, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementPropertyGetter(Match, string)
{
	auto& valueThis = GetValueThis(valueTarget);
	const Match& match = valueThis.GetMatch();
	return new Value_String(match.GetString());
}

//------------------------------------------------------------------------------
// VType_Match
//------------------------------------------------------------------------------
VType_Match VTYPE_Match("Match");

void VType_Match::DoPrepare(Frame& frameOuter)
{
	// Add help
	AddHelpTmpl(Gurax_Symbol(en), g_docHelp_en);
	// Declaration of VType
	Declare(VTYPE_Object, Flag::Immutable, Gurax_CreateConstructor(Match));
	// Assignment of method
	Assign(Gurax_CreateMethod(Match, Group));
	Assign(Gurax_CreateMethod(Match, Groups));
	// Assignment of property
	Assign(Gurax_CreateProperty(Match, begin));
	Assign(Gurax_CreateProperty(Match, end));
	Assign(Gurax_CreateProperty(Match, source));
	Assign(Gurax_CreateProperty(Match, string));
}

//------------------------------------------------------------------------------
// Value_Match
//------------------------------------------------------------------------------
VType& Value_Match::vtype = VTYPE_Match;

Value* Value_Match::DoIndexGet(const Index& index) const
{
	const ValueList& valuesIndex = index.GetValueOwner();
	if (valuesIndex.size() == 1) {
		return GetValueOfGroupString(*valuesIndex.front());
	} else {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		for (const Value* pValueIndex : valuesIndex) {
			RefPtr<Value> pValue(GetValueOfGroupString(*pValueIndex));
			if (Error::IsIssued()) return Value::nil();
			pValueOwner->push_back(pValue.release());
		}
		return new Value_List(pValueOwner.release());
	}
	return Value::nil();
}

Value* Value_Match::GetValueOfGroup(const Value& valueIndex) const
{
	if (valueIndex.IsType(VTYPE_Number)) {
		int iGroup = Value_Number::GetNumber<int>(valueIndex);
		if (iGroup < 0 || iGroup >= GetMatch().CountGroups()) {
			Error::Issue(ErrorType::IndexError, "index is out of range");
			return nullptr;
		}
		return new Value_Group(GetMatch().CreateGroup(iGroup));
	} else if (valueIndex.IsType(VTYPE_String)) {
		const char* name = Value_String::GetString(valueIndex);
		int iGroup = GetMatch().LookupGroupNum(name);
		if (iGroup < 0) {
			Error::Issue(ErrorType::IndexError, "the name '%s' is not found", name);
			return nullptr;
		}
		return new Value_Group(GetMatch().CreateGroup(iGroup));
	} else {
		Error::Issue(ErrorType::ValueError, "string or number value must be specified");
		return nullptr;
	}
}

Value* Value_Match::GetValueOfGroupString(const Value& valueIndex) const
{
	if (valueIndex.IsType(VTYPE_Number)) {
		int iGroup = Value_Number::GetNumber<int>(valueIndex);
		if (iGroup < 0 || iGroup >= GetMatch().CountGroups()) {
			Error::Issue(ErrorType::IndexError, "index is out of range");
			return nullptr;
		}
		return new Value_String(GetMatch().GetGroupString(iGroup));
	} else if (valueIndex.IsType(VTYPE_String)) {
		const char* name = Value_String::GetString(valueIndex);
		int iGroup = GetMatch().LookupGroupNum(name);
		if (iGroup < 0) {
			Error::Issue(ErrorType::IndexError, "the name '%s' is not found", name);
			return nullptr;
		}
		return new Value_String(GetMatch().GetGroupString(iGroup));
	} else {
		Error::Issue(ErrorType::ValueError, "string or number value must be specified");
		return nullptr;
	}
}

Gurax_EndModuleScope(re)
