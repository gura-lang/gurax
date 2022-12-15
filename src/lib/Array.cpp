//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"

#define SetElemTypeRtn(elemTypeRtn, elemTypeL, elemTypeR) \
_pElemTypeRtnTbl[ElemType::elemTypeL.id][ElemType::elemTypeR.id] = &ElemType::elemTypeRtn;

#define SetFuncBurst(func, funcTmpl) do { \
	Array::ElemType::Bool.func		= funcTmpl<Bool>; \
	Array::ElemType::Int8.func		= funcTmpl<Int8>; \
	Array::ElemType::UInt8.func		= funcTmpl<UInt8>; \
	Array::ElemType::Int16.func		= funcTmpl<Int16>; \
	Array::ElemType::UInt16.func	= funcTmpl<UInt16>; \
	Array::ElemType::Int32.func		= funcTmpl<Int32>; \
	Array::ElemType::UInt32.func	= funcTmpl<UInt32>; \
	Array::ElemType::Int64.func		= funcTmpl<Int64>; \
	Array::ElemType::UInt64.func	= funcTmpl<UInt64>; \
	Array::ElemType::Half.func		= funcTmpl<Half>; \
	Array::ElemType::Float.func		= funcTmpl<Float>; \
	Array::ElemType::Double.func	= funcTmpl<Double>; \
	Array::ElemType::Complex.func	= funcTmpl<Complex>; \
} while (0)

#define SetFuncBurst2_Sub(func, funcTmpl, elemTypeSub) do { \
	Array::ElemType::Bool.func[ElemType::elemTypeSub.id]	= funcTmpl<Bool, elemTypeSub>; \
	Array::ElemType::Int8.func[ElemType::elemTypeSub.id]	= funcTmpl<Int8, elemTypeSub>; \
	Array::ElemType::UInt8.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt8, elemTypeSub>; \
	Array::ElemType::Int16.func[ElemType::elemTypeSub.id]	= funcTmpl<Int16, elemTypeSub>; \
	Array::ElemType::UInt16.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt16, elemTypeSub>; \
	Array::ElemType::Int32.func[ElemType::elemTypeSub.id]	= funcTmpl<Int32, elemTypeSub>; \
	Array::ElemType::UInt32.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt32, elemTypeSub>; \
	Array::ElemType::Int64.func[ElemType::elemTypeSub.id]	= funcTmpl<Int64, elemTypeSub>; \
	Array::ElemType::UInt64.func[ElemType::elemTypeSub.id]	= funcTmpl<UInt64, elemTypeSub>; \
	Array::ElemType::Half.func[ElemType::elemTypeSub.id]	= funcTmpl<Half, elemTypeSub>; \
	Array::ElemType::Float.func[ElemType::elemTypeSub.id]	= funcTmpl<Float, elemTypeSub>; \
	Array::ElemType::Double.func[ElemType::elemTypeSub.id]	= funcTmpl<Double, elemTypeSub>; \
	Array::ElemType::Complex.func[ElemType::elemTypeSub.id]	= funcTmpl<Complex, elemTypeSub>; \
} while (0)

#define SetFuncBurst2(func, funcTmpl) do { \
	SetFuncBurst2_Sub(func, funcTmpl, Bool); \
	SetFuncBurst2_Sub(func, funcTmpl, Int8); \
	SetFuncBurst2_Sub(func, funcTmpl, UInt8); \
	SetFuncBurst2_Sub(func, funcTmpl, Int16); \
	SetFuncBurst2_Sub(func, funcTmpl, UInt16); \
	SetFuncBurst2_Sub(func, funcTmpl, Int32); \
	SetFuncBurst2_Sub(func, funcTmpl, UInt32); \
	SetFuncBurst2_Sub(func, funcTmpl, Int64); \
	SetFuncBurst2_Sub(func, funcTmpl, UInt64); \
	SetFuncBurst2_Sub(func, funcTmpl, Half); \
	SetFuncBurst2_Sub(func, funcTmpl, Float); \
	SetFuncBurst2_Sub(func, funcTmpl, Double); \
	SetFuncBurst2_Sub(func, funcTmpl, Complex); \
} while (0)

