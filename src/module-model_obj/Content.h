//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CONTENT_H
#define GURAX_MODULE_MODEL_OBJ_CONTENT_H
#include <gurax.h>
#include "Tokenizer.h"
#include "Beval.h"
#include "Bmat.h"
#include "CallObj.h"
#include "Connect.h"
#include "Content.h"
#include "Cstype.h"
#include "Ctech.h"
#include "Curv.h"
#include "Curv2.h"
#include "C_interp.h"
#include "Deg.h"
#include "D_interp.h"
#include "Face.h"
#include "GroupName.h"
#include "Hole.h"
#include "Line.h"
#include "Lod.h"
#include "Maplib.h"
#include "MergingGroup.h"
#include "Mtllib.h"
#include "ObjectName.h"
#include "Parm.h"
#include "Point.h"
#include "Scrv.h"
#include "Shadow_obj.h"
#include "SmoothingGroup.h"
#include "Spoint.h"
#include "Stech.h"
#include "Step.h"
#include "Surf.h"
#include "Trace_obj.h"
#include "Trim.h"
#include "Usemap.h"
#include "Usemtl.h"
#include "Vertex3.h"
#include "Vertex4.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Content");
public:
	enum class Stat {
		Keyword,
		call,
		csh,
		Param,
		v,
		vt,
		vn,
		vp,
		cstype,
		deg,
		bmat,
		step,
		p,
		l,
		f,
		curv,
		curv2,
		surf,
		parm,
		trim,
		hole,
		scrv,
		sp,
		end,
		con,
		g,
		s,
		mg,
		o,
		beval,
		c_interp,
		d_interp,
		lod,
		usemap,
		maplib,
		usemtl,
		mtllib,
		shadow_obj,
		trace_obj,
		ctech,
		stech,
	};
private:
	Vertex4Owner	_vs;
	Vertex3Owner	_vts;
	Vertex3Owner	_vns;
	Vertex3Owner	_vps;
	CstypeOwner		_cstypes;
	DegOwner		_degs;
	BmatOwner		_bmats;
	StepOwner		_steps;
	PointOwner		_points;
	LineOwner		_lines;
	FaceOwner		_faces;
	CurvOwner		_curvs;
	Curv2Owner		_curv2s;
	SurfOwner		_surfs;
	ParmOwner		_parms;
	TrimOwner		_trims;
	HoleOwner		_holes;
	ScrvOwner		_scrvs;
	SpointOwner		_spoints;
	ConnectOwner	_connects;
	GroupNameOwner	_groupNames;
	SmoothingGroupOwner	_smoothingGroups;
	MergingGroupOwner	_mergingGroups;
	ObjectNameOwner	_objectNames;
	BevalOwner		_bevals;
	C_interpOwner	_c_interps;
	D_interpOwner	_d_interps;
	LodOwner		_lods;
	UsemapOwner		_usemaps;
	MaplibOwner		_maplibs;
	UsemtlOwner		_usemtls;
	MtllibOwner		_mtllibs;
	Shadow_objOwner	_shadow_objs;
	Trace_objOwner	_trace_objs;
	CtechOwner		_ctechs;
	StechOwner		_stechs;
public:
	// Constructor
	Content() {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) noexcept = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	bool Read(Stream& stream);
	static bool ExtractFloat(const char* field, double* pNum);
	static bool ExtractIndex(const char* field, int* piV);
	static bool ExtractIndexPair(const char* field, int* piV, int* piVt);
	static bool ExtractIndexTriplet(const Tokenizer& tokenizer, const char* field, int* piV, int* piVt, int* piVn);
	const Vertex4* GetV(Index iV) const { return (0 < iV && iV < _vs.size() + 1)? _vs[iV - 1] : nullptr; }
	const Vertex3* GetVp(Index iVp) const { return (0 < iVp && iVp < _vps.size() + 1)? _vps[iVp - 1] : nullptr; }
	const Vertex3* GetVn(Index iVn) const { return (0 < iVn && iVn < _vns.size() + 1)? _vns[iVn - 1] : nullptr; }
	const Vertex3* GetVt(Index iVt) const { return (0 < iVt && iVt < _vts.size() + 1)? _vts[iVt - 1] : nullptr; }
	const PointOwner& GetPoints() const { return _points; }
	const LineOwner& GetLines() const { return _lines; }
	const FaceOwner& GetFaces() const { return _faces; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Iterator_EachPoint
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachPoint : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_EachPoint");
private:
	RefPtr<Content> _pContent;
	size_t _idx;
public:
	Iterator_EachPoint(Content* pContent) : _pContent(pContent), _idx(0) {}
public:
	const PointOwner& GetPoints() const { return _pContent->GetPoints(); }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetPoints().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_EachLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachLine : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_EachLine");
private:
	RefPtr<Content> _pContent;
	size_t _idx;
public:
	Iterator_EachLine(Content* pContent) : _pContent(pContent), _idx(0) {}
public:
	const LineOwner& GetLines() const { return _pContent->GetLines(); }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetLines().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_EachFace
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachFace : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_EachFace");
private:
	RefPtr<Content> _pContent;
	size_t _idx;
public:
	Iterator_EachFace(Content* pContent) : _pContent(pContent), _idx(0) {}
public:
	const FaceOwner& GetFaces() const { return _pContent->GetFaces(); }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetFaces().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
