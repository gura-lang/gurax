//==============================================================================
// Argument.h
//==============================================================================
#ifndef GURAX_ARGUMENT_H
#define GURAX_ARGUMENT_H
#include "ArgSlot.h"
#include "Processor.h"
#include "VType_Dict.h"

namespace Gurax {

class PUnit;
class Function;

//------------------------------------------------------------------------------
// Argument
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Argument : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Argument);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Argument");
private:
	RefPtr<Value> _pValueCar;
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<Attribute> _pAttr;
	RefPtr<Value> _pValueThis;				// this may be nullptr
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
	RefPtr<Value_Dict> _pValueOfDict;		// this may be nullptr
	RefPtr<ArgSlot> _pArgSlotFirst;			// this may be nullptr
	const PUnit *_pPUnitCont;				// this may be nullptr
	UInt32 _flags;
	ArgSlot* _pArgSlotToFeed;
public:
	// Constructor
	Argument(Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr,
			 Value* pValueThis, Expr_Block* pExprOfBlock);
	Argument(DeclCallable* pDeclCallable) :
		Argument(Value::nil(), pDeclCallable, Attribute::Empty->Reference(), Value::nil(), nullptr) {}
	Argument(const Function& function);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	Value& GetValueCar() { return *_pValueCar; }
	const Value& GetValueCar() const { return *_pValueCar; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(const Symbol* pSymbol) {
		return GetDeclCallable().IsSet(pSymbol) || GetAttr().IsSet(pSymbol);
	}
	bool IsSetOpt(const Symbol* pSymbol) {
		return GetDeclCallable().IsSetOpt(pSymbol) || GetAttr().IsSetOpt(pSymbol);
	}
	ArgSlot* GetArgSlotFirst() { return _pArgSlotFirst.get(); }
	const ArgSlot* GetArgSlotFirst() const { return _pArgSlotFirst.get(); }
	ArgSlot* GetArgSlotToFeed() { return _pArgSlotToFeed; }
	void SetValueThis(Value* pValueThis) { _pValueThis.reset(pValueThis); }
	Value& GetValueThis() { return *_pValueThis; }
	bool HasBlock() const { return _pExprOfBlock.get() != nullptr; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
	Function* CreateFunctionOfBlock(Frame& frameParent) const;
	Function* CreateFunctionOfBlock(Processor& processor) const {
		return CreateFunctionOfBlock(processor.GetFrameCur());
	}
	Function* CreateFunctionOfBlock(Frame& frameParent, RefPtr<Argument>& pArgument) const;
	Function* CreateFunctionOfBlock(Processor& processor, RefPtr<Argument>& pArgument) const {
		return CreateFunctionOfBlock(processor.GetFrameCur(), pArgument);
	}
	Value_Dict* GetValueOfDict() { return _pValueOfDict.get(); }
	const Value_Dict* GetValueOfDict() const { return _pValueOfDict.get(); }
	void ResetAllValues();
	void FeedValue(Frame& frame, Value* pValue) {
		if (!_pArgSlotToFeed) return;
		_pArgSlotToFeed->FeedValue(frame, pValue);
		_pArgSlotToFeed = _pArgSlotToFeed->Advance();
	}
	ArgSlot* FindArgSlot(const Symbol* pSymbol) {
		return _pArgSlotFirst? _pArgSlotFirst->Find(pSymbol) : nullptr;
	}
	const ArgSlot* FindArgSlot(const Symbol* pSymbol) const {
		return const_cast<Argument*>(this)->FindArgSlot(pSymbol);
	}
	void SetPUnitCont(const PUnit* pPUnit) { _pPUnitCont = pPUnit; }
	const PUnit* GetPUnitCont() const { return _pPUnitCont; }
	void AssignToFrame(Frame& frame) const;
	Value* DoCall(Processor& processor);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& argument) const { return this == &argument; }
	bool IsEqualTo(const Argument& argument) const { return IsIdentical(argument); }
	bool IsLessThan(const Argument& argument) const { return this < &argument; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
