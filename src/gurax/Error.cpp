//==============================================================================
// Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Error
//-----------------------------------------------------------------------------
bool Error::_errorFlag = false;
ErrorOwner* Error::_pErrorOwnerGlobal = nullptr;

void Error::Bootup()
{
	_errorFlag = false;
	_pErrorOwnerGlobal = new ErrorOwner();
}

String Error::GetString() const
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
	rtn += _message;
	return rtn;
}

void Error::Clear()
{
	_errorFlag = false;
	_pErrorOwnerGlobal->Clear();
}

void Error::AddError(const Expr* pExpr, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	AddErrorV(pExpr->GetPathNameSrc(), pExpr->GetLineNo(), format, ap);
}

void Error::AddError(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	AddErrorV("", 0, format, ap);
}

void Error::AddError(const String& fileName, int lineNo, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	AddErrorV(fileName, lineNo, format, ap);
}

void Error::AddErrorV(const String& fileName, int lineNo, const char* format, va_list ap)
{
	char message[512];
	::vsprintf(message, format, ap);
	if (!_pErrorOwnerGlobal->DoesExist(fileName.c_str(), lineNo, message)) {
		_pErrorOwnerGlobal->push_back(new Error(fileName, lineNo, message));
	}
}

void Error::Print(FILE* fp)
{
	for (auto pError : *_pErrorOwnerGlobal) {
		::fprintf(fp, "%s\n", pError->GetString().c_str());
	}
}

String Error::MakeResultText()
{
	String str;
	for (auto pError : *_pErrorOwnerGlobal) {
		str += pError->GetString();
		str += "\n";
	}
	return str;
}

//-----------------------------------------------------------------------------
// ErrorList
//-----------------------------------------------------------------------------
bool ErrorList::DoesExist(const char* fileName, int lineNo, const char* message)
{
	for (auto pError : *this) {
		if (pError->DoesMatch(fileName, lineNo, message)) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// ErrorOwner
//-----------------------------------------------------------------------------

}
