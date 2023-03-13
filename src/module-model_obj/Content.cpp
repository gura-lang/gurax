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
	Data* pData = nullptr;
	for (;;) {
		TokenId tokenId = tokenizer.Tokenize(stream);
		const char* field = tokenizer.GetField();
		switch (stat) {
		case Stat::Keyword: {
			if (tokenId == TokenId::Field) {
				iParam = 0;
				// General statement
				if (::strcmp(field, "call") == 0) {
					stat = Stat::call;
				} else if (::strcmp(field, "csh") == 0) {
					stat = Stat::csh;
				// Vertex data
				} else if (::strcmp(field, "v") == 0) {
					// geometric vertices: v x y z [w]
					stat = Stat::v;
				} else if (::strcmp(field, "vt") == 0) {
					// texture vertices: vt u [v] [w]
					_vs.push_back(new Vertex4(0, 0, 0, 1));
					stat = Stat::Param;
				} else if (::strcmp(field, "vn") == 0) {
					// vertex normals: vn i j k
					stat = Stat::vn;
				} else if (::strcmp(field, "vp") == 0) {
					// parameter space vertices: vp u v [w]
					stat = Stat::vp;
				} else if (::strcmp(field, "cstype") == 0) {
					stat = Stat::cstype;
				} else if (::strcmp(field, "deg") == 0) {
					// degree: deg degu [degv]
					stat = Stat::deg;
				} else if (::strcmp(field, "bmat") == 0) {
					// basic matrix: bmat u|v matrix
					stat = Stat::bmat;
				} else if (::strcmp(field, "step") == 0) {
					// step size: step stepu [stepv]
					stat = Stat::step;
				// Elements
				} else if (::strcmp(field, "p") == 0) {
					// point: p v1 v2 v3 ...
					_points.push_back(new Point());
					stat = Stat::p;
				} else if (::strcmp(field, "l") == 0) {
					// line: l v1/vt1 v2/vt2 v3/vt3 ...
					_lines.push_back(new Line());
					stat = Stat::l;
				} else if (::strcmp(field, "f") == 0) {
					// face: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
					_faces.push_back(new Face());
					stat = Stat::f;
				} else if (::strcmp(field, "curv") == 0) {
					// curve: curv u0 u1 v1 v2 ...
					stat = Stat::curv;
				} else if (::strcmp(field, "curv2") == 0) {
					// 2D curve: curv2 vp1 vp2 vp3 ...
					stat = Stat::curv2;
				} else if (::strcmp(field, "surf") == 0) {
					// surface: surf s0 s1 t0 t1 v1/vt1/vn1 v2/vt2/vn2 ...
					stat = Stat::surf;
				// Free-form curve/surface body statements
				} else if (::strcmp(field, "parm") == 0) {
					// parameter values: parm u|v p1 p2 p3 ...
					stat = Stat::parm;
				} else if (::strcmp(field, "trim") == 0) {
					// outer trimming loop: trim u0 u1 curv2d u0 u1 curv2d ...
					stat = Stat::trim;
				} else if (::strcmp(field, "hole") == 0) {
					// inner trimming loop: hole u0 u1 curv2d u0 u1 curv2d ...
					stat = Stat::hole;
				} else if (::strcmp(field, "scrv") == 0) {
					// special curve: scrv u0 u1 curv2d u0 u1 curv2d ...
					stat = Stat::scrv;
				} else if (::strcmp(field, "sp") == 0) {
					// special point: sp vp1 vp ...
					stat = Stat::sp;
				} else if (::strcmp(field, "end") == 0) {
					// end statement: end
					stat = Stat::end;
				// Connectivity between free-form surfaces
				} else if (::strcmp(field, "con") == 0) {
					// connect: con surf_1 q0_1 q1_1 curv2d_1 surf_2 q0_2 q1_2 curv2d_2
					stat = Stat::con;
				// Grouping
				} else if (::strcmp(field, "g") == 0) {
					// group name: g group_name1 group_name2 ...
					stat = Stat::g;
				} else if (::strcmp(field, "s") == 0) {
					// smoothing group: s group_number
					stat = Stat::s;
				} else if (::strcmp(field, "mg") == 0) {
					// merging group: mg group_number res
					stat = Stat::mg;
				} else if (::strcmp(field, "o") == 0) {
					// object name: o object_name
					stat = Stat::o;
				// Display/render attributes
				} else if (::strcmp(field, "bevel") == 0) {
					// bevel interpolation: bevel on|off
					stat = Stat::beval;
				} else if (::strcmp(field, "c_interp") == 0) {
					// color interpolation: c_interp on|off
					stat = Stat::c_interp;
				} else if (::strcmp(field, "d_interp") == 0) {
					// dissolve interpolation: d_interp on|off
					stat = Stat::d_interp;
				} else if (::strcmp(field, "lod") == 0) {
					// level of detail: lod level
					stat = Stat::lod;
				} else if (::strcmp(field, "usemap") == 0) {
					// map name: usemap map_name|off
					stat = Stat::usemap;
				} else if (::strcmp(field, "maplib") == 0) {
					// map library: maplib filename1 filename2 ...
					stat = Stat::maplib;
				} else if (::strcmp(field, "usemtl") == 0) {
					// material name: usemtl material_name
					stat = Stat::usemtl;
				} else if (::strcmp(field, "mtllib") == 0) {
					// material library: mtllib filename1 filename2 ...
					stat = Stat::mtllib;
				} else if (::strcmp(field, "shadow_obj") == 0) {
					// shadow casting: shadow_obj filename
					stat = Stat::shadow_obj;
				} else if (::strcmp(field, "trace_obj") == 0) {
					// ray tracing: trace_obj filename
					stat = Stat::trace_obj;
				} else if (::strcmp(field, "ctech") == 0) {
					// curve approximation technique: ctech technique resolution
					stat = Stat::ctech;
				} else if (::strcmp(field, "stech") == 0) {
					// surface approximation technique: stech technique resolution
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
		// Param
		case Stat::Param: {
			if (tokenId == TokenId::Field) {
				if (!pData->FeedField(tokenizer, iParam)) return false;
				iParam++;
			} else if (tokenId == TokenId::EndOfLine) {
				// complete
				if (!pData->FinishField(tokenizer, iParam)) return false;
				stat = Stat::Keyword;
			}
			break;
		}
		//----------------------------------------------------------------------
		// Vertex data
		case Stat::v: {
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
			if (tokenId == TokenId::EndOfLine) {
				
				
				stat = Stat::Keyword;
				return false;
			} else if (tokenId == TokenId::Field) {
				iParam++;
			}
			break;
		}
		case Stat::shadow_obj: {
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
	return String().Format("model.obj.Content:%zupoints:%zulines:%zufaces", _points.size(), _lines.size(), _faces.size());
}

//------------------------------------------------------------------------------
// Iterator_EachPoint
//------------------------------------------------------------------------------
Value* Iterator_EachPoint::DoNextValue()
{
	if (_idx >= GetPoints().size()) return nullptr;
	return new Value_Point(_pContent->Reference(), _pContent->GetPoints()[_idx++]->Reference());
}

String Iterator_EachPoint::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.EachPoint");
}

//------------------------------------------------------------------------------
// Iterator_EachLine
//------------------------------------------------------------------------------
Value* Iterator_EachLine::DoNextValue()
{
	if (_idx >= GetLines().size()) return nullptr;
	return new Value_Line(_pContent->Reference(), _pContent->GetLines()[_idx++]->Reference());
}

String Iterator_EachLine::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.EachLine");
}

//------------------------------------------------------------------------------
// Iterator_EachFace
//------------------------------------------------------------------------------
Value* Iterator_EachFace::DoNextValue()
{
	if (_idx >= GetFaces().size()) return nullptr;
	return new Value_Face(_pContent->Reference(), _pContent->GetFaces()[_idx++]->Reference());
}

String Iterator_EachFace::ToString(const StringStyle& ss) const
{
	return String().Format("model.obj.EachFace");
}

Gurax_EndModuleScope(model_obj)
