//=============================================================================
// Formatter
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Formatter
//-----------------------------------------------------------------------------
bool Formatter::DoFormat(const char* format, const ObjectList& objectList)
{
	Source_ObjectList source(objectList);
	return DoFormat(format, source);
}

bool Formatter::DoFormat(const char* format, va_list ap)
{
	Source_va_list source(ap);
	return DoFormat(format, source);
}

bool Formatter::DoFormat(const char* format, Source& source)
{
	bool eatNextFlag;
	FormatterFlags formatterFlags;
	enum class Stat {
		Start, FlagsPre, Flags, FlagsAfterWhite, PrecisionPre, Precision, Padding,
	} stat = Stat::Start;
	_strErr.clear();
	for (const char* formatp = format; ; ) {
		char ch = *formatp;
		eatNextFlag = true;
		if (ch == '\0') break;
		switch (stat) {
		case Stat::Start: {
			if (ch == '%') {
				stat = Stat::FlagsPre;
			} else if (ch == '\n') {
				for (const char* p = _lineSep; *p != '\0'; p++) {
					if (!PutChar(*p)) return false;
				}
			} else {
				if (!PutChar(ch)) return false;
			}
			break;
		}
		case Stat::FlagsPre: {
			if (ch == '%') {
				if (!PutChar(ch)) return false;
				stat = Stat::Start;
			} else {
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					return false;
				}
				// initialize formatterFlags
				formatterFlags.Initialize();
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		case Stat::Flags: {
			if (ch == '#') {
				formatterFlags.sharpFlag = true;
			} else if (ch == '0') {
				if (!formatterFlags.leftAlignFlag) {
					formatterFlags.charPadding = '0';
				}
			} else if (ch == '-') {
				formatterFlags.leftAlignFlag = true;
				formatterFlags.charPadding = ' ';
			} else if (ch == ' ') {
				if (formatterFlags.plusMode == FormatterFlags::PlusMode::None) {
					formatterFlags.plusMode = FormatterFlags::PlusMode::Space;
				}
				stat = Stat::FlagsAfterWhite;
			} else if (ch == '+') {
				formatterFlags.plusMode = FormatterFlags::PlusMode::Plus;
			} else if (ch == '*') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->IsType<Object_number>()) {
					IssueError_NumberIsExpectedForAsterisk();
					return false;
				}
				formatterFlags.fieldMinWidth = dynamic_cast<Object_number*>(pObject.get())->GetInt();
				if (formatterFlags.fieldMinWidth < 0) {
					formatterFlags.leftAlignFlag = true;
					formatterFlags.fieldMinWidth = -formatterFlags.fieldMinWidth;
				}
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					return false;
				}
			} else if ('0' < ch && ch <= '9') {
				eatNextFlag = false;
				stat = Stat::Padding;
			} else if (ch == '.') {
				stat = Stat::PrecisionPre;
			} else if (ch == 'l') {
				// just ignore it
			} else if (ch == 'z') {
				// just ignore it
			} else if (ch == 'd' || ch == 'i') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->Format_d(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'u') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->Format_u(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'b') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->Format_b(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'o') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->Format_o(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'x' || ch == 'X') {
				RefPtr<Object> pObject = source.FetchInt();
				formatterFlags.upperCaseFlag = (ch == 'X');
				if (!pObject->Format_x(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'e' || ch == 'E') {
				RefPtr<Object> pObject = source.FetchDouble();
				formatterFlags.upperCaseFlag = (ch == 'E');
				if (!pObject->Format_e(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'f' || ch == 'F') {
				RefPtr<Object> pObject = source.FetchDouble();
				if (!pObject->Format_f(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'g' || ch == 'G') {
				RefPtr<Object> pObject = source.FetchDouble();
				formatterFlags.upperCaseFlag = (ch == 'G');
				if (!pObject->Format_g(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 's') {
				RefPtr<Object> pObject = source.FetchString();
				if (!pObject->Format_s(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'c') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->Format_c(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else {
				IssueError_WrongFormat();
				return false;
			}
			break;
		}
		case Stat::FlagsAfterWhite: {
			if (ch == ' ') {
				IssueError_WrongFormat();
				return false;
			} else {
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		case Stat::Padding: {
			if ('0' <= ch && ch <= '9') {
				formatterFlags.fieldMinWidth = formatterFlags.fieldMinWidth * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		case Stat::PrecisionPre: {
			if (ch == '*') {
				RefPtr<Object> pObject = source.FetchInt();
				if (!pObject->IsType<Object_number>()) {
					IssueError_NumberIsExpectedForAsterisk();
					return false;
				}
				formatterFlags.precision = dynamic_cast<Object_number*>(pObject.get())->GetInt();
				if (formatterFlags.precision < 0) formatterFlags.precision = FormatterFlags::PREC_Default;
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					return false;
				}
				stat = Stat::Flags;
			} else if ('0' <= ch && ch <= '9') {
				formatterFlags.precision = 0;
				eatNextFlag = false;
				stat = Stat::Precision;
			} else {
				formatterFlags.precision = FormatterFlags::PREC_Null;
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		case Stat::Precision: {
			if ('0' <= ch && ch <= '9') {
				formatterFlags.precision = formatterFlags.precision * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		default:
			break;
		}
		if (eatNextFlag) formatp++;
	}
	return true;
}

bool Formatter::PutString(const char* p)
{
	for ( ; *p != '\0'; p++) if (!PutChar(*p)) return false;
	return true;
}

bool Formatter::PutAlignedString(const FormatterFlags& formatterFlags, const char* p, int cntMax)
{
	int cnt = static_cast<int>(::strlen(p));
	if (cntMax >= 0 && cnt > cntMax) cnt = cntMax;
	//int cntPadding = formatterFlags.fieldMinWidth - static_cast<int>(String::Width(p));
	int cntPadding = formatterFlags.fieldMinWidth - static_cast<int>(0);
	if (formatterFlags.leftAlignFlag) {
		for ( ; cnt > 0; p++, cnt--) if (!PutChar(*p)) return false;
		while (cntPadding-- > 0) if (!PutChar(formatterFlags.charPadding)) return false;
	} else {
		while (cntPadding-- > 0) if (!PutChar(formatterFlags.charPadding)) return false;
		for ( ; cnt > 0; p++, cnt--) if (!PutChar(*p)) return false;
	}
	return true;
}

bool Formatter::PutInvalid(const FormatterFlags& formatterFlags)
{
	if (!_nilVisibleFlag) return true;
	std::string str;
	str += Gurax_Symbol(nil)->GetName();
	return PutAlignedString(formatterFlags, str.c_str());
}

#if 0
String Formatter::Format(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return FormatV(format, ap);
}

String Formatter::FormatV(const char* format, va_list ap)
{
	FormatterString formatter;
	formatter.DoFormat(format, ap);
	return formatter.GetStringSTL();
}

String Formatter::FormatObjectList(const char* format, const ObjectList& objectList)
{
	FormatterString formatter;
	formatter.DoFormat(format, objectList);
	return formatter.GetStringSTL();
}
#endif

#if 0
const Object* Formatter::FormatIterator(const char* format, IteratorOwner& iterOwner)
{
	const Object* pObject;
	Object_list* pObjListResult = result.InitAsList(env);
	ObjectList objectList;
	while (iterOwner.Next(objectList)) {
		String str = FormatObjectList(format, objectList);
		if (Error::IsIssued()) return Object::nil();
		pObjListResult->Add(Value(str));
	}
	if (Error::IsIssued()) return Object::nil();
	return result;
}
#endif

char* Formatter::FillZeroDigit(char* dstp, char* dstpEnd, int cnt)
{
	for ( ; cnt > 0 && dstp < dstpEnd - 1; cnt--, dstp++) {
		*dstp = '0';
	}
	*dstp = '\0';
	return dstp;
}

char* Formatter::CopyDigits(char* dstp, char* dstpEnd, const char* srcp)
{
	for ( ; *srcp != '\0' && dstp < dstpEnd - 1; srcp++, dstp++) {
		*dstp = static_cast<char>(*srcp);
	}
	*dstp = '\0';
	return dstp;
}

char* Formatter::CopyDigits(char* dstp, char* dstpEnd, const char* srcp, int cnt)
{
	for ( ; *srcp != '\0' && dstp < dstpEnd - 1 && cnt > 0; srcp++, dstp++, cnt--) {
		*dstp = static_cast<char>(*srcp);
	}
	for ( ; dstp < dstpEnd - 1 && cnt > 0; dstp++, cnt--) {
		*dstp = '0';
	}
	*dstp = '\0';
	return dstp;
}

//-----------------------------------------------------------------------------
// FormatterFlags
//-----------------------------------------------------------------------------
void FormatterFlags::Initialize()
{
	upperCaseFlag = false;
	leftAlignFlag = false;
	sharpFlag = false;
	fieldMinWidth = 0;
	precision = PREC_Default;
	plusMode = PlusMode::None;
	charPadding = ' ';
}

const char* FormatterFlags::FormatNumber_d(Int64 num, char* buff, size_t size) const
{
	char* p = buff + size - 1;
	*p = '\0';
	if (num == 0) {
		if (precision == 0) {
			// empty string
		} else {
			p--;
			*p = '0';
		}
	} else if (num > 0) {
		int nCols = 0;
		for ( ; num != 0; num /= 10, nCols++) {
			p--;
			*p = (num % 10) + '0';
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 2);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		}
		if (plusMode == PlusMode::Space) {
			p--;
			*p = ' ';
		} else if (plusMode == PlusMode::Plus) {
			p--;
			*p = '+';
		}
	} else {
		int nCols = 0;
		UInt64 numNeg = -num;
		for ( ; numNeg != 0; numNeg /= 10, nCols++) {
			p--;
			*p = (numNeg % 10) + '0';
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 2);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		}
		p--;
		*p = '-';
	}
	return p;
}

const char* FormatterFlags::FormatNumber_u(UInt64 num, char* buff, size_t size) const
{
	char* p = buff + size - 1;
	*p = '\0';
	if (num == 0) {
		if (precision == 0) {
			// empty string
		} else {
			p--;
			*p = '0';
		}
	} else {
		int nCols = 0;
		for ( ; num != 0; num /= 10, nCols++) {
			p--;
			*p = (num % 10) + '0';
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 1);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		}
	}
	return p;
}

const char* FormatterFlags::FormatNumber_b(UInt64 num, char* buff, size_t size) const
{
	char* p = buff + size - 1;
	*p = '\0';
	if (num == 0) {
		if (precision == 0) {
			// empty string
		} else {
			p--;
			*p = '0';
		}
	} else {
		int nCols = 0;
		for ( ; num != 0; num >>= 1, nCols++) {
			p--;
			*p = '0' + (num & 0x1);
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 1);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		} else if (sharpFlag) {
			p--;
			*p = 'b';
			p--;
			*p = '0';
		}
	}
	return p;
}

const char* FormatterFlags::FormatNumber_o(UInt64 num, char* buff, size_t size) const
{
	char* p = buff + size - 1;
	*p = '\0';
	if (num == 0) {
		if (precision == 0) {
			// empty string
		} else {
			p--;
			*p = '0';
		}
	} else {
		int nCols = 0;
		for ( ; num != 0; num >>= 3, nCols++) {
			p--;
			*p = '0' + (num & 0x7);
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 1);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		} else if (sharpFlag) {
			p--;
			*p = '0';
		}
	}
	return p;
}

const char* FormatterFlags::FormatNumber_x(UInt64 num, char* buff, size_t size) const
{
	char* p = buff + size - 1;
	*p = '\0';
	const char* convTbl = upperCaseFlag? "0123456789ABCDEF" : "0123456789abcdef";
	if (num == 0) {
		if (precision == 0) {
			// empty string
		} else {
			p--;
			*p = '0';
		}
	} else {
		int nCols = 0;
		for ( ; num != 0; num >>= 4, nCols++) {
			p--;
			*p = convTbl[num & 0xf];
		}
		if (nCols < precision) {
			int precision = std::min(precision, static_cast<int>(size) - 3);
			int cnt = precision - nCols;
			while (cnt-- > 0) {
				p--;
				*p = '0';
			}
		}
		if (sharpFlag) {
			p--;
			*p = upperCaseFlag? 'X' : 'x';
			p--;
			*p = '0';
		}
	}
	return p;
}

const char* FormatterFlags::FormatNumber_e(double num, char* buff, size_t size) const
{
	::snprintf(buff, size, ToString(upperCaseFlag? "E" : "e").c_str(), num);
	return buff;
}

const char* FormatterFlags::FormatNumber_f(double num, char* buff, size_t size) const
{
	::snprintf(buff, size, ToString("f").c_str(), num);
	return buff;
}

const char* FormatterFlags::FormatNumber_g(double num, char* buff, size_t size) const
{
	::snprintf(buff, size, ToString(upperCaseFlag? "G" : "g").c_str(), num);
	return buff;
}

String FormatterFlags::ToString(const char* qualifier) const
{
	String fmt = "%";
	if (leftAlignFlag) fmt += "-";
	if (sharpFlag) fmt += "#";
	if (charPadding == '0') fmt += '0';
	if (plusMode == PlusMode::Space) {
		fmt += " ";
	} else if (plusMode == PlusMode::Plus) {
		fmt += "+";
	}
	if (fieldMinWidth > 0) {
		char buff[64];
		::sprintf(buff, "%d", fieldMinWidth);
		fmt += buff;
	}
	if (precision == PREC_Null) {
		fmt += '.';
	} else if (precision >= 0) {
		char buff[64];
		::sprintf(buff, ".%d", precision);
		fmt += buff;
	}
	fmt += qualifier;
	return fmt;
}

//-----------------------------------------------------------------------------
// FormatterString
//-----------------------------------------------------------------------------

}
