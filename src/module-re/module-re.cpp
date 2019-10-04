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
// String#Match(pattern:Pattern, pos?:Number, posEnd?:Number):map {block?}
Gurax_DeclareMethod(String, Match)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("pos", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	DeclareArg("posEnd", VTYPE_Number, ArgOccur::ZeroOrOnce, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Applies a pattern matching to the given string and returns a `re.match` instance\n"
		"if the matching successes. If not, it would return `nil`.\n"
		"\n"
		"The argument `pos` specifies the starting position for matching process.\n"
		"If omitted, it starts from the beginning of the string.\n"
		"\n"
		"The argument `endpos` specifies the ending position for matching process.\n"
		"If omitted, it would be processed until the end of the string.\n");
}

Gurax_ImplementMethod(String, Match)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	int pos = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	int posEnd = args.IsValid()? args.PickNumberNonNeg<Int>() : -1;
	if (Error::IsIssued()) return Value::nil();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(valueThis.GetString()));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

// String#Sub(pattern:Pattern, replace, cnt?:Number):map {block?}
Gurax_DeclareMethod(String, Sub)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::Once, ArgFlag::None);
	DeclareArg("replace", VTYPE_Any, ArgOccur::Once, ArgFlag::None);
	DeclareArg("cnt", VTYPE_Number, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Substitutes strings that matches `pattern` with the specified replacer.\n"
		"\n"
		"The argument `replace` takes a `string` or `function`.\n"
		"\n"
		"If a `string` is specified, it would be used as a substituting string,\n"
		"in which you can use macros `\\0`, `\\1`, `\\2` .. to refer to matched groups.\n"
		"\n"
		"If a `function` is specified, it would be called with an argument `m:re.match`\n"
		"and is expected to return a string for subsitution.\n"
		"\n"
		"The argument `count` specifies the maximum number of substitutions.\n"
		"If omitted, no limit would be applied.\n");
}

Gurax_ImplementMethod(String, Sub)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	Value& replace = args.PickValue();
	int cnt = args.IsValid()? args.PickNumberNonNeg<int>() : -1;
	// Function body
	String strRtn;
	if (replace.IsType(VTYPE_String)) {
		strRtn = pattern.SubstituteByString(valueThis.GetString(),
											Value_String::GetString(replace), cnt);
	} else if (replace.IsType(VTYPE_Function)) {
		strRtn = pattern.SubstituteByFunction(valueThis.GetString(), processor,
											  Value_Function::GetFunction(replace), cnt);
	} else {
		Error::Issue(ErrorType::ValueError, "string or function must be specified");
		return Value::nil();
	}
	return ReturnValue(processor, argument, new Value_String(strRtn));
}

// String#SplitReg(pattern:Pattern):map {block?}
Gurax_DeclareMethod(String, SplitReg)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that splits the source string with the specified pattern.\n"
		"\n"
		"The argument `count` specifies the maximum number for splitting.\n"
		"If omitted, no limit would be applied.\n");
}

Gurax_ImplementMethod(String, SplitReg)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(valueThis.GetString()));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

// String#Scan(pattern:Pattern):map {block?}
Gurax_DeclareMethod(String, Scan)
{
	Declare(VTYPE_String, Flag::Map);
	DeclareArg("pattern", VTYPE_Pattern, ArgOccur::OnceOrMore, ArgFlag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Creates an iterator that returns strings that match the specified pattern.\n"
		"\n"
		"The argument `pos` specifies the starting position for matching process.\n"
		"If omitted, it starts from the beginning of the string.\n"
		"\n"
		"The argument `endpos` specifies the ending position for matching process.\n"
		"If omitted, it would be processed until the end of the string.\n");
}

Gurax_ImplementMethod(String, Scan)
{
	// Target
	auto& valueThis = GetValueThis(argument);
	// Arguments
	ArgPicker args(argument);
	Pattern& pattern = args.Pick<Value_Pattern>().GetPattern();
	// Function body
	RefPtr<Match> pMatch(pattern.CreateMatch(valueThis.GetString()));
	if (!pMatch) return Value::nil();
	return ReturnValue(processor, argument, new Value_Match(pMatch.release()));
}

//------------------------------------------------------------------------------
// utilities
//------------------------------------------------------------------------------
void IssueError_Onigmo()
{
	Error::Issue(ErrorType::GuestError,
				 "something's wrong in the process of Onigmo library");
}

void IssueError_Onigmo(int rtn)
{
	OnigUChar str[ONIG_MAX_ERROR_MESSAGE_LEN];
	::onig_error_code_to_str(str, rtn);
	Error::Issue(ErrorType::GuestError, "%s", str);
}

void IssueError_Onigmo(int rtn, const OnigErrorInfo& einfo)
{
	OnigUChar str[ONIG_MAX_ERROR_MESSAGE_LEN];
	::onig_error_code_to_str(str, rtn, &einfo);
	Error::Issue(ErrorType::GuestError, "%s", str);
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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(re)
