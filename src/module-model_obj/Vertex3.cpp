//==============================================================================
// Vertex3.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Vertex3
//------------------------------------------------------------------------------
bool Vertex3::FeedField(const Tokenizer& tokenizer, size_t iParam)
{
	switch (iParam) {
	case 0: {
		if (!tokenizer.ExtractFloat(&_x)) return false;
		break;
	}
	case 1: {
		if (!tokenizer.ExtractFloat(&_y)) return false;
		break;
	}
	case 2: {
		if (!tokenizer.ExtractFloat(&_z)) return false;
		break;
	}
	case 3: {
		Error::Issue(ErrorType::FormatError, "%d: too many elements", tokenizer.GetLineNo());
		return false;
	}
	}
	return true;
}

bool Vertex3::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	if (nParams < 2) {
		Error::Issue(ErrorType::FormatError,
			"%d: there should be three elements at least", tokenizer.GetLineNo());
		return false;
	}
	return true;
}

String Vertex3::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Vertex3:%g,%g,%g", _x, _y, _z);
}

//------------------------------------------------------------------------------
// Vertex3List
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Vertex3Owner
//------------------------------------------------------------------------------
void Vertex3Owner::Clear()
{
	for (Vertex3* pVertex3 : *this) Vertex3::Delete(pVertex3);
	clear();
}

Gurax_EndModuleScope(model_obj)
