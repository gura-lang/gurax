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
	RefPtr<Attribute> _pAttr;
	RefPtr<ArgSlot> _pArgSlotTop;
	ArgSlot* _pArgSlotCur;
public:
	// Constructor
	Argument(DeclCaller* pDeclCaller, Attribute* pAttr);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	const DeclCaller& GetDeclCaller() const { return *_pDeclCaller; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(const Symbol* pSymbol) {
		return GetDeclCaller().IsSet(pSymbol) || GetAttr().IsSet(pSymbol);
	}
	bool IsSetOpt(const Symbol* pSymbol) {
		return GetDeclCaller().IsSetOpt(pSymbol) || GetAttr().IsSetOpt(pSymbol);
	}
	void RewindArgSlot() { _pArgSlotCur = _pArgSlotTop.get(); }
	void NextArgSlot() { _pArgSlotCur = _pArgSlotCur->GetNext(); }
	ArgSlot* GetArgSlotCur() { return _pArgSlotCur; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& attr) const { return this == &attr; }
	bool IsEqualTo(const Argument& attr) const { return IsIdentical(attr); }
	bool IsLessThan(const Argument& attr) const { return this < &attr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
