//==============================================================================
// VType_Referencer.h
//==============================================================================
#ifndef GURAX_VTYPE_REFERENCER_H
#define GURAX_VTYPE_REFERENCER_H
#include "VType_Object.h"
#include "Referencer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Referencer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Referencer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Referencer VTYPE_Referencer;

//------------------------------------------------------------------------------
// Value_Referencer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Referencer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Referencer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Referencer");
protected:
	RefPtr<Referencer> _pReferencer;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Referencer() = delete;
	explicit Value_Referencer(Referencer* pReferencer, VType& vtype = VTYPE_Referencer) :
		Value_Object(vtype), _pReferencer(pReferencer) {}
	// Copy constructor/operator
	Value_Referencer(const Value_Referencer& src) :
		Value_Object(src), _pReferencer(src._pReferencer->Reference()) {}
	Value_Referencer& operator=(const Value_Referencer& src) = delete;
	// Move constructor/operator
	Value_Referencer(Value_Referencer&& src) noexcept = delete;
	Value_Referencer& operator=(Value_Referencer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Referencer() = default;
public:
	Referencer& GetReferencer() { return *_pReferencer; }
	const Referencer& GetReferencer() const { return *_pReferencer; }
public:
	static Referencer& GetReferencer(Value& value) {
		return dynamic_cast<Value_Referencer&>(value).GetReferencer();
	}
	static const Referencer& GetReferencer(const Value& value) {
		return dynamic_cast<const Value_Referencer&>(value).GetReferencer();
	}
	static Referencer* GetEntityPtr(Value& value) { return &GetReferencer(value); }
	static const Referencer* GetEntityPtr(const Value& value) { return &GetReferencer(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetReferencer().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetReferencer().IsEqualTo(Value_Referencer::GetReferencer(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetReferencer().IsLessThan(Value_Referencer::GetReferencer(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
