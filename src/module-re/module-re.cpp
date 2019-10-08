//==============================================================================
// module-re.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(re)

//------------------------------------------------------------------------------
// Implementation of function
//------------------------------------------------------------------------------
// re.test()
Gurax_DeclareFunction(test)
{
	Declare(VTYPE_Any, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"");
}

Gurax_ImplementFunction(test)
{
	int r;
	unsigned char *start, *range, *end;
	regex_t* reg;
	OnigErrorInfo einfo;
	OnigRegion *region;

	static UChar* pattern = (UChar* )"a(.*)b|[e-f]+";
	static UChar* str     = (UChar* )"zzzzaffffffffb";

	r = onig_new(&reg, pattern, pattern + strlen((char* )pattern),
				 ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &einfo);
	if (r != ONIG_NORMAL) {
		OnigUChar s[ONIG_MAX_ERROR_MESSAGE_LEN];
		onig_error_code_to_str(s, r, &einfo);
		fprintf(stderr, "ERROR: %s\n", s);
		return Value::nil();
	}

	region = onig_region_new();

	end   = str + strlen((char* )str);
	start = str;
	range = end;
	r = onig_search(reg, str, end, start, range, region, ONIG_OPTION_NONE);
	if (r >= 0) {
		int i;

		fprintf(stderr, "match at %d\n", r);
		for (i = 0; i < region->num_regs; i++) {
			fprintf(stderr, "%d: (%ld-%ld)\n", i, region->beg[i], region->end[i]);
		}
		r = 0;
	}
	else if (r == ONIG_MISMATCH) {
		fprintf(stderr, "search fail\n");
		r = -1;
	}
	else { /* error */
		OnigUChar s[ONIG_MAX_ERROR_MESSAGE_LEN];
		onig_error_code_to_str(s, r);
		fprintf(stderr, "ERROR: %s\n", s);
		return Value::nil();
	}

	onig_region_free(region, 1 /* 1:free self, 0:free contents only */);
	onig_free(reg);
	onig_end();
	return Value::nil();
}

//------------------------------------------------------------------------------
// Implementation of method for String
//------------------------------------------------------------------------------
// String#Match(pattern:re.Pattern, pos?:Number, posEnd?:Number):map {block?}
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
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

// String#Sub(pattern:Pattern, replace, cnt?:Number):map {block?}
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
	if (replace.IsType(VTYPE_String)) {
		strRtn = pattern.SubstituteByString(str, Value_String::GetString(replace), cnt);
	} else if (replace.IsType(VTYPE_Function)) {
		strRtn = pattern.SubstituteByFunction(str, processor, Value_Function::GetFunction(replace), cnt);
	} else {
		Error::Issue(ErrorType::ValueError, "string or function must be specified");
		return Value::nil();
	}
	return ReturnValue(processor, argument, new Value_String(strRtn));
}

// String#SplitReg(pattern:Pattern, cntMax?:Number):map {block?}
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
	return ReturnIterator(processor, argument, pIterator.release());
}

// String#Scan(pattern:Pattern, pos?:Number, posEnd?:Number):map {block?}
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
	return ReturnIterator(processor, argument, pIterator.release());
}

//------------------------------------------------------------------------------
// Implementation of method for List
//------------------------------------------------------------------------------
// List#Grep(pattern:Pattern) {block?}
Gurax_DeclareMethod(List, Grep)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	return ReturnIterator(processor, argument, pIterator.release());
}

//------------------------------------------------------------------------------
// Implementation of method for Iterator
//------------------------------------------------------------------------------
// Iterator#Grep(pattern:Pattern) {block?}
Gurax_DeclareMethod(Iterator, Grep)
{
	Declare(VTYPE_Iterator, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareBlock(DeclBlock::Occur::ZeroOrOnce);
	AddHelp(
		Gurax_Symbol(en),
		"");
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
	return ReturnIterator(processor, argument, pIterator.release());
}

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
	Frame& frame = GetFrame();
	// Preparation of VType
	VTYPE_Group.Prepare(frame);
	VTYPE_Match.Prepare(frame);
	VTYPE_Pattern.Prepare(frame);
	// Assignment of function
	Assign(Gurax_CreateFunction(test));
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
