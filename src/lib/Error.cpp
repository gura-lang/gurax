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
const ErrorType ErrorType::DeclarationError("declaration error");
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

Error::Error(const ErrorType& errorType, String text) :
	_errorType(errorType), _lineNoTop(0), _lineNoBtm(0), _text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, String text) :
	_errorType(errorType), _pFileName(pFileName), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm),
	_text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, Expr *pExpr, String text) :
	_errorType(errorType), _pExpr(pExpr), _pFileName(pExpr->GetPathNameSrcReferable()->Reference()),
	_lineNoTop(pExpr->GetLineNoTop()), _lineNoBtm(pExpr->GetLineNoBtm()), _text(std::move(text))
{
}

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

void Error::SetExpr(Expr* pExpr)
{
	_pExpr.reset(pExpr);
	_pFileName.reset(pExpr->GetPathNameSrcReferable()->Reference());
	_lineNoTop = pExpr->GetLineNoTop();
	_lineNoBtm = pExpr->GetLineNoBtm();
}

void Error::Clear()
{
	_errorIssuedFlag = false;
	_pErrorOwnerGlobal->Clear();
}

void Error::Print(Stream& stream)
{
	for (Error* pError : *_pErrorOwnerGlobal) {
		stream.Printf("%s\n", pError->MakeMessage().c_str());
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
