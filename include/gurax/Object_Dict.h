//==============================================================================
// Value_Dict.h
//==============================================================================
#ifndef GURAX_OBJECT_DICT_H
#define GURAX_OBJECT_DICT_H
#include "Value_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
class VType_Dict : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Dict VTYPE_Dict;

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Dict : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Dict);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Dict");
private:
	RefPtr<ObjectDict> _pValueDict;
public:
	// Constructor
	explicit Value_Dict(VType& vtype = VTYPE_Dict) :
		Value_Dict(new ObjectDict(), vtype) {}
	explicit Value_Dict(ObjectDict* pValueDict, VType& vtype = VTYPE_Dict) :
		Value_Object(vtype), _pValueDict(pValueDict) {}
	// Copy constructor/operator
	Value_Dict(const Value_Dict& src) :
		Value_Object(src), _pValueDict(src._pValueDict->CloneDeep()) {}
	Value_Dict& operator=(const Value_Dict& src) = delete;
	// Move constructor/operator
	Value_Dict(Value_Dict&& src) = delete;
	Value_Dict& operator=(Value_Dict&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Dict() = default;
public:
	ObjectDict& GetObjectDict() { return *_pValueDict; }
	const ObjectDict& GetObjectDict() const { return *_pValueDict; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return new Value_Dict(*this); }
	virtual size_t DoCalcHash() const override { return GetObjectDict().CalcHash(); }
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetObjectDict().IsEqualTo(dynamic_cast<const Value_Dict*>(pValue)->GetObjectDict());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetObjectDict().IsLessThan(dynamic_cast<const Value_Dict*>(pValue)->GetObjectDict()) :
			GetVType().IsLessThan(pValue->GetVType());
		
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetObjectDict().ToString(ss);
	}
};

}

#endif
