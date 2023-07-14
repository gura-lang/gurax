//==============================================================================
// VType_LabelSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_VTYPE_LABELSET_H
#define GURAX_MODULE_ML_CIFAR_VTYPE_LABELSET_H
#include <gurax.h>
#include "LabelSet.h"

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// VType_LabelSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_LabelSet : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_LabelSet VTYPE_LabelSet;

//------------------------------------------------------------------------------
// Value_LabelSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_LabelSet : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_LabelSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_LabelSet");
protected:
	RefPtr<LabelSet> _pLabelSet;
public:
	static VType& vtype;
public:
	// Constructor
	Value_LabelSet() = delete;
	explicit Value_LabelSet(LabelSet* pLabelSet, VType& vtype = VTYPE_LabelSet) :
		Value_Object(vtype), _pLabelSet(pLabelSet) {}
	// Copy constructor/operator
	Value_LabelSet(const Value_LabelSet& src) :
		Value_Object(src), _pLabelSet(src._pLabelSet->Reference()) {}
	Value_LabelSet& operator=(const Value_LabelSet& src) = delete;
	// Move constructor/operator
	Value_LabelSet(Value_LabelSet&& src) noexcept = delete;
	Value_LabelSet& operator=(Value_LabelSet&& src) noexcept = delete;
protected:
	// Destructor
	~Value_LabelSet() = default;
public:
	LabelSet& GetLabelSet() { return *_pLabelSet; }
	const LabelSet& GetLabelSet() const { return *_pLabelSet; }
public:
	static LabelSet& GetLabelSet(Value& value) {
		return dynamic_cast<Value_LabelSet&>(value).GetLabelSet();
	}
	static const LabelSet& GetLabelSet(const Value& value) {
		return dynamic_cast<const Value_LabelSet&>(value).GetLabelSet();
	}
	static LabelSet* GetEntityPtr(Value& value) { return &GetLabelSet(value); }
	static const LabelSet* GetEntityPtr(const Value& value) { return &GetLabelSet(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetLabelSet().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetLabelSet().IsEqualTo(Value_LabelSet::GetLabelSet(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetLabelSet().IsLessThan(Value_LabelSet::GetLabelSet(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(ml_cifar)

#endif
