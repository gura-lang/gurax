//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CONTENT_H
#define GURAX_MODULE_MODEL_OBJ_CONTENT_H
#include <gurax.h>
#include "Face.h"
#include "Line.h"
#include "Point.h"
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
	enum class TokenId { None, EndOfLine, EndOfFile, Field, };
	class Tokenizer {
	public:
		enum class Stat { LineTop, SkipToNextLine, Field, SkipWhite, FileEnd, };
	private:
		Stat _stat;
		size_t _iLine;
		size_t _iChar;
		char _field[128];
		TokenId _tokenIdPending;
	public:
		Tokenizer() : _stat(Stat::LineTop), _iLine(0), _iChar(0), _tokenIdPending(TokenId::None) {}
		TokenId Tokenize(Stream& stream);
		inline const char* GetField() const { return _field; }
		inline size_t GetLineNo() const { return _iLine + 1; }
	};
	enum class Stat {
		Keyword,
		call,
		csh,
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
	Vertex3Owner	_vps;
	Vertex3Owner	_vns;
	Vertex3Owner	_vts;
	PointOwner		_points;
	LineOwner		_lines;
	FaceOwner		_faces;
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
	const Vertex4* GetV(Index iV) const { return (0 < iV && iV < _vs.size() + 1)? _vs[iV - 1] : nullptr; }
	const Vertex3* GetVp(Index iVp) const { return (0 < iVp && iVp < _vps.size() + 1)? _vps[iVp - 1] : nullptr; }
	const Vertex3* GetVn(Index iVn) const { return (0 < iVn && iVn < _vns.size() + 1)? _vns[iVn - 1] : nullptr; }
	const Vertex3* GetVt(Index iVt) const { return (0 < iVt && iVt < _vts.size() + 1)? _vts[iVt - 1] : nullptr; }
	const Face* GetFace(Index iFace) const { return (iFace < _faces.size())? _faces[iFace] : nullptr; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_obj)

#endif