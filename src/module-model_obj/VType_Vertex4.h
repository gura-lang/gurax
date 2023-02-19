//==============================================================================
// VType_Vertex4.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_VERTEX4_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_VERTEX4_H
#include <gurax.h>
#include "Vertex4.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Vertex4
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Vertex4 : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Vertex4 VTYPE_Vertex4;

//------------------------------------------------------------------------------
// Value_Vertex4
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Vertex4 : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Vertex4);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Vertex4");
protected:
	RefPtr<Vertex4> _pVertex4;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Vertex4() = delete;
	explicit Value_Vertex4(Vertex4* pVertex4, VType& vtype = VTYPE_Vertex4) :
		Value_Object(vtype), _pVertex4(pVertex4) {}
	// Copy constructor/operator
	Value_Vertex4(const Value_Vertex4& src) :
		Value_Object(src), _pVertex4(src._pVertex4->Reference()) {}
	Value_Vertex4& operator=(const Value_Vertex4& src) = delete;
	// Move constructor/operator
	Value_Vertex4(Value_Vertex4&& src) noexcept = delete;
	Value_Vertex4& operator=(Value_Vertex4&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Vertex4() = default;
public:
	Vertex4& GetVertex4() { return *_pVertex4; }
	const Vertex4& GetVertex4() const { return *_pVertex4; }
public:
	static Vertex4& GetVertex4(Value& value) {
		return dynamic_cast<Value_Vertex4&>(value).GetVertex4();
	}
	static const Vertex4& GetVertex4(const Value& value) {
		return dynamic_cast<const Value_Vertex4&>(value).GetVertex4();
	}
	static Vertex4* GetEntityPtr(Value& value) { return &GetVertex4(value); }
	static const Vertex4* GetEntityPtr(const Value& value) { return &GetVertex4(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetVertex4().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetVertex4().IsEqualTo(Value_Vertex4::GetVertex4(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetVertex4().IsLessThan(Value_Vertex4::GetVertex4(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
