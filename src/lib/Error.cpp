//==============================================================================
// Error.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ErrorType
//------------------------------------------------------------------------------
const ErrorType ErrorType::AccessError			("AccessError",			"access error");
const ErrorType ErrorType::ArgumentError		("ArgumentError",		"argument error");
const ErrorType ErrorType::CastError			("CastError",			"cast error");
const ErrorType ErrorType::CodecError			("CodecError",			"codec error");
const ErrorType ErrorType::CommandError			("CommandError",		"command error");
const ErrorType ErrorType::ContextError			("ContextError",		"context error");
const ErrorType ErrorType::DeclarationError		("DeclarationError",	"declaration error");
const ErrorType ErrorType::DividedByZero		("DividedByZero",		"divided by zero");
const ErrorType ErrorType::FormatError			("FormatError",			"format error");
const ErrorType ErrorType::GuestError			("GuestError",			"guest error");
const ErrorType ErrorType::ImportError			("ImportError",			"import error");
const ErrorType ErrorType::IndexError			("IndexError",			"index error");
const ErrorType ErrorType::InvalidOperation		("InvalidOperation",	"invalid operation");
const ErrorType ErrorType::IOError				("IOError",				"I/O error");
const ErrorType ErrorType::IteratorError		("IteratorError",		"iterator error");
const ErrorType ErrorType::KeyError				("KeyError",			"key error");
const ErrorType ErrorType::MemoryError			("MemoryError",			"memory error");
const ErrorType ErrorType::PathError			("PathError",			"path error");
const ErrorType ErrorType::PropertyError		("PropertyError",		"property error");
const ErrorType ErrorType::RangeError			("RangeError",			"range error");
const ErrorType ErrorType::StreamError			("StreamError",			"stream error");
const ErrorType ErrorType::SuffixError			("SuffixError",			"suffix error");
const ErrorType ErrorType::SymbolError			("SymbolError",			"symbol error");
const ErrorType ErrorType::SyntaxError			("SyntaxError",			"syntax error");
const ErrorType ErrorType::TypeError			("TypeError",			"type error");
const ErrorType ErrorType::UnimplementedError	("UnimplementedError",	"unimplemented error");
const ErrorType ErrorType::ValueError			("ValueError",			"value error");
const ErrorType ErrorType::DetectEncoding		("DetectEncoding",		"detect encoding");

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
bool Error::_errorIssuedFlag = false;
ErrorOwner* Error::_pErrorOwnerGlobal = nullptr;

Error::Error(const ErrorType& errorType, String text) :
	_errorType(errorType), _pExpr(Expr::Empty.Reference()),
	_lineNoTop(0), _lineNoBtm(0), _text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, String text) :
	_errorType(errorType), _pExpr(Expr::Empty.Reference()),
	_pPathName(pFileName), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm), _text(std::move(text))
{
}

Error::Error(const ErrorType& errorType, Expr* pExpr, String text) :
	_errorType(errorType), _pExpr(pExpr),
	_pPathName(pExpr->GetPathNameSrcReferable().Reference()),
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
	if (_pPathName && !_pPathName->GetStringSTL().empty()) {
		str += _pPathName->GetStringSTL();
		if (_lineNoTop == 0) {
			str += ": ";
		} else if (_lineNoTop == _lineNoBtm) {
			str.Format(":%d: ", _lineNoTop);
		} else {
			str.Format(":%d:%d: ", _lineNoTop, _lineNoBtm);
		}
	}
	str += _errorType.GetDispName();
	str += ": ";
	str += _text;
	return str;
}

void Error::SetExpr(const Expr& expr)
{
	if (_pExpr->IsType<Expr_Empty>()) _pExpr.reset(expr.Reference());
	if (!_pPathName) {
		_pPathName.reset(expr.GetPathNameSrcReferable().Reference());
		_lineNoTop = expr.GetLineNoTop();
		_lineNoBtm = expr.GetLineNoBtm();
	}
}

void Error::Clear()
{
	_errorIssuedFlag = false;
	_pErrorOwnerGlobal->Clear();
}

void Error::Print(Stream& stream)
{
	for (Error* pError : GetErrorOwner()) {
		stream.Printf("%s\n", pError->MakeMessage().c_str());
	}
}

String Error::ToString(const StringStyle& ss) const
{
	String str;
	str.Format("Error:%s", GetErrorType().GetName());
	if (HasPathName()) {
		str.Format(":%s", PathName(GetPathName()).ExtractFileName().c_str());
		int lineNoTop = GetLineNoTop();
		int lineNoBtm = GetLineNoBtm();
		if (lineNoTop == lineNoBtm) {
			str.Format(":%d", lineNoTop);
		} else {
			str.Format(":%d:%d", lineNoTop, lineNoBtm);
		}
	}
	return str;
}

void Error::Issue_UnimplementedOperation()
{
	Error::Issue(ErrorType::UnimplementedError, "unimplemented operation");
}

void Error::Issue_UnimplementedFunction()
{
	Error::Issue(ErrorType::UnimplementedError, "unimplemented function");
}

void Error::Issue_UnimplementedMethod()
{
	Error::Issue(ErrorType::UnimplementedError, "unimplemented method");
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
