//==============================================================================
// Formatter
//==============================================================================
#ifndef GURAX_FORMATTER_H
#define GURAX_FORMATTER_H
#include "Common.h"
#include "OAL.h"
#include "VType_Number.h"
#include "VType_StringPtr.h"

namespace Gurax {

class IteratorOwner;

//------------------------------------------------------------------------------
// FormatterFlags
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// Formatter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Formatter {
public:
	enum class VaType { None, Int, Int64, SizeT, Float, Pointer, };
	class GURAX_DLLDECLARE Source {
	public:
		virtual bool IsEnd() = 0;
		virtual Value* FetchInt() = 0;
		virtual Value* FetchUInt() = 0;
		virtual Value* FetchInt64() = 0;
		virtual Value* FetchUInt64() = 0;
		virtual Value* FetchSizeT() = 0;
		virtual Value* FetchDouble() = 0;
		virtual Value* FetchString() = 0;
		virtual bool Finish() { return true; }
	};
	class GURAX_DLLDECLARE Source_Value : public Source {
	private:
		const Value* _pValue;
	public:
		Source_Value(const Value& value) : _pValue(&value) {}
	public:
		virtual bool IsEnd() override { return !_pValue; }
		virtual Value* FetchInt() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchUInt() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchInt64() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchUInt64() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchSizeT() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchDouble() override { return _pValue->Reference(); _pValue = nullptr; }
		virtual Value* FetchString() override { return _pValue->Reference(); _pValue = nullptr; }
	};
	class GURAX_DLLDECLARE Source_ValueList : public Source {
	private:
		const ValueList& _valueList;
		ValueList::const_iterator _ppValue;
	public:
		Source_ValueList(const ValueList& valueList);
	public:
		virtual bool IsEnd() override { return _ppValue == _valueList.end(); }
		virtual Value* FetchInt() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchUInt() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchInt64() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchUInt64() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchSizeT() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchDouble() override { return (*_ppValue++)->Reference(); }
		virtual Value* FetchString() override { return (*_ppValue++)->Reference(); }
	};
	class GURAX_DLLDECLARE Source_va_list : public Source {
	private:
		va_list _ap;
	public:
		Source_va_list(va_list ap);
	public:
		virtual bool IsEnd() override { return false; }
		virtual Value* FetchInt() override;
		virtual Value* FetchUInt() override;
		virtual Value* FetchInt64() override;
		virtual Value* FetchUInt64() override;
		virtual Value* FetchSizeT() override;
		virtual Value* FetchDouble() override;
		virtual Value* FetchString() override;
	};
	class GURAX_DLLDECLARE Source_Verifier : public Source {
	private:
		va_list _ap;
	public:
		Source_Verifier(va_list ap);
	public:
		virtual bool IsEnd() override { return false; }
		virtual Value* FetchInt() override { return Fetch(VaType::Int); }
		virtual Value* FetchUInt() override { return Fetch(VaType::Int); }
		virtual Value* FetchInt64() override { return Fetch(VaType::Int64); }
		virtual Value* FetchUInt64() override { return Fetch(VaType::Int64); }
		virtual Value* FetchSizeT() override { return Fetch(VaType::SizeT); }
		virtual Value* FetchDouble() override { return Fetch(VaType::Float); }
		virtual Value* FetchString() override { return Fetch(VaType::Pointer); }
		virtual bool Finish() override;
	protected:
		Value* Fetch(VaType vaType);
	};
private:
	bool _nilVisibleFlag;
	const char* _lineSep;
public:
	Formatter(bool nilVisibleFlag = true) : _nilVisibleFlag(nilVisibleFlag), _lineSep("\n") {}
	bool Format(const char* format, const Value& value);
	bool Format(const char* format, const ValueList& valueList);
	bool FormatV(const char* format, va_list ap);
	bool VerifyFormatV(const char* format, va_list ap);
	bool VerifyFormat(const char* format, ...);
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
	virtual bool PutChar(char ch) { return true; }
};

}

#endif
