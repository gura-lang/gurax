//==============================================================================
// Error.h
//==============================================================================
#ifndef GURAX_ERROR_H
#define GURAX_ERROR_H
#include "String.h"

namespace Gurax {

class Expr;

//-----------------------------------------------------------------------------
// Error
//-----------------------------------------------------------------------------
class Error {
public:
	class Entry {
	private:
		String _fileName;
		int _lineNo;
		String _message;
	public:
		Entry(const String& fileName, const String& message) :
			_fileName(fileName), _lineNo(0), _message(message) {}
		Entry(const String& fileName, int lineNo, const String& message) :
			_fileName(fileName), _lineNo(lineNo), _message(message) {}
		bool DoesMatch(const char* fileName, int lineNo, const char* message) {
			return _fileName == fileName && _lineNo == lineNo && _message == message;
		}
		String GetString() const;
	};
	class EntryList : public std::vector<Entry*> {
	public:
		bool DoesExist(const char* fileName, int lineNo, const char* message);
	};
	class EntryOwner : public EntryList {
	public:
		~EntryOwner() { Clear(); }
		void Clear() {
			for (auto pEntry : *this) delete pEntry;
		}
	};
private:
	EntryOwner _entryOwner;
	static Error _instance;
public:
	Error() {}
	EntryOwner& GetEntryOwner() { return _entryOwner; }
	static Error& GetInstance() { return _instance; }
	static bool HasError() { return !_instance.GetEntryOwner().empty(); }
	static void Clear() { _instance._entryOwner.Clear(); }
	static void AddError(const Expr* pExpr, const char* format, ...);
	static void AddError(const char* format, ...);
	static void AddError(const String& fileName, int lineNo, const char* format, ...);
	static void AddErrorV(const String& fileName, int lineNo, const char* format, va_list ap);
	static void Print(FILE* fp);
	static String MakeResultText();
};

}

#endif
