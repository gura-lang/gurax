//=============================================================================
// Formatter
//=============================================================================
#ifndef GURAX_FORMATTER_H
#define GURAX_FORMATTER_H
#include "Common.h"
#include "OAL.h"
#include "VType_Number.h"
#include "VType_StringPtr.h"

namespace Gurax {

class IteratorOwner;

//-----------------------------------------------------------------------------
// FormatterFlags
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE FormatterFlags {
public:
	enum class PlusMode { None, Space, Plus };
	struct Prec {
		static const int Default	= -1;
		static const int Null		= -2;
	};
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
	class GURAX_DLLDECLARE Source {
	public:
		virtual bool IsEnd() = 0;
		virtual Value* FetchInt() = 0;
		virtual Value* FetchUInt() = 0;
		virtual Value* FetchSizeT() = 0;
		virtual Value* FetchDouble() = 0;
		virtual Value* FetchString() = 0;
	};
	class GURAX_DLLDECLARE Source_ValueList : public Source {
	private:
		const ValueList& _valueList;
		ValueList::const_iterator _ppValue;
	public:
		Source_ValueList(const ValueList& valueList) : _valueList(valueList) {
			_ppValue = _valueList.begin();
		}
		virtual bool IsEnd() override { return _ppValue == _valueList.end(); }
		virtual Value* FetchInt() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchUInt() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchSizeT() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchDouble() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchString() override { return (*_ppValue++)->Reference(); }
	};
	class GURAX_DLLDECLARE Source_va_list : public Source {
	private:
		va_list _ap;
	public:
#if defined(va_copy)
		Source_va_list(va_list ap) { va_copy(_ap, ap); }
#else
		Source_va_list(va_list ap) { _ap = ap; }
#endif
		virtual bool IsEnd() override { return false; }
		virtual Value* FetchInt() override {
			Int num = va_arg(_ap, Int);
			return new Value_Number(static_cast<Int>(num));
		}
		virtual Value* FetchUInt() override {
			UInt num = va_arg(_ap, UInt);
			return new Value_Number(static_cast<UInt>(num));
		}
		virtual Value* FetchSizeT() override {
			size_t num = va_arg(_ap, size_t);
			return new Value_Number(num);
		}
		virtual Value* FetchDouble() override {
			Double num = va_arg(_ap, Double);
			return new Value_Number(num);
		}
		virtual Value* FetchString() override {
			char* str = va_arg(_ap, char*);
			return new Value_StringPtr(str);
		}
	};
private:
	bool _nilVisibleFlag;
	const char* _lineSep;
public:
	Formatter(bool nilVisibleFlag = true) : _nilVisibleFlag(nilVisibleFlag), _lineSep("\n") {}
	bool Format(const char* format, const ValueList& valueList) {
		return Format(format, Source_ValueList(valueList));
	}
	bool Format(const char* format, va_list ap) {
		return Format(format, Source_va_list(ap));
	}
	bool Format(const char* format, Source&& source);
	bool PutString(const char* p);
	bool PutAlignedString(const FormatterFlags& formatterFlags, const char* p, int cntMax = -1);
	bool PutInvalid(const FormatterFlags& formatterFlags);
	//static const Value* FormatIterator(const char* format, IteratorOwner& iterOwner);
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
