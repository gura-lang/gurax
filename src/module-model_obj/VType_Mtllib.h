//==============================================================================
// VType_Mtllib.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_MTLLIB_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_MTLLIB_H
#include <gurax.h>
#include "Mtllib.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Mtllib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Mtllib : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Mtllib VTYPE_Mtllib;

//------------------------------------------------------------------------------
// Value_Mtllib
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Mtllib : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Mtllib);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Mtllib");
protected:
	RefPtr<Mtllib> _pMtllib;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Mtllib() = delete;
	explicit Value_Mtllib(Mtllib* pMtllib, VType& vtype = VTYPE_Mtllib) :
		Value_Object(vtype), _pMtllib(pMtllib) {}
	// Copy constructor/operator
	Value_Mtllib(const Value_Mtllib& src) :
		Value_Object(src), _pMtllib(src._pMtllib->Reference()) {}
	Value_Mtllib& operator=(const Value_Mtllib& src) = delete;
	// Move constructor/operator
	Value_Mtllib(Value_Mtllib&& src) noexcept = delete;
	Value_Mtllib& operator=(Value_Mtllib&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Mtllib() = default;
public:
	Mtllib& GetMtllib() { return *_pMtllib; }
	const Mtllib& GetMtllib() const { return *_pMtllib; }
public:
	static Mtllib& GetMtllib(Value& value) {
		return dynamic_cast<Value_Mtllib&>(value).GetMtllib();
	}
	static const Mtllib& GetMtllib(const Value& value) {
		return dynamic_cast<const Value_Mtllib&>(value).GetMtllib();
	}
	static Mtllib* GetEntityPtr(Value& value) { return &GetMtllib(value); }
	static const Mtllib* GetEntityPtr(const Value& value) { return &GetMtllib(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetMtllib().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetMtllib().IsEqualTo(Value_Mtllib::GetMtllib(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetMtllib().IsLessThan(Value_Mtllib::GetMtllib(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
