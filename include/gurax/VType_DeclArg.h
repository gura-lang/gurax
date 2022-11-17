//==============================================================================
// VType_DeclArg.h
//==============================================================================
#ifndef GURAX_VTYPE_DECLARG_H
#define GURAX_VTYPE_DECLARG_H
#include "VType_Object.h"
#include "DeclArg.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_DeclArg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_DeclArg : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_DeclArg VTYPE_DeclArg;

//------------------------------------------------------------------------------
// Value_DeclArg
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_DeclArg : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_DeclArg);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_DeclArg");
protected:
	RefPtr<DeclArg> _pDeclArg;
public:
	static VType& vtype;
public:
	// Constructor
	Value_DeclArg() = delete;
	explicit Value_DeclArg(DeclArg* pDeclArg, VType& vtype = VTYPE_DeclArg) :
		Value_Object(vtype), _pDeclArg(pDeclArg) {}
	// Copy constructor/operator
	Value_DeclArg(const Value_DeclArg& src) :
		Value_Object(src), _pDeclArg(src._pDeclArg->Reference()) {}
	Value_DeclArg& operator=(const Value_DeclArg& src) = delete;
	// Move constructor/operator
	Value_DeclArg(Value_DeclArg&& src) noexcept = delete;
	Value_DeclArg& operator=(Value_DeclArg&& src) noexcept = delete;
protected:
	// Destructor
	~Value_DeclArg() = default;
public:
	DeclArg& GetDeclArg() { return *_pDeclArg; }
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
public:
	static DeclArg& GetDeclArg(Value& value) {
		return dynamic_cast<Value_DeclArg&>(value).GetDeclArg();
	}
	static const DeclArg& GetDeclArg(const Value& value) {
		return dynamic_cast<const Value_DeclArg&>(value).GetDeclArg();
	}
	static DeclArg* GetEntityPtr(Value& value) { return &GetDeclArg(value); }
	static const DeclArg* GetEntityPtr(const Value& value) { return &GetDeclArg(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDeclArg().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetDeclArg().IsEqualTo(Value_DeclArg::GetDeclArg(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetDeclArg().IsLessThan(Value_DeclArg::GetDeclArg(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