#define SetFuncBurst3(func, funcTmpl) do { \
	Array::ElemType::Bool.func[ElemType::Bool.id]		= funcTmpl<Bool, Bool, Bool>; \
	Array::ElemType::Int8.func[ElemType::Bool.id]		= funcTmpl<Int8, Int8, Bool>; \
	Array::ElemType::UInt8.func[ElemType::Bool.id]		= funcTmpl<UInt8, UInt8, Bool>; \
	Array::ElemType::Int16.func[ElemType::Bool.id]		= funcTmpl<Int16, Int16, Bool>; \
	Array::ElemType::UInt16.func[ElemType::Bool.id]		= funcTmpl<UInt16, UInt16, Bool>; \
	Array::ElemType::Int32.func[ElemType::Bool.id]		= funcTmpl<Int32, Int32, Bool>; \
	Array::ElemType::UInt32.func[ElemType::Bool.id]		= funcTmpl<UInt32, UInt32, Bool>; \
	Array::ElemType::Int64.func[ElemType::Bool.id]		= funcTmpl<Int64, Int64, Bool>; \
	Array::ElemType::UInt64.func[ElemType::Bool.id]		= funcTmpl<UInt64, UInt64, Bool>; \
	Array::ElemType::Half.func[ElemType::Bool.id]		= funcTmpl<Half, Half, Bool>; \
	Array::ElemType::Float.func[ElemType::Bool.id]		= funcTmpl<Float, Float, Bool>; \
	Array::ElemType::Double.func[ElemType::Bool.id]		= funcTmpl<Double, Double, Bool>; \
	Array::ElemType::Complex.func[ElemType::Bool.id]	= funcTmpl<Complex, Complex, Bool>; \
	Array::ElemType::Bool.func[ElemType::Int8.id]		= funcTmpl<Int8, Bool, Int8>; \
	Array::ElemType::Int8.func[ElemType::Int8.id]		= funcTmpl<Int8, Int8, Int8>; \
	Array::ElemType::UInt8.func[ElemType::Int8.id]		= funcTmpl<UInt8, UInt8, Int8>; \
	Array::ElemType::Int16.func[ElemType::Int8.id]		= funcTmpl<Int16, Int16, Int8>; \
	Array::ElemType::UInt16.func[ElemType::Int8.id]		= funcTmpl<UInt16, UInt16, Int8>; \
	Array::ElemType::Int32.func[ElemType::Int8.id]		= funcTmpl<Int32, Int32, Int8>; \
	Array::ElemType::UInt32.func[ElemType::Int8.id]		= funcTmpl<UInt32, UInt32, Int8>; \
	Array::ElemType::Int64.func[ElemType::Int8.id]		= funcTmpl<Int64, Int64, Int8>; \
	Array::ElemType::UInt64.func[ElemType::Int8.id]		= funcTmpl<UInt64, UInt64, Int8>; \
	Array::ElemType::Half.func[ElemType::Int8.id]		= funcTmpl<Half, Half, Int8>; \
	Array::ElemType::Float.func[ElemType::Int8.id]		= funcTmpl<Float, Float, Int8>; \
	Array::ElemType::Double.func[ElemType::Int8.id]		= funcTmpl<Double, Double, Int8>; \
	Array::ElemType::Complex.func[ElemType::Int8.id]	= funcTmpl<Complex, Complex, Int8>; \
	Array::ElemType::Bool.func[ElemType::UInt8.id]		= funcTmpl<UInt8, Bool, UInt8>; \
	Array::ElemType::Int8.func[ElemType::UInt8.id]		= funcTmpl<UInt8, Int8, UInt8>; \
	Array::ElemType::UInt8.func[ElemType::UInt8.id]		= funcTmpl<UInt8, UInt8, UInt8>; \
	Array::ElemType::Int16.func[ElemType::UInt8.id]		= funcTmpl<Int16, Int16, UInt8>; \
	Array::ElemType::UInt16.func[ElemType::UInt8.id]	= funcTmpl<UInt16, UInt16, UInt8>; \
	Array::ElemType::Int32.func[ElemType::UInt8.id]		= funcTmpl<Int32, Int32, UInt8>; \
	Array::ElemType::UInt32.func[ElemType::UInt8.id]	= funcTmpl<UInt32, UInt32, UInt8>; \
	Array::ElemType::Int64.func[ElemType::UInt8.id]		= funcTmpl<Int64, Int64, UInt8>; \
	Array::ElemType::UInt64.func[ElemType::UInt8.id]	= funcTmpl<UInt64, UInt64, UInt8>; \
	Array::ElemType::Half.func[ElemType::UInt8.id]		= funcTmpl<Half, Half, UInt8>; \
	Array::ElemType::Float.func[ElemType::UInt8.id]		= funcTmpl<Float, Float, UInt8>; \
	Array::ElemType::Double.func[ElemType::UInt8.id]	= funcTmpl<Double, Double, UInt8>; \
	Array::ElemType::Complex.func[ElemType::UInt8.id]	= funcTmpl<Complex, Complex, UInt8>; \
	Array::ElemType::Bool.func[ElemType::Int16.id]		= funcTmpl<Int16, Bool, Int16>; \
	Array::ElemType::Int8.func[ElemType::Int16.id]		= funcTmpl<Int16, Int8, Int16>; \
	Array::ElemType::UInt8.func[ElemType::Int16.id]		= funcTmpl<Int16, UInt8, Int16>; \
	Array::ElemType::Int16.func[ElemType::Int16.id]		= funcTmpl<Int16, Int16, Int16>; \
	Array::ElemType::UInt16.func[ElemType::Int16.id]	= funcTmpl<UInt16, UInt16, Int16>; \
	Array::ElemType::Int32.func[ElemType::Int16.id]		= funcTmpl<Int32, Int32, Int16>; \
	Array::ElemType::UInt32.func[ElemType::Int16.id]	= funcTmpl<UInt32, UInt32, Int16>; \
	Array::ElemType::Int64.func[ElemType::Int16.id]		= funcTmpl<Int64, Int64, Int16>; \
	Array::ElemType::UInt64.func[ElemType::Int16.id]	= funcTmpl<UInt64, UInt64, Int16>; \
	Array::ElemType::Half.func[ElemType::Int16.id]		= funcTmpl<Half, Half, Int16>; \
	Array::ElemType::Float.func[ElemType::Int16.id]		= funcTmpl<Float, Float, Int16>; \
	Array::ElemType::Double.func[ElemType::Int16.id]	= funcTmpl<Double, Double, Int16>; \
	Array::ElemType::Complex.func[ElemType::Int16.id]	= funcTmpl<Complex, Complex, Int16>; \
	Array::ElemType::Bool.func[ElemType::UInt16.id]		= funcTmpl<UInt16, Bool, UInt16>; \
	Array::ElemType::Int8.func[ElemType::UInt16.id]		= funcTmpl<UInt16, Int8, UInt16>; \
	Array::ElemType::UInt8.func[ElemType::UInt16.id]	= funcTmpl<UInt16, UInt8, UInt16>; \
	Array::ElemType::Int16.func[ElemType::UInt16.id]	= funcTmpl<UInt16, Int16, UInt16>; \
	Array::ElemType::UInt16.func[ElemType::UInt16.id]	= funcTmpl<UInt16, UInt16, UInt16>; \
	Array::ElemType::Int32.func[ElemType::UInt16.id]	= funcTmpl<Int32, Int32, UInt16>; \
	Array::ElemType::UInt32.func[ElemType::UInt16.id]	= funcTmpl<UInt32, UInt32, UInt16>; \
	Array::ElemType::Int64.func[ElemType::UInt16.id]	= funcTmpl<Int64, Int64, UInt16>; \
	Array::ElemType::UInt64.func[ElemType::UInt16.id]	= funcTmpl<UInt64, UInt64, UInt16>; \
	Array::ElemType::Half.func[ElemType::UInt16.id]		= funcTmpl<Half, Half, UInt16>; \
	Array::ElemType::Float.func[ElemType::UInt16.id]	= funcTmpl<Float, Float, UInt16>; \
	Array::ElemType::Double.func[ElemType::UInt16.id]	= funcTmpl<Double, Double, UInt16>; \
	Array::ElemType::Complex.func[ElemType::UInt16.id]	= funcTmpl<Complex, Complex, UInt16>; \
	Array::ElemType::Bool.func[ElemType::Int32.id]		= funcTmpl<Int32, Bool, Int32>; \
	Array::ElemType::Int8.func[ElemType::Int32.id]		= funcTmpl<Int32, Int8, Int32>; \
	Array::ElemType::UInt8.func[ElemType::Int32.id]		= funcTmpl<Int32, UInt8, Int32>; \
	Array::ElemType::Int16.func[ElemType::Int32.id]		= funcTmpl<Int32, Int16, Int32>; \
	Array::ElemType::UInt16.func[ElemType::Int32.id]	= funcTmpl<Int32, UInt16, Int32>; \
	Array::ElemType::Int32.func[ElemType::Int32.id]		= funcTmpl<Int32, Int32, Int32>; \
	Array::ElemType::UInt32.func[ElemType::Int32.id]	= funcTmpl<UInt32, UInt32, Int32>; \
	Array::ElemType::Int64.func[ElemType::Int32.id]		= funcTmpl<Int64, Int64, Int32>; \
	Array::ElemType::UInt64.func[ElemType::Int32.id]	= funcTmpl<UInt64, UInt64, Int32>; \
	Array::ElemType::Half.func[ElemType::Int32.id]		= funcTmpl<Half, Half, Int32>; \
	Array::ElemType::Float.func[ElemType::Int32.id]		= funcTmpl<Float, Float, Int32>; \
	Array::ElemType::Double.func[ElemType::Int32.id]	= funcTmpl<Double, Double, Int32>; \
	Array::ElemType::Complex.func[ElemType::Int32.id]	= funcTmpl<Complex, Complex, Int32>; \
	Array::ElemType::Bool.func[ElemType::UInt32.id]		= funcTmpl<UInt32, Bool, UInt32>; \
	Array::ElemType::Int8.func[ElemType::UInt32.id]		= funcTmpl<UInt32, Int8, UInt32>; \
	Array::ElemType::UInt8.func[ElemType::UInt32.id]	= funcTmpl<UInt32, UInt8, UInt32>; \
	Array::ElemType::Int16.func[ElemType::UInt32.id]	= funcTmpl<UInt32, Int16, UInt32>; \
	Array::ElemType::UInt16.func[ElemType::UInt32.id]	= funcTmpl<UInt32, UInt16, UInt32>; \
	Array::ElemType::Int32.func[ElemType::UInt32.id]	= funcTmpl<UInt32, Int32, UInt32>; \
	Array::ElemType::UInt32.func[ElemType::UInt32.id]	= funcTmpl<UInt32, UInt32, UInt32>; \
	Array::ElemType::Int64.func[ElemType::UInt32.id]	= funcTmpl<Int64, Int64, UInt32>; \
	Array::ElemType::UInt64.func[ElemType::UInt32.id]	= funcTmpl<UInt64, UInt64, UInt32>; \
	Array::ElemType::Half.func[ElemType::UInt32.id]		= funcTmpl<Half, Half, UInt32>; \
	Array::ElemType::Float.func[ElemType::UInt32.id]	= funcTmpl<Float, Float, UInt32>; \
	Array::ElemType::Double.func[ElemType::UInt32.id]	= funcTmpl<Double, Double, UInt32>; \
	Array::ElemType::Complex.func[ElemType::UInt32.id]	= funcTmpl<Complex, Complex, UInt32>; \
	Array::ElemType::Bool.func[ElemType::Int64.id]		= funcTmpl<Int64, Bool, Int64>; \
	Array::ElemType::Int8.func[ElemType::Int64.id]		= funcTmpl<Int64, Int8, Int64>; \
	Array::ElemType::UInt8.func[ElemType::Int64.id]		= funcTmpl<Int64, UInt8, Int64>; \
	Array::ElemType::Int16.func[ElemType::Int64.id]		= funcTmpl<Int64, Int16, Int64>; \
	Array::ElemType::UInt16.func[ElemType::Int64.id]	= funcTmpl<Int64, UInt16, Int64>; \
	Array::ElemType::Int32.func[ElemType::Int64.id]		= funcTmpl<Int64, Int32, Int64>; \
	Array::ElemType::UInt32.func[ElemType::Int64.id]	= funcTmpl<Int64, UInt32, Int64>; \
	Array::ElemType::Int64.func[ElemType::Int64.id]		= funcTmpl<Int64, Int64, Int64>; \
	Array::ElemType::UInt64.func[ElemType::Int64.id]	= funcTmpl<UInt64, UInt64, Int64>; \
	Array::ElemType::Half.func[ElemType::Int64.id]		= funcTmpl<Half, Half, Int64>; \
	Array::ElemType::Float.func[ElemType::Int64.id]		= funcTmpl<Float, Float, Int64>; \
	Array::ElemType::Double.func[ElemType::Int64.id]	= funcTmpl<Double, Double, Int64>; \
	Array::ElemType::Complex.func[ElemType::Int64.id]	= funcTmpl<Complex, Complex, Int64>; \
	Array::ElemType::Bool.func[ElemType::UInt64.id]		= funcTmpl<UInt64, Bool, UInt64>; \
	Array::ElemType::Int8.func[ElemType::UInt64.id]		= funcTmpl<UInt64, Int8, UInt64>; \
	Array::ElemType::UInt8.func[ElemType::UInt64.id]	= funcTmpl<UInt64, UInt8, UInt64>; \
	Array::ElemType::Int16.func[ElemType::UInt64.id]	= funcTmpl<UInt64, Int16, UInt64>; \
	Array::ElemType::UInt16.func[ElemType::UInt64.id]	= funcTmpl<UInt64, UInt16, UInt64>; \
	Array::ElemType::Int32.func[ElemType::UInt64.id]	= funcTmpl<UInt64, Int32, UInt64>; \
	Array::ElemType::UInt32.func[ElemType::UInt64.id]	= funcTmpl<UInt64, UInt32, UInt64>; \
	Array::ElemType::Int64.func[ElemType::UInt64.id]	= funcTmpl<UInt64, Int64, UInt64>; \
	Array::ElemType::UInt64.func[ElemType::UInt64.id]	= funcTmpl<UInt64, UInt64, UInt64>; \
	Array::ElemType::Half.func[ElemType::UInt64.id]		= funcTmpl<Half, Half, UInt64>; \
	Array::ElemType::Float.func[ElemType::UInt64.id]	= funcTmpl<Float, Float, UInt64>; \
	Array::ElemType::Double.func[ElemType::UInt64.id]	= funcTmpl<Double, Double, UInt64>; \
	Array::ElemType::Complex.func[ElemType::UInt64.id]	= funcTmpl<Complex, Complex, UInt64>; \
	Array::ElemType::Bool.func[ElemType::Half.id]		= funcTmpl<Half, Bool, Half>; \
	Array::ElemType::Int8.func[ElemType::Half.id]		= funcTmpl<Half, Int8, Half>; \
	Array::ElemType::UInt8.func[ElemType::Half.id]		= funcTmpl<Half, UInt8, Half>; \
	Array::ElemType::Int16.func[ElemType::Half.id]		= funcTmpl<Half, Int16, Half>; \
	Array::ElemType::UInt16.func[ElemType::Half.id]		= funcTmpl<Half, UInt16, Half>; \
	Array::ElemType::Int32.func[ElemType::Half.id]		= funcTmpl<Half, Int32, Half>; \
	Array::ElemType::UInt32.func[ElemType::Half.id]		= funcTmpl<Half, UInt32, Half>; \
	Array::ElemType::Int64.func[ElemType::Half.id]		= funcTmpl<Half, Int64, Half>; \
	Array::ElemType::UInt64.func[ElemType::Half.id]		= funcTmpl<Half, UInt64, Half>; \
	Array::ElemType::Half.func[ElemType::Half.id]		= funcTmpl<Half, Half, Half>; \
	Array::ElemType::Float.func[ElemType::Half.id]		= funcTmpl<Float, Float, Half>; \
	Array::ElemType::Double.func[ElemType::Half.id]		= funcTmpl<Double, Double, Half>; \
	Array::ElemType::Complex.func[ElemType::Half.id]	= funcTmpl<Complex, Complex, Half>; \
	Array::ElemType::Bool.func[ElemType::Float.id]		= funcTmpl<Float, Bool, Float>; \
	Array::ElemType::Int8.func[ElemType::Float.id]		= funcTmpl<Float, Int8, Float>; \
	Array::ElemType::UInt8.func[ElemType::Float.id]		= funcTmpl<Float, UInt8, Float>; \
	Array::ElemType::Int16.func[ElemType::Float.id]		= funcTmpl<Float, Int16, Float>; \
	Array::ElemType::UInt16.func[ElemType::Float.id]	= funcTmpl<Float, UInt16, Float>; \
	Array::ElemType::Int32.func[ElemType::Float.id]		= funcTmpl<Float, Int32, Float>; \
	Array::ElemType::UInt32.func[ElemType::Float.id]	= funcTmpl<Float, UInt32, Float>; \
	Array::ElemType::Int64.func[ElemType::Float.id]		= funcTmpl<Float, Int64, Float>; \
	Array::ElemType::UInt64.func[ElemType::Float.id]	= funcTmpl<Float, UInt64, Float>; \
	Array::ElemType::Half.func[ElemType::Float.id]		= funcTmpl<Float, Half, Float>; \
	Array::ElemType::Float.func[ElemType::Float.id]		= funcTmpl<Float, Float, Float>; \
	Array::ElemType::Double.func[ElemType::Float.id]	= funcTmpl<Double, Double, Float>; \
	Array::ElemType::Complex.func[ElemType::Float.id]	= funcTmpl<Complex, Complex, Float>; \
	Array::ElemType::Bool.func[ElemType::Double.id]		= funcTmpl<Double, Bool, Double>; \
	Array::ElemType::Int8.func[ElemType::Double.id]		= funcTmpl<Double, Int8, Double>; \
	Array::ElemType::UInt8.func[ElemType::Double.id]	= funcTmpl<Double, UInt8, Double>; \
	Array::ElemType::Int16.func[ElemType::Double.id]	= funcTmpl<Double, Int16, Double>; \
	Array::ElemType::UInt16.func[ElemType::Double.id]	= funcTmpl<Double, UInt16, Double>; \
	Array::ElemType::Int32.func[ElemType::Double.id]	= funcTmpl<Double, Int32, Double>; \
	Array::ElemType::UInt32.func[ElemType::Double.id]	= funcTmpl<Double, UInt32, Double>; \
	Array::ElemType::Int64.func[ElemType::Double.id]	= funcTmpl<Double, Int64, Double>; \
	Array::ElemType::UInt64.func[ElemType::Double.id]	= funcTmpl<Double, UInt64, Double>; \
	Array::ElemType::Half.func[ElemType::Double.id]		= funcTmpl<Double, Half, Double>; \
	Array::ElemType::Float.func[ElemType::Double.id]	= funcTmpl<Double, Float, Double>; \
	Array::ElemType::Double.func[ElemType::Double.id]	= funcTmpl<Double, Double, Double>; \
	Array::ElemType::Complex.func[ElemType::Double.id]	= funcTmpl<Complex, Complex, Double>; \
	Array::ElemType::Bool.func[ElemType::Complex.id]	= funcTmpl<Complex, Bool, Complex>; \
	Array::ElemType::Int8.func[ElemType::Complex.id]	= funcTmpl<Complex, Int8, Complex>; \
	Array::ElemType::UInt8.func[ElemType::Complex.id]	= funcTmpl<Complex, UInt8, Complex>; \
	Array::ElemType::Int16.func[ElemType::Complex.id]	= funcTmpl<Complex, Int16, Complex>; \
	Array::ElemType::UInt16.func[ElemType::Complex.id]	= funcTmpl<Complex, UInt16, Complex>; \
	Array::ElemType::Int32.func[ElemType::Complex.id]	= funcTmpl<Complex, Int32, Complex>; \
	Array::ElemType::UInt32.func[ElemType::Complex.id]	= funcTmpl<Complex, UInt32, Complex>; \
	Array::ElemType::Int64.func[ElemType::Complex.id]	= funcTmpl<Complex, Int64, Complex>; \
	Array::ElemType::UInt64.func[ElemType::Complex.id]	= funcTmpl<Complex, UInt64, Complex>; \
	Array::ElemType::Half.func[ElemType::Complex.id]	= funcTmpl<Complex, Half, Complex>; \
	Array::ElemType::Float.func[ElemType::Complex.id]	= funcTmpl<Complex, Float, Complex>; \
	Array::ElemType::Double.func[ElemType::Complex.id]	= funcTmpl<Complex, Double, Complex>; \
	Array::ElemType::Complex.func[ElemType::Complex.id]	= funcTmpl<Complex, Complex, Complex>; \
} while (0)

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
Array::ElemTypeT* Array::_pElemTypeRtnTbl[ElemTypeIdMax][ElemTypeIdMax];
Array::MapSymbolToElemType Array::_mapSymbolToElemType;
Array::MapSymbolToElemType Array::_mapAtSymbolToElemType;

