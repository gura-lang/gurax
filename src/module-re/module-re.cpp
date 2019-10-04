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
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(re)
