//==============================================================================
// VType_Csh.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_VTYPE_CSH_H
#define GURAX_MODULE_MODEL_OBJ_VTYPE_CSH_H
#include <gurax.h>
#include "Csh.h"

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// VType_Csh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Csh : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Csh VTYPE_Csh;

//------------------------------------------------------------------------------
// Value_Csh
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Csh : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Csh);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Csh");
protected:
	RefPtr<Csh> _pCsh;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Csh() = delete;
	explicit Value_Csh(Csh* pCsh, VType& vtype = VTYPE_Csh) :
		Value_Object(vtype), _pCsh(pCsh) {}
	// Copy constructor/operator
	Value_Csh(const Value_Csh& src) :
		Value_Object(src), _pCsh(src._pCsh->Reference()) {}
	Value_Csh& operator=(const Value_Csh& src) = delete;
	// Move constructor/operator
	Value_Csh(Value_Csh&& src) noexcept = delete;
	Value_Csh& operator=(Value_Csh&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Csh() = default;
public:
	Csh& GetCsh() { return *_pCsh; }
	const Csh& GetCsh() const { return *_pCsh; }
public:
	static Csh& GetCsh(Value& value) {
		return dynamic_cast<Value_Csh&>(value).GetCsh();
	}
	static const Csh& GetCsh(const Value& value) {
		return dynamic_cast<const Value_Csh&>(value).GetCsh();
	}
	static Csh* GetEntityPtr(Value& value) { return &GetCsh(value); }
	static const Csh* GetEntityPtr(const Value& value) { return &GetCsh(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCsh().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCsh().IsEqualTo(Value_Csh::GetCsh(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCsh().IsLessThan(Value_Csh::GetCsh(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_obj)

#endif