Array::Array(ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes) :
		_elemType(elemType), _pMemory(pMemory), _dimSizes(std::move(dimSizes))
{
}

Array::Array(const Array& src) :
		_elemType(src._elemType), _pMemory(src._pMemory->Clone()), _dimSizes(src._dimSizes)
{
}

Array::Array(Array&& src) :
		_elemType(src._elemType), _pMemory(src._pMemory->Reference()), _dimSizes(std::move(src._dimSizes))
{
}

Array* Array::Create(ElemTypeT& elemType, DimSizes dimSizes)
{
	RefPtr<Memory> pMemory(new MemoryHeap(elemType.bytes * dimSizes.CalcLength()));
	pMemory->Fill(0);
	return new Array(elemType, pMemory.release(), std::move(dimSizes));
}

Array* Array::CreateIdentity(ElemTypeT& elemType, size_t n, Double mag)
{
	RefPtr<Array> pArray(Create2d(elemType, n, n));
	size_t idx = 0;
	for (size_t i = 0; i < n; i++, idx += n + 1) pArray->IndexSetDouble(idx, mag);
	return pArray.release();
}

template<typename T_Elem> bool IndexSetValue_T(void* pv, size_t idx, const Value& value)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + idx;
	if (value.IsType(VTYPE_Number)) {
		*p = Value_Number::GetNumber<T_Elem>(value);
	} else if (value.IsType(VTYPE_Bool)) {
		*p = value.GetBool()? 1 : 0;
	} else {
		Error::Issue(ErrorType::ValueError, "Number value is expected");
		return false;
	}
	return true;
}

template<> bool IndexSetValue_T<Bool>(void* pv, size_t idx, const Value& value)
{
	*(reinterpret_cast<Bool*>(pv) + idx) = value.GetBool();
	return true;
}

template<> bool IndexSetValue_T<Complex>(void* pv, size_t idx, const Value& value)
{
	Complex* p = reinterpret_cast<Complex*>(pv) + idx;
	if (value.IsType(VTYPE_Number)) {
		*p = Complex(Value_Number::GetNumber<Double>(value));
	} else if (value.IsType(VTYPE_Complex)) {
		*p = Value_Complex::GetComplex(value);
	} else if (value.IsType(VTYPE_Bool)) {
		*p = Complex(value.GetBool()? 1. : 0.);
	} else {
		Error::Issue(ErrorType::ValueError, "Number or Complex value is expected");
		return false;
	}
	return true;
}

