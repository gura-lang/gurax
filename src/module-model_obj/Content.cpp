//==============================================================================
// Content.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
bool Content::Read(Stream& stream)
{
	return false;
}

String Content::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.Content");
}

//------------------------------------------------------------------------------
// Content::Tokenizer
//------------------------------------------------------------------------------
Content::TokenId Content::Tokenizer::Tokenize(Stream& stream)
{
	_iChar = 0;
	if (_tokenIdPending != TokenId::None) {
		TokenId tokenId = _tokenIdPending;
		_tokenIdPending = TokenId::None;
		return tokenId;
	}
	bool escapeFlag = false;
	for (;;) {
		int chRaw = stream.GetChar();
		if (Error::IsIssued()) break;
		char ch = (chRaw < 0)? '\0' : static_cast<char>(static_cast<UChar>(chRaw));
		if (ch == '\\' && !escapeFlag) {
			escapeFlag = true;
			continue;
		}
		Gurax_BeginPushbackRegion();
		switch (_stat) {
		case Stat::LineTop: {
			if (ch == ' ' || ch == '\t') {
				// nothing to do
			} else if (ch == '\n' || ch == '\0') {
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
				_stat = Stat::FileEnd;
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
					// nothing to do
				} else {
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
		case Stat::FileEnd: {
			// nothing to do
			break;
		}
		}
		Gurax_EndPushbackRegion();
		escapeFlag = false;
		if (ch == '\0') break;
		if (ch == '\n') _iLine++;
	}
	return TokenId::EndOfFile;
}

Gurax_EndModuleScope(model_obj)
