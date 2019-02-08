//==============================================================================
// Object_DateTime.h
//==============================================================================
#ifndef GURAX_OBJECT_DATETIME_H
#define GURAX_OBJECT_DATETIME_H
#include "Object_Object.h"
#include "DateTime.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_DateTime
//------------------------------------------------------------------------------
class KlassT_DateTime : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_DateTime Klass_DateTime;

//------------------------------------------------------------------------------
// Object_DateTime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_DateTime : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_DateTime);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_DateTime");
private:
	RefPtr<DateTime> _pDateTime;
public:
	// Constructor
	Object_DateTime() = delete;
	explicit Object_DateTime(DateTime *pDateTime, Klass& klass) :
		Object_Object(klass), _pDateTime(pDateTime) {}
	// Copy constructor/operator
	Object_DateTime(const Object_DateTime& src) :
		Object_Object(src), _pDateTime(src._pDateTime->Reference()) {}
	Object_DateTime& operator=(const Object_DateTime& src) = delete;
	// Move constructor/operator
	Object_DateTime(Object_DateTime&& src) = delete;
	Object_DateTime& operator=(Object_DateTime&& src) noexcept = delete;
protected:
	// Destructor
	~Object_DateTime() = default;
public:
	DateTime& GetDateTime() { return *_pDateTime; }
	const DateTime& GetDateTime() const { return *_pDateTime; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDateTime().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetDateTime().IsEqualTo(dynamic_cast<const Object_DateTime*>(pObject)->GetDateTime());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetDateTime().IsLessThan(dynamic_cast<const Object_DateTime*>(pObject)->GetDateTime()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetDateTime().ToString(ss);
	}
};

}

#endif