template<typename T_Elem> bool IndexSetDouble_T(void* pv, size_t idx, Double num)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + idx;
	*p = static_cast<T_Elem>(num);
	return true;
}

template<> bool IndexSetDouble_T<Bool>(void* pv, size_t idx, Double num)
{
	*(reinterpret_cast<Bool*>(pv) + idx) = (num > 0);
	return true;
}

template<> bool IndexSetDouble_T<Complex>(void* pv, size_t idx, Double num)
{
	Complex* p = reinterpret_cast<Complex*>(pv) + idx;
	*p = Complex(num);
	return true;
}

template<typename T_Elem> Value* IndexGetValue_T(const void* pv, size_t idx)
{
	return new Value_Number(*(reinterpret_cast<const T_Elem*>(pv) + idx));
}

template<> Value* IndexGetValue_T<Bool>(const void* pv, size_t idx)
{
	return new Value_Bool(*(reinterpret_cast<const Bool*>(pv) + idx));
}

template<> Value* IndexGetValue_T<Complex>(const void* pv, size_t idx)
{
	return new Value_Complex(*(reinterpret_cast<const Complex*>(pv) + idx));
}

template<typename T_Elem> Double IndexGetDouble_T(const void* pv, size_t idx)
{
	return static_cast<Double>(*(reinterpret_cast<const T_Elem*>(pv) + idx));
}

template<> Double IndexGetDouble_T<Bool>(const void* pv, size_t idx)
{
	return *(reinterpret_cast<const Bool*>(pv) + idx)? 1. : 0.;
}

template<> Double IndexGetDouble_T<Complex>(const void* pv, size_t idx)
{
	return 0.;
}

template<typename T_Elem> void InjectFromValueList_T(const ValueList& values, void* pv, size_t offset, size_t len)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, p++, ppValue++) {
		*p = Value_Number::GetNumber<T_Elem>(**ppValue);
	}
}

template<> void InjectFromValueList_T<Bool>(const ValueList& values, void* pv, size_t offset, size_t len)
{
	Bool* p = reinterpret_cast<Bool*>(pv) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, p++, ppValue++) {
		*p = (*ppValue)->GetBool();
	}
}

template<> void InjectFromValueList_T<Complex>(const ValueList& values, void* pv, size_t offset, size_t len)
{
	Complex* p = reinterpret_cast<Complex*>(pv) + offset;
	auto ppValue = values.begin();
	for (size_t i = 0; i < len; i++, p++, ppValue++) {
		*p = Value_Complex::GetComplexRobust(**ppValue);
	}
}

template<typename T_Elem> bool InjectFromIterator_T(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	T_Elem* p = reinterpret_cast<T_Elem*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (!pValue->IsType(VTYPE_Number)) {
			Error::Issue(ErrorType::TypeError, "must be Number value");
			return false;
		}
		*p = Value_Number::GetNumber<T_Elem>(*pValue);
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Bool>(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	Bool* p = reinterpret_cast<Bool*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		*p = pValue->GetBool();
	}
	return !Error::IsIssued();
}

template<> bool InjectFromIterator_T<Complex>(Iterator& iterator, void* pv, size_t offset, size_t len)
{
	Complex* p = reinterpret_cast<Complex*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) {
		RefPtr<Value> pValue(iterator.NextValue());
		if (!pValue) break;
		if (pValue->IsType(VTYPE_Number)) {
			*p = Value_Number::GetNumber<Double>(*pValue);
		} else if (pValue->IsType(VTYPE_Complex)) {
			*p = Value_Complex::GetComplex(*pValue);
		} else {
			Error::Issue(ErrorType::TypeError, "must be Complex or Number value");
			return false;
		}
	}
	return !Error::IsIssued();
}

template<typename T_Elem> void ExtractToValueOwner_T(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	const T_Elem* p = reinterpret_cast<const T_Elem*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) values.push_back(new Value_Number(*p));
}

template<> void ExtractToValueOwner_T<Bool>(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	const Bool* p = reinterpret_cast<const Bool*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) values.push_back(new Value_Bool(!!*p));
}

template<> void ExtractToValueOwner_T<Complex>(ValueOwner& values, const void* pv, size_t offset, size_t len)
{
	const Complex* p = reinterpret_cast<const Complex*>(pv) + offset;
	for (size_t i = 0; i < len; i++, p++) values.push_back(new Value_Complex(*p));
}

template<typename T_ElemDst, typename T_ElemSrc> void CopyElems_T(void* pvDst, const void* pvSrc, size_t offset, size_t len)
{
	T_ElemDst* pDst = reinterpret_cast<T_ElemDst*>(pvDst);
	const T_ElemSrc* pSrc = reinterpret_cast<const T_ElemSrc*>(pvSrc) + offset;
	for (size_t i = 0; i < len; i++, pDst++, pSrc++) {
		*pDst = static_cast<T_ElemDst>(*pSrc);
	}
}

template<typename T_ElemDst, typename T_ElemSrc> void Transpose_T(void* pvDst, size_t nRows, size_t nCols, const void* pvSrc)
{
	T_ElemDst* pDst = reinterpret_cast<T_ElemDst*>(pvDst);
	const T_ElemSrc* pSrcSave = reinterpret_cast<const T_ElemSrc*>(pvSrc);
	for (size_t iRow = 0; iRow < nRows; iRow++, pSrcSave++) {
		const T_ElemSrc* pSrc = pSrcSave;
		for (size_t iCol = 0; iCol < nCols; iCol++, pDst++, pSrc += nRows) {
			*pDst = static_cast<T_ElemDst>(*pSrc);
		}
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Add_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Add_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + numRCasted);
	}
}

template<typename T_ElemL>
void Add_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) + numR);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Sub_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Sub_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - numRCasted);
	}
}

template<typename T_ElemR>
void Sub_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = T_ElemR;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn numLCasted = static_cast<T_ElemRtn>(numL);
	for (size_t i = 0; i < len; i++, pRtn++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(numLCasted - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Sub_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) - numR);
	}
}

template<typename T_ElemR>
void Sub_ComplexArray_T(void* pvRtn, const Complex& numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(numL - static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Mul_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++, pR++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * static_cast<T_ElemRtn>(*pR));
	}
}

template<typename T_ElemL>
void Mul_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * numRCasted);
	}
}

template<typename T_ElemL>
void Mul_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) * numR);
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
bool Div_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t len)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pL++, pR++) {
		auto elemR = static_cast<T_ElemRtn>(*pR);
		if (elemR == 0) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / elemR);
	}
	return true;
}

template<typename T_ElemL>
bool Div_ArrayNumber_T(void* pvRtn, const void* pvL, Double numR, size_t len)
{
	using T_ElemRtn = T_ElemL;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	T_ElemRtn numRCasted = static_cast<T_ElemRtn>(numR);
	if (numRCasted == 0) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return false;
	}
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / numRCasted);
	}
	return true;
}

template<typename T_ElemR>
bool Div_NumberArray_T(void* pvRtn, Double numL, const void* pvR, size_t len)
{
	using T_ElemRtn = T_ElemR;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn numLCasted = static_cast<T_ElemRtn>(numL);
	for (size_t i = 0; i < len; i++, pRtn++, pR++) {
		auto elemR = static_cast<T_ElemRtn>(*pR);
		if (elemR == 0) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(numLCasted / elemR);
	}
	return true;
}

template<typename T_ElemL>
bool Div_ArrayComplex_T(void* pvRtn, const void* pvL, const Complex& numR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	if (numR.IsZero()) {
		Error::Issue(ErrorType::DividedByZero, "divided by zero");
		return false;
	}
	for (size_t i = 0; i < len; i++, pRtn++, pL++) {
		*pRtn = static_cast<T_ElemRtn>(static_cast<T_ElemRtn>(*pL) / numR);
	}
	return true;
}

template<typename T_ElemR>
bool Div_ComplexArray_T(void* pvRtn, const Complex& numL, const void* pvR, size_t len)
{
	using T_ElemRtn = Complex;
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < len; i++, pRtn++, pR++) {
		auto elemR = static_cast<T_ElemRtn>(*pR);
		if (elemR == 0) {
			Error::Issue(ErrorType::DividedByZero, "divided by zero");
			return false;
		}
		*pRtn = static_cast<T_ElemRtn>(numL - elemR);
	}
	return true;
}

// [m, n] = dot([m, l], [l, n])
template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Dot_ArrayArray_T(void* pvRtn, size_t m, size_t n, const void* pvL, const void* pvR, size_t l)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pBaseL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pBaseR = reinterpret_cast<const T_ElemR*>(pvR);
	for (size_t i = 0; i < m; i++, pBaseL += l) {
		const T_ElemR* pSaveR = pBaseR;
		for (size_t j = 0; j < n; j++, pRtn++, pSaveR++) {
			T_ElemRtn elemRtn = 0;
			const T_ElemL* pL = pBaseL;
			const T_ElemR* pR = pSaveR;
			for (size_t k = 0; k < l; k++, pL++, pR += n) {
				elemRtn += static_cast<T_ElemRtn>(*pL) * static_cast<T_ElemRtn>(*pR);
			}
			*pRtn = elemRtn;
		}
	}
}

