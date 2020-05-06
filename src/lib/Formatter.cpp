//=============================================================================
// Formatter
//=============================================================================
#include "stdafx.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// Formatter
//-----------------------------------------------------------------------------
bool Formatter::Format(const char* format, Source&& source)
{
	enum class Stat {
		Start,
		FlagsPre, Flags,
		FlagsAfterWhite, FlagsAfterL, FlagsAfterLL, FlagsAfterZ,
		PrecisionPre, Precision, Padding,
	};
	bool eatNextFlag;
	FormatterFlags formatterFlags;
	Stat stat = Stat::Start;
	for (const char* formatp = format; ; ) {
		char ch = *formatp;
		eatNextFlag = true;
		if (ch == '\0') break;
		switch (stat) {
		case Stat::Start: {
			if (ch == '%') {
				stat = Stat::FlagsPre;
			} else if (ch == '\n') {
				if (!PutString(_lineSep)) return false;
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
				RefPtr<Value> pValue(source.FetchInt());
				if (!pValue->IsType(VTYPE_Number)) {
					IssueError_NumberIsExpectedForAsterisk();
					return false;
				}
				formatterFlags.fieldMinWidth = Value_Number::GetNumber<Int>(*pValue);
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
				stat = Stat::FlagsAfterL;
			} else if (ch == 'z') {
				stat = Stat::FlagsAfterZ;
			} else if (ch == 'd' || ch == 'i') {
				RefPtr<Value> pValue(source.FetchInt());
				if (!pValue->Format_d(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'u') {
				RefPtr<Value> pValue(source.FetchUInt());
				if (!pValue->Format_u(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'b') {
				RefPtr<Value> pValue(source.FetchUInt());
				if (!pValue->Format_b(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'o') {
				RefPtr<Value> pValue(source.FetchUInt());
				if (!pValue->Format_o(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'x' || ch == 'X') {
				RefPtr<Value> pValue(source.FetchUInt());
				formatterFlags.upperCaseFlag = (ch == 'X');
				if (!pValue->Format_x(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'p') {
				RefPtr<Value> pValue(source.FetchSizeT());
				if (!PutString("0x")) return false;
				if (!pValue->Format_x(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'e' || ch == 'E') {
				RefPtr<Value> pValue(source.FetchDouble());
				formatterFlags.upperCaseFlag = (ch == 'E');
				if (!pValue->Format_e(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'f' || ch == 'F') {
				RefPtr<Value> pValue(source.FetchDouble());
				if (!pValue->Format_f(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'g' || ch == 'G') {
				RefPtr<Value> pValue(source.FetchDouble());
				formatterFlags.upperCaseFlag = (ch == 'G');
				if (!pValue->Format_g(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 's') {
				RefPtr<Value> pValue(source.FetchString());
				if (!pValue->Format_s(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'c') {
				RefPtr<Value> pValue(source.FetchInt());
				if (!pValue->Format_c(*this, formatterFlags)) return false;
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
		case Stat::FlagsAfterL: {
			if (ch == 'l') {
				stat = Stat::FlagsAfterLL;
			} else {
				eatNextFlag = false;
				stat = Stat::Flags;
			}
			break;
		}
		case Stat::FlagsAfterLL: {
			if (ch == 'd' || ch == 'i') {
				RefPtr<Value> pValue(source.FetchInt64());
				if (!pValue->Format_d(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'u') {
				RefPtr<Value> pValue(source.FetchUInt64());
				if (!pValue->Format_u(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'b') {
				RefPtr<Value> pValue(source.FetchUInt64());
				if (!pValue->Format_b(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'o') {
				RefPtr<Value> pValue(source.FetchUInt64());
				if (!pValue->Format_o(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'x' || ch == 'X') {
				RefPtr<Value> pValue(source.FetchUInt64());
				formatterFlags.upperCaseFlag = (ch == 'X');
				if (!pValue->Format_x(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else {
				IssueError_WrongFormat();
				return false;
			}
			break;
		}
		case Stat::FlagsAfterZ: {
			if (ch == 'd' || ch == 'i') {
				RefPtr<Value> pValue(source.FetchSizeT());
				if (!pValue->Format_d(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'u') {
				RefPtr<Value> pValue(source.FetchSizeT());
				if (!pValue->Format_u(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'b') {
				RefPtr<Value> pValue(source.FetchSizeT());
				if (!pValue->Format_b(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'o') {
				RefPtr<Value> pValue(source.FetchSizeT());
				if (!pValue->Format_o(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else if (ch == 'x' || ch == 'X') {
				RefPtr<Value> pValue(source.FetchSizeT());
				formatterFlags.upperCaseFlag = (ch == 'X');
				if (!pValue->Format_x(*this, formatterFlags)) return false;
				stat = Stat::Start;
			} else {
				IssueError_WrongFormat();
				return false;
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
				RefPtr<Value> pValue(source.FetchInt());
				if (!pValue->IsType(VTYPE_Number)) {
					IssueError_NumberIsExpectedForAsterisk();
					return false;
				}
				formatterFlags.precision = Value_Number::GetNumber<Int>(*pValue);
				if (formatterFlags.precision < 0) formatterFlags.precision = FormatterFlags::Prec::Default;
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
				formatterFlags.precision = FormatterFlags::Prec::Null;
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
	int cntPadding = formatterFlags.fieldMinWidth - static_cast<int>(String::Width(p));
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
	String str;
	str += Gurax_Symbol(nil)->GetName();
	return PutAlignedString(formatterFlags, str.c_str());
}

#if 0
Value_list* Formatter::FormatIterator(const char* format, IteratorOwner& iterOwner)
{
	const Value* pValue;
	Value_list* pValueListResult = result.InitAsList(env);
	ValueList valueList;
	while (iterOwner.Next(valueList)) {
		String str = FormatValueList(format, valueList);
		if (Error::IsIssued()) return Value::nil();
		pValueListResult->Add(Value(str));
	}
	if (Error::IsIssued()) return Value::nil();
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
	precision = Prec::Default;
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
	if (fieldMinWidth > 0) fmt.Printf("%d", fieldMinWidth);
	if (precision == Prec::Null) {
		fmt += '.';
	} else if (precision >= 0) {
		fmt.Printf(".%d", precision);
	}
	fmt += qualifier;
	return fmt;
}

}
