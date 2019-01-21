//=============================================================================
// Formatter
//=============================================================================
#ifndef GURAX_FORMATTER_H
#define GURAX_FORMATTER_H
#include "Common.h"

namespace Gurax {

class IteratorOwner;
class Object;

//-----------------------------------------------------------------------------
// Formatter
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Formatter {
public:
	enum PlusMode {
		PLUSMODE_None, PLUSMODE_Space, PLUSMODE_Plus,
	};
	enum {
		PREC_Default	= -1,
		PREC_Null		= -2,
	};
	struct Flags {
		bool upperCaseFlag;
		bool leftAlignFlag;
		bool sharpFlag;
		int fieldMinWidth;
		int precision;
		PlusMode plusMode;
		char charPadding;
	};
public:
	class Source {
	public:
		virtual bool IsEnd() = 0;
		virtual Object* GetInt() = 0;
		virtual Object* GetDouble() = 0;
		virtual Object* GetString() = 0;
	};
	class Source_ObjectList : public Source {
	private:
		const ObjectList& _objectList;
		ObjectList::const_iterator _ppObject;
	public:
		inline Source_ObjectList(const ObjectList& objectList) : _objectList(objectList) {
			_ppObject = _objectList.begin();
		}
		virtual bool IsEnd();
		virtual Object* GetInt();
		virtual Object* GetDouble();
		virtual Object* GetString();
	};
	class Source_va_list : public Source {
	private:
		va_list _ap;
	public:
#if defined(va_copy)
		inline Source_va_list(va_list ap) { va_copy(_ap, ap); }
#else
		inline Source_va_list(va_list ap) { _ap = ap; }
#endif
		virtual bool IsEnd();
		virtual Object* GetInt();
		virtual Object* GetDouble();
		virtual Object* GetString();
	};
private:
	bool _nilVisibleFlag;
	const char* _lineSep;
public:
	inline Formatter(bool nilVisibleFlag = true) :
					_nilVisibleFlag(nilVisibleFlag), _lineSep("\n") {}
	bool DoFormat(const char* format, const ObjectList& objectList);
	bool DoFormat(const char* format, va_list ap);
	bool DoFormat(const char* format, Source& source);
	bool PutString(const char* p);
	bool PutAlignedString(const Flags& flags, const char* p, int cntMax = -1);
	bool PutInvalid(const Flags& flags);
	virtual bool PutChar(char ch) = 0;
	static String Format(const char* format, ...);
	static String FormatV(const char* format, va_list ap);
	static String FormatObjectList(const char* format, const ObjectList& objectList);
	static const Object* FormatIterator(const char* format, IteratorOwner& iterOwner);
	static const char* Format_d(const Flags& flags, Int64 value, char* buff, size_t size);
	static const char* Format_u(const Flags& flags, UInt64 value, char* buff, size_t size);
	static const char* Format_b(const Flags& flags, UInt64 value, char* buff, size_t size);
	static const char* Format_o(const Flags& flags, UInt64 value, char* buff, size_t size);
	static const char* Format_x(const Flags& flags, UInt64 value, char* buff, size_t size);
	static const char* Format_e(const Flags& flags, double value, char* buff, size_t size);
	static const char* Format_f(const Flags& flags, double value, char* buff, size_t size);
	static const char* Format_g(const Flags& flags, double value, char* buff, size_t size);
	static String ComposeFlags(const Flags& flags, const char* qualifier);
private:
	static void SetError_WrongFormat();
	static void SetError_NotEnoughArguments();
	static char* FillZeroDigit(char* dstp, char* dstpEnd, int cnt);
	static char* CopyDigits(char* dstp, char* dstpEnd, const char* srcp);
	static char* CopyDigits(char* dstp, char* dstpEnd, const char* srcp, int cnt);
};

//-----------------------------------------------------------------------------
// FormatterString
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE FormatterString : public Formatter {
private:
	String _str;
public:
	virtual bool PutChar(char ch);
	inline const String& GetStringSTL() const { return _str; }
};

}

#endif
