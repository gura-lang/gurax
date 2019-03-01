//==============================================================================
// Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ErrorType
//------------------------------------------------------------------------------
const ErrorType ErrorType::ArgumentError("argument error");
const ErrorType ErrorType::CodecError("codec error");
const ErrorType ErrorType::IndexError("index error");
const ErrorType ErrorType::InvalidOperation("invalid operation");
const ErrorType ErrorType::SyntaxError("syntax error");
const ErrorType ErrorType::TypeError("type error");
const ErrorType ErrorType::ValueError("value error");

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
bool Error::_errorIssuedFlag = false;
ErrorOwner* Error::_pErrorOwnerGlobal = nullptr;

void Error::Bootup()
{
	_errorIssuedFlag = false;
	_pErrorOwnerGlobal = new ErrorOwner();
}

String Error::MakeMessage() const
{
	String rtn;
	if (_pFileName && !_pFileName->GetStringSTL().empty()) {
		rtn += _pFileName->GetStringSTL();
		if (_lineNoTop == 0) {
			rtn += ": ";
		} else if (_lineNoTop == _lineNoBtm) {
			char buff[128];
			::sprintf(buff, ":%d: ", _lineNoTop);
			rtn += buff;
		} else {
			char buff[128];
			::sprintf(buff, ":%d:%d: ", _lineNoTop, _lineNoBtm);
			rtn += buff;
		}
	}
	rtn += _errorType.GetName();
	rtn += ": ";
	rtn += _text;
	return rtn;
}

void Error::Clear()
{
	_errorIssuedFlag = false;
	_pErrorOwnerGlobal->Clear();
}

void Error::Print(FILE* fp)
{
	for (Error* pError : *_pErrorOwnerGlobal) {
		::fprintf(fp, "%s\n", pError->MakeMessage().c_str());
	}
}

//------------------------------------------------------------------------------
// ErrorList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------
void ErrorOwner::Clear()
{
	for (Error* pError : *this) Error::Delete(pError);
	clear();
}

}
