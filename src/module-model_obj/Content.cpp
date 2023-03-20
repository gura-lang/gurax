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
				//::printf("%zu: %s\n", tokenizer.GetLineNo(), field);
				if (::strcmp(field, "call") == 0) {
					stat = Stat::call;
				} else if (::strcmp(field, "csh") == 0) {
					stat = Stat::csh;
				// Vertex data
				} else if (::strcmp(field, "v") == 0) {
					// geometric vertices: v x y z [w]
					_vs.push_back(new Vertex4(0, 0, 0, 1));
					pData = _vs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "vt") == 0) {
					// texture vertices: vt u [v] [w]
					_vts.push_back(new Vertex3(0, 0, 0));
					pData = _vts.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "vn") == 0) {
					// vertex normals: vn i j k
					_vns.push_back(new Vertex3(0, 0, 0));
					pData = _vns.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "vp") == 0) {
					// parameter space vertices: vp u v [w]
					_vps.push_back(new Vertex3(0, 0, 0));
					pData = _vps.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "cstype") == 0) {
					//
					_cstypes.push_back(new Cstype());
					pData = _cstypes.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "deg") == 0) {
					// degree: deg degu [degv]
					_degs.push_back(new Deg());
					pData = _degs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "bmat") == 0) {
					// basic matrix: bmat u|v matrix
					_bmats.push_back(new Bmat());
					pData = _bmats.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "step") == 0) {
					// step size: step stepu [stepv]
					_steps.push_back(new Step());
					pData = _steps.back();
					stat = Stat::Param;
				// Elements
				} else if (::strcmp(field, "p") == 0) {
					// point: p v1 v2 v3 ...
					_points.push_back(new Point());
					pData = _points.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "l") == 0) {
					// line: l v1/vt1 v2/vt2 v3/vt3 ...
					_lines.push_back(new Line());
					pData = _lines.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "f") == 0) {
					// face: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
					_faces.push_back(new Face());
					pData = _faces.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "curv") == 0) {
					// curve: curv u0 u1 v1 v2 ...
					_curvs.push_back(new Curv());
					pData = _curvs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "curv2") == 0) {
					// 2D curve: curv2 vp1 vp2 vp3 ...
					_curv2s.push_back(new Curv2());
					pData = _curv2s.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "surf") == 0) {
					// surface: surf s0 s1 t0 t1 v1/vt1/vn1 v2/vt2/vn2 ...
					_surfs.push_back(new Surf());
					pData = _surfs.back();
					stat = Stat::Param;
				// Free-form curve/surface body statements
				} else if (::strcmp(field, "parm") == 0) {
					// parameter values: parm u|v p1 p2 p3 ...
					_parms.push_back(new Parm());
					pData = _parms.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "trim") == 0) {
					// outer trimming loop: trim u0 u1 curv2d u0 u1 curv2d ...
					_trims.push_back(new Trim());
					pData = _trims.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "hole") == 0) {
					// inner trimming loop: hole u0 u1 curv2d u0 u1 curv2d ...
					_holes.push_back(new Hole());
					pData = _holes.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "scrv") == 0) {
					// special curve: scrv u0 u1 curv2d u0 u1 curv2d ...
					_scrvs.push_back(new Scrv());
					pData = _scrvs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "sp") == 0) {
					// special point: sp vp1 vp ...
					_spoints.push_back(new Spoint());
					pData = _spoints.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "end") == 0) {
					// end statement: end
					//_ends.push_back(new End());
					//pData = _ends.back();
					stat = Stat::Param;
				// Connectivity between free-form surfaces
				} else if (::strcmp(field, "con") == 0) {
					// connect: con surf_1 q0_1 q1_1 curv2d_1 surf_2 q0_2 q1_2 curv2d_2
					_connects.push_back(new Connect());
					pData = _connects.back();
					stat = Stat::Param;
				// Grouping
				} else if (::strcmp(field, "g") == 0) {
					// group name: g group_name1 group_name2 ...
					_groupNames.push_back(new GroupName());
					pData = _groupNames.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "s") == 0) {
					// smoothing group: s group_number
					_smoothingGroups.push_back(new SmoothingGroup());
					pData = _smoothingGroups.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "mg") == 0) {
					// merging group: mg group_number res
					_mergingGroups.push_back(new MergingGroup());
					pData = _mergingGroups.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "o") == 0) {
					// object name: o object_name
					_objectNames.push_back(new ObjectName());
					pData = _objectNames.back();
					stat = Stat::Param;
				// Display/render attributes
				} else if (::strcmp(field, "bevel") == 0) {
					// bevel interpolation: bevel on|off
					_bevels.push_back(new Bevel());
					pData = _bevels.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "c_interp") == 0) {
					// color interpolation: c_interp on|off
					_c_interps.push_back(new C_interp());
					pData = _c_interps.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "d_interp") == 0) {
					// dissolve interpolation: d_interp on|off
					_d_interps.push_back(new D_interp());
					pData = _d_interps.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "lod") == 0) {
					// level of detail: lod level
					_lods.push_back(new Lod());
					pData = _lods.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "usemap") == 0) {
					// map name: usemap map_name|off
					_usemaps.push_back(new Usemap());
					pData = _usemaps.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "maplib") == 0) {
					// map library: maplib filename1 filename2 ...
					_maplibs.push_back(new Maplib());
					pData = _maplibs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "usemtl") == 0) {
					// material name: usemtl material_name
					_usemtls.push_back(new Usemtl());
					pData = _usemtls.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "mtllib") == 0) {
					// material library: mtllib filename1 filename2 ...
					_mtllibs.push_back(new Mtllib());
					pData = _mtllibs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "shadow_obj") == 0) {
					// shadow casting: shadow_obj filename
					_shadow_objs.push_back(new Shadow_obj());
					pData = _shadow_objs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "trace_obj") == 0) {
					// ray tracing: trace_obj filename
					_trace_objs.push_back(new Trace_obj());
					pData = _trace_objs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "ctech") == 0) {
					// curve approximation technique: ctech technique resolution
					_ctechs.push_back(new Ctech());
					pData = _ctechs.back();
					stat = Stat::Param;
				} else if (::strcmp(field, "stech") == 0) {
					// surface approximation technique: stech technique resolution
					_stechs.push_back(new Stech());
					pData = _stechs.back();
					stat = Stat::Param;
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
		}
		if (tokenId == TokenId::EndOfFile) break;
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
