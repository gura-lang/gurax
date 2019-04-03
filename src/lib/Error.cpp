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
const ErrorType ErrorType::DividedByZero("divided by zero");
const ErrorType ErrorType::IndexError("index error");
const ErrorType ErrorType::InvalidOperation("invalid operation");
const ErrorType ErrorType::IteratorError("iterator error");
const ErrorType ErrorType::StreamError("stream error");
const ErrorType ErrorType::SyntaxError("syntax error");
const ErrorType ErrorType::TypeError("type error");
const ErrorType ErrorType::ValueError("value error");

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
bool Error::_errorIssuedFlag = false;
ErrorOwner* Error::_pErrorOwnerGlobal = nullptr;

Error::Error(const ErrorType& errorType, String text) :
	_errorType(errorType), _pExpr(Expr::Empty->Reference()),
	_lineNoTop(0), _lineNoBtm(0), _text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, String text) :
	_errorType(errorType), _pExpr(Expr::Empty->Reference()),
	_pFileName(pFileName), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm), _text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, Expr* pExpr, String text) :
	_errorType(errorType), _pExpr(pExpr),
	_pFileName(StringReferable::Reference(pExpr->GetPathNameSrcReferable())),
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
	String str;
	if (_pFileName && !_pFileName->GetStringSTL().empty()) {
		str += _pFileName->GetStringSTL();
		if (_lineNoTop == 0) {
			str += ": ";
		} else if (_lineNoTop == _lineNoBtm) {
			str.Printf(":%d: ", _lineNoTop);
		} else {
			str.Printf(":%d:%d: ", _lineNoTop, _lineNoBtm);
		}
	}
	str += _errorType.GetName();
	str += ": ";
	str += _text;
	return str;
}

void Error::SetExpr(const Expr& expr)
{
	_pExpr.reset(expr.Reference());
	_pFileName.reset(expr.GetPathNameSrcReferable()->Reference());
	_lineNoTop = expr.GetLineNoTop();
	_lineNoBtm = expr.GetLineNoBtm();
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
void ErrorList::SetExpr(const Expr& expr)
{
	for (Error* pError : *this) {
		if (pError->GetExpr().IsType<Expr_Empty>()) pError->SetExpr(expr);
	}
}

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------
void ErrorOwner::Clear()
{
	for (Error* pError : *this) Error::Delete(pError);
	clear();
}

}
