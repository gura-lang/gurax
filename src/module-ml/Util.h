//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ML_UTIL_H
#define GURAX_MODULE_ML_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

bool Img2dToCol(RefPtr<Array>& pArrayExp, const Array& arrayImg, size_t nRowsFilter, size_t nColsFilter,
	size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol, size_t* pnRowsOut = nullptr, size_t* pnColsOut = nullptr);
bool ColToImg2d(RefPtr<Array>& pArrayImg, const DimSizes& dimSizesImg, const Array& arrayExp, size_t nRowsFilter, size_t nColsFilter,
	size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol);

bool MaxPool2d(RefPtr<Array>& pArrayPool, const Array& arraySrc, size_t nRowsKernel, size_t nColsKernel, size_t stridesRow, size_t stridesCol);

Gurax_EndModuleScope(ml)

#endif
