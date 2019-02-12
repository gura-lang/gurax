//==============================================================================
// ArgSlot.h
//==============================================================================
#ifndef GURAX_ARGSLOT_H
#define GURAX_ARGSLOT_H
#include "Referable.h"
#include "Attribute.h"
#include "Value_List.h"
#include "DeclCaller.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ArgSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ArgSlot);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ArgSlot");
protected:
	RefPtr<DeclArg> _pDeclArg;
	RefPtr<ArgSlot> _pArgSlotNext;
public:
	ArgSlot(DeclArg* pDeclArg) : _pDeclArg(pDeclArg) {}
protected:
	virtual ~ArgSlot() = default;
public:
	const DeclArg& GetDeclArg() const { return *_pDeclArg; }
	bool IsMatched(const Symbol* pSymbol) const {
		return GetDeclArg().GetSymbol()->IsIdentical(pSymbol);
	}
	ArgSlot* Find(const Symbol* pSymbol);
	void SetNext(ArgSlot* pArgSlotNext) { _pArgSlotNext.reset(pArgSlotNext); }
	ArgSlot* GetNext() { return _pArgSlotNext.get(); }
public:
	// Virtual functions
	virtual void FeedValue(Value* pValue) = 0;
	virtual const Value& GetValue() = 0;
};

//------------------------------------------------------------------------------
// ArgSlot_Value
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_Value : public ArgSlot {
protected:
	RefPtr<Value> _pValue;
public:
	ArgSlot_Value(DeclArg* pDeclArg) : ArgSlot(pDeclArg), _pValue(Value::undefined()) {}
public:
	// Virtual functions of ArgSlot
	virtual void FeedValue(Value* pValue) override;
	virtual const Value& GetValue() override { return *_pValue; }
};

//------------------------------------------------------------------------------
// ArgSlot_ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ArgSlot_ValueList : public ArgSlot {
protected:
	RefPtr<Value_List> _pValue;
public:
	ArgSlot_ValueList(DeclArg* pDeclArg) : ArgSlot(pDeclArg), _pValue(new Value_List()) {}
public:
	// Virtual functions of ArgSlot
	virtual void FeedValue(Value* pValue) override;
	virtual const Value& GetValue() override { return *_pValue; }
};

}

#endif
