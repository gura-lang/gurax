//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "ArgSlot.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Argument : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Argument");
public:
private:
	RefPtr<DeclCaller> _pDeclCaller;
	UInt32 _flags;
	RefPtr<Attribute> _pAttr;
	RefPtr<ArgSlot> _pArgSlotTop;
	ArgSlot* _pArgSlotToFeed;
	RefPtr<Value> _pValueThis;
	RefPtr<Value> _pValueCar;
public:
	// Constructor
	Argument(DeclCaller* pDeclCaller, Attribute* pAttr, Value* pValueThis, Value* pValueCar);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	bool CheckValidity() const;
	const DeclCaller& GetDeclCaller() const { return *_pDeclCaller; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(const Symbol* pSymbol) {
		return GetDeclCaller().IsSet(pSymbol) || GetAttr().IsSet(pSymbol);
	}
	bool IsSetOpt(const Symbol* pSymbol) {
		return GetDeclCaller().IsSetOpt(pSymbol) || GetAttr().IsSetOpt(pSymbol);
	}
	ArgSlot* GetArgSlotTop() { return _pArgSlotTop.get(); }
	const ArgSlot* GetArgSlotTop() const { return _pArgSlotTop.get(); }
	ArgSlot* GetArgSlotToFeed() { return _pArgSlotToFeed; }
	void SetValueThis(Value* pValueThis) { _pValueThis.reset(pValueThis); }
	Value& GetValueThis() { return *_pValueThis; }
	Value& GetValueCar() { return *_pValueCar; }
	void FeedValue(Value* pValue) {
		if (!_pArgSlotToFeed) return;
		_pArgSlotToFeed->FeedValue(pValue);
		_pArgSlotToFeed = _pArgSlotToFeed->GoNext();
	}
	ArgSlot* FindArgSlot(const Symbol* pSymbol) {
		return _pArgSlotTop? _pArgSlotTop->Find(pSymbol) : nullptr;
	}
	const ArgSlot* FindArgSlot(const Symbol* pSymbol) const {
		return const_cast<Argument*>(this)->FindArgSlot(pSymbol);
	}
	void Call(Frame& frame) { GetValueCar().DoCall(frame, *this); }
	void IndexAccess(Frame& frame) { GetValueCar().DoIndexAccess(frame, *this); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& argument) const { return this == &argument; }
	bool IsEqualTo(const Argument& argument) const { return IsIdentical(argument); }
	bool IsLessThan(const Argument& argument) const { return this < &argument; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
