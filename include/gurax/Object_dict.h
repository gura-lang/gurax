//==============================================================================
// Object_dict.h
//==============================================================================
#ifndef GURAX_OBJECT_DICT_H
#define GURAX_OBJECT_DICT_H
#include "Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_dict
//------------------------------------------------------------------------------
class KlassT_dict : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_dict Klass_dict;

//------------------------------------------------------------------------------
// Object_dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_dict : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_dict);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_dict");
private:
	RefPtr<ObjectDict> _pObjectDict;
public:
	// Constructor
	Object_dict() : Object(Klass_dict), _pObjectDict(new ObjectDict()) {}
	// Copy constructor/operator
	Object_dict(const Object_dict& src) : Object(Klass_dict), _pObjectDict(src._pObjectDict->CloneDeep()) {}
	Object_dict& operator=(const Object_dict& src) {
		_pObjectDict.reset(src._pObjectDict->CloneDeep()); return *this;
	}
	// Move constructor/operator
	Object_dict(Object_dict&& src) : Object(Klass_dict), _pObjectDict(src._pObjectDict.release()) {}
	Object_dict& operator=(Object_dict&& src) noexcept {
		_pObjectDict.reset(src._pObjectDict.release()); return *this;
	}
protected:
	// Destructor
	~Object_dict() = default;
public:
	ObjectDict& GetObjectDict() { return *_pObjectDict; }
	const ObjectDict& GetObjectDict() const { return *_pObjectDict; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Object_dict(*this); }
	virtual size_t DoCalcHash() const override { return GetObjectDict().CalcHash(); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetObjectDict().IsEqualTo(dynamic_cast<const Object_dict*>(pObject)->GetObjectDict());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetObjectDict().IsLessThan(dynamic_cast<const Object_dict*>(pObject)->GetObjectDict()) :
			GetKlass().IsLessThan(pObject->GetKlass());
		
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectDict().ToString(ss);
	}
};

}

#endif
