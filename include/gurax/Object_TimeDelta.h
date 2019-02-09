//==============================================================================
// Object_TimeDelta.h
//==============================================================================
#ifndef GURAX_OBJECT_TIMEDELTA_H
#define GURAX_OBJECT_TIMEDELTA_H
#include "Object_Object.h"
#include "TimeDelta.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_TimeDelta
//------------------------------------------------------------------------------
class VTypeT_TimeDelta : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_TimeDelta VType_TimeDelta;

//------------------------------------------------------------------------------
// Object_TimeDelta
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_TimeDelta : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_TimeDelta);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_TimeDelta");
private:
	RefPtr<TimeDelta> _pTimeDelta;
public:
	// Constructor
	explicit Object_TimeDelta(VType& vtype = VType_TimeDelta) :
		Object_TimeDelta(new TimeDelta(), vtype) {}
	explicit Object_TimeDelta(TimeDelta *pTimeDelta, VType& vtype = VType_TimeDelta) :
		Object_Object(vtype), _pTimeDelta(pTimeDelta) {}
	// Copy constructor/operator
	Object_TimeDelta(const Object_TimeDelta& src) :
		Object_Object(src), _pTimeDelta(src._pTimeDelta->Reference()) {}
	Object_TimeDelta& operator=(const Object_TimeDelta& src) = delete;
	// Move constructor/operator
	Object_TimeDelta(Object_TimeDelta&& src) = delete;
	Object_TimeDelta& operator=(Object_TimeDelta&& src) noexcept = delete;
protected:
	// Destructor
	~Object_TimeDelta() = default;
public:
	TimeDelta& GetTimeDelta() { return *_pTimeDelta; }
	const TimeDelta& GetTimeDelta() const { return *_pTimeDelta; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetTimeDelta().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return GetTimeDelta().IsEqualTo(dynamic_cast<const Object_TimeDelta*>(pObject)->GetTimeDelta());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetTimeDelta().IsLessThan(dynamic_cast<const Object_TimeDelta*>(pObject)->GetTimeDelta()) :
			GetVType().IsLessThan(pObject->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetTimeDelta().ToString(ss);
	}
};

}

#endif
