//==============================================================================
// Array.cpp
//==============================================================================
#include "stdafx.h"
#include <gurax-tentative.h>

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
template<typename T_Elem> void Tmpl_IndexSet(void* p, size_t idx, Double num)
{
	*(reinterpret_cast<T_Elem*>(p) + idx) = static_cast<T_Elem>(num);
}

Array::Array(ElemTypeT& elemType, size_t nElems, Memory* pMemory) :
				_elemType(elemType), _nElems(nElems), _pMemory(pMemory)
{
}

void Array::Bootup()
{
	ElemType::None.pSymbol		= Symbol::Empty;
	ElemType::Bool.pSymbol		= Gurax_Symbol(bool_);
	ElemType::Int8.pSymbol		= Gurax_Symbol(int8);
	ElemType::UInt8.pSymbol		= Gurax_Symbol(uint8);
	ElemType::Int16.pSymbol		= Gurax_Symbol(int16);
	ElemType::UInt16.pSymbol	= Gurax_Symbol(uint16);
	ElemType::Int32.pSymbol		= Gurax_Symbol(int32);
	ElemType::UInt32.pSymbol	= Gurax_Symbol(uint32);
	ElemType::Int64.pSymbol		= Gurax_Symbol(int64);
	ElemType::UInt64.pSymbol	= Gurax_Symbol(uint64);
	ElemType::Half.pSymbol		= Gurax_Symbol(half);
	ElemType::Float.pSymbol		= Gurax_Symbol(float_);
	ElemType::Double.pSymbol	= Gurax_Symbol(double_);
	ElemType::Complex.pSymbol	= Gurax_Symbol(complex);
	ElemType::Bool.IndexSet		= Tmpl_IndexSet<Bool>;
	ElemType::Int8.IndexSet		= Tmpl_IndexSet<Int8>;
	ElemType::UInt8.IndexSet	= Tmpl_IndexSet<UInt8>;
	ElemType::Int16.IndexSet	= Tmpl_IndexSet<Int16>;
	ElemType::UInt16.IndexSet	= Tmpl_IndexSet<UInt16>;
	ElemType::Int32.IndexSet	= Tmpl_IndexSet<Int32>;
	ElemType::UInt32.IndexSet	= Tmpl_IndexSet<UInt32>;
	ElemType::Int64.IndexSet	= Tmpl_IndexSet<Int64>;
	ElemType::UInt64.IndexSet	= Tmpl_IndexSet<UInt64>;
	ElemType::Half.IndexSet		= Tmpl_IndexSet<Half>;
	ElemType::Float.IndexSet	= Tmpl_IndexSet<Float>;
	ElemType::Double.IndexSet	= Tmpl_IndexSet<Double>;
	ElemType::Complex.IndexSet	= Tmpl_IndexSet<Complex>;
}

String Array::ToString(const StringStyle& ss) const
{
	return String().Format("Array:%s", _elemType.pSymbol->GetName());
}

//------------------------------------------------------------------------------
// Array::ElemType
//------------------------------------------------------------------------------
Array::ElemTypeT Array::ElemType::None(0);
Array::ElemTypeT Array::ElemType::Bool(sizeof(Bool));
Array::ElemTypeT Array::ElemType::Int8(sizeof(Int8));
Array::ElemTypeT Array::ElemType::UInt8(sizeof(UInt8));
Array::ElemTypeT Array::ElemType::Int16(sizeof(Int16));
Array::ElemTypeT Array::ElemType::UInt16(sizeof(UInt16));
Array::ElemTypeT Array::ElemType::Int32(sizeof(Int32));
Array::ElemTypeT Array::ElemType::UInt32(sizeof(UInt32));
Array::ElemTypeT Array::ElemType::Int64(sizeof(Int64));
Array::ElemTypeT Array::ElemType::UInt64(sizeof(UInt64));
Array::ElemTypeT Array::ElemType::Half(sizeof(Half));
Array::ElemTypeT Array::ElemType::Float(sizeof(Float));
Array::ElemTypeT Array::ElemType::Double(sizeof(Double));
Array::ElemTypeT Array::ElemType::Complex(sizeof(Complex));

bool Array::ElemTypeT::IsNone() const
{
	return IsIdentical(ElemType::None);
}

}
