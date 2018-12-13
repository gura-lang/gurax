//==============================================================================
// Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ErrorType
//------------------------------------------------------------------------------
const ErrorType ErrorType::SyntaxError("syntax error");

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
	if (!_fileName.empty()) {
		rtn += _fileName;
		if (_lineNo == 0) {
			rtn += ": ";
		} else {
			char buff[64];
			::sprintf(buff, ":%d: ", _lineNo);
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

void Error::Issue(const ErrorType& errorType, const Expr* pExpr, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, pExpr->GetPathNameSrc(), pExpr->GetLineNo(), format, ap);
}

void Error::Issue(const ErrorType& errorType, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, "", 0, format, ap);
}

void Error::Issue(const ErrorType& errorType, const String& fileName, int lineNo, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, fileName, lineNo, format, ap);
}

void Error::IssueV(const ErrorType& errorType, const String& fileName, int lineNo, const char* format, va_list ap)
{
	char text[512];
	::vsprintf(text, format, ap);
	_pErrorOwnerGlobal->push_back(new Error(errorType, fileName, lineNo, text));
}

void Error::Print(FILE* fp)
{
	for (auto pError : *_pErrorOwnerGlobal) {
		::fprintf(fp, "%s\n", pError->MakeMessage().c_str());
	}
}

//------------------------------------------------------------------------------
// ErrorList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------

}
