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
	Stat stat = Stat::Keyword;
	size_t iParam = 0;
	Tokenizer tokenizer;
	double numTbl[32];
	StringList strList;
	for (;;) {
		TokenId tokenId = tokenizer.Tokenize(stream);
		const char* field = tokenizer.GetField();
		switch (stat) {
		case Stat::Keyword: {
			if (tokenId == TokenId::Field) {
				iParam = 0;
				if (::strcmp(field, "call") == 0) {
					stat = Stat::call;
				} else if (::strcmp(field, "csh") == 0) {
					stat = Stat::csh;
				} else if (::strcmp(field, "v") == 0) {
					stat = Stat::v;
				} else if (::strcmp(field, "vt") == 0) {
					stat = Stat::vt;
				} else if (::strcmp(field, "vn") == 0) {
					stat = Stat::vn;
				} else if (::strcmp(field, "vp") == 0) {
					stat = Stat::vp;
				} else if (::strcmp(field, "cstype") == 0) {
					stat = Stat::cstype;
				} else if (::strcmp(field, "deg") == 0) {
					stat = Stat::deg;
				} else if (::strcmp(field, "bmat") == 0) {
					stat = Stat::bmat;
				} else if (::strcmp(field, "step") == 0) {
					stat = Stat::step;
				} else if (::strcmp(field, "p") == 0) {
					_points.push_back(new Point());
					stat = Stat::p;
				} else if (::strcmp(field, "l") == 0) {
					_lines.push_back(new Line());
					stat = Stat::l;
				} else if (::strcmp(field, "f") == 0) {
					_faces.push_back(new Face());
					stat = Stat::f;
				} else if (::strcmp(field, "curv") == 0) {
					stat = Stat::curv;
				} else if (::strcmp(field, "curv2") == 0) {
					stat = Stat::curv2;
				} else if (::strcmp(field, "surf") == 0) {
					stat = Stat::surf;
				} else if (::strcmp(field, "parm") == 0) {
					stat = Stat::parm;
				} else if (::strcmp(field, "trim") == 0) {
					stat = Stat::trim;
				} else if (::strcmp(field, "hole") == 0) {
					stat = Stat::hole;
				} else if (::strcmp(field, "scrv") == 0) {
					stat = Stat::scrv;
				} else if (::strcmp(field, "sp") == 0) {
					stat = Stat::sp;
				} else if (::strcmp(field, "end") == 0) {
					stat = Stat::end;
				} else if (::strcmp(field, "con") == 0) {
					stat = Stat::con;
				} else if (::strcmp(field, "g") == 0) {
					stat = Stat::g;
				} else if (::strcmp(field, "s") == 0) {
					stat = Stat::s;
				} else if (::strcmp(field, "mg") == 0) {
					stat = Stat::mg;
				} else if (::strcmp(field, "o") == 0) {
					stat = Stat::o;
				} else if (::strcmp(field, "bevel") == 0) {
					stat = Stat::beval;
				} else if (::strcmp(field, "c_interp") == 0) {
					stat = Stat::c_interp;
				} else if (::strcmp(field, "d_interp") == 0) {
					stat = Stat::d_interp;
				} else if (::strcmp(field, "lod") == 0) {
					stat = Stat::lod;
				} else if (::strcmp(field, "usemap") == 0) {
					stat = Stat::usemap;
				} else if (::strcmp(field, "maplib") == 0) {
					stat = Stat::maplib;
				} else if (::strcmp(field, "usemtl") == 0) {
					stat = Stat::usemtl;
				} else if (::strcmp(field, "mtllib") == 0) {
					stat = Stat::mtllib;
				} else if (::strcmp(field, "shadow_obj") == 0) {
					stat = Stat::shadow_obj;
				} else if (::strcmp(field, "trace_obj") == 0) {
					stat = Stat::trace_obj;
				} else if (::strcmp(field, "ctech") == 0) {
					stat = Stat::ctech;
				} else if (::strcmp(field, "stech") == 0) {
					stat = Stat::stech;
				} else {
					Error::Issue(ErrorType::FormatError, "%d: unknown keyword '%s'", tokenizer.GetLineNo(), field);
					return false;
				}
			}
			break;
		}
		//----------------------------------------------------------------------
		// General statement
		case Stat::call: {
			// reads another obj file: call filename.ext arg1 arg2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("call");
				return false;
			} else if (tokenId == TokenId::Field) {
				strList.push_back(field);
				iParam++;
			}
			break;
		}
		case Stat::csh: {
			// executed UNIX command: csh command|-command
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("csh");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Vertex data
		case Stat::v: {
			// geometric vertices: v x y z [w]
			if (tokenId == TokenId::EndOfLine) {
				// complete
				if (iParam < 3) {
					Error::Issue(ErrorType::FormatError,
						"%d: item v should haves three elements at least", tokenizer.GetLineNo());
					return false;
				}
				_vs.push_back(new Vertex4(numTbl[0], numTbl[1], numTbl[2], (iParam < 4)? 1. : numTbl[3]));
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				if (iParam >= 4) {
					Error::Issue(ErrorType::FormatError, "%d: too many elements for item v", tokenizer.GetLineNo());
					return false;
				}
				double num;
				if (!ExtractFloat(field, &num)) {
					SetError_FormatError();
					return false;
				}
				numTbl[iParam++] = num;
			}
			break;
		}
		case Stat::vt: {
			// texture vertices: vt u [v] [w]
			if (tokenId == TokenId::EndOfLine) {
				// complete
				if (iParam < 1) {
					Error::Issue(ErrorType::FormatError, "item vt should haves one element at least");
					return false;
				}
				_vts.push_back(new Vertex3(numTbl[0], (iParam < 2)? 0 : numTbl[1], (iParam < 3)? 0 : numTbl[2]));
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				if (iParam >= 3) {
					Error::Issue(ErrorType::FormatError, "too many elements for item vt");
					return false;
				}
				double num;
				if (!ExtractFloat(field, &num)) {
					SetError_FormatError();
					return false;
				}
				numTbl[iParam++] = num;
			}
			break;
		}
		case Stat::vn: {
			// vertex normals: vn i j k
			if (tokenId == TokenId::EndOfLine) {
				// complete
				if (iParam < 3) {
					Error::Issue(ErrorType::FormatError, "item vn should haves three elements");
					return false;
				}
				_vns.push_back(new Vertex3(numTbl[0], numTbl[1], numTbl[2]));
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				if (iParam >= 3) {
					Error::Issue(ErrorType::FormatError, "too many elements for item vn");
					return false;
				}
				double num;
				if (!ExtractFloat(field, &num)) {
					SetError_FormatError();
					return false;
				}
				numTbl[iParam++] = num;
			}
			break;
		}
		case Stat::vp: {
			// parameter space vertices: vp u v [w]
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Free-form curve/surface attributes
		case Stat::cstype: {
			// curve or surface type: cstype [rat] type
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("cstype");
				return false;
			} else if (tokenId == TokenId::Field) {
				if (::strcmp(field, "rat") == 0) {
				} else if (::strcmp(field, "bmatrix") == 0) {
				} else if (::strcmp(field, "bezier") == 0) {
				} else if (::strcmp(field, "bspline") == 0) {
				} else if (::strcmp(field, "cardinal") == 0) {
				} else if (::strcmp(field, "taylor") == 0) {
				} else {
					Error::Issue(ErrorType::FormatError, "invalid parameter for item cstype");
					return false;
				}
				iParam++;
			}
			break;
		}
		case Stat::deg: {
			// degree: deg degu [degv]
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("deg");
				return false;
			} else if (tokenId == TokenId::Field) {
				if (iParam >= 2) {
					Error::Issue(ErrorType::FormatError, "too many elements for item deg");
					return false;
				}
				double num;
				if (!ExtractFloat(field, &num)) {
					SetError_FormatError();
					return false;
				}
				numTbl[iParam++] = num;
			}
			break;
		}
		case Stat::bmat: {
			// basic matrix: bmat u|v matrix
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("bmat");
				return false;
			} else if (tokenId == TokenId::Field) {
				if (iParam == 0) {
					if (::strcmp(field, "u") == 0) {
					} else if (::strcmp(field, "v") == 0) {
					} else {
						Error::Issue(ErrorType::FormatError, "invalid parameter for item bmat");
						return false;
					}
				} else {
					
				}
				iParam++;
			}
			break;
		}
		case Stat::step: {
			// step size: step stepu [stepv]
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("step");
				return false;
			} else if (tokenId == TokenId::Field) {
				if (iParam >= 2) {
					Error::Issue(ErrorType::FormatError, "too many elements for item step");
					return false;
				}
				double num;
				if (!ExtractFloat(field, &num)) {
					SetError_FormatError();
					return false;
				}
				numTbl[iParam++] = num;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Elements
		case Stat::p: {
			// point: p v1 v2 v3 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				int iV;
				if (!ExtractIndex(field, &iV)) {
					return false;
				} else if (iV <= 0) {
					Error::Issue(ErrorType::FormatError, "invalid index for vertex");
					return false;
				}
				Point* pPoint = _points.back();
				if (!ExtractIndex(field, &iV)) {
					return false;
				} else if (iV <= 0) {
					Error::Issue(ErrorType::FormatError, "invalid index for vertex");
					return false;
				}
				pPoint->AddIndex(iV);
				iParam++;
			}
			break;
		}
		case Stat::l: {
			// line: l v1/vt1 v2/vt2 v3/vt3 ...
			if (tokenId == TokenId::EndOfLine) {
				// complete
				if (iParam < 2) {
					Error::Issue(ErrorType::FormatError, "at least two index-pairs must exist");
					return false;
				}
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				Line* pLine = _lines.back();
				int iV, iVt;
				if (!ExtractIndexPair(field, &iV, &iVt)) {
					return false;
				} else if (iV <= 0) {
					Error::Issue(ErrorType::FormatError, "invalid index for vertex");
					return false;
				}
				pLine->AddIndexPair(iV, iVt);
				iParam++;
			}
			break;
		}
		case Stat::f: {
			// face: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			if (tokenId == TokenId::EndOfLine) {
				// complete
				if (iParam < 3) {
					Error::Issue(ErrorType::FormatError, "at least three index-triplets must exist");
					return false;
				}
				stat = Stat::Keyword;
			} else if (tokenId == TokenId::Field) {
				Face* pFace = _faces.back();
				int iV, iVt, iVn;
				if (!ExtractIndexTriplet(tokenizer, field, &iV, &iVt, &iVn)) {
					return false;
				} else if (iV <= 0) {
					Error::Issue(ErrorType::FormatError, "invalid index for vertex");
					return false;
				}
				pFace->AddIndexTriplet(iV, iVt, iVn);
				iParam++;
			}
			break;
		}
		case Stat::curv: {
			// curve: curv u0 u1 v1 v2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("curv");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::curv2: {
			// 2D curve: curv2 vp1 vp2 vp3 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("curv2");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::surf: {
			// surface: surf s0 s1 t0 t1 v1/vt1/vn1 v2/vt2/vn2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("surf");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Parameter values and knot vectors
		case Stat::parm: {
			// parameter values: parm u|v p1 p2 p3 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("parm");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::trim: {
			// outer trimming loop: trim u0 u1 curv2d u0 u1 curv2d ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("trim");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::hole: {
			// inner trimming loop: u0 u1 curv2d u0 u1 curv2d ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("hole");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::scrv: {
			// special curve: u0 u1 curv2d u0 u1 curv2d ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("scrv");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::sp: {
			// special point: vp1 vp ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("sp");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::end: {
			// end statement: end
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("end");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Connectivity between free-form surfaces
		case Stat::con: {
			// connect: con surf_1 q0_1 q1_1 curv2d_1 surf_2 q0_2 q1_2 curv2d_2
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("con");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Grouping
		case Stat::g: {
			// group name: g group_name1 group_name2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				//SetError_NotImplementedKeyword("g");
				//return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::s: {
			// smoothing group: s group_number
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("s");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::mg: {
			// merging group: mg group_number res
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("mg");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::o: {
			// object name: o object_name
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("o");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Display/render attributes
		case Stat::beval: {
			// bevel interpolation: bevel on|off
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("beval");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::c_interp: {
			// color interpolation: c_interp on|off
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("c_interp");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::d_interp: {
			// dissolve interpolation: d_interp on|off
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("d_interp");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::lod: {
			// level of detail: lod level
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("lod");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::usemap: {
			// map name: usemap map_name|off
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("usemap");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::maplib: {
			// map library: maplib filename1 filename2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("maplib");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::usemtl: {
			// material name: usemtl material_name
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("usemtl");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::mtllib: {
			// material library: mtllib filename1 filename2 ...
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("mtllib");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::shadow_obj: {
			// shadow casting: shadow_obj filename
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("shadow_obj");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::trace_obj: {
			// ray tracing: trace_obj filename
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("trace_obj");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::ctech: {
			// curve approximation technique: ctech technique resolution
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("ctech");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::stech: {
			// surface approximation technique: stech technique resolution
			if (tokenId == TokenId::EndOfLine) {
				stat = Stat::Keyword;
				SetError_NotImplementedKeyword("stech");
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		}
		if (tokenId == TokenId::EndOfFile) break;
	}
	return true;
}

bool Content::ExtractFloat(const char* field, double* pNum)
{
	char* p = nullptr;
	*pNum = ::strtod(field, &p);
	if (*p == '\0') return true;
	Error::Issue(ErrorType::FormatError, "invalid format of float number");
	return false;
}

bool Content::ExtractIndex(const char* field, int* piV)
{
	const char* errMsg = "invalid format of vertex index";
	char* p = nullptr;
	*piV = static_cast<int>(::strtol(field, &p, 10));
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

bool Content::ExtractIndexPair(const char* field, int* piV, int* piVt)
{
	const char* errMsg = "invalid format of vertex index pair";
	*piV = *piVt = 0;
	char* p = const_cast<char*>(field);
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

bool Content::ExtractIndexTriplet(const Tokenizer& tokenizer, const char* field, int* piV, int* piVt, int* piVn)
{
	const char* errMsg = "%d: invalid format of vertex index triplet";
	*piV = *piVt = *piVn = 0;
	char* p = const_cast<char*>(field);
	if (*p == '/') {
		*piV = 0;
		p++;
	} else if (String::IsDigit(*p)) {
		*piV = static_cast<int>(::strtol(p, &p, 10));
		if (*p == '/') p++;
	} else {
		Error::Issue(ErrorType::FormatError, errMsg, tokenizer.GetLineNo());
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
		Error::Issue(ErrorType::FormatError, errMsg, tokenizer.GetLineNo());
		return false;
	}
	if (*p == '\0') {
		return true;
	} else if (*p == '/') {
		p++;
	} else if (String::IsDigit(*p)) {
		*piVn = static_cast<int>(::strtol(p, &p, 10));
	} else {
		Error::Issue(ErrorType::FormatError, errMsg, tokenizer.GetLineNo());
		return false;
	}
	if (*p != '\0') {
		Error::Issue(ErrorType::FormatError, errMsg, tokenizer.GetLineNo());
		return false;
	}
	if (*piV < 0 || *piVt < 0 || *piVn < 0) {
		Error::Issue(ErrorType::FormatError, errMsg, tokenizer.GetLineNo());
	}
	return true;
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
