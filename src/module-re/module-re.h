//==============================================================================
// module-re.h
//==============================================================================
#ifndef GURAX_MODULE_RE_H
#define GURAX_MODULE_RE_H
#include <gurax.h>
#if defined(GURAX_ON_MSWIN)
#include <onigmo.h>
#else
#include <oniguruma.h>
#endif
#include "Util.h"
#include "Group.h"
#include "Iterators.h"
#include "Match.h"
#include "Pattern.h"
#include "VType_Group.h"
#include "VType_Match.h"
#include "VType_Pattern.h"

Gurax_BeginModuleHeader(re)
Gurax_EndModuleHeader(re)

#endif
