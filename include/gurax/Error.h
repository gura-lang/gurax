//==============================================================================
// Error.h
//==============================================================================
#ifndef GURAX_ERROR_H
#define GURAX_ERROR_H
#include "Expr.h"
#include "String.h"
#include "StringStyle.h"

namespace Gurax {

class Error;
class Stream;

//------------------------------------------------------------------------------
// ErrorType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ErrorType {
private:
	String _name;
	String _dispName;
public:
	static const ErrorType AccessError;
	static const ErrorType ArgumentError;
	static const ErrorType CastError;
	static const ErrorType CodecError;
	static const ErrorType CommandError;
	static const ErrorType ContextError;
	static const ErrorType DeclarationError;
	static const ErrorType DividedByZero;
	static const ErrorType FormatError;
	static const ErrorType GuestError;
	static const ErrorType ImportError;
	static const ErrorType IndexError;
	static const ErrorType InvalidOperation;
	static const ErrorType IOError;
	static const ErrorType IteratorError;
	static const ErrorType KeyError;
	static const ErrorType MemoryError;
	static const ErrorType PathError;
	static const ErrorType PropertyError;
	static const ErrorType RangeError;
	static const ErrorType StreamError;
	static const ErrorType SuffixError;
	static const ErrorType SymbolError;
	static const ErrorType SyntaxError;
	static const ErrorType TypeError;
	static const ErrorType UnimplementedError;
	static const ErrorType ValueError;
	static const ErrorType DetectEncoding;
public:
	ErrorType(const String& name, const String& dispName) : _name(name), _dispName(dispName) {}
	const char* GetName() const { return _name.c_str(); }
	const char* GetDispName() const { return _dispName.c_str(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ErrorType& errorType) const { return this == &errorType; }
	bool IsEqualTo(const ErrorType& errorType) const { return IsIdentical(errorType); }
	bool IsLessThan(const ErrorType& errorType) const { return ::strcmp(GetName(), errorType.GetName()) < 0; }
};

//------------------------------------------------------------------------------
// ErrorList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ErrorList : public ListBase<Error*> {
public:
	void SetExpr(const Expr& expr);
};

//------------------------------------------------------------------------------
// ErrorOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ErrorOwner : public ErrorList {
private:
	bool _suppressFlag;
public:
	ErrorOwner() : _suppressFlag(false) {}
	~ErrorOwner() { Clear(); }
	void Clear();
	void SetSuppressFlag() { _suppressFlag = true; }
	void ClearSuppressFlag() { _suppressFlag = false; }
	bool GetSuppressFlag() const { return _suppressFlag; }
};

//------------------------------------------------------------------------------
// Error
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Error : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Error);
private:
	const ErrorType& _errorType;
	RefPtr<Expr> _pExpr;
	RefPtr<StringReferable> _pPathName;	// maybe nullptr
	int _lineNoTop;
	int _lineNoBtm;
	String _text;
private:
	static bool _errorIssuedFlag;
	static ErrorOwner* _pErrorOwnerGlobal;
public:
	// Constructor
	Error(const ErrorType& errorType, String text);
	Error(const ErrorType& errorType, StringReferable* pFileName, int lineNoTop, int lineNoBtm, String text);
	Error(const ErrorType& errorType, Expr *pExpr, String text);
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
	const Expr& GetExpr() const { return *_pExpr; }
	void SetExpr(const Expr& expr);
	const ErrorType& GetErrorType() const { return _errorType; }
	bool HasPathName() const { return _pPathName && !_pPathName->GetStringSTL().empty(); }
	const char* GetPathName() const { return _pPathName? _pPathName->GetString() : ""; }
	int GetLineNoTop() const { return _lineNoTop; }
	int GetLineNoBtm() const { return _lineNoBtm; }
	const char* GetText() const { return _text.c_str(); }
	static const Error* GetLastError() {
		return _pErrorOwnerGlobal->empty()? nullptr : _pErrorOwnerGlobal->back();
	}
	static ErrorOwner& GetErrorOwner() { return *_pErrorOwnerGlobal; }
	static bool IsIssued() { return _errorIssuedFlag; }
	static void SetIssuedFlag() { _errorIssuedFlag = true; }
	static void ClearIssuedFlag() { _errorIssuedFlag = false; }
	static void Clear();
	template<typename... Args>
	static void Issue(const ErrorType& errorType, const char* const format, const Args&... args) {
		if (_pErrorOwnerGlobal->GetSuppressFlag()) return;
		_pErrorOwnerGlobal->SetSuppressFlag(); // suppress error in String::Format()
		_pErrorOwnerGlobal->push_back(new Error(errorType, String().Format(format, args...)));
		_pErrorOwnerGlobal->ClearSuppressFlag();
		_errorIssuedFlag = true;
	}
	template<typename... Args>
	static void IssueIfFirst(const ErrorType& errorType, const char* const format, const Args&... args) {
		if (_errorIssuedFlag || _pErrorOwnerGlobal->GetSuppressFlag()) return;
		_pErrorOwnerGlobal->SetSuppressFlag(); // suppress error in String::Format()
		_pErrorOwnerGlobal->push_back(new Error(errorType, String().Format(format, args...)));
		_pErrorOwnerGlobal->ClearSuppressFlag();
		_errorIssuedFlag = true;
	}
	template<typename... Args>
	static void IssueAt(const ErrorType& errorType, StringReferable* pFileName,
						int lineNoTop, int lineNoBtm, const char* const format, const Args&... args) {
		if (_pErrorOwnerGlobal->GetSuppressFlag()) return;
		_pErrorOwnerGlobal->SetSuppressFlag(); // suppress error in String::Format()
		_pErrorOwnerGlobal->push_back(
			new Error(errorType, pFileName, lineNoTop, lineNoBtm, String().Format(format, args...)));
		_pErrorOwnerGlobal->ClearSuppressFlag();
		_errorIssuedFlag = true;
	}
	template<typename... Args>
	static void IssueWith(const ErrorType& errorType, const Expr& expr, const char* format, const Args&... args) {
		if (_pErrorOwnerGlobal->GetSuppressFlag()) return;
		_pErrorOwnerGlobal->SetSuppressFlag(); // suppress error in String::Format()
		_pErrorOwnerGlobal->push_back(
			new Error(errorType, expr.Reference(), String().Format(format, args...)));
		_pErrorOwnerGlobal->ClearSuppressFlag();
		_errorIssuedFlag = true;
	}
	static void Print(Stream& stream);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Error& error) const { return this == &error; }
	bool IsEqualTo(const Error& error) const {
		return GetErrorType().IsEqualTo(error.GetErrorType()) &&
			::strcmp(GetText(), error.GetText()) == 0;
	}
	bool IsLessThan(const Error& error) const {
		return GetErrorType().IsEqualTo(error.GetErrorType())?
			::strcmp(GetText(), error.GetText()) < 0 :
			GetErrorType().IsLessThan(error.GetErrorType());
	}
	String ToString(const StringStyle& ss) const;
public:
	static void Issue_UnimplementedOperation();
	static void Issue_UnimplementedFunction();
	static void Issue_UnimplementedMethod();
};

}

#endif