template<typename T_ElemRtn, typename T_ElemL, typename T_ElemR>
void Cross_ArrayArray_T(void* pvRtn, const void* pvL, const void* pvR, size_t n)
{
	T_ElemRtn* pRtn = reinterpret_cast<T_ElemRtn*>(pvRtn);
	const T_ElemL* pL = reinterpret_cast<const T_ElemL*>(pvL);
	const T_ElemR* pR = reinterpret_cast<const T_ElemR*>(pvR);
	T_ElemRtn a1 = static_cast<T_ElemRtn>(pL[0]);
	T_ElemRtn a2 = static_cast<T_ElemRtn>(pL[1]);
	T_ElemRtn a3 = static_cast<T_ElemRtn>(pL[2]);
	T_ElemRtn b1 = static_cast<T_ElemRtn>(pR[0]);
	T_ElemRtn b2 = static_cast<T_ElemRtn>(pR[1]);
	T_ElemRtn b3 = static_cast<T_ElemRtn>(pR[2]);
	pRtn[0] = static_cast<T_ElemRtn>(a2 * b3 - a3 * b2);
	pRtn[1] = static_cast<T_ElemRtn>(a3 * b1 - a1 * b3);
	pRtn[2] = static_cast<T_ElemRtn>(a1 * b2 - a2 * b1); 
}

