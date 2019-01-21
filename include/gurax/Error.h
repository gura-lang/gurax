//==============================================================================
// Error.h
//==============================================================================
#ifndef GURAX_ERROR_H
#define GURAX_ERROR_H
#include "String.h"
#include "Expr.h"

namespace Gurax {

class Expr;
class Error;

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
	void Clear();
};

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
class Error : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Error);
private:
	const ErrorType& _errorType;
	RefPtr<Expr> _pExpr;				// maybe nullptr
	RefPtr<StringReferable> _pFileName;	// maybe nullptr
	int _lineNoTop;
	int _lineNoBtm;
	String _text;
private:
	static bool _errorIssuedFlag;
	static ErrorOwner* _pErrorOwnerGlobal;
public:
	// Constructor
	Error(const ErrorType& errorType, const String& text) :
		_errorType(errorType), _lineNoTop(0), _lineNoBtm(0), _text(text) {}
	Error(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, const String& text) :
		_errorType(errorType), _pFileName(pFileName), _lineNoTop(lineNoTop), _lineNoBtm(lineNoBtm), _text(text) {}
	Error(const ErrorType& errorType, Expr *pExpr, const String& text) :
		_errorType(errorType), _pExpr(pExpr), _lineNoTop(0), _lineNoBtm(0), _text(text) {}
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
	static void Bootup();
	String MakeMessage() const;
	static bool IsIssued() { return _errorIssuedFlag; }
	static void Clear();
	template<typename... Args>
	static void Issue(const ErrorType& errorType, const char* const format, const Args&... args) {
		char text[512];
		::sprintf(text, format, args...);
		_pErrorOwnerGlobal->push_back(new Error(errorType, text));
	}
	template<typename... Args>
	static void IssueAt(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, const char* const format, const Args&... args) {
		char text[512];
		::sprintf(text, format, args...);
		_pErrorOwnerGlobal->push_back(new Error(errorType, pFileName, lineNoTop, lineNoBtm, text));
		
	}
	template<typename... Args>
	static void IssueWith(const ErrorType& errorType, Expr* pExpr, const char* format, const Args&... args) {
		char text[512];
		::sprintf(text, format, args...);
		_pErrorOwnerGlobal->push_back(new Error(errorType, pExpr, text));
	}
	static void Print(FILE* fp);
};


}

#endif
