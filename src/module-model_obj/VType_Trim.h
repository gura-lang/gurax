//==============================================================================
// VType_Trim.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_TRIM_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_TRIM_H
#include <gurax.h>
#include "Data.h"
#include "Trim.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Trim
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Trim : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Trim VTYPE_Trim;

//------------------------------------------------------------------------------
// Value_Trim
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Trim : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Trim);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Trim");
protected:
	RefPtr<Trim> _pTrim;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Trim() = delete;
	explicit Value_Trim(Trim* pTrim, VType& vtype = VTYPE_Trim) :
		Value_Object(vtype), _pTrim(pTrim) {}
	// Copy constructor/operator
	Value_Trim(const Value_Trim& src) :
		Value_Object(src), _pTrim(src._pTrim->Reference()) {}
	Value_Trim& operator=(const Value_Trim& src) = delete;
	// Move constructor/operator
	Value_Trim(Value_Trim&& src) noexcept = delete;
	Value_Trim& operator=(Value_Trim&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Trim() = default;
public:
	Trim& GetTrim() { return *_pTrim; }
	const Trim& GetTrim() const { return *_pTrim; }
public:
	static Trim& GetTrim(Value& value) {
		return dynamic_cast<Value_Trim&>(value).GetTrim();
	}
	static const Trim& GetTrim(const Value& value) {
		return dynamic_cast<const Value_Trim&>(value).GetTrim();
	}
	static Trim* GetEntityPtr(Value& value) { return &GetTrim(value); }
	static const Trim* GetEntityPtr(const Value& value) { return &GetTrim(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTrim().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTrim().IsEqualTo(Value_Trim::GetTrim(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTrim().IsLessThan(Value_Trim::GetTrim(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
