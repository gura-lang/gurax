//==============================================================================
// VType_PathMgr.h
//==============================================================================
#ifndef GURAX_VTYPE_PATHMGR_H
#define GURAX_VTYPE_PATHMGR_H
#include "VType_Object.h"
#include "PathMgr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PathMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_PathMgr : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_PathMgr VTYPE_PathMgr;

//------------------------------------------------------------------------------
// Value_PathMgr
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PathMgr : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PathMgr);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PathMgr");
protected:
	RefPtr<PathMgr> _pPathMgr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_PathMgr() = delete;
	Value_PathMgr(PathMgr* pPathMgr, VType& vtype = VTYPE_PathMgr) :
		Value_Object(vtype), _pPathMgr(pPathMgr) {}
	// Copy constructor/operator
	Value_PathMgr(const Value_PathMgr& src) :
		Value_Object(src), _pPathMgr(src._pPathMgr->Reference()) {}
	Value_PathMgr& operator=(const Value_PathMgr& src) = delete;
	// Move constructor/operator
	Value_PathMgr(Value_PathMgr&& src) = delete;
	Value_PathMgr& operator=(Value_PathMgr&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PathMgr() = default;
public:
	PathMgr& GetPathMgr() { return *_pPathMgr; }
	const PathMgr& GetPathMgr() const { return *_pPathMgr; }
public:
	static PathMgr& GetPathMgr(Value& value) {
		return dynamic_cast<Value_PathMgr&>(value).GetPathMgr();
	}
	static const PathMgr& GetPathMgr(const Value& value) {
		return dynamic_cast<const Value_PathMgr&>(value).GetPathMgr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPathMgr().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPathMgr().IsEqualTo(Value_PathMgr::GetPathMgr(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPathMgr().IsLessThan(Value_PathMgr::GetPathMgr(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
