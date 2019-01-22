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
	const char* formatp = format;
	FormatterFlags formatterFlags;
	enum {
		STAT_Start,
		STAT_FlagsPre, STAT_Flags, STAT_FlagsAfterWhite,
		STAT_PrecisionPre, STAT_Precision,
		STAT_Padding,
	} stat = STAT_Start;
	for (;;) {
		char ch = *formatp;
		eatNextFlag = true;
		if (ch == '\0') {
			break;
		} else if (stat == STAT_Start) {
			if (ch == '%') {
				stat = STAT_FlagsPre;
			} else if (ch == '\n') {
				for (const char* p = _lineSep; *p != '\0'; p++) {
					if (!PutChar(*p)) return false;
				}
			} else {
				if (!PutChar(ch)) return false;
			}
		} else if (stat == STAT_FlagsPre) {
			if (ch == '%') {
				if (!PutChar(ch)) return false;
				stat = STAT_Start;
			} else {
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					break;
				}
				// initialize formatterFlags
				formatterFlags.Initialize();
				eatNextFlag = false;
				stat = STAT_Flags;
			}
		} else if (stat == STAT_Flags) {
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
				stat = STAT_FlagsAfterWhite;
			} else if (ch == '+') {
				formatterFlags.plusMode = FormatterFlags::PlusMode::Plus;
			} else if (ch == '*') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->IsType<Object_number>()) {
					Error::Issue(ErrorType::ValueError, "number is expected for * specifier");
					break;
				}
				formatterFlags.fieldMinWidth = dynamic_cast<Object_number*>(pObject.get())->GetInt();
				if (formatterFlags.fieldMinWidth < 0) {
					formatterFlags.leftAlignFlag = true;
					formatterFlags.fieldMinWidth = -formatterFlags.fieldMinWidth;
				}
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					break;
				}
			} else if ('0' < ch && ch <= '9') {
				eatNextFlag = false;
				stat = STAT_Padding;
			} else if (ch == '.') {
				stat = STAT_PrecisionPre;
			} else if (ch == 'l') {
				// just ignore it
			} else if (ch == 'z') {
				// just ignore it
			} else if (ch == 'd' || ch == 'i') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->Format_d(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'u') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->Format_u(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'b') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->Format_b(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'o') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->Format_o(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'x' || ch == 'X') {
				RefPtr<Object> pObject = source.GetInt();
				formatterFlags.upperCaseFlag = (ch == 'X');
				if (!pObject->Format_x(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'e' || ch == 'E') {
				RefPtr<Object> pObject = source.GetDouble();
				formatterFlags.upperCaseFlag = (ch == 'E');
				if (!pObject->Format_e(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'f' || ch == 'F') {
				RefPtr<Object> pObject = source.GetDouble();
				if (!pObject->Format_f(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'g' || ch == 'G') {
				RefPtr<Object> pObject = source.GetDouble();
				formatterFlags.upperCaseFlag = (ch == 'G');
				if (!pObject->Format_g(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 's') {
				RefPtr<Object> pObject = source.GetString();
				if (!pObject->Format_s(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else if (ch == 'c') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->Format_c(*this, formatterFlags)) break;
				stat = STAT_Start;
			} else {
				IssueError_WrongFormat();
				break;
			}
		} else if (stat == STAT_FlagsAfterWhite) {
			if (ch == ' ') {
				IssueError_WrongFormat();
				break;
			} else {
				eatNextFlag = false;
				stat = STAT_Flags;
			}
		} else if (stat == STAT_Padding) {
			if ('0' <= ch && ch <= '9') {
				formatterFlags.fieldMinWidth = formatterFlags.fieldMinWidth * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = STAT_Flags;
			}
		} else if (stat == STAT_PrecisionPre) {
			if (ch == '*') {
				RefPtr<Object> pObject = source.GetInt();
				if (!pObject->IsType<Object_number>()) {
					Error::Issue(ErrorType::ValueError, "number is expected for * specifier");
					break;
				}
				formatterFlags.precision = dynamic_cast<Object_number*>(pObject.get())->GetInt();
				if (formatterFlags.precision < 0) formatterFlags.precision = FormatterFlags::PREC_Default;
				if (source.IsEnd()) {
					IssueError_NotEnoughArguments();
					break;
				}
				stat = STAT_Flags;
			} else if ('0' <= ch && ch <= '9') {
				formatterFlags.precision = 0;
				eatNextFlag = false;
				stat = STAT_Precision;
			} else {
				formatterFlags.precision = FormatterFlags::PREC_Null;
				eatNextFlag = false;
				stat = STAT_Flags;
			}
		} else if (stat == STAT_Precision) {
			if ('0' <= ch && ch <= '9') {
				formatterFlags.precision = formatterFlags.precision * 10 + (ch - '0');
			} else {
				eatNextFlag = false;
				stat = STAT_Flags;
			}
		}
		if (eatNextFlag) formatp++;
	}
	return !Error::IsIssued();
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

String Formatter::Format(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	return Formatter::FormatV(format, ap);
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

void Formatter::IssueError_WrongFormat()
{
	Error::Issue(ErrorType::ValueError, "wrong format for formatter");
}

void Formatter::IssueError_NotEnoughArguments()
{
	Error::Issue(ErrorType::TypeError, "not enough arguments for formatter");
}

//-----------------------------------------------------------------------------
// Formatter::Source_ObjectList
//-----------------------------------------------------------------------------
bool Formatter::Source_ObjectList::IsEnd()
{
	return _ppObject == _objectList.end();
}

Object* Formatter::Source_ObjectList::GetInt()
{
	return (*_ppObject++)->Reference();
}

Object* Formatter::Source_ObjectList::GetDouble()
{
	return (*_ppObject++)->Reference();
}

Object* Formatter::Source_ObjectList::GetString()
{
	return (*_ppObject++)->Reference();
}

//-----------------------------------------------------------------------------
// Formatter::Source_va_list
//-----------------------------------------------------------------------------
bool Formatter::Source_va_list::IsEnd()
{
	return false;
}

Object* Formatter::Source_va_list::GetInt()
{
	int value = va_arg(_ap, int);
	return new Object_number(value);
}

Object* Formatter::Source_va_list::GetDouble()
{
	double value = va_arg(_ap, double);
	return new Object_number(value);
}

Object* Formatter::Source_va_list::GetString()
{
	char* value = va_arg(_ap, char*);
	return new Object_string(value);
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
bool FormatterString::PutChar(char ch)
{
	_str += ch;
	return true;
}

}
