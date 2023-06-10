//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ML_UTIL_H
#define GURAX_MODULE_ML_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)
bool Img2dToCol(RefPtr<Array>& pArrayOut, const Array& arrayIn, size_t nRowsFilter, size_t nColsFilter, size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol);
Gurax_EndModuleScope(ml)

#endif
