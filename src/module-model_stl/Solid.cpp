//==============================================================================
// Solid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Solid
//------------------------------------------------------------------------------
Solid::Solid(Stream* pStream) : _pStream(pStream), _nFace(0)
{
}

bool Solid::Prepare()
{
	char buff[81];
	size_t bytesRead = _pStream->Read(buff, 6);
	if (bytesRead < 6) {
		SetError_FormatError();
		return false;
	}
	if (::memcmp(buff, "solid ", 6) == 0) {
		String field;
		for (;;) {
			int chRaw = _pStream->GetChar();
			if (Error::IsIssued()) return false;
			char ch = (chRaw < 0)? '\0' : static_cast<char>(static_cast<UInt8>(chRaw));
			if (ch == '\0' || ch == '\n') break;
			field += ch;
		}
		_text = field.Strip(true, true);
	} else {
		_binaryFlag = true;
		size_t bytesRead = _pStream->Read(buff + 6, 80 - 6);
		buff[80] = '\0';
		if (bytesRead < 80 - 6) {
			SetError_FormatError();
			return false;
		}
		_text = buff;
		bytesRead = _pStream->Read(buff, 4);
		if (bytesRead < 4) {
			SetError_FormatError();
			return false;
		}
		_nFace = *reinterpret_cast<UInt32*>(buff);
	}
	return true;
}

Iterator* Solid::EachFace()
{
	if (_binaryFlag) {
		return new Iterator_EachFace_Binary(Reference());
	} else {
		return new Iterator_EachFace_Text(Reference());
	}
}

String Solid::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.Solid");
}

//------------------------------------------------------------------------------
// Solid::Tokenizer
//------------------------------------------------------------------------------
Solid::TokenId Solid::Tokenizer::Tokenize(Stream& stream)
{
	_iChar = 0;
	if (_tokenIdPending != TokenId::None) {
		TokenId tokenId = _tokenIdPending;
		_tokenIdPending = TokenId::None;
		return tokenId;
	}
	for (;;) {
		int chRaw = stream.GetChar();
		if (Error::IsIssued()) break;
		char ch = (chRaw < 0)? '\0' : static_cast<char>(static_cast<UChar>(chRaw));
		Gurax_BeginPushbackRegion();
		switch (_stat) {
		case Stat::LineTop: {
			if (ch == ' ' || ch == '\t') {
				// nothing to do
			} else if (ch == '\n' || ch == '\0') {
				// nothing to do
			} else {
				Gurax_Pushback();
				_stat = Stat::Field;
			}
			break;
		}
		case Stat::Field: {
			if (ch == ' ' || ch == '\t') {
				_stat = Stat::SkipWhite;
				_field[_iChar] = '\0';
				return TokenId::Field;
			} else if (ch == '\n') {
				_tokenIdPending = TokenId::EOL;
				_stat = Stat::LineTop;
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
				_stat = Stat::LineTop;
				return TokenId::EOL;
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
		if (ch == '\0') break;
	}
	return TokenId::EndOfFile;
}

//------------------------------------------------------------------------------
// Iterator_EachFace_Binary
//------------------------------------------------------------------------------
Value* Iterator_EachFace_Binary::DoNextValue()
{
	return nullptr;
}

String Iterator_EachFace_Binary::ToString(const StringStyle& ss) const
{
	return "model.stl.EachFace_Binary";
}

//------------------------------------------------------------------------------
// Iterator_EachFace_Text
//------------------------------------------------------------------------------
Value* Iterator_EachFace_Text::DoNextValue()
{
	return nullptr;
}

String Iterator_EachFace_Text::ToString(const StringStyle& ss) const
{
	return "model.stl.EachFace_Text";
}

Gurax_EndModuleScope(model_stl)
