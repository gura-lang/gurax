//==============================================================================
// Object_datetime.h
//==============================================================================
#ifndef GURAX_OBJECT_DATETIME_H
#define GURAX_OBJECT_DATETIME_H
#include "Object.h"
#include "DateTime.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_datetime
//------------------------------------------------------------------------------
class KlassT_datetime : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_datetime Klass_datetime;

//------------------------------------------------------------------------------
// Object_datetime
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_datetime : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_datetime);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_datetime");
private:
	RefPtr<DateTime> _pDateTime;
public:
	// Constructor
	Object_datetime() = delete;
	explicit Object_datetime(DateTime *pDateTime) : Object(Klass_datetime), _pDateTime(pDateTime) {}
	// Copy constructor/operator
	Object_datetime(const Object_datetime& src) : Object(Klass_datetime), _pDateTime(src._pDateTime->Reference()) {}
	Object_datetime& operator=(const Object_datetime& src) { _pDateTime.reset(src._pDateTime->Reference()); return *this; }
	// Move constructor/operator
	Object_datetime(Object_datetime&& src) : Object(Klass_datetime), _pDateTime(src._pDateTime.release()) {}
	Object_datetime& operator=(Object_datetime&& src) noexcept { _pDateTime.reset(src._pDateTime.release()); return *this; }
protected:
	// Destructor
	~Object_datetime() = default;
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
			GetDateTime().IsEqualTo(dynamic_cast<const Object_datetime*>(pObject)->GetDateTime());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetDateTime().IsLessThan(dynamic_cast<const Object_datetime*>(pObject)->GetDateTime()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetDateTime().ToString(ss);
	}
};

}

#endif
