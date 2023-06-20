//==============================================================================
// Util.h
//==============================================================================
#ifndef GURAX_MODULE_ML_UTIL_H
#define GURAX_MODULE_ML_UTIL_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

struct Funcs {
	std::function<void (void* pvPool, const void* pvSrc, size_t len, UInt32 scanPosIn, UInt32* pScanPosInSel)> MaxPool[Array::ElemTypeIdMax];
};

extern Funcs funcs;

void InitializeUtil();

bool Img2dToCol(RefPtr<Array>& pArrayExp, const Array& arrayImg, size_t nRowsFilter, size_t nColsFilter,
	size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol, size_t* pnRowsOut = nullptr, size_t* pnColsOut = nullptr);
bool ColToImg2d(RefPtr<Array>& pArrayImg, const DimSizes& dimSizesImg, const Array& arrayExp, size_t nRowsFilter, size_t nColsFilter,
	size_t stridesRow, size_t stridesCol, size_t paddingRow, size_t paddingCol);

Gurax_EndModuleScope(ml)

#endif
