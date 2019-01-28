//==============================================================================
// Object_timedelta.h
//==============================================================================
#ifndef GURAX_OBJECT_TIMEDELTA_H
#define GURAX_OBJECT_TIMEDELTA_H
#include "Object.h"
#include "TimeDelta.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_timedelta
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_timedelta : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_timedelta);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_timedelta");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<TimeDelta> _pTimeDelta;
public:
	// Constructor
	Object_timedelta() = delete;
	explicit Object_timedelta(TimeDelta *pTimeDelta) : Object(klass), _pTimeDelta(pTimeDelta) {}
	// Copy constructor/operator
	Object_timedelta(const Object_timedelta& src) : Object(klass), _pTimeDelta(src._pTimeDelta->Reference()) {}
	Object_timedelta& operator=(const Object_timedelta& src) { _pTimeDelta.reset(src._pTimeDelta->Reference()); return *this; }
	// Move constructor/operator
	Object_timedelta(Object_timedelta&& src) : Object(klass), _pTimeDelta(src._pTimeDelta.release()) {}
	Object_timedelta& operator=(Object_timedelta&& src) noexcept { _pTimeDelta.reset(src._pTimeDelta.release()); return *this; }
protected:
	// Destructor
	~Object_timedelta() = default;
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
		return GetTimeDelta().IsEqualTo(dynamic_cast<const Object_timedelta*>(pObject)->GetTimeDelta());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetTimeDelta().IsLessThan(dynamic_cast<const Object_timedelta*>(pObject)->GetTimeDelta()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetTimeDelta().ToString(ss);
	}
};

}

#endif
