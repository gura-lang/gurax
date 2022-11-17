//==============================================================================
// VType_PropSlot.h
//==============================================================================
#ifndef GURAX_VTYPE_PROPSLOT_H
#define GURAX_VTYPE_PROPSLOT_H
#include "VType_Object.h"
#include "PropSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_PropSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_PropSlot : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_PropSlot VTYPE_PropSlot;

//------------------------------------------------------------------------------
// Value_PropSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_PropSlot : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_PropSlot);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_PropSlot");
protected:
	RefPtr<PropSlot> _pPropSlot;
public:
	static VType& vtype;
public:
	// Constructor
	Value_PropSlot() = delete;
	Value_PropSlot(PropSlot* pPropSlot, VType& vtype = VTYPE_PropSlot) :
		Value_Object(vtype), _pPropSlot(pPropSlot) {}
	// Copy constructor/operator
	Value_PropSlot(const Value_PropSlot& src) :
		Value_Object(src), _pPropSlot(src._pPropSlot->Reference()) {}
	Value_PropSlot& operator=(const Value_PropSlot& src) = delete;
	// Move constructor/operator
	Value_PropSlot(Value_PropSlot&& src) = delete;
	Value_PropSlot& operator=(Value_PropSlot&& src) noexcept = delete;
protected:
	// Destructor
	~Value_PropSlot() = default;
public:
	PropSlot& GetPropSlot() { return *_pPropSlot; }
	const PropSlot& GetPropSlot() const { return *_pPropSlot; }
public:
	static PropSlot& GetPropSlot(Value& value) {
		return dynamic_cast<Value_PropSlot&>(value).GetPropSlot();
	}
	static const PropSlot& GetPropSlot(const Value& value) {
		return dynamic_cast<const Value_PropSlot&>(value).GetPropSlot();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPropSlot().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPropSlot().IsEqualTo(Value_PropSlot::GetPropSlot(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPropSlot().IsLessThan(Value_PropSlot::GetPropSlot(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	// Virtual functions for runtime process
	virtual HelpHolder* GetHelpHolder(bool classFlag) const override { return &_pPropSlot->GetHelpHolder(); }
	virtual void PresentHelp(Processor& processor, const Symbol* pLangCode) const override;
};

//------------------------------------------------------------------------------
// Iterator_PropSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_PropSlot : public Iterator {
private:
	RefPtr<PropSlotOwner> _pPropSlotOwner;
	size_t _idx;
public:
	Iterator_PropSlot(PropSlotOwner* pPropSlotOwner);
public:
	const PropSlotOwner& GetPropSlotOwner() const { return *_pPropSlotOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
