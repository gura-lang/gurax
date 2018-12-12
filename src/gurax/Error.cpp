//==============================================================================
// Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Error
//-----------------------------------------------------------------------------
Error Error::_instance;

void Error::AddError(const Expr* pExpr, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	_instance.AddErrorV(pExpr->GetPathNameSrc(), pExpr->GetLineNo(), format, ap);
}

void Error::AddError(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	_instance.AddErrorV("", 0, format, ap);
}

void Error::AddError(const String& fileName, int lineNo, const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	_instance.AddErrorV(fileName, lineNo, format, ap);
}

void Error::AddErrorV(const String& fileName, int lineNo, const char* format, va_list ap)
{
	char message[512];
	::vsprintf(message, format, ap);
	if (!_instance.GetEntryOwner().DoesExist(fileName.c_str(), lineNo, message)) {
		_instance.GetEntryOwner().push_back(new Entry(fileName, lineNo, message));
	}
}

void Error::Print(FILE* fp)
{
	for (auto pEntry : _instance.GetEntryOwner()) {
		::fprintf(fp, "%s\n", pEntry->GetString().c_str());
	}
}

String Error::MakeResultText()
{
	String str;
	for (auto pEntry : _instance.GetEntryOwner()) {
		str += pEntry->GetString();
		str += "\n";
	}
	return str;
}

//-----------------------------------------------------------------------------
// Error::Entry
//-----------------------------------------------------------------------------
String Error::Entry::GetString() const
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

//-----------------------------------------------------------------------------
// Error::EntryList
//-----------------------------------------------------------------------------
bool Error::EntryList::DoesExist(const char* fileName, int lineNo, const char* message)
{
	for (auto pEntry : *this) {
		if (pEntry->DoesMatch(fileName, lineNo, message)) return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Error::EntryOwner
//-----------------------------------------------------------------------------

}
