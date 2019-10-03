//==============================================================================
// module-re.h
//==============================================================================
#ifndef GURAX_MODULE_RE_H
#define GURAX_MODULE_RE_H
#include <gurax.h>
#include <onigmo.h>
#include "Group.h"
#include "Match.h"
#include "Pattern.h"
#include "VType_Group.h"
#include "VType_Match.h"
#include "VType_Pattern.h"

Gurax_BeginModuleHeader(re)

void IssueGuestError(int rtn, const OnigErrorInfo& einfo);

Gurax_EndModuleHeader(re)

#endif
