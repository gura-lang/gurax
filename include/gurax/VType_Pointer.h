//==============================================================================
// VType_Pointer.h
//==============================================================================
#ifndef GURAX_VTYPE_POINTER_H
#define GURAX_VTYPE_POINTER_H
#include "VType_Object.h"
#include "Pointer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Pointer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Pointer VTYPE_Pointer;

//------------------------------------------------------------------------------
// Value_Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Pointer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Pointer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Pointer");
protected:
	RefPtr<Pointer> _pPointer;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Pointer() = delete;
	explicit Value_Pointer(Pointer* pPointer, VType& vtype = VTYPE_Pointer) :
		Value_Object(vtype), _pPointer(pPointer) {}
	// Copy constructor/operator
	Value_Pointer(const Value_Pointer& src) :
		Value_Object(src), _pPointer(src._pPointer->Reference()) {}
	Value_Pointer& operator=(const Value_Pointer& src) = delete;
	// Move constructor/operator
	Value_Pointer(Value_Pointer&& src) = delete;
	Value_Pointer& operator=(Value_Pointer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Pointer() = default;
public:
	Pointer& GetPointer() { return *_pPointer; }
	const Pointer& GetPointer() const { return *_pPointer; }
public:
	static Pointer& GetPointer(Value& value) {
		return dynamic_cast<Value_Pointer&>(value).GetPointer();
	}
	static const Pointer& GetPointer(const Value& value) {
		return dynamic_cast<const Value_Pointer&>(value).GetPointer();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPointer().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetPointer().IsEqualTo(Value_Pointer::GetPointer(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetPointer().IsLessThan(Value_Pointer::GetPointer(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringFormatter(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
