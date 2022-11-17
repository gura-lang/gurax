//==============================================================================
// VType_Semaphore.h
//==============================================================================
#ifndef GURAX_VTYPE_SEMAPHORE_H
#define GURAX_VTYPE_SEMAPHORE_H
#include "VType_Object.h"
#include "OAL.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Semaphore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Semaphore : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Semaphore VTYPE_Semaphore;

//------------------------------------------------------------------------------
// Value_Semaphore
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Semaphore : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Semaphore);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Semaphore");
protected:
	RefPtr<OAL::Semaphore> _pSemaphore;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Semaphore() = delete;
	explicit Value_Semaphore(OAL::Semaphore* pSemaphore, VType& vtype = VTYPE_Semaphore) :
		Value_Object(vtype), _pSemaphore(pSemaphore) {}
	// Copy constructor/operator
	Value_Semaphore(const Value_Semaphore& src) :
		Value_Object(src), _pSemaphore(src._pSemaphore->Reference()) {}
	Value_Semaphore& operator=(const Value_Semaphore& src) = delete;
	// Move constructor/operator
	Value_Semaphore(Value_Semaphore&& src) noexcept = delete;
	Value_Semaphore& operator=(Value_Semaphore&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Semaphore() = default;
public:
	OAL::Semaphore& GetSemaphore() { return *_pSemaphore; }
	const OAL::Semaphore& GetSemaphore() const { return *_pSemaphore; }
public:
	static OAL::Semaphore& GetSemaphore(Value& value) {
		return dynamic_cast<Value_Semaphore&>(value).GetSemaphore();
	}
	static const OAL::Semaphore& GetSemaphore(const Value& value) {
		return dynamic_cast<const Value_Semaphore&>(value).GetSemaphore();
	}
	static OAL::Semaphore* GetEntityPtr(Value& value) { return &GetSemaphore(value); }
	static const OAL::Semaphore* GetEntityPtr(const Value& value) { return &GetSemaphore(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetSemaphore().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetSemaphore().IsEqualTo(Value_Semaphore::GetSemaphore(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetSemaphore().IsLessThan(Value_Semaphore::GetSemaphore(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
