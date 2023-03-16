//==============================================================================
// VType_Bevel.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_BEVEL_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_BEVEL_H
#include <gurax.h>
#include "Data.h"
#include "Bevel.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Bevel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Bevel : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Bevel VTYPE_Bevel;

//------------------------------------------------------------------------------
// Value_Bevel
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Bevel : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Bevel);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Bevel");
protected:
	RefPtr<Bevel> _pBevel;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Bevel() = delete;
	explicit Value_Bevel(Bevel* pBevel, VType& vtype = VTYPE_Bevel) :
		Value_Object(vtype), _pBevel(pBevel) {}
	// Copy constructor/operator
	Value_Bevel(const Value_Bevel& src) :
		Value_Object(src), _pBevel(src._pBevel->Reference()) {}
	Value_Bevel& operator=(const Value_Bevel& src) = delete;
	// Move constructor/operator
	Value_Bevel(Value_Bevel&& src) noexcept = delete;
	Value_Bevel& operator=(Value_Bevel&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Bevel() = default;
public:
	Bevel& GetBevel() { return *_pBevel; }
	const Bevel& GetBevel() const { return *_pBevel; }
public:
	static Bevel& GetBevel(Value& value) {
		return dynamic_cast<Value_Bevel&>(value).GetBevel();
	}
	static const Bevel& GetBevel(const Value& value) {
		return dynamic_cast<const Value_Bevel&>(value).GetBevel();
	}
	static Bevel* GetEntityPtr(Value& value) { return &GetBevel(value); }
	static const Bevel* GetEntityPtr(const Value& value) { return &GetBevel(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetBevel().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetBevel().IsEqualTo(Value_Bevel::GetBevel(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetBevel().IsLessThan(Value_Bevel::GetBevel(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
