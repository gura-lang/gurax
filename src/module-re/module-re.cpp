//==============================================================================
// module-re.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(re)

//------------------------------------------------------------------------------
// Implementation of method for String
//------------------------------------------------------------------------------
// String#Match(pattern as re.Pattern, pos? as Number, posEnd? as Number):map {block?}
Gurax_DeclareMethod(String, Match)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	LinkHelp(VTYPE_Pattern, GetSymbol());
}

Gurax_ImplementMethod(String, Match)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const char* str = valueThis.GetString();
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	int posEnd = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(str, pos, posEnd));
	if (!pMatch) return Value::nil();
	return argument.ReturnValue(processor, new Value_Match(pMatch.release()));
}

// String#Sub(pattern as Pattern, replace, cnt? as Number):map {block?}
Gurax_DeclareMethod(String, Sub)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	LinkHelp(VTYPE_Pattern, GetSymbol());
}

Gurax_ImplementMethod(String, Sub)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const char* str = valueThis.GetString();
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
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

// String#SplitReg(pattern as Pattern, cntMax? as Number):map {block?}
Gurax_DeclareMethod(String, SplitReg)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cntMax", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	LinkHelp(VTYPE_Pattern, Symbol::Add("Split"));
}

Gurax_ImplementMethod(String, SplitReg)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const char* str = valueThis.GetString();
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	int cntMax = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Split(pattern.Reference(), str, cntMax));
	return argument.ReturnIterator(processor, pIterator.release());
}

// String#Scan(pattern as Pattern, pos? as Number, posEnd? as Number):map {block?}
Gurax_DeclareMethod(String, Scan)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	LinkHelp(VTYPE_Pattern, GetSymbol());
}

Gurax_ImplementMethod(String, Scan)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	const char* str = valueThis.GetString();
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : 0;
	int posEnd = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Scan(pattern.Reference(), new StringReferable(str), pos, posEnd));
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// Implementation of method for List
//------------------------------------------------------------------------------
// List#Grep(pattern as Pattern) {block?}
Gurax_DeclareMethod(List, Grep)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(List, Grep)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetValueTypedOwner().GenerateIterator());
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Grep(pIteratorThis.release(), pattern.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// Implementation of method for Iterator
//------------------------------------------------------------------------------
// Iterator#Grep(pattern as Pattern) {block?}
Gurax_DeclareMethod(Iterator, Grep)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(Gurax_Symbol(en), u8R"""(

)""");
}

Gurax_ImplementMethod(Iterator, Grep)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	RefPtr<Iterator> pIteratorThis(valueThis.GetIterator().Reference());
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	// Function body
	RefPtr<Iterator> pIterator(new Iterator_Grep(pIteratorThis.release(), pattern.Reference()));
	return argument.ReturnIterator(processor, pIterator.release());
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Assignment of VType
	Assign(VTYPE_Group);
	Assign(VTYPE_Match);
	Assign(VTYPE_Pattern);
	// Assignment of method to String
	VTYPE_String.Assign(Gurax_CreateMethod(String, Match));
	VTYPE_String.Assign(Gurax_CreateMethod(String, Sub));
	VTYPE_String.Assign(Gurax_CreateMethod(String, SplitReg));
	VTYPE_String.Assign(Gurax_CreateMethod(String, Scan));
	// Assignment of method to List
	VTYPE_List.Assign(Gurax_CreateMethod(List, Grep));
	// Assignment of method to Iterator
	VTYPE_Iterator.Assign(Gurax_CreateMethod(Iterator, Grep));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(re)
