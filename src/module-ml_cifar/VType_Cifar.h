//==============================================================================
// VType_Cifar.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_VTYPE_CIFAR_H
#define GURAX_MODULE_ML_CIFAR_VTYPE_CIFAR_H
#include <gurax.h>
#include "Cifar.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// VType_Cifar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Cifar : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Cifar VTYPE_Cifar;

//------------------------------------------------------------------------------
// Value_Cifar
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Cifar : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Cifar);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Cifar");
protected:
	RefPtr<Cifar> _pCifar;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Cifar() = delete;
	explicit Value_Cifar(Cifar* pCifar, VType& vtype = VTYPE_Cifar) :
		Value_Object(vtype), _pCifar(pCifar) {}
	// Copy constructor/operator
	Value_Cifar(const Value_Cifar& src) :
		Value_Object(src), _pCifar(src._pCifar->Reference()) {}
	Value_Cifar& operator=(const Value_Cifar& src) = delete;
	// Move constructor/operator
	Value_Cifar(Value_Cifar&& src) noexcept = delete;
	Value_Cifar& operator=(Value_Cifar&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Cifar() = default;
public:
	Cifar& GetCifar() { return *_pCifar; }
	const Cifar& GetCifar() const { return *_pCifar; }
public:
	static Cifar& GetCifar(Value& value) {
		return dynamic_cast<Value_Cifar&>(value).GetCifar();
	}
	static const Cifar& GetCifar(const Value& value) {
		return dynamic_cast<const Value_Cifar&>(value).GetCifar();
	}
	static Cifar* GetEntityPtr(Value& value) { return &GetCifar(value); }
	static const Cifar* GetEntityPtr(const Value& value) { return &GetCifar(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCifar().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCifar().IsEqualTo(Value_Cifar::GetCifar(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCifar().IsLessThan(Value_Cifar::GetCifar(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_cifar)

#endif
