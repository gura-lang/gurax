//==============================================================================
// Index.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
Value* Index::IndexGet() const
{
	return GetValueCar().DoIndexGet(*this);
}

void Index::IndexSet(Value* pValue)
{
	GetValueCar().DoIndexSet(*this, pValue);
}

Value* Index::IndexOpApply(Value& value, Processor& processor, Operator& op)
{
	return GetValueCar().DoIndexOpApply(*this, value, processor, op);
}

String Index::ToString(const StringStyle& ss) const
{
	return String().Format("Index:%s", GetValueCar().ToString(StringStyle(ss).SetQuoteSymbol()).c_str());
}

}
