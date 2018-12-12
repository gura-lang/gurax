//==============================================================================
// Error.h
//==============================================================================
#ifndef GURAX_ERROR_H
#define GURAX_ERROR_H
#include "String.h"

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
	String _fileName;
	int _lineNo;
	String _message;
private:
	static bool _errorIssuedFlag;
	static ErrorOwner* _pErrorOwnerGlobal;
public:
	// Constructor
	Error(const ErrorType& errorType, const String& fileName, const String& message) :
		_errorType(errorType), _fileName(fileName), _lineNo(0), _message(message) {}
	Error(const ErrorType& errorType, const String& fileName, int lineNo, const String& message) :
		_errorType(errorType), _fileName(fileName), _lineNo(lineNo), _message(message) {}
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
	bool DoesMatch(const char* fileName, int lineNo, const char* message) {
		return _fileName == fileName && _lineNo == lineNo && _message == message;
	}
	String GetString() const;
	static bool IsIssued() { return _errorIssuedFlag; }
	static void Clear();
	static void Issue(const ErrorType& errorType, const Expr* pExpr, const char* format, ...);
	static void Issue(const ErrorType& errorType, const char* format, ...);
	static void Issue(const ErrorType& errorType, const String& fileName, int lineNo, const char* format, ...);
	static void IssueV(const ErrorType& errorType, const String& fileName, int lineNo, const char* format, va_list ap);
	static void Print(FILE* fp);
	static String MakeResultText();
};

//------------------------------------------------------------------------------
// ErrorList
//------------------------------------------------------------------------------
class ErrorList : public std::vector<Error*> {
public:
	bool DoesExist(const char* fileName, int lineNo, const char* message);
};

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------
class ErrorOwner : public ErrorList {
public:
	~ErrorOwner() { Clear(); }
	void Clear() {
		for (auto pError : *this) Error::Delete(pError);
	}
};

}

#endif
