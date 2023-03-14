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
		if (!tokenizer.ExtractFloat(&_w)) return false;
		break;
	}
	case 4: {
		Error::Issue(ErrorType::FormatError, "%d: too many elements", tokenizer.GetLineNo());
		return false;
	}
	}
	return true;
}

bool Vertex4::FinishField(const Tokenizer& tokenizer, size_t nParams)
{
	if (nParams < 3) {
		Error::Issue(ErrorType::FormatError,
			"%d: item v should have three elements at least", tokenizer.GetLineNo());
		return false;
	}
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