void Array::Bootup()
{
	auto AssocSymbol = [](const Symbol* pSymbol, const Symbol* pAtSymbol, ElemTypeT& elemType) {
		_mapSymbolToElemType[pSymbol] = &elemType;
		_mapAtSymbolToElemType[pAtSymbol] = &elemType;
	};
	SetElemTypeRtn(Bool, Bool, Bool);
	SetElemTypeRtn(Int8, Int8, Bool);
	SetElemTypeRtn(UInt8, UInt8, Bool);
	SetElemTypeRtn(Int16, Int16, Bool);
	SetElemTypeRtn(UInt16, UInt16, Bool);
	SetElemTypeRtn(Int32, Int32, Bool);
	SetElemTypeRtn(UInt32, UInt32, Bool);
	SetElemTypeRtn(Int64, Int64, Bool);
	SetElemTypeRtn(UInt64, UInt64, Bool);
	SetElemTypeRtn(Half, Half, Bool);
	SetElemTypeRtn(Float, Float, Bool);
	SetElemTypeRtn(Double, Double, Bool);
	SetElemTypeRtn(Complex, Complex, Bool);
	SetElemTypeRtn(Int8, Bool, Int8);
	SetElemTypeRtn(Int8, Int8, Int8);
	SetElemTypeRtn(UInt8, UInt8, Int8);
	SetElemTypeRtn(Int16, Int16, Int8);
	SetElemTypeRtn(UInt16, UInt16, Int8);
	SetElemTypeRtn(Int32, Int32, Int8);
	SetElemTypeRtn(UInt32, UInt32, Int8);
	SetElemTypeRtn(Int64, Int64, Int8);
	SetElemTypeRtn(UInt64, UInt64, Int8);
	SetElemTypeRtn(Half, Half, Int8);
	SetElemTypeRtn(Float, Float, Int8);
	SetElemTypeRtn(Double, Double, Int8);
	SetElemTypeRtn(Complex, Complex, Int8);
	SetElemTypeRtn(UInt8, Bool, UInt8);
	SetElemTypeRtn(UInt8, Int8, UInt8);
	SetElemTypeRtn(UInt8, UInt8, UInt8);
	SetElemTypeRtn(Int16, Int16, UInt8);
	SetElemTypeRtn(UInt16, UInt16, UInt8);
	SetElemTypeRtn(Int32, Int32, UInt8);
	SetElemTypeRtn(UInt32, UInt32, UInt8);
	SetElemTypeRtn(Int64, Int64, UInt8);
	SetElemTypeRtn(UInt64, UInt64, UInt8);
	SetElemTypeRtn(Half, Half, UInt8);
	SetElemTypeRtn(Float, Float, UInt8);
	SetElemTypeRtn(Double, Double, UInt8);
	SetElemTypeRtn(Complex, Complex, UInt8);
	SetElemTypeRtn(Int16, Bool, Int16);
	SetElemTypeRtn(Int16, Int8, Int16);
	SetElemTypeRtn(Int16, UInt8, Int16);
	SetElemTypeRtn(Int16, Int16, Int16);
	SetElemTypeRtn(UInt16, UInt16, Int16);
	SetElemTypeRtn(Int32, Int32, Int16);
	SetElemTypeRtn(UInt32, UInt32, Int16);
	SetElemTypeRtn(Int64, Int64, Int16);
	SetElemTypeRtn(UInt64, UInt64, Int16);
	SetElemTypeRtn(Half, Half, Int16);
	SetElemTypeRtn(Float, Float, Int16);
	SetElemTypeRtn(Double, Double, Int16);
	SetElemTypeRtn(Complex, Complex, Int16);
	SetElemTypeRtn(UInt16, Bool, UInt16);
	SetElemTypeRtn(UInt16, Int8, UInt16);
	SetElemTypeRtn(UInt16, UInt8, UInt16);
	SetElemTypeRtn(UInt16, Int16, UInt16);
	SetElemTypeRtn(UInt16, UInt16, UInt16);
	SetElemTypeRtn(Int32, Int32, UInt16);
	SetElemTypeRtn(UInt32, UInt32, UInt16);
	SetElemTypeRtn(Int64, Int64, UInt16);
	SetElemTypeRtn(UInt64, UInt64, UInt16);
	SetElemTypeRtn(Half, Half, UInt16);
	SetElemTypeRtn(Float, Float, UInt16);
	SetElemTypeRtn(Double, Double, UInt16);
	SetElemTypeRtn(Complex, Complex, UInt16);
	SetElemTypeRtn(Int32, Bool, Int32);
	SetElemTypeRtn(Int32, Int8, Int32);
	SetElemTypeRtn(Int32, UInt8, Int32);
	SetElemTypeRtn(Int32, Int16, Int32);
	SetElemTypeRtn(Int32, UInt16, Int32);
	SetElemTypeRtn(Int32, Int32, Int32);
	SetElemTypeRtn(UInt32, UInt32, Int32);
	SetElemTypeRtn(Int64, Int64, Int32);
	SetElemTypeRtn(UInt64, UInt64, Int32);
	SetElemTypeRtn(Half, Half, Int32);
	SetElemTypeRtn(Float, Float, Int32);
	SetElemTypeRtn(Double, Double, Int32);
	SetElemTypeRtn(Complex, Complex, Int32);
	SetElemTypeRtn(UInt32, Bool, UInt32);
	SetElemTypeRtn(UInt32, Int8, UInt32);
	SetElemTypeRtn(UInt32, UInt8, UInt32);
	SetElemTypeRtn(UInt32, Int16, UInt32);
	SetElemTypeRtn(UInt32, UInt16, UInt32);
	SetElemTypeRtn(UInt32, Int32, UInt32);
	SetElemTypeRtn(UInt32, UInt32, UInt32);
	SetElemTypeRtn(Int64, Int64, UInt32);
	SetElemTypeRtn(UInt64, UInt64, UInt32);
	SetElemTypeRtn(Half, Half, UInt32);
	SetElemTypeRtn(Float, Float, UInt32);
	SetElemTypeRtn(Double, Double, UInt32);
	SetElemTypeRtn(Complex, Complex, UInt32);
	SetElemTypeRtn(Int64, Bool, Int64);
	SetElemTypeRtn(Int64, Int8, Int64);
	SetElemTypeRtn(Int64, UInt8, Int64);
	SetElemTypeRtn(Int64, Int16, Int64);
	SetElemTypeRtn(Int64, UInt16, Int64);
	SetElemTypeRtn(Int64, Int32, Int64);
	SetElemTypeRtn(Int64, UInt32, Int64);
	SetElemTypeRtn(Int64, Int64, Int64);
	SetElemTypeRtn(UInt64, UInt64, Int64);
	SetElemTypeRtn(Half, Half, Int64);
	SetElemTypeRtn(Float, Float, Int64);
	SetElemTypeRtn(Double, Double, Int64);
	SetElemTypeRtn(Complex, Complex, Int64);
	SetElemTypeRtn(UInt64, Bool, UInt64);
	SetElemTypeRtn(UInt64, Int8, UInt64);
	SetElemTypeRtn(UInt64, UInt8, UInt64);
	SetElemTypeRtn(UInt64, Int16, UInt64);
	SetElemTypeRtn(UInt64, UInt16, UInt64);
	SetElemTypeRtn(UInt64, Int32, UInt64);
	SetElemTypeRtn(UInt64, UInt32, UInt64);
	SetElemTypeRtn(UInt64, Int64, UInt64);
	SetElemTypeRtn(UInt64, UInt64, UInt64);
	SetElemTypeRtn(Half, Half, UInt64);
	SetElemTypeRtn(Float, Float, UInt64);
	SetElemTypeRtn(Double, Double, UInt64);
	SetElemTypeRtn(Complex, Complex, UInt64);
	SetElemTypeRtn(Half, Bool, Half);
	SetElemTypeRtn(Half, Int8, Half);
	SetElemTypeRtn(Half, UInt8, Half);
	SetElemTypeRtn(Half, Int16, Half);
	SetElemTypeRtn(Half, UInt16, Half);
	SetElemTypeRtn(Half, Int32, Half);
	SetElemTypeRtn(Half, UInt32, Half);
	SetElemTypeRtn(Half, Int64, Half);
	SetElemTypeRtn(Half, UInt64, Half);
	SetElemTypeRtn(Half, Half, Half);
	SetElemTypeRtn(Float, Float, Half);
	SetElemTypeRtn(Double, Double, Half);
	SetElemTypeRtn(Complex, Complex, Half);
	SetElemTypeRtn(Float, Bool, Float);
	SetElemTypeRtn(Float, Int8, Float);
	SetElemTypeRtn(Float, UInt8, Float);
	SetElemTypeRtn(Float, Int16, Float);
	SetElemTypeRtn(Float, UInt16, Float);
	SetElemTypeRtn(Float, Int32, Float);
	SetElemTypeRtn(Float, UInt32, Float);
	SetElemTypeRtn(Float, Int64, Float);
	SetElemTypeRtn(Float, UInt64, Float);
	SetElemTypeRtn(Float, Half, Float);
	SetElemTypeRtn(Float, Float, Float);
	SetElemTypeRtn(Double, Double, Float);
	SetElemTypeRtn(Complex, Complex, Float);
	SetElemTypeRtn(Double, Bool, Double);
	SetElemTypeRtn(Double, Int8, Double);
	SetElemTypeRtn(Double, UInt8, Double);
	SetElemTypeRtn(Double, Int16, Double);
	SetElemTypeRtn(Double, UInt16, Double);
	SetElemTypeRtn(Double, Int32, Double);
	SetElemTypeRtn(Double, UInt32, Double);
	SetElemTypeRtn(Double, Int64, Double);
	SetElemTypeRtn(Double, UInt64, Double);
	SetElemTypeRtn(Double, Half, Double);
	SetElemTypeRtn(Double, Float, Double);
	SetElemTypeRtn(Double, Double, Double);
	SetElemTypeRtn(Complex, Complex, Double);
	SetElemTypeRtn(Complex, Bool, Complex);
	SetElemTypeRtn(Complex, Int8, Complex);
	SetElemTypeRtn(Complex, UInt8, Complex);
	SetElemTypeRtn(Complex, Int16, Complex);
	SetElemTypeRtn(Complex, UInt16, Complex);
	SetElemTypeRtn(Complex, Int32, Complex);
	SetElemTypeRtn(Complex, UInt32, Complex);
	SetElemTypeRtn(Complex, Int64, Complex);
	SetElemTypeRtn(Complex, UInt64, Complex);
	SetElemTypeRtn(Complex, Half, Complex);
	SetElemTypeRtn(Complex, Float, Complex);
	SetElemTypeRtn(Complex, Double, Complex);
	SetElemTypeRtn(Complex, Complex, Complex);
	AssocSymbol(Symbol::Empty,			Symbol::Empty,				ElemType::None);
	AssocSymbol(Gurax_Symbol(bool_),	Gurax_Symbol(at_bool),		ElemType::Bool);
	AssocSymbol(Gurax_Symbol(int8),		Gurax_Symbol(at_int8),		ElemType::Int8);
	AssocSymbol(Gurax_Symbol(uint8),	Gurax_Symbol(at_uint8),		ElemType::UInt8);
	AssocSymbol(Gurax_Symbol(int16),	Gurax_Symbol(at_int16),		ElemType::Int16);
	AssocSymbol(Gurax_Symbol(uint16),	Gurax_Symbol(at_uint16),	ElemType::UInt16);
	AssocSymbol(Gurax_Symbol(int32),	Gurax_Symbol(at_int32),		ElemType::Int32);
	AssocSymbol(Gurax_Symbol(uint32),	Gurax_Symbol(at_uint32),	ElemType::UInt32);
	AssocSymbol(Gurax_Symbol(int64),	Gurax_Symbol(at_int64),		ElemType::Int64);
	AssocSymbol(Gurax_Symbol(uint64),	Gurax_Symbol(at_uint64),	ElemType::UInt64);
	AssocSymbol(Gurax_Symbol(half),		Gurax_Symbol(at_half),		ElemType::Half);
	AssocSymbol(Gurax_Symbol(float_),	Gurax_Symbol(at_float),		ElemType::Float);
	AssocSymbol(Gurax_Symbol(double_),	Gurax_Symbol(at_double),	ElemType::Double);
	AssocSymbol(Gurax_Symbol(complex),	Gurax_Symbol(at_complex),	ElemType::Complex);
	AssocSymbol(Gurax_Symbol(char_),	Gurax_Symbol(at_char),		ElemType::Int8);
	AssocSymbol(Gurax_Symbol(uchar),	Gurax_Symbol(at_uchar),		ElemType::UInt8);
	AssocSymbol(Gurax_Symbol(short_),	Gurax_Symbol(at_short),		ElemType::Int16);
	AssocSymbol(Gurax_Symbol(ushort),	Gurax_Symbol(at_ushort),	ElemType::UInt16);
	AssocSymbol(Gurax_Symbol(int_),		Gurax_Symbol(at_int),		(sizeof(int) == sizeof(Int32))? ElemType::Int32 : ElemType::Int64);
	AssocSymbol(Gurax_Symbol(uint),		Gurax_Symbol(at_uint),		(sizeof(int) == sizeof(Int32))? ElemType::UInt32 : ElemType::UInt64);
	AssocSymbol(Gurax_Symbol(long_),	Gurax_Symbol(at_long),		(sizeof(long) == sizeof(Int32))? ElemType::Int32 : ElemType::Int64);
	AssocSymbol(Gurax_Symbol(ulong),	Gurax_Symbol(at_ulong),		(sizeof(long) == sizeof(Int32))? ElemType::UInt32 : ElemType::UInt64);
	ElemType::Bool.bytes				= sizeof(bool);
	ElemType::Int8.bytes				= sizeof(Int8);
	ElemType::UInt8.bytes				= sizeof(UInt8);
	ElemType::Int16.bytes				= sizeof(Int16);
	ElemType::UInt16.bytes				= sizeof(UInt16);
	ElemType::Int32.bytes				= sizeof(Int32);
	ElemType::UInt32.bytes				= sizeof(UInt32);
	ElemType::Int64.bytes				= sizeof(Int64);
	ElemType::UInt64.bytes				= sizeof(UInt64);
	ElemType::Half.bytes				= sizeof(Half);
	ElemType::Float.bytes				= sizeof(Float);
	ElemType::Double.bytes				= sizeof(Double);
	ElemType::Complex.bytes				= sizeof(Complex);
	ElemType::None.pSymbol				= Symbol::Empty;
	ElemType::Bool.pSymbol				= Gurax_Symbol(bool_);
	ElemType::Int8.pSymbol				= Gurax_Symbol(int8);
	ElemType::UInt8.pSymbol				= Gurax_Symbol(uint8);
	ElemType::Int16.pSymbol				= Gurax_Symbol(int16);
	ElemType::UInt16.pSymbol			= Gurax_Symbol(uint16);
	ElemType::Int32.pSymbol				= Gurax_Symbol(int32);
	ElemType::UInt32.pSymbol			= Gurax_Symbol(uint32);
	ElemType::Int64.pSymbol				= Gurax_Symbol(int64);
	ElemType::UInt64.pSymbol			= Gurax_Symbol(uint64);
	ElemType::Half.pSymbol				= Gurax_Symbol(half);
	ElemType::Float.pSymbol				= Gurax_Symbol(float_);
	ElemType::Double.pSymbol			= Gurax_Symbol(double_);
	ElemType::Complex.pSymbol			= Gurax_Symbol(complex);
	SetFuncBurst(IndexSetValue,			IndexSetValue_T);
	SetFuncBurst(IndexGetValue,			IndexGetValue_T);
	SetFuncBurst(IndexSetDouble,		IndexSetDouble_T);
	SetFuncBurst(IndexGetDouble,		IndexGetDouble_T);
	SetFuncBurst(InjectFromValueList,	InjectFromValueList_T);
	SetFuncBurst(InjectFromIterator,	InjectFromIterator_T);
	SetFuncBurst(ExtractToValueOwner,	ExtractToValueOwner_T);
	SetFuncBurst2(CopyElems,			CopyElems_T);
	SetFuncBurst2(Transpose,			Transpose_T);
	SetFuncBurst3(Add_ArrayArray,		Add_ArrayArray_T);
	SetFuncBurst(Add_ArrayNumber,		Add_ArrayNumber_T);
	SetFuncBurst(Add_ArrayComplex,		Add_ArrayComplex_T);
	SetFuncBurst3(Sub_ArrayArray,		Sub_ArrayArray_T);
	SetFuncBurst(Sub_ArrayNumber,		Sub_ArrayNumber_T);
	SetFuncBurst(Sub_NumberArray,		Sub_NumberArray_T);
	SetFuncBurst(Sub_ArrayComplex,		Sub_ArrayComplex_T);
	SetFuncBurst(Sub_ComplexArray,		Sub_ComplexArray_T);
	SetFuncBurst3(Mul_ArrayArray,		Mul_ArrayArray_T);
	SetFuncBurst(Mul_ArrayNumber,		Mul_ArrayNumber_T);
	SetFuncBurst(Mul_ArrayComplex,		Mul_ArrayComplex_T);
	SetFuncBurst3(Div_ArrayArray,		Div_ArrayArray_T);
	SetFuncBurst(Div_ArrayNumber,		Div_ArrayNumber_T);
	SetFuncBurst(Div_NumberArray,		Div_NumberArray_T);
	SetFuncBurst(Div_ArrayComplex,		Div_ArrayComplex_T);
	SetFuncBurst(Div_ComplexArray,		Div_ComplexArray_T);
	SetFuncBurst3(Dot_ArrayArray,		Dot_ArrayArray_T);
	SetFuncBurst3(Cross_ArrayArray,		Cross_ArrayArray_T);
}

