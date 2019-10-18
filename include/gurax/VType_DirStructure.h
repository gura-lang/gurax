//==============================================================================
// VType_DirStructure.h
//==============================================================================
#ifndef GURAX_VTYPE_DIRSTRUCTURE_H
#define GURAX_VTYPE_DIRSTRUCTURE_H
#include "VType_Object.h"
#include "DirStructure.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DirStructure
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_DirStructure : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_DirStructure VTYPE_DirStructure;

//------------------------------------------------------------------------------
// Value_DirStructure
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_DirStructure : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_DirStructure);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_DirStructure");
protected:
	RefPtr<DirStructure> _pDirStructure;
public:
	static VType& vtype;
public:
	// Constructor
	Value_DirStructure() = delete;
	Value_DirStructure(DirStructure* pDirStructure, VType& vtype = VTYPE_DirStructure) :
		Value_Object(vtype), _pDirStructure(pDirStructure) {}
	// Copy constructor/operator
	Value_DirStructure(const Value_DirStructure& src) :
		Value_Object(src), _pDirStructure(src._pDirStructure.Reference()) {}
	Value_DirStructure& operator=(const Value_DirStructure& src) = delete;
	// Move constructor/operator
	Value_DirStructure(Value_DirStructure&& src) = delete;
	Value_DirStructure& operator=(Value_DirStructure&& src) noexcept = delete;
protected:
	// Destructor
	~Value_DirStructure() = default;
public:
	DirStructure& GetDirStructure() { return *_pDirStructure; }
	const DirStructure& GetDirStructure() const { return *_pDirStructure; }
public:
	static DirStructure& GetDirStructure(Value& value) {
		return dynamic_cast<Value_DirStructure&>(value).GetDirStructure();
	}
	static const DirStructure& GetDirStructure(const Value& value) {
		return dynamic_cast<const Value_DirStructure&>(value).GetDirStructure();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDirStructure().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetDirStructure().IsEqualTo(Value_DirStructure::GetDirStructure(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDirStructure().IsLessThan(Value_DirStructure::GetDirStructure(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetDirStructure().ToString(ss);
	}
};

}

#endif
