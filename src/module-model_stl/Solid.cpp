//==============================================================================
// Solid.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Solid
//------------------------------------------------------------------------------
Solid::Solid(Stream* pStream) : _pStream(pStream), _binaryFlag(false), _nFace(0)
{
}

bool Solid::ReadHeader()
{
	char buff[128];
	size_t bytesRead = _pStream->Read(buff, 6);
	if (bytesRead < 6) {
		SetError_FormatError();
		return false;
	}
	if (::memcmp(buff, "solid ", 6) == 0) {
		// "solid name"
		_binaryFlag = false;
		String field;
		for (;;) {
			int chRaw = _pStream->GetChar();
			if (Error::IsIssued()) return false;
			char ch = (chRaw < 0)? '\0' : static_cast<char>(static_cast<UInt8>(chRaw));
			if (ch == '\0' || ch == '\n') break;
			field += ch;
		}
		_name = field.Strip(true, true);
	} else {
		// UInt8[80] Header
		// UInt32    Number of triangles
		_binaryFlag = true;
		size_t bytesRead = _pStream->Read(buff + 6, 80 - 6);
		if (bytesRead < 80 - 6) {
			SetError_FormatError();
			return false;
		}
		_header = Binary(buff, 80);
		bytesRead = _pStream->Read(buff, 4);
		if (bytesRead < 4) {
			SetError_FormatError();
			return false;
		}
		_nFace =* reinterpret_cast<UInt32*>(buff);
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
// Iterator_EachFace_Binary
//------------------------------------------------------------------------------
Value* Iterator_EachFace_Binary::DoNextValue()
{
	if (_idxFace >= GetSolid().GetNFace()) return false;
	Face::Packed facePacked;
	size_t bytesRead = GetSolid().GetStream().Read(&facePacked, Face::Packed::Size);
	if (bytesRead < Face::Packed::Size) {
		SetError_FormatError();
		return false;
	}
	RefPtr<Face> pFace(new Face(
		new VertexRef(Vertex(facePacked.vertex1[0], facePacked.vertex1[1], facePacked.vertex1[2])),
		new VertexRef(Vertex(facePacked.vertex2[0], facePacked.vertex2[1], facePacked.vertex2[2])),
		new VertexRef(Vertex(facePacked.vertex3[0], facePacked.vertex3[1], facePacked.vertex3[2])),
		facePacked.attr));
	if (facePacked.normal[0] != 0. || facePacked.normal[1] != 0. || facePacked.normal[2] != 0.) {
		pFace->SetNormal(new VertexRef(Vertex(facePacked.normal[0], facePacked.normal[1], facePacked.normal[2])));
	}
	_idxFace++;
	return new Value_Face(pFace.release());
}

String Iterator_EachFace_Binary::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.EachFace:Binary:%dtriangles", GetSolid().GetNFace());
}

//------------------------------------------------------------------------------
// Iterator_EachFace_Text
//------------------------------------------------------------------------------
Value* Iterator_EachFace_Text::DoNextValue()
{
	size_t nCoords = 0;
	size_t nVertexes = 0;
	Vertex vertex;
	RefPtr<Face> pFace(new Face());
	for (;;) {
		TokenId tokenId = _tokenizer.Tokenize(GetSolid().GetStream());
		if (Error::IsIssued()) return nullptr;
		switch (_stat) {
		case Stat::facet: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "facet") == 0) {
					//pObjFace.reset(new Object_face());
					_stat = Stat::normal;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::normal: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "normal") == 0) {
					nCoords = 0;
					_stat = Stat::normal_coords;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::normal_coords: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				double num = 0;
				char* p = nullptr;
				num = ::strtod(field, &p);
				if (*p != '\0') {
					// error
				}
				nCoords++;
				if (nCoords == 1) {
					vertex.x = num;
				} else if (nCoords == 2) {
					vertex.y = num;
				} else if (nCoords == 3) {
					vertex.z = num;
					pFace->SetNormal(new VertexRef(vertex));
					_stat = Stat::outer;
				}
			}
			break;
		}
		case Stat::outer: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "outer") == 0) {
					_stat = Stat::loop;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::loop: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "loop") == 0) {
					nVertexes = 0;
					_stat = Stat::vertex;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::vertex: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "vertex") == 0) {
					nCoords = 0;
					_stat = Stat::vertex_coords;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::vertex_coords: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				double num = 0;
				char* p = nullptr;
				num = ::strtod(field, &p);
				if (*p != '\0') {
					// error
				}
				nCoords++;
				if (nCoords == 1) {
					vertex.x = num;
				} else if (nCoords == 2) {
					vertex.y = num;
				} else if (nCoords == 3) {
					vertex.z = num;
					if (nVertexes == 0) {
						pFace->SetVertex1(new VertexRef(vertex));
					} else if (nVertexes == 1) {
						pFace->SetVertex2(new VertexRef(vertex));
					} else if (nVertexes == 2) {
						pFace->SetVertex3(new VertexRef(vertex));
					}
					nVertexes++;
					if (nVertexes == 3) {
						if (pFace->GetNormal().IsZero()) {
							pFace->UpdateNormal();
						}
						_stat = Stat::endloop;
					} else {
						_stat = Stat::vertex;
					}
				}
			}
			break;
		}
		case Stat::endloop: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "endloop") == 0) {
					_stat = Stat::endfacet;
				} else {
					// error
				}
			}
			break;
		}
		case Stat::endfacet: {
			if (tokenId == TokenId::Field) {
				const char* field = _tokenizer.GetField();
				if (::strcmp(field, "endfacet") == 0) {
					_stat = Stat::facet;
					return new Value_Face(pFace.release());
				} else {
					// error
				}
			}
			break;
		}
		}
		if (tokenId == TokenId::EndOfFile) break;
	}
	return nullptr;
}

String Iterator_EachFace_Text::ToString(const StringStyle& ss) const
{
	return String().Format("model.stl.EachFace:Text:'%s'", GetSolid().GetName());
}

Iterator_EachFace_Text::TokenId Iterator_EachFace_Text::Tokenizer::Tokenize(Stream& stream)
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

Gurax_EndModuleScope(model_stl)