void Array::InjectElems(ValueList& values, size_t offset, size_t len)
{
	_elemType.InjectFromValueList(values, GetPointerC<void>(), offset, len);
}

void Array::InjectElems(ValueList& values, size_t offset)
{
	InjectElems(values, offset, std::min(values.size(), _dimSizes.CalcLength() - offset));
}

bool Array::InjectElems(Iterator& iterator, size_t offset, size_t len)
{
	return _elemType.InjectFromIterator(iterator, GetPointerC<void>(), offset, len);
}

bool Array::InjectElems(Iterator& iterator, size_t offset)
{
	return InjectElems(iterator, offset, _dimSizes.CalcLength() - offset);
}

void Array::InjectElems(const void* pSrc, ElemTypeT& elemType, size_t offset, size_t len)
{
	_elemType.CopyElems[elemType.id](GetPointerC<void>(), pSrc, offset, len);
}

void Array::ExtractElems(ValueOwner& values, size_t offset, size_t len) const
{
	values.reserve(values.size() + len);
	_elemType.ExtractToValueOwner(values, GetPointerC<void>(), offset, len);
}

void Array::ExtractElemsSub(ValueOwner& values, size_t& offset, DimSizes::const_iterator pDimSize) const
{
	if (pDimSize + 1 == _dimSizes.end()) {
		ExtractElems(values, offset, *pDimSize);
		offset += *pDimSize;
	} else {
		for (size_t i = 0; i < *pDimSize; i++) {
			RefPtr<ValueOwner> pValues(new ValueOwner());
			ExtractElemsSub(*pValues, offset, pDimSize + 1);
			VType& vtypeOfElems = pValues->GetVTypeOfElemsQuick();
			values.push_back(new Value_List(vtypeOfElems, pValues.release()));
		}
	}
}

void Array::ExtractElems(ValueOwner& values) const
{
	size_t offset = 0;
	ExtractElemsSub(values, offset, _dimSizes.begin());
}

Array* Array::Transpose() const
{
	const DimSizes& dimSizes = GetDimSizes();
	if (dimSizes.size() < 2) return Clone();
	DimSizes dimSizesRtn;
	dimSizesRtn.reserve(dimSizes.size());
	size_t nUnits = 1;
	for (auto pDim = dimSizes.begin(); pDim != dimSizes.begin() + dimSizes.size() - 2; pDim++) {
		nUnits *= *pDim;
		dimSizesRtn.push_back(*pDim);
	}
	size_t nRows = dimSizes.GetColSize();
	size_t nCols = dimSizes.GetRowSize();
	size_t lenFwd = nRows * nCols;
	dimSizesRtn.push_back(nRows);
	dimSizesRtn.push_back(nCols);
	RefPtr<Array> pArrayRtn(Create(GetElemType(), dimSizesRtn));	
	auto func = GetElemType().Transpose[GetElemType().id];
	void* pvDst = pArrayRtn->GetPointerC<void>();
	const void* pvSrc = GetPointerC<void>();
	for (size_t iUnit = 0; iUnit < nUnits; iUnit++) {
		func(pvDst, nRows, nCols, pvSrc);
		pvDst = pArrayRtn->FwdPointer(pvDst, lenFwd);
		pvSrc = FwdPointer(pvSrc, lenFwd);
	}
	return pArrayRtn.release();
}

Array* Array::GenericOp(const Array& arrayL, const Array& arrayR,
	const std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>& func)
{
	size_t nUnits = 1;
	size_t lenUnit = 0;;
	size_t lenFwdL = 0, lenFwdR = 0;
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	const DimSizes* pDimSizesRtn = nullptr;;
	bool matchFlag = false;
	if (dimSizesL.size() >= dimSizesR.size()) {
		size_t nDimsHead = dimSizesL.size() - dimSizesR.size();
		nUnits = DimSizes::CalcLength(dimSizesL.begin(), dimSizesL.begin() + nDimsHead);
		lenUnit = dimSizesR.CalcLength();
		lenFwdL = lenUnit, lenFwdR = 0;
		pDimSizesRtn = &dimSizesL;
		matchFlag = dimSizesR.DoesMatch(dimSizesL, nDimsHead);
	} else {
		size_t nDimsHead = dimSizesR.size() - dimSizesL.size();
		nUnits = DimSizes::CalcLength(dimSizesR.begin(), dimSizesR.begin() + nDimsHead);
		lenUnit = dimSizesL.CalcLength();
		lenFwdL = 0, lenFwdR = lenUnit;
		pDimSizesRtn = &dimSizesR;
		matchFlag = dimSizesL.DoesMatch(dimSizesR, nDimsHead);
	}
	if (!matchFlag) {
		Error::Issue(ErrorType::RangeError, "unmatched array size");
		return nullptr;
	}
	RefPtr<Array> pArrayRtn(Create(GetElemTypeRtn(arrayL, arrayR), *pDimSizesRtn));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	for (size_t iUnit = 0; iUnit < nUnits; iUnit++) {
		func(pvRtn, pvL, pvR, lenUnit);
		pvRtn = pArrayRtn->FwdPointer(pvRtn, lenUnit);
		pvL = arrayL.FwdPointer(pvL, lenFwdL);
		pvR = arrayR.FwdPointer(pvR, lenFwdR);
	}
	return pArrayRtn.release();
}

Array* Array::GenericOp(const Array& arrayL, Double numR,
	const std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>& func)
{
	//const DimSizes& dimSizesL = arrayL.GetDimSizes();
	RefPtr<Array> pArrayRtn(Create(arrayL.GetElemType(), arrayL.GetDimSizes()));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	size_t len = arrayL.GetDimSizes().CalcLength();
	func(pvRtn, pvL, numR, len);
	return pArrayRtn.release();
}

Array* Array::GenericOp(Double numL, const Array& arrayR,
	const std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>& func)
{
	//const DimSizes& dimSizesR = arrayR.GetDimSizes();
	RefPtr<Array> pArrayRtn(Create(arrayR.GetElemType(), arrayR.GetDimSizes()));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	size_t len = arrayR.GetDimSizes().CalcLength();
	func(pvRtn, numL, pvR, len);
	return pArrayRtn.release();
}

Array* Array::GenericOp(const Array& arrayL, const Complex& numR,
	const std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>& func)
{
	//const DimSizes& dimSizesL = arrayL.GetDimSizes();
	RefPtr<Array> pArrayRtn(Create(ElemType::Complex, arrayL.GetDimSizes()));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	size_t len = arrayL.GetDimSizes().CalcLength();
	func(pvRtn, pvL, numR, len);
	return pArrayRtn.release();
}

Array* Array::GenericOp(const Complex& numL, const Array& arrayR,
	const std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>& func)
{
	//const DimSizes& dimSizesR = arrayR.GetDimSizes();
	RefPtr<Array> pArrayRtn(Create(ElemType::Complex, arrayR.GetDimSizes()));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	size_t len = arrayR.GetDimSizes().CalcLength();
	func(pvRtn, numL, pvR, len);
	return pArrayRtn.release();
}

Array* Array::Add(const Array& arrayL, const Array& arrayR)
{
	return GenericOp(arrayL, arrayR, arrayL.GetElemType().Add_ArrayArray[arrayR.GetElemType().id]);
}

Array* Array::Add(const Array& arrayL, Double numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Add_ArrayNumber);
}

Array* Array::Add(const Array& arrayL, const Complex& numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Add_ArrayComplex);
}

Array* Array::Sub(const Array& arrayL, const Array& arrayR)
{
	return GenericOp(arrayL, arrayR, arrayL.GetElemType().Sub_ArrayArray[arrayR.GetElemType().id]);
}

Array* Array::Sub(const Array& arrayL, Double numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Sub_ArrayNumber);
}

Array* Array::Sub(Double numL, const Array& arrayR)
{
	return GenericOp(numL, arrayR, arrayR.GetElemType().Sub_NumberArray);
}

Array* Array::Sub(const Array& arrayL, const Complex& numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Sub_ArrayComplex);
}

Array* Array::Sub(const Complex& numL, const Array& arrayR)
{
	return GenericOp(numL, arrayR, arrayR.GetElemType().Sub_ComplexArray);
}

