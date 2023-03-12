//==============================================================================
// VType_Vertex3.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_VERTEX3_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_VERTEX3_H
#include <gurax.h>
#include "Data.h"
#include "Vertex3.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Vertex3
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Vertex3 : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Vertex3 VTYPE_Vertex3;

//------------------------------------------------------------------------------
// Value_Vertex3
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Vertex3 : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Vertex3);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Vertex3");
protected:
	RefPtr<Vertex3> _pVertex3;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Vertex3() = delete;
	explicit Value_Vertex3(Vertex3* pVertex3, VType& vtype = VTYPE_Vertex3) :
		Value_Object(vtype), _pVertex3(pVertex3) {}
	// Copy constructor/operator
	Value_Vertex3(const Value_Vertex3& src) :
		Value_Object(src), _pVertex3(src._pVertex3->Reference()) {}
	Value_Vertex3& operator=(const Value_Vertex3& src) = delete;
	// Move constructor/operator
	Value_Vertex3(Value_Vertex3&& src) noexcept = delete;
	Value_Vertex3& operator=(Value_Vertex3&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Vertex3() = default;
public:
	Vertex3& GetVertex3() { return *_pVertex3; }
	const Vertex3& GetVertex3() const { return *_pVertex3; }
public:
	static Vertex3& GetVertex3(Value& value) {
		return dynamic_cast<Value_Vertex3&>(value).GetVertex3();
	}
	static const Vertex3& GetVertex3(const Value& value) {
		return dynamic_cast<const Value_Vertex3&>(value).GetVertex3();
	}
	static Vertex3* GetEntityPtr(Value& value) { return &GetVertex3(value); }
	static const Vertex3* GetEntityPtr(const Value& value) { return &GetVertex3(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetVertex3().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetVertex3().IsEqualTo(Value_Vertex3::GetVertex3(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetVertex3().IsLessThan(Value_Vertex3::GetVertex3(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
