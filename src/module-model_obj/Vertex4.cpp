//==============================================================================
// Vertex4.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex4
//------------------------------------------------------------------------------
bool Vertex4::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	if (iParam >= 4) {
		Error::Issue(ErrorType::FormatError, "%d: too many elements for item v", tokenizer.GetLineNo());
		return false;
	}
	double num;
	if (!Content::ExtractFloat(tokenizer.GetField(), &num)) {
		SetError_FormatError();
		return false;
	}
	return true;
}

bool Vertex4::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	return true;
}

String Vertex4::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Vertex4:%g,%g,%g,%g", _x, _y, _z, _w);
}

//------------------------------------------------------------------------------
// Vertex4List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Vertex4Owner
//------------------------------------------------------------------------------
void Vertex4Owner::Clear()
{
	for (Vertex4* pVertex4 : *this) Vertex4::Delete(pVertex4);
	clear();
}

Gurax_EndModuleScope(model_obj)