Array* Array::Mul(const Array& arrayL, const Array& arrayR)
{
	return GenericOp(arrayL, arrayR, arrayL.GetElemType().Mul_ArrayArray[arrayR.GetElemType().id]);
}

Array* Array::Mul(const Array& arrayL, Double numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Mul_ArrayNumber);
}

Array* Array::Mul(const Array& arrayL, const Complex& numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Mul_ArrayComplex);
}

Array* Array::Div(const Array& arrayL, const Array& arrayR)
{
	return GenericOp(arrayL, arrayR, arrayL.GetElemType().Div_ArrayArray[arrayR.GetElemType().id]);
}

Array* Array::Div(const Array& arrayL, Double numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Div_ArrayNumber);
}

Array* Array::Div(Double numL, const Array& arrayR)
{
	return GenericOp(numL, arrayR, arrayR.GetElemType().Div_NumberArray);
}

Array* Array::Div(const Array& arrayL, const Complex& numR)
{
	return GenericOp(arrayL, numR, arrayL.GetElemType().Div_ArrayComplex);
}

Array* Array::Div(const Complex& numL, const Array& arrayR)
{
	return GenericOp(numL, arrayR, arrayR.GetElemType().Div_ComplexArray);
}

Array* Array::Dot(const Array& arrayL, const Array& arrayR)
{
#if 1
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	if (dimSizesL.size() != 2 || dimSizesR.size() != 2 ||
					dimSizesL.GetColSize() != dimSizesR.GetRowSize()) {
		Error::Issue(ErrorType::RangeError, "unmatched array size");
		return nullptr;
	}
	DimSizes dimSizesRtn(dimSizesL.GetRowSize(), dimSizesR.GetColSize());
	auto func = arrayL.GetElemType().Dot_ArrayArray[arrayR.GetElemType().id];
	RefPtr<Array> pArrayRtn(Create(GetElemTypeRtn(arrayL, arrayR), dimSizesRtn));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	func(pvRtn, dimSizesRtn.GetRowSize(), dimSizesRtn.GetColSize(), pvL, pvR, dimSizesL.GetColSize());
	return pArrayRtn.release();
#else
	size_t nUnits = 1;
	size_t lenUnit = 0;;
	size_t lenFwdL = 0, lenFwdR = 0;
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	const DimSizes* pDimSizesRtn = nullptr;;
	bool matchFlag = false;
	if (dimSizesL.size() >= dimSizesR.size()) {
		size_t nDimsHead = dimSizesL.size() - dimSizesR.size();
		nUnits = DimSizes::CalcLength(dimSizesL.begin(), dimSizesL.begin() + nDimsHead);
		lenUnit = dimSizesR.CalcLength();
		lenFwdL = lenUnit, lenFwdR = 0;
		pDimSizesRtn = &dimSizesL;
		matchFlag = dimSizesR.DoesMatchDot(dimSizesL, nDimsHead);
	} else {
		size_t nDimsHead = dimSizesR.size() - dimSizesL.size();
		nUnits = DimSizes::CalcLength(dimSizesR.begin(), dimSizesR.begin() + nDimsHead);
		lenUnit = dimSizesL.CalcLength();
		lenFwdL = 0, lenFwdR = lenUnit;
		pDimSizesRtn = &dimSizesR;
		matchFlag = dimSizesL.DoesMatchDot(dimSizesR, nDimsHead);
	}
	if (!matchFlag) {
		Error::Issue(ErrorType::RangeError, "unmatched array size");
		return nullptr;
	}
	RefPtr<Array> pArrayRtn(Create(GetElemTypeRtn(arrayL, arrayR), *pDimSizesRtn));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	auto func = arrayL.GetElemType().Dot_ArrayArray[arrayR.GetElemType().id];
	size_t m = pDimSizesRtn->GetRowSize();
	size_t n = pDimSizesRtn->GetColSize();
	size_t l = dimSizesL.GetColSize();
	for (size_t iUnit = 0; iUnit < nUnits; iUnit++) {
		func(pvRtn, m, n, pvL, pvR, l);
		pvRtn = pArrayRtn->FwdPointer(pvRtn, lenUnit);
		pvL = arrayL.FwdPointer(pvL, lenFwdL);
		pvR = arrayR.FwdPointer(pvR, lenFwdR);
	}
	return pArrayRtn.release();
#endif
}

Array* Array::Cross(const Array& arrayL, const Array& arrayR)
{
	const DimSizes& dimSizesL = arrayL.GetDimSizes();
	const DimSizes& dimSizesR = arrayR.GetDimSizes();
	if (dimSizesL.size() != 1 || dimSizesR.size() != 1 ||
								dimSizesL[0] != 3 || dimSizesR[0] != 3) {
		Error::Issue(ErrorType::RangeError, "unmatched array size");
		return nullptr;
	}
	size_t n = 3;
	RefPtr<Array> pArrayRtn(Create(GetElemTypeRtn(arrayL, arrayR), DimSizes(n)));
	void* pvRtn = pArrayRtn->GetPointerC<void>();
	const void* pvL = arrayL.GetPointerC<void>();
	const void* pvR = arrayR.GetPointerC<void>();
	auto func = arrayL.GetElemType().Cross_ArrayArray[arrayR.GetElemType().id];
	func(pvRtn, pvL, pvR, n);
	return pArrayRtn.release();
}

Value_List* Array::ToList() const
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	ExtractElems(*pValues);
	VType& vtypeOfElems = pValues->GetVTypeOfElemsQuick();
	return new Value_List(vtypeOfElems, pValues.release());
}

Array* Array::CreateCasted(ElemTypeT& elemType) const
{
	RefPtr<Array> pArray(Array::Create(elemType, _dimSizes));
	pArray->InjectElems(GetPointerC<void>(), GetElemType(), 0, _dimSizes.CalcLength());
	return pArray.release();
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Format("Array:%s:dim=%s",
		_elemType.pSymbol->GetName(), _dimSizes.ToString(StringStyle::Cram).c_str());
}

//------------------------------------------------------------------------------
// Array::ElemType
//------------------------------------------------------------------------------
Array::ElemTypeT Array::ElemType::None(-1);
Array::ElemTypeT Array::ElemType::Bool(0);
Array::ElemTypeT Array::ElemType::Int8(1);
Array::ElemTypeT Array::ElemType::UInt8(2);
Array::ElemTypeT Array::ElemType::Int16(3);
Array::ElemTypeT Array::ElemType::UInt16(4);
Array::ElemTypeT Array::ElemType::Int32(5);
Array::ElemTypeT Array::ElemType::UInt32(6);
Array::ElemTypeT Array::ElemType::Int64(7);
Array::ElemTypeT Array::ElemType::UInt64(8);
Array::ElemTypeT Array::ElemType::Half(9);
Array::ElemTypeT Array::ElemType::Float(10);
Array::ElemTypeT Array::ElemType::Double(11);
Array::ElemTypeT Array::ElemType::Complex(12);

bool Array::ElemTypeT::IsNone() const
{
	return IsIdentical(ElemType::None);
}

//------------------------------------------------------------------------------
// DimSizes
//------------------------------------------------------------------------------
DimSizes::DimSizes(const ValueList& values)
{
	reserve(values.size());
	for (const Value* pValue : values) {
		push_back(Value_Number::GetNumberPos<size_t>(*pValue));
		if (Error::IsIssued()) break;
	}
}

size_t DimSizes::CalcLength(const_iterator pDimSizeBegin, const_iterator pDimSizeEnd)
{
	size_t len = 1;
	for (auto pDimSize = pDimSizeBegin; pDimSize != pDimSizeEnd; pDimSize++) len *= *pDimSize;
	return len;
}

bool DimSizes::DoesMatch(const DimSizes& dimSizes, size_t offset) const
{
	auto pDimSize1 = begin();
	auto pDimSize2 = dimSizes.begin() + offset;
	if (size() != dimSizes.size() - offset) return false;
	for ( ; pDimSize1 != end(); pDimSize1++, pDimSize2++) {
		if (*pDimSize1 != *pDimSize2) return false;
	}
	return true;
}

bool DimSizes::DoesMatchDot(const DimSizes& dimSizes, size_t offset) const
{
	auto pDimSize1 = begin();
	auto pDimSize2 = dimSizes.begin() + offset;
	if (size() != dimSizes.size() - offset) return false;
	auto pDimSizeEnd1 = begin() + size() - 2;
	for ( ; pDimSize1 != pDimSizeEnd1; pDimSize1++, pDimSize2++) {
		if (*pDimSize1 != *pDimSize2) return false;
	}
	return GetColSize() == dimSizes.GetRowSize();
}

bool DimSizes::Verify(const ValueList& values) const
{
	auto pDimSize = begin();
	auto ppValue = values.begin();
	for ( ; pDimSize != end() && ppValue != values.end(); pDimSize++, ppValue++) {
		if (*pDimSize != Value_Number::GetNumber<size_t>(**ppValue)) return false;
	}
	return pDimSize == end() && ppValue == values.end();
}

String DimSizes::ToString(const StringStyle& ss) const
{
	String str;
	for (size_t dimSize : *this) {
		if (!str.empty()) str += 'x';
		str.Format("%zu", dimSize);
	}
	return str;
}

}
