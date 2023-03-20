//==============================================================================
// VType_Trainer.h
//==============================================================================
#ifndef GURAX_VTYPE_TRAINER_H
#define GURAX_VTYPE_TRAINER_H
#include "VType_Object.h"
#include "Trainer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Trainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Trainer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Trainer VTYPE_Trainer;

//------------------------------------------------------------------------------
// Value_Trainer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Trainer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Trainer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Trainer");
protected:
	RefPtr<Trainer> _pTrainer;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Trainer() = delete;
	explicit Value_Trainer(Trainer* pTrainer, VType& vtype = VTYPE_Trainer) :
		Value_Object(vtype), _pTrainer(pTrainer) {}
	// Copy constructor/operator
	Value_Trainer(const Value_Trainer& src) :
		Value_Object(src), _pTrainer(src._pTrainer->Reference()) {}
	Value_Trainer& operator=(const Value_Trainer& src) = delete;
	// Move constructor/operator
	Value_Trainer(Value_Trainer&& src) noexcept = delete;
	Value_Trainer& operator=(Value_Trainer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Trainer() = default;
public:
	Trainer& GetTrainer() { return *_pTrainer; }
	const Trainer& GetTrainer() const { return *_pTrainer; }
public:
	static Trainer& GetTrainer(Value& value) {
		return dynamic_cast<Value_Trainer&>(value).GetTrainer();
	}
	static const Trainer& GetTrainer(const Value& value) {
		return dynamic_cast<const Value_Trainer&>(value).GetTrainer();
	}
	static Trainer* GetEntityPtr(Value& value) { return &GetTrainer(value); }
	static const Trainer* GetEntityPtr(const Value& value) { return &GetTrainer(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTrainer().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetTrainer().IsEqualTo(Value_Trainer::GetTrainer(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetTrainer().IsLessThan(Value_Trainer::GetTrainer(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
