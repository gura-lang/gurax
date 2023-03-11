//==============================================================================
// VType_Scrv.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_SCRV_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_SCRV_H
#include <gurax.h>
#include "Scrv.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Scrv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Scrv : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Scrv VTYPE_Scrv;

//------------------------------------------------------------------------------
// Value_Scrv
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Scrv : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Scrv);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Scrv");
protected:
	RefPtr<Scrv> _pScrv;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Scrv() = delete;
	explicit Value_Scrv(Scrv* pScrv, VType& vtype = VTYPE_Scrv) :
		Value_Object(vtype), _pScrv(pScrv) {}
	// Copy constructor/operator
	Value_Scrv(const Value_Scrv& src) :
		Value_Object(src), _pScrv(src._pScrv->Reference()) {}
	Value_Scrv& operator=(const Value_Scrv& src) = delete;
	// Move constructor/operator
	Value_Scrv(Value_Scrv&& src) noexcept = delete;
	Value_Scrv& operator=(Value_Scrv&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Scrv() = default;
public:
	Scrv& GetScrv() { return *_pScrv; }
	const Scrv& GetScrv() const { return *_pScrv; }
public:
	static Scrv& GetScrv(Value& value) {
		return dynamic_cast<Value_Scrv&>(value).GetScrv();
	}
	static const Scrv& GetScrv(const Value& value) {
		return dynamic_cast<const Value_Scrv&>(value).GetScrv();
	}
	static Scrv* GetEntityPtr(Value& value) { return &GetScrv(value); }
	static const Scrv* GetEntityPtr(const Value& value) { return &GetScrv(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetScrv().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetScrv().IsEqualTo(Value_Scrv::GetScrv(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetScrv().IsLessThan(Value_Scrv::GetScrv(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
