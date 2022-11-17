//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_RE_UTIL_H
#define GURAX_MODULE_RE_UTIL_H

Gurax_BeginModuleScope(re)

//------------------------------------------------------------------------------
// Utility Functions
//------------------------------------------------------------------------------
void IssueError_Onigmo();
void IssueError_Onigmo(int rtn);
void IssueError_Onigmo(int rtn, const OnigErrorInfo& einfo);

//------------------------------------------------------------------------------
// OnigRegion_Ptr
//------------------------------------------------------------------------------
class OnigRegion_Ptr : public CustomPtr<OnigRegion> {
public:
	using CustomPtr::CustomPtr;
	~OnigRegion_Ptr() { if (_p) ::onig_region_free(_p, 1); }
};

Gurax_EndModuleScope(re)

#endif
