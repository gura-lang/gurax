//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_DIFF_UTIL_H
#define GURAX_MODULE_DIFF_UTIL_H
#include <gurax.h>
#include <dtl/dtl.hpp>

Gurax_BeginModuleScope(diff)

const char* GetEditMark_Normal(dtl::edit_t editType);
const char* GetEditMark_Context(dtl::edit_t editType);
const char* GetEditMark_Unified(dtl::edit_t editType);

Gurax_EndModuleScope(diff)

#endif
