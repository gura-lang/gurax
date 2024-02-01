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
	RefPtr<Frame> _pFrameForVType;
	RefPtr<DeclCallable> _pDeclCallable;
	RefPtr<Attribute> _pAttr;
	DeclCallable::Flags _flags;
	RefPtr<Value> _pValueThis;
	RefPtr<Expr_Block> _pExprOfBlock;		// this may be nullptr
	RefPtr<Value_Dict> _pValueOfDict;		// this may be nullptr
	RefPtr<ArgSlot> _pArgSlotFirst;			// this may be nullptr
	ArgSlot* _pArgSlotToFeed;
	MapMode _mapMode;
public:
	// Constructor
	Argument(Processor& processor, Value* pValueCar, DeclCallable* pDeclCallable, Attribute* pAttr,
			DeclCallable::Flags flags, Value* pValueThis, Expr_Block* pExprOfBlock);
	Argument(Processor& processor, DeclCallable* pDeclCallable, DeclCallable::Flags flags = DeclCallable::Flag::None) :
		Argument(processor, Value::nil(), pDeclCallable, Attribute::Empty->Reference(), flags, Value::undefined(), nullptr) {}
	Argument(Processor& processor, const Function& function, DeclCallable::Flags flags = DeclCallable::Flag::None);
	// Copy constructor/operator
	Argument(const Argument& src) = delete;
	Argument& operator=(const Argument& src) = delete;
	// Move constructor/operator
	Argument(Argument&& src) = delete;
	Argument& operator=(Argument&& src) noexcept = delete;
protected:
	~Argument() = default;
public:
	static Argument* CreateForBlockCall(Processor& processor, const Expr_Block& exprOfBlock) {
		return new Argument(processor, exprOfBlock.GetDeclCallable().Reference(), DeclCallable::Flag::CutExtraArgs);
	}
public:
	Value& GetValueCar() { return *_pValueCar; }
	const Value& GetValueCar() const { return *_pValueCar; }
	Frame& GetFrameForVType() { return *_pFrameForVType; }
	const DeclCallable& GetDeclCallable() const { return *_pDeclCallable; }
	DeclCallable::Flags GetFlags() const { return _flags; }
	const Attribute& GetAttr() const { return *_pAttr; }
	bool IsSet(DeclCallable::Flags flags) const { return (GetFlags() & flags) != 0; }
	bool IsSet(const Symbol* pSymbol) const {
		return GetDeclCallable().IsSet(pSymbol) || GetAttr().IsSet(pSymbol);
	}
	bool IsSetOpt(const Symbol* pSymbol) const {
		return GetDeclCallable().IsSetOpt(pSymbol) || GetAttr().IsSetOpt(pSymbol);
	}
	bool HasArgSlot() const { return _pArgSlotFirst? true : false; }
	ArgSlot* GetArgSlotFirst() { return _pArgSlotFirst.get(); }
	const ArgSlot* GetArgSlotFirst() const { return _pArgSlotFirst.get(); }
	Value& GetValueThis() { return *_pValueThis; }
	const Value& GetValueThis() const { return *_pValueThis; }
	bool HasExprOfBlock() const { return _pExprOfBlock.get() != nullptr; }
	const Expr_Block* GetExprOfBlock() const { return _pExprOfBlock.get(); }
	Expr_Block* SuspendExprOfBlock() { return _pExprOfBlock.release(); }
	void ResumeExprOfBlock(Expr_Block* pExpr) { _pExprOfBlock.reset(pExpr); }
	Function* CreateBlockFunction(Frame& frameOuter, const Symbol* pSymbol, bool holdFrameFlag) const;
	bool HasValueOfDict() const { return _pValueOfDict.get() != nullptr; }
	Value_Dict* GetValueOfDict() { return _pValueOfDict.get(); }
	const Value_Dict* GetValueOfDict() const { return _pValueOfDict.get(); }
	bool IsMapNone() const { return _mapMode == MapMode::None; }
	bool IsMapToList() const { return _mapMode == MapMode::ToList; }
	bool IsMapToIter() const { return _mapMode == MapMode::ToIter; }
public:
	void SetValueThis(Value* pValueThis) { _pValueThis.reset(pValueThis); }
	ArgSlot* GetArgSlotToFeed() { return _pArgSlotToFeed; }
	void SetMapMode(MapMode mapMode) { _mapMode = mapMode; }
	bool CheckArgSlotToFeed() const;
public:
	size_t CountArgSlot() const;
	void ResetAllValues();
	void FeedValue(Processor& processor, Frame& frameForVType, RefPtr<Value> pValue) {
		if (!_pArgSlotToFeed) return;
		_pArgSlotToFeed->FeedValue(processor, *this, frameForVType, pValue.release());
		_pArgSlotToFeed = _pArgSlotToFeed->Advance();
	}
	bool FeedValues(Processor& processor, Frame& frameForVType, const ValueList& values);
	bool CompleteFeedValue(Processor& processor);
	bool FeedValuesAndComplete(Processor& processor, Frame& frameForVType, const ValueList& values) {
		return FeedValues(processor, frameForVType, values) && CompleteFeedValue(processor);
	}
	bool FeedValuesAndComplete(Processor& processor, const ValueList& values) {
		return FeedValuesAndComplete(processor, processor.GetFrameCur(), values);
	}
	ArgSlot* FindArgSlot(const Symbol* pSymbol) {
		return _pArgSlotFirst? _pArgSlotFirst->Find(pSymbol) : nullptr;
	}
	const ArgSlot* FindArgSlot(const Symbol* pSymbol) const {
		return const_cast<Argument*>(this)->FindArgSlot(pSymbol);
	}
	bool ReadyToPickValue(Processor& processor, Frame& frame);
	void AssignToFrame(Processor& processor, Frame& frame, Frame& frameOuter) const;
	void DoCall(Processor& processor);
	Value* ReturnValue(Processor& processor, RefPtr<Value> pValueRtn) {
		return _pExprOfBlock? _pExprOfBlock->EvalEasy(processor, pValueRtn.release()) : pValueRtn.release();
	}
	Value* ReturnIterator(Processor& processor, RefPtr<Iterator> pIterator);
	static void AssignThisToFrame(Processor& processor, Frame& frame, Value* pValueThis) {
		frame.AssignFromArgument(processor, Gurax_Symbol(this_), pValueThis);
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
