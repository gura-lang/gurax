//==============================================================================
// Tokenizer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
TokenId Tokenizer::Tokenize(Stream& stream)
{
	_iChar = 0;
	_iLine += _iLineInc;
	_iLineInc = 0;
	if (_tokenIdPending != TokenId::None) {
		TokenId tokenId = _tokenIdPending;
		_tokenIdPending = TokenId::None;
		return tokenId;
	}
	bool escapeFlag = false;
	for (;;) {
		char ch = stream.GetChar();
		if (Error::IsIssued()) break;
		if (ch == '\\' && !escapeFlag) {
			escapeFlag = true;
			continue;
		}
		Gurax_BeginPushbackRegion();
		switch (_stat) {
		case Stat::LineTop: {
			if (ch == ' ' || ch == '\t') {
				// nothing to do
			} else if (ch == '\n') {
				_iLine++;
			} else if (ch == '\0') {
				// nothing to do
			} else if (ch == '#') {
				_stat = Stat::SkipToNextLine;
			} else {
				Gurax_Pushback();
				_stat = Stat::Field;
			}
			break;
		}
		case Stat::SkipToNextLine: {
			if (ch == '\n') {
				_iLine++;
				if (escapeFlag) {
					// nothing to do
				} else {
					_stat = Stat::LineTop;
				}
			} else {
				// nothing to do
			}
			break;
		}
		case Stat::Field: {
			if (ch == ' ' || ch == '\t') {
				_stat = Stat::SkipWhite;
				_field[_iChar] = '\0';
				return TokenId::Field;
			} else if (ch == '\n') {
				_iLineInc = 1;
				if (escapeFlag) {
					_stat = Stat::SkipWhite;
				} else {
					_tokenIdPending = TokenId::EndOfLine;
					_stat = Stat::LineTop;
				}
				_field[_iChar] = '\0';
				return TokenId::Field;
			} else if (ch == '\0') {
				_tokenIdPending = TokenId::EndOfFile;
				_stat = Stat::EndOfFile;
				_field[_iChar] = '\0';
				return TokenId::Field;
			} else {
				_field[_iChar++] = ch;
				if (_iChar >= Gurax_ArraySizeOf(_field)) {
					SetError_FormatError();
					return TokenId::EndOfFile;
				}
			}
			break;
		}
		case Stat::SkipWhite: {
			if (ch == ' ' || ch == '\t') {
				// nothing to do
			} else if (ch == '\n') {
				if (escapeFlag) {
					_iLine++;
				} else {
					_iLineInc = 1;
					_stat = Stat::LineTop;
					return TokenId::EndOfLine;
				}
			} else if (ch == '\0') {
				_stat = Stat::LineTop;
				return TokenId::EndOfFile;
			} else {
				Gurax_Pushback();
				_stat = Stat::Field;
			}
			break;
		}
		case Stat::EndOfFile: {
			// nothing to do
			break;
		}
		}
		Gurax_EndPushbackRegion();
		escapeFlag = false;
		if (ch == '\0') break;
	}
	return TokenId::EndOfFile;
}

bool Tokenizer::ExtractFloat(double* pNum) const
{
	char* p = nullptr;
	*pNum = ::strtod(GetField(), &p);
	if (*p == '\0') return true;
	Error::Issue(ErrorType::FormatError, "invalid format of float number");
	return false;
}

bool Tokenizer::ExtractIndex(int* piV) const
{
	const char* errMsg = "invalid format of vertex index";
	char* p = nullptr;
	*piV = static_cast<int>(::strtol(GetField(), &p, 10));
	while (*p == ' ' || *p == '\t') p++;
	if (*p != '\0') {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	if (*piV < 0) {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	return true;
}

bool Tokenizer::ExtractIndexPair(int* piV, int* piVt) const
{
	const char* errMsg = "invalid format of vertex index pair";
	*piV = *piVt = 0;
	char* p = const_cast<char*>(GetField());
	if (*p == '/') {
		*piV = 0;
		p++;
	} else if (String::IsDigit(*p)) {
		*piV = static_cast<int>(::strtol(p, &p, 10));
		if (*p == '/') p++;
	} else {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	while (*p == ' ' || *p == '\t') p++;
	if (*p == '\0') {
		return true;
	} else if (*p == '/') {
		p++;
	} else if (String::IsDigit(*p)) {
		*piVt = static_cast<int>(::strtol(p, &p, 10));
	} else {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	while (*p == ' ' || *p == '\t') p++;
	if (*p != '\0') {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	if (*piV < 0 || *piVt < 0) {
		Error::Issue(ErrorType::FormatError, errMsg);
		return false;
	}
	return true;
}

bool Tokenizer::ExtractIndexTriplet(int* piV, int* piVt, int* piVn) const
{
	const char* errMsg = "%d: invalid format of vertex index triplet";
	*piV = *piVt = *piVn = 0;
	char* p = const_cast<char*>(GetField());
	if (*p == '/') {
		*piV = 0;
		p++;
	} else if (String::IsDigit(*p)) {
		*piV = static_cast<int>(::strtol(p, &p, 10));
		if (*p == '/') p++;
	} else {
		Error::Issue(ErrorType::FormatError, errMsg, GetLineNo());
		return false;
	}
	if (*p == '\0') {
		return true;
	} else if (*p == '/') {
		p++;
	} else if (String::IsDigit(*p)) {
		*piVt = static_cast<int>(::strtol(p, &p, 10));
		if (*p == '/') p++;
	} else {
		Error::Issue(ErrorType::FormatError, errMsg, GetLineNo());
		return false;
	}
	if (*p == '\0') {
		return true;
	} else if (*p == '/') {
		p++;
	} else if (String::IsDigit(*p)) {
		*piVn = static_cast<int>(::strtol(p, &p, 10));
	} else {
		Error::Issue(ErrorType::FormatError, errMsg, GetLineNo());
		return false;
	}
	if (*p != '\0') {
		Error::Issue(ErrorType::FormatError, errMsg, GetLineNo());
		return false;
	}
	if (*piV < 0 || *piVt < 0 || *piVn < 0) {
		Error::Issue(ErrorType::FormatError, errMsg, GetLineNo());
	}
	return true;
}

Gurax_EndModuleScope(model_obj)
