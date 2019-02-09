//==============================================================================
// Value_List.h
//==============================================================================
#ifndef GURAX_OBJECT_LIST_H
#define GURAX_OBJECT_LIST_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_List
//------------------------------------------------------------------------------
class VType_List : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_List VTYPE_List;

//------------------------------------------------------------------------------
// Value_List
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_List : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_List);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_List");
private:
	RefPtr<ObjectTypedOwner> _pValueTypedOwner;
public:
	// Constructor
	Value_List(VType& vtype = VTYPE_List) :
		Value_List(new ObjectTypedOwner(), vtype) {}
	explicit Value_List(ObjectTypedOwner* pValueTypedOwner, VType& vtype = VTYPE_List) :
		Value_Object(vtype), _pValueTypedOwner(pValueTypedOwner) {}
	// Copy constructor/operator
	Value_List(const Value_List& src) :
		Value_Object(src), _pValueTypedOwner(src._pValueTypedOwner->Reference()) {}
	Value_List& operator=(const Value_List& src) = delete;
	// Move constructor/operator
	Value_List(Value_List&& src) = delete;
	Value_List& operator=(Value_List&& src) noexcept = delete;
protected:
	// Destructor
	~Value_List() = default;
public:
	ObjectTypedOwner& GetObjectTypedOwner() { return *_pValueTypedOwner; }
	const ObjectTypedOwner& GetObjectTypedOwner() const { return *_pValueTypedOwner; }
	const ObjectOwner& GetObjectOwner() const { return _pValueTypedOwner->GetObjectOwner(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Value_List(*this); }
	virtual size_t DoCalcHash() const override {
		return GetObjectOwner().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetObjectOwner().IsEqualTo(dynamic_cast<const Value_List*>(pValue)->GetObjectOwner());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetObjectOwner().IsLessThan(dynamic_cast<const Value_List*>(pValue)->GetObjectOwner()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectOwner().ToString(ss);
	}
};

}

#endif
