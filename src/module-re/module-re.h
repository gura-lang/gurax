//==============================================================================
// module-re.h
//==============================================================================
#ifndef GURAX_MODULE_RE_H
#define GURAX_MODULE_RE_H
#include <gurax.h>
#include <onigmo.h>
#include "Group.h"
#include "Iterators.h"
#include "Match.h"
#include "Pattern.h"
#include "VType_Group.h"
#include "VType_Match.h"
#include "VType_Pattern.h"

Gurax_BeginModuleHeader(re)

//------------------------------------------------------------------------------
// utilities
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

Gurax_EndModuleHeader(re)

#endif
