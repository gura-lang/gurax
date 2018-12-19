//==============================================================================
// Error.h
//==============================================================================
#ifndef GURAX_ERROR_H
#define GURAX_ERROR_H
#include "String.h"
#include "Expr.h"

namespace Gurax {

class Expr;
class ErrorOwner;

//------------------------------------------------------------------------------
// ErrorType
//------------------------------------------------------------------------------
class ErrorType {
private:
	String _name;
public:
	static const ErrorType SyntaxError;
public:
	ErrorType(const String& name) : _name(name) {}
	const char* GetName() const { return _name.c_str(); }
};

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
class Error : public Referable {
private:
	const ErrorType& _errorType;
	RefPtr<Expr> _pExpr;		// maybe nullptr
	StringShared _pFileName;	// maybe nullptr
	int _lineNo;
	String _text;
private:
	static bool _errorIssuedFlag;
	static ErrorOwner* _pErrorOwnerGlobal;
public:
	// Constructor
	Error(const ErrorType& errorType, const String& text) :
		_errorType(errorType), _lineNo(0), _text(text) {}
	Error(const ErrorType& errorType, const StringShared& pFileName, int lineNo, const String& text) :
		_errorType(errorType), _pFileName(pFileName), _lineNo(lineNo), _text(text) {}
	Error(const ErrorType& errorType, Expr *pExpr, const String& text) :
		_errorType(errorType), _pExpr(pExpr), _lineNo(0), _text(text) {}
	// Copy constructor/operator
	Error(const Error& src) = delete;
	Error& operator=(const Error& src) = delete;
	// Move constructor/operator
	Error(Error&& src) = delete;
	Error& operator=(Error&& src) noexcept = delete;
protected:
	// Destructor
	~Error() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Error);
public:
	static void Bootup();
	String MakeMessage() const;
	static bool IsIssued() { return _errorIssuedFlag; }
	static void Clear();
	static void Issue(const ErrorType& errorType, const char* format, ...);
	static void Issue(const ErrorType& errorType, const StringShared& pFileName, int lineNo, const char* format, ...);
	static void Issue(const ErrorType& errorType, Expr* pExpr, const char* format, ...);
	static void IssueV(const ErrorType& errorType, const char* format, va_list ap);
	static void IssueV(const ErrorType& errorType, const StringShared& pFileName, int lineNo, const char* format, va_list ap);
	static void IssueV(const ErrorType& errorType, Expr* pExpr, const char* format, va_list ap);
	static void Print(FILE* fp);
};

//------------------------------------------------------------------------------
// ErrorList
//------------------------------------------------------------------------------
class ErrorList : public std::vector<Error*> {
};

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------
class ErrorOwner : public ErrorList {
public:
	~ErrorOwner() { Clear(); }
	void Clear() {
		for (auto& pError : *this) Error::Delete(pError);
	}
};

}

#endif
