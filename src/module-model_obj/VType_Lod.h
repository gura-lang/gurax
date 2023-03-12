//==============================================================================
// VType_Lod.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_LOD_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_LOD_H
#include <gurax.h>
#include "Data.h"
#include "Lod.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Lod
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Lod : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Lod VTYPE_Lod;

//------------------------------------------------------------------------------
// Value_Lod
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Lod : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Lod);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Lod");
protected:
	RefPtr<Lod> _pLod;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Lod() = delete;
	explicit Value_Lod(Lod* pLod, VType& vtype = VTYPE_Lod) :
		Value_Object(vtype), _pLod(pLod) {}
	// Copy constructor/operator
	Value_Lod(const Value_Lod& src) :
		Value_Object(src), _pLod(src._pLod->Reference()) {}
	Value_Lod& operator=(const Value_Lod& src) = delete;
	// Move constructor/operator
	Value_Lod(Value_Lod&& src) noexcept = delete;
	Value_Lod& operator=(Value_Lod&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Lod() = default;
public:
	Lod& GetLod() { return *_pLod; }
	const Lod& GetLod() const { return *_pLod; }
public:
	static Lod& GetLod(Value& value) {
		return dynamic_cast<Value_Lod&>(value).GetLod();
	}
	static const Lod& GetLod(const Value& value) {
		return dynamic_cast<const Value_Lod&>(value).GetLod();
	}
	static Lod* GetEntityPtr(Value& value) { return &GetLod(value); }
	static const Lod* GetEntityPtr(const Value& value) { return &GetLod(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetLod().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetLod().IsEqualTo(Value_Lod::GetLod(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetLod().IsLessThan(Value_Lod::GetLod(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
