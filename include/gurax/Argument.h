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
public:
	enum class MapMode { None, ToIter, ToList, };
private:
	RefPtr<Value> _pValueCar;
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	RefPtr<Value> _pValueThis;				// this may be nullptr
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
	RefPtr<Value_Dict> _pValueOfDict;		// this may be nullptr
	RefPtr<ArgSlot> _pArgSlotFirst;			// this may be nullptr
	ArgSlot* _pArgSlotToFeed;
	MapMode _mapMode;
public:
	// Constructor
	Argument(Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr,
			 DeclCallable::Flags flags, Value* pValueThis, Expr_Block* pExprOfBlock);
	Argument(DeclCallable* pDeclCallable, DeclCallable::Flags flags = DeclCallable::Flag::None) :
		Argument(Value::nil(), pDeclCallable, Attribute::Empty->Reference(), flags, Value::nil(), nullptr) {}
	Argument(const Function& function, DeclCallable::Flags flags = DeclCallable::Flag::None);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	static Argument* CreateForBlockCall(const Expr_Block& exprOfBlock) {
		return new Argument(exprOfBlock.GetDeclCallable().Reference(), DeclCallable::Flag::CutExtraArgs);
	}
public:
	Value& GetValueCar() { return *_pValueCar; }
	const Value& GetValueCar() const { return *_pValueCar; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	DeclCallable::Flags GetFlags() const { return _flags; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(DeclCallable::Flags flags) const { return (GetFlags() & flags) != 0; }
	bool IsSet(const Symbol* pSymbol) {
		return GetDeclCallable().IsSet(pSymbol) || GetAttr().IsSet(pSymbol);
	}
	bool IsSetOpt(const Symbol* pSymbol) {
		return GetDeclCallable().IsSetOpt(pSymbol) || GetAttr().IsSetOpt(pSymbol);
	}
	bool HasArgSlot() const { return _pArgSlotFirst? true : false; }
	ArgSlot* GetArgSlotFirst() { return _pArgSlotFirst.get(); }
	const ArgSlot* GetArgSlotFirst() const { return _pArgSlotFirst.get(); }
	ArgSlot* GetArgSlotToFeed() { return _pArgSlotToFeed; }
	void SetValueThis(Value* pValueThis) { _pValueThis.reset(pValueThis); }
	Value& GetValueThis() { return *_pValueThis; }
	const Value& GetValueThis() const { return *_pValueThis; }
	bool HasExprOfBlock() const { return _pExprOfBlock.get() != nullptr; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
	Function* CreateBlockFunction(const Symbol* pSymbol) const;
	bool HasValueOfDict() const { return _pValueOfDict.get() != nullptr; }
	Value_Dict* GetValueOfDict() { return _pValueOfDict.get(); }
	const Value_Dict* GetValueOfDict() const { return _pValueOfDict.get(); }
	void SetMapMode(MapMode mapMode) { _mapMode = mapMode; }
	bool IsMapNone() const { return _mapMode == MapMode::None; }
	bool IsMapToList() const { return _mapMode == MapMode::ToList; }
	bool IsMapToIter() const { return _mapMode == MapMode::ToIter; }
	void ResetAllValues();
	void FeedValue(Frame& frame, Value* pValue) {
		if (!_pArgSlotToFeed) return;
		_pArgSlotToFeed->FeedValue(*this, frame, pValue);
		_pArgSlotToFeed = _pArgSlotToFeed->Advance();
	}
	ArgSlot* FindArgSlot(const Symbol* pSymbol) {
		return _pArgSlotFirst? _pArgSlotFirst->Find(pSymbol) : nullptr;
	}
	const ArgSlot* FindArgSlot(const Symbol* pSymbol) const {
		return const_cast<Argument*>(this)->FindArgSlot(pSymbol);
	}
	bool ReadyToPickValue(Frame& frame);
	void AssignToFrame(Frame& frame) const;
	bool Compensate(Processor& processor);
	void DoCall(Processor& processor);
	Value* ReturnValue(Processor& processor, RefPtr<Value> pValueRtn) {
		return _pExprOfBlock? _pExprOfBlock->DoEval(processor, pValueRtn.release()) : pValueRtn.release();
	}
	Value* ReturnIterator(Processor& processor, RefPtr<Iterator> pIterator);
	static void AssignThisToFrame(Frame& frame, Value* pValueThis) {
		frame.AssignFromArgument(Gurax_Symbol(this_), pValueThis);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Argument& argument) const { return this == &argument; }
	bool IsEqualTo(const Argument& argument) const { return IsIdentical(argument); }
	bool IsLessThan(const Argument& argument) const { return this < &argument; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
