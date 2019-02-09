//==============================================================================
// Object_Dict.h
//==============================================================================
#ifndef GURAX_OBJECT_DICT_H
#define GURAX_OBJECT_DICT_H
#include "Object_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
class VTypeT_Dict : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VTypeT_Dict VType_Dict;

//------------------------------------------------------------------------------
// Object_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Dict : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Dict);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Dict");
private:
	RefPtr<ObjectDict> _pObjectDict;
public:
	// Constructor
	explicit Object_Dict(VType& vtype = VType_Dict) :
		Object_Dict(new ObjectDict(), vtype) {}
	explicit Object_Dict(ObjectDict* pObjectDict, VType& vtype = VType_Dict) :
		Object_Object(vtype), _pObjectDict(pObjectDict) {}
	// Copy constructor/operator
	Object_Dict(const Object_Dict& src) :
		Object_Object(src), _pObjectDict(src._pObjectDict->CloneDeep()) {}
	Object_Dict& operator=(const Object_Dict& src) = delete;
	// Move constructor/operator
	Object_Dict(Object_Dict&& src) = delete;
	Object_Dict& operator=(Object_Dict&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Dict() = default;
public:
	ObjectDict& GetObjectDict() { return *_pObjectDict; }
	const ObjectDict& GetObjectDict() const { return *_pObjectDict; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Object_Dict(*this); }
	virtual size_t DoCalcHash() const override { return GetObjectDict().CalcHash(); }
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetObjectDict().IsEqualTo(dynamic_cast<const Object_Dict*>(pObject)->GetObjectDict());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetObjectDict().IsLessThan(dynamic_cast<const Object_Dict*>(pObject)->GetObjectDict()) :
			GetVType().IsLessThan(pObject->GetVType());
		
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectDict().ToString(ss);
	}
};

}

#endif
