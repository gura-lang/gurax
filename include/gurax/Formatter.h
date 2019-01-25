//=============================================================================
// Formatter
//=============================================================================
#ifndef GURAX_FORMATTER_H
#define GURAX_FORMATTER_H
#include "Object_number.h"
#include "Object_stringptr.h"

namespace Gurax {

class IteratorOwner;

//-----------------------------------------------------------------------------
// FormatterFlags
//-----------------------------------------------------------------------------
class FormatterFlags {
public:
	enum class PlusMode { None, Space, Plus };
public:
	static const int PREC_Default	= -1;
	static const int PREC_Null		= -2;
public:
	bool upperCaseFlag;
	bool leftAlignFlag;
	bool sharpFlag;
	int fieldMinWidth;
	int precision;
	PlusMode plusMode;
	char charPadding;
public:
	void Initialize();
	const char* FormatNumber_d(Int64 num, char* buff, size_t size) const;
	const char* FormatNumber_u(UInt64 num, char* buff, size_t size) const;
	const char* FormatNumber_b(UInt64 num, char* buff, size_t size) const;
	const char* FormatNumber_o(UInt64 num, char* buff, size_t size) const;
	const char* FormatNumber_x(UInt64 num, char* buff, size_t size) const;
	const char* FormatNumber_e(double num, char* buff, size_t size) const;
	const char* FormatNumber_f(double num, char* buff, size_t size) const;
	const char* FormatNumber_g(double num, char* buff, size_t size) const;
	String ToString(const char* qualifier) const;
};

//-----------------------------------------------------------------------------
// Formatter
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Formatter {
public:
	enum class Stat {
		Start, FlagsPre, Flags, FlagsAfterWhite, PrecisionPre, Precision, Padding,
	};
	class Source {
	public:
		virtual bool IsEnd() = 0;
		virtual Object* FetchInt() = 0;
		virtual Object* FetchDouble() = 0;
		virtual Object* FetchString() = 0;
	};
	class Source_ObjectList : public Source {
	private:
		const ObjectList& _objectList;
		ObjectList::const_iterator _ppObject;
	public:
		Source_ObjectList(const ObjectList& objectList) : _objectList(objectList) {
			_ppObject = _objectList.begin();
		}
		virtual bool IsEnd() override { return _ppObject == _objectList.end(); }
		virtual Object* FetchInt() override { return (*_ppObject++)->Reference(); }
		virtual Object* FetchDouble() override { return (*_ppObject++)->Reference(); }
		virtual Object* FetchString() override { return (*_ppObject++)->Reference(); }
	};
	class Source_va_list : public Source {
	private:
		va_list _ap;
	public:
#if defined(va_copy)
		Source_va_list(va_list ap) { va_copy(_ap, ap); }
#else
		Source_va_list(va_list ap) { _ap = ap; }
#endif
		virtual bool IsEnd() override { return false; }
		virtual Object* FetchInt() override {
			Int num = va_arg(_ap, Int);
			return new Object_number(num);
		}
		virtual Object* FetchDouble() override {
			Double num = va_arg(_ap, Double);
			return new Object_number(num);
		}
		virtual Object* FetchString() override {
			char* str = va_arg(_ap, char*);
			return new Object_stringptr(str);
		}
	};
private:
	bool _nilVisibleFlag;
	const char* _lineSep;
public:
	Formatter(bool nilVisibleFlag = true) : _nilVisibleFlag(nilVisibleFlag), _lineSep("\n") {}
	bool Format(const char* format, const ObjectList& objectList) {
		return Format(format, Source_ObjectList(objectList));
	}
	bool Format(const char* format, va_list ap) {
		return Format(format, Source_va_list(ap));
	}
	bool Format(const char* format, Source&& source);
	bool PutString(const char* p);
	bool PutAlignedString(const FormatterFlags& formatterFlags, const char* p, int cntMax = -1);
	bool PutInvalid(const FormatterFlags& formatterFlags);
	//static const Object* FormatIterator(const char* format, IteratorOwner& iterOwner);
private:
	static char* FillZeroDigit(char* dstp, char* dstpEnd, int cnt);
	static char* CopyDigits(char* dstp, char* dstpEnd, const char* srcp);
	static char* CopyDigits(char* dstp, char* dstpEnd, const char* srcp, int cnt);
	void IssueError_NumberIsExpectedForAsterisk() {
		Error::Issue(ErrorType::ValueError, "number is expected for * specifier");
	}
	void IssueError_WrongFormat() {
		Error::Issue(ErrorType::ValueError, "wrong format for formatter");
	}
	void IssueError_NotEnoughArguments() {
		Error::Issue(ErrorType::ValueError, "not enough arguments for formatter");
	}
public:
	// Virtual functions
	virtual bool PutChar(char ch) = 0;
};

}

#endif
