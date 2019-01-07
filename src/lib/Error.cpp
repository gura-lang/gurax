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

void Error::Issue(const ErrorType& errorType, Expr* pExpr, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, pExpr, format, ap);
}

void Error::Issue(const ErrorType& errorType, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, format, ap);
}

void Error::Issue(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	IssueV(errorType, pFileName, lineNoTop, lineNoBtm, format, ap);
}

void Error::IssueV(const ErrorType& errorType, const char* format, va_list ap)
{
	char text[512];
	::vsprintf(text, format, ap);
	_pErrorOwnerGlobal->push_back(new Error(errorType, text));
}

void Error::IssueV(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, const char* format, va_list ap)
{
	char text[512];
	::vsprintf(text, format, ap);
	_pErrorOwnerGlobal->push_back(new Error(errorType, pFileName, lineNoTop, lineNoBtm, text));
}

void Error::IssueV(const ErrorType& errorType, Expr *pExpr, const char* format, va_list ap)
{
	char text[512];
	::vsprintf(text, format, ap);
	_pErrorOwnerGlobal->push_back(new Error(errorType, pExpr, text));
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

}
