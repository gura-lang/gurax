//==============================================================================
// BasicIterator.h
//==============================================================================
#ifndef GURAX_BASICITERATOR_H
#define GURAX_BASICITERATOR_H
#include "Argument.h"
#include "Iterator.h"
#include "Processor.h"

#undef min

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator_Empty
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Empty : public Iterator {
public:
	Iterator_Empty() {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined | Flag::Rewindable;
	}
	virtual size_t GetLength() const override { return 0; }
	virtual Value* DoNextValue() override { return nullptr; }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Const
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Const : public Iterator {
private:
	RefPtr<Value> _pValue;
public:
	Iterator_Const(Value* pValue) : _pValue(pValue) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Infinite | Flag::LenUndetermined | Flag::Rewindable;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override { return _pValue->Reference(); }
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_ConstN
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ConstN : public Iterator {
private:
	RefPtr<Value> _pValue;
	size_t _num;
	size_t _idx;
public:
	Iterator_ConstN(Value* pValue, size_t num) : _pValue(pValue) , _num(num), _idx(0) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined | Flag::Rewindable;
	}
	virtual size_t GetLength() const override { return _num; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Concat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Concat : public Iterator {
private:
	RefPtr<Iterator> _pIteratorFirst;
	RefPtr<Iterator> _pIteratorSecond;
public:
	Iterator_Concat(Iterator* pIteratorFirst, Iterator* pIteratorSecond) :
					_pIteratorFirst(pIteratorFirst), _pIteratorSecond(pIteratorSecond) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override;
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Counter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Counter : public Iterator {
private:
	int _idxBegin;
	int _idxStep;
	int _idx;
public:
	Iterator_Counter(int idxBegin, int idxStep) :
		_idxBegin(idxBegin), _idxStep(idxStep), _idx(idxBegin) {}
	Iterator_Counter() : Iterator_Counter(0, 1) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Infinite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_UnaryOpImpMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_UnaryOpImpMap : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	Operator* _pOp;
	const OpEntry* _pOpEntry;
	RefPtr<Value> _pValue;
	const VType* _pVTypePrev;
	Flags _flags;
	size_t _len;
public:
	Iterator_UnaryOpImpMap(Processor* pProcessor, Operator* pOp, Value* pValue);
protected:
	// Destructor
	virtual ~Iterator_UnaryOpImpMap() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Value& GetValue() { return *_pValue; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return _flags; }
	virtual size_t GetLength() const override { return _len; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_BinaryOpImpMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_BinaryOpImpMap : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	Operator* _pOp;
	const OpEntry* _pOpEntry;
	RefPtr<Value> _pValueL;
	RefPtr<Value> _pValueR;
	const VType* _pVTypePrevL;
	const VType* _pVTypePrevR;
	Flags _flags;
	size_t _len;
public:
	Iterator_BinaryOpImpMap(Processor* pProcessor, Operator* pOp, Value* pValueL, Value* pValueR);
protected:
	// Destructor
	virtual ~Iterator_BinaryOpImpMap() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Value& GetValueL() { return *_pValueL; }
	Value& GetValueR() { return *_pValueR; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return _flags; }
	virtual size_t GetLength() const override { return _len; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_FunctionImpMap
//------------------------------------------------------------------------------
template<bool skipNilFlag>
class Iterator_FunctionImpMap : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Argument> _pArgument;
	Flags _flags;
	size_t _len;
public:
	Iterator_FunctionImpMap(Processor* pProcessor, Function* pFunction, Argument* pArgument);
protected:
	// Destructor
	virtual ~Iterator_FunctionImpMap() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Function& GetFunction() { return *_pFunction; }
	Argument& GetArgument() { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return _flags; }
	virtual size_t GetLength() const override { return _len; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

extern template class Iterator_FunctionImpMap<true>;
extern template class Iterator_FunctionImpMap<false>;

//------------------------------------------------------------------------------
// Iterator_Range
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Range : public Iterator {
private:
	int _idxBegin, _idxEnd;
	int _idxStep;
	int _idx;
public:
	Iterator_Range(int idxBegin, int idxEnd, int idxStep) :
		_idxBegin(idxBegin), _idxEnd(idxEnd), _idxStep(idxStep), _idx(idxBegin) {}
	Iterator_Range(int n) : Iterator_Range(0, n, 1) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined | Flag::Rewindable;
	}
	virtual size_t GetLength() const override { return (_idxEnd - _idxBegin) / _idxStep; }
	virtual void DoRewind() override { _idx = _idxBegin; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Member_MapAlong
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Member_MapAlong : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Iterator> _pIteratorTarget;
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	Iterator_Member_MapAlong(Processor* pProcessor, Iterator* pIteratorTarget, const Symbol* pSymbol, Attribute* pAttr) :
		_pProcessor(pProcessor), _pIteratorTarget(pIteratorTarget), _pSymbol(pSymbol), _pAttr(pAttr) {}
protected:
	// Destructor
	virtual ~Iterator_Member_MapAlong() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	const Processor& GetProcessor() const { return *_pProcessor; }
	const Iterator& GetIteratorTarget() const { return *_pIteratorTarget; }
	Iterator& GetIteratorTarget() { return *_pIteratorTarget; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIteratorTarget().GetFlags(); }
	virtual size_t GetLength() const override { return GetIteratorTarget().GetLength(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Member_MapToIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Member_MapToIter : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Iterator> _pIteratorTarget;
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	Iterator_Member_MapToIter(Processor* pProcessor, Iterator* pIteratorTarget, const Symbol* pSymbol, Attribute* pAttr) :
		_pProcessor(pProcessor), _pIteratorTarget(pIteratorTarget), _pSymbol(pSymbol), _pAttr(pAttr) {}
protected:
	// Destructor
	virtual ~Iterator_Member_MapToIter() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	const Processor& GetProcessor() const { return *_pProcessor; }
	const Iterator& GetIteratorTarget() const { return *_pIteratorTarget; }
	Iterator& GetIteratorTarget() { return *_pIteratorTarget; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIteratorTarget().GetFlags(); }
	virtual size_t GetLength() const override { return GetIteratorTarget().GetLength(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_IteratorEvaluator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_IteratorEvaluator : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Iterator> _pIterator;
	RefPtr<Argument> _pArgument;
public:
	Iterator_IteratorEvaluator(Processor* pProcessor, Iterator* pIterator, Argument* pArgument) :
		_pProcessor(pProcessor), _pIterator(pIterator), _pArgument(pArgument) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	const Processor& GetProcessor() const { return *_pProcessor; }
	Iterator& GetIterator() { return *_pIterator; }
	const Iterator& GetIterator() const { return *_pIterator; }
	Argument& GetArgument() { return *_pArgument; }
	const Argument& GetArgument() const { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIterator().GetFlags(); }
	virtual size_t GetLength() const override { return GetIterator().GetLength(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_cross
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_cross : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Frame> _pFrame;
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<Argument> _pArgument;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	RefPtr<IteratorOwner> _pIteratorOwner;
	bool _skipNilFlag;
	size_t _idx;
	bool _contFlag;
public:
	Iterator_cross(Processor* pProcessor, Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner,
				IteratorOwner* pIteratorOwner, bool skipNilFlag) :
		_pProcessor(pProcessor), _pFrame(pProcessor->CreateFrame<Frame_Scope>()),
		_pExprOfBlock(pExprOfBlock), _pArgument(Argument::CreateForBlockCall(*pProcessor, *pExprOfBlock)),
		_pDeclArgOwner(pDeclArgOwner), _pIteratorOwner(pIteratorOwner),
		_skipNilFlag(skipNilFlag), _idx(0), _contFlag(true) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Frame& GetFrame() { return *_pFrame; }
	const Expr_Block& GetExprOfBlock() { return *_pExprOfBlock; }
	Argument& GetArgument() { return *_pArgument; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
	IteratorOwner& GetIteratorOwner() { return *_pIteratorOwner; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_for
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_for : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Frame> _pFrame;
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<Argument> _pArgument;
	RefPtr<DeclArgOwner> _pDeclArgOwner;
	RefPtr<IteratorOwner> _pIteratorOwner;
	bool _skipNilFlag;
	size_t _idx;
	bool _contFlag;
public:
	Iterator_for(Processor* pProcessor, Expr_Block* pExprOfBlock, DeclArgOwner* pDeclArgOwner,
				IteratorOwner* pIteratorOwner, bool skipNilFlag) :
		_pProcessor(pProcessor), _pFrame(pProcessor->CreateFrame<Frame_Scope>()),
		_pExprOfBlock(pExprOfBlock), _pArgument(Argument::CreateForBlockCall(*pProcessor, *pExprOfBlock)),
		_pDeclArgOwner(pDeclArgOwner), _pIteratorOwner(pIteratorOwner),
		_skipNilFlag(skipNilFlag), _idx(0), _contFlag(true) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Frame& GetFrame() { return *_pFrame; }
	const Expr_Block& GetExprOfBlock() { return *_pExprOfBlock; }
	Argument& GetArgument() { return *_pArgument; }
	const DeclArgOwner& GetDeclArgOwner() const { return *_pDeclArgOwner; }
	IteratorOwner& GetIteratorOwner() { return *_pIteratorOwner; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_while
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_while : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Frame> _pFrame;
	RefPtr<Expr> _pExprCriteria;
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<Argument> _pArgument;
	bool _skipNilFlag;
	size_t _idx;
	bool _contFlag;
public:
	Iterator_while(Processor* pProcessor, Expr* pExprCriteria, Expr_Block* pExprOfBlock, bool skipNilFlag) :
		_pProcessor(pProcessor), _pFrame(pProcessor->GetFrameCur().Reference()),
		_pExprCriteria(pExprCriteria), _pExprOfBlock(pExprOfBlock),
		_pArgument(Argument::CreateForBlockCall(*pProcessor, *pExprOfBlock)),
		_skipNilFlag(skipNilFlag), _idx(0), _contFlag(true) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Frame& GetFrame() { return *_pFrame; }
	const Expr& GetExprCriteria() { return *_pExprCriteria; }
	const Expr_Block& GetExprOfBlock() { return *_pExprOfBlock; }
	Argument& GetArgument() { return *_pArgument; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenUndetermined; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_repeat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_repeat : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Frame> _pFrame;
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<Argument> _pArgument;
	bool _finiteFlag;
	bool _skipNilFlag;
	size_t _cnt;
	size_t _idx;
	bool _contFlag;
public:
	Iterator_repeat(Processor* pProcessor, Expr_Block* pExprOfBlock, bool finiteFlag, bool skipNilFlag, size_t cnt = -1) :
		_pProcessor(pProcessor), _pFrame(pProcessor->GetFrameCur().Reference()),
		_pExprOfBlock(pExprOfBlock), _pArgument(Argument::CreateForBlockCall(*pProcessor, *pExprOfBlock)),
		_finiteFlag(finiteFlag), _skipNilFlag(skipNilFlag), _cnt(cnt), _idx(0), _contFlag(true) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Frame& GetFrame() { return *_pFrame; }
	const Expr_Block& GetExprOfBlock() { return *_pExprOfBlock; }
	Argument& GetArgument() { return *_pArgument; }
	bool GetFiniteFlag() const { return _finiteFlag; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return GetFiniteFlag()?
			(Flag::Finite | Flag::LenDetermined) :
			(Flag::Infinite | Flag::LenUndetermined);
	}
	virtual size_t GetLength() const override { return _cnt; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_DoEach
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_DoEach : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Frame> _pFrame;
	RefPtr<Expr_Block> _pExprOfBlock;
	RefPtr<Argument> _pArgument;
	RefPtr<Iterator> _pIteratorSrc;
	bool _skipNilFlag;
	size_t _idx;
	bool _contFlag;
public:
	Iterator_DoEach(Processor* pProcessor, Expr_Block* pExprOfBlock, Iterator* pIteratorSrc, bool skipNilFlag) :
		_pProcessor(pProcessor), _pFrame(pProcessor->CreateFrame<Frame_Scope>()),
		_pExprOfBlock(pExprOfBlock), _pArgument(Argument::CreateForBlockCall(*pProcessor, *pExprOfBlock)),
		_pIteratorSrc(pIteratorSrc), _skipNilFlag(skipNilFlag), _idx(0), _contFlag(true) {}
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Frame& GetFrame() { return *_pFrame; }
	const Expr_Block& GetExprOfBlock() { return *_pExprOfBlock; }
	Argument& GetArgument() { return *_pArgument; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
	bool GetSkipNilFlag() const { return _skipNilFlag; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIteratorSrc().GetFlags(); }
	virtual size_t GetLength() const override { return GetIteratorSrc().GetLength(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Each
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Each : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Each");
private:
	RefPtr<ValueOwner> _pValueOwner;
	size_t _idx;
	size_t _idxBegin;
	size_t _idxEnd;
public:
	Iterator_Each(ValueOwner* pValueOwner) :
		_pValueOwner(pValueOwner), _idx(0), _idxBegin(0), _idxEnd(pValueOwner->size()) {}
	Iterator_Each(ValueOwner* pValueOwner, size_t idxBegin) :
		_pValueOwner(pValueOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(pValueOwner->size()) {}
	Iterator_Each(ValueOwner* pValueOwner, size_t idxBegin, size_t idxEnd) :
		_pValueOwner(pValueOwner), _idx(idxBegin), _idxBegin(idxBegin), _idxEnd(idxEnd) {}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined | Flag::Rewindable; }
	virtual size_t GetLength() const override { return GetValueOwner().size(); }
	virtual void DoRewind() override { _idx = _idxBegin; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_ExprLink
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ExprLink : public Iterator {
private:
	RefPtr<ExprLink> _pExprLink;
	const Expr* _pExprCur;
public:
	Iterator_ExprLink(ExprLink* pExprLink) :
		_pExprLink(pExprLink), _pExprCur(_pExprLink->GetExprFirst()) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Reverse
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Reverse : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Reverse");
private:
	RefPtr<ValueOwner> _pValueOwner;
	size_t _idx;
public:
	Iterator_Reverse(ValueOwner* pValueOwner) : _pValueOwner(pValueOwner), _idx(0) {}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetValueOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Cycle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Cycle : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Cycle");
private:
	RefPtr<ValueOwner> _pValueOwner;
	Int _cnt;
	Int _idx;
public:
	Iterator_Cycle(ValueOwner* pValueOwner, Int cnt) :
		_pValueOwner(pValueOwner), _cnt(cnt), _idx(0) {}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (_cnt < 0)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
	}
	virtual size_t GetLength() const override { return (_cnt < 0)? -1 : _cnt; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_Align
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Align : public Iterator {
private:
	RefPtr<Iterator> _pIteratorSrc;
	size_t _cnt;
	RefPtr<Value> _pValueStuff;
	bool _stuffFlag;
public:
	Iterator_Align(Iterator* pIteratorSrc, size_t cnt, Value* pValueStuff) :
		_pIteratorSrc(pIteratorSrc), _cnt(cnt), _pValueStuff(pValueStuff), _stuffFlag(false) {}
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _cnt; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Head
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Head : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Head");
private:
	RefPtr<Iterator> _pIteratorSrc;
	Int _cnt;
	bool _doneFlag;
public:
	Iterator_Head(Iterator* pIteratorSrc, Int cnt) : _pIteratorSrc(pIteratorSrc), _cnt(cnt), _doneFlag(false) {}
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override {
		return std::min(GetIteratorSrc().GetLength(), static_cast<size_t>(_cnt));
	}
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Uniq
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Uniq : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Uniq");
private:
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Value> _pValuePrev;
	bool _doneFlag;
public:
	Iterator_Uniq(Iterator* pIteratorSrc) : _pIteratorSrc(pIteratorSrc), _pValuePrev(Value::undefined()), _doneFlag(false) {}
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIteratorSrc().GetFlags() & Flag::Finite; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_RunLength
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_RunLength : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_RunLength");
private:
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Value> _pValuePrev;
	bool _doneFlag;
	size_t _cnt;
public:
	Iterator_RunLength(Iterator* pIteratorSrc) : _pIteratorSrc(pIteratorSrc), _doneFlag(false), _cnt(0) {}
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return GetIteratorSrc().GetFlags() & Flag::Finite; }
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Offset
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Offset : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Offset");
private:
	RefPtr<Iterator> _pIteratorSrc;
	Int _offset;
	bool _raiseFlag;
	bool _firstFlag;
public:
	Iterator_Offset(Iterator* pIteratorSrc, Int offset, bool raiseFlag) :
		_pIteratorSrc(pIteratorSrc), _offset(offset), _raiseFlag(raiseFlag), _firstFlag(true) {}
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return GetIteratorSrc().GetFlags() & (Flag::Finite | Flag::LenDetermined);
	}
	virtual size_t GetLength() const override {
		if (!GetIteratorSrc().IsLenDetermined()) return -1;
		size_t len = GetIteratorSrc().GetLength();
		return (len < static_cast<size_t>(_offset))? 0 : len - _offset;
	}
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_PingPong
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_PingPong : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_PingPong");
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
private:
	RefPtr<ValueOwner> _pValueOwner;
	Int _cnt;
	bool _stickyFlagTop, _stickyFlagBtm;
	size_t _idx;
	bool _forwardFlag;
public:
	Iterator_PingPong(ValueOwner* pValueOwner, Int cnt, bool stickyFlagTop, bool stickyFlagBtm) :
		_pValueOwner(pValueOwner), _cnt(cnt), _stickyFlagTop(stickyFlagTop), _stickyFlagBtm(stickyFlagBtm),
		_idx(0), _forwardFlag(true) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (_cnt < 0)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
	}
	virtual size_t GetLength() const override { return (_cnt < 0)? -1 : _cnt; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Fold
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Fold : public Iterator {
private:
	RefPtr<Iterator> _pIteratorSrc;
	size_t _nSize;
	size_t _nAdvance;
	bool _itemAsIterFlag;
	bool _neatFlag;
	RefPtr<ValueOwner> _pValueOwnerRemain;
	bool _doneFlag;
public:
	Iterator_Fold(Iterator* pIteratorSrc, size_t nSize, size_t nAdvance,
				bool itemAsIterFlag, bool neatFlag);
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return GetIteratorSrc().GetFlags() & (Flag::Finite | Flag::LenDetermined);
	}
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Flatten
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Flatten : public Iterator {
public:
private:
	IteratorDequeOwner _iteratorDeque;
	RefPtr<Iterator> _pIteratorCur;
	SearchMode _searchMode;
public:
	Iterator_Flatten(Iterator* pIterator, SearchMode searchMode);
public:
	Iterator& GetIteratorCur() { return *_pIteratorCur; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_SinceWithFunc
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_SinceWithFunc : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Argument> _pArgument;
	size_t _idx;
	bool _includeFirstFlag;
	bool _contFlag;
	bool _triggeredFlag;
public:
	Iterator_SinceWithFunc(Processor* pProcessor, Function* pFunction, Iterator* pIteratorSrc, bool includeFirstFlag);
protected:
	// Destructor
	virtual ~Iterator_SinceWithFunc() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Function& GetFunction() { return *_pFunction; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
	Argument& GetArgument() { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_SinceWithIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_SinceWithIter : public Iterator {
private:
	RefPtr<Iterator> _pIteratorCriteria;
	RefPtr<Iterator> _pIteratorSrc;
	bool _includeFirstFlag;
	bool _contFlag;
	bool _triggeredFlag;
public:
	Iterator_SinceWithIter(Iterator* pIteratorCriteria, Iterator* pIteratorSrc, bool includeFirstFlag);
protected:
	// Destructor
	virtual ~Iterator_SinceWithIter() = default;
public:
	Iterator& GetIteratorCriteria() { return *_pIteratorCriteria; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_UntilWithFunc
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_UntilWithFunc : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Argument> _pArgument;
	size_t _idx;
	bool _includeLastFlag;
	bool _doneFlag;
public:
	Iterator_UntilWithFunc(Processor* pProcessor, Function* pFunction, Iterator* pIteratorSrc, bool includeLastFlag);
protected:
	// Destructor
	virtual ~Iterator_UntilWithFunc() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Function& GetFunction() { return *_pFunction; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
	Argument& GetArgument() { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		//return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_UntilWithIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_UntilWithIter : public Iterator {
private:
	RefPtr<Iterator> _pIteratorCriteria;
	RefPtr<Iterator> _pIteratorSrc;
	bool _includeLastFlag;
	bool _doneFlag;
public:
	Iterator_UntilWithIter(Iterator* pIteratorCriteria, Iterator* pIteratorSrc, bool includeLastFlag);
protected:
	// Destructor
	virtual ~Iterator_UntilWithIter() = default;
public:
	Iterator& GetIteratorCriteria() { return *_pIteratorCriteria; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		//return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_WhileWithFunc
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_WhileWithFunc : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Argument> _pArgument;
	size_t _idx;
	bool _doneFlag;
public:
	Iterator_WhileWithFunc(Processor* pProcessor, Function* pFunction, Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_WhileWithFunc() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Function& GetFunction() { return *_pFunction; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
	Argument& GetArgument() { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		//return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_WhileWithIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_WhileWithIter : public Iterator {
private:
	RefPtr<Iterator> _pIteratorCriteria;
	RefPtr<Iterator> _pIteratorSrc;
	bool _doneFlag;
public:
	Iterator_WhileWithIter(Iterator* pIteratorCriteria, Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_WhileWithIter() = default;
public:
	Iterator& GetIteratorCriteria() { return *_pIteratorCriteria; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		//return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_FilterWithFunc
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_FilterWithFunc : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Argument> _pArgument;
	size_t _idx;
	bool _doneFlag;
public:
	Iterator_FilterWithFunc(Processor* pProcessor, Function* pFunction, Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_FilterWithFunc() = default;
public:
	Processor& GetProcessor() { return *_pProcessor; }
	Function& GetFunction() { return *_pFunction; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
	Argument& GetArgument() { return *_pArgument; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_FilterWithIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_FilterWithIter : public Iterator {
private:
	RefPtr<Iterator> _pIteratorCriteria;
	RefPtr<Iterator> _pIteratorSrc;
	bool _doneFlag;
public:
	Iterator_FilterWithIter(Iterator* pIteratorCriteria, Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_FilterWithIter() = default;
public:
	Iterator& GetIteratorCriteria() { return *_pIteratorCriteria; }
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_SkipNil
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_SkipNil : public Iterator {
private:
	RefPtr<Iterator> _pIteratorSrc;
	bool _doneFlag;
public:
	Iterator_SkipNil(Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_SkipNil() = default;
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_SkipFalse
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_SkipFalse : public Iterator {
private:
	RefPtr<Iterator> _pIteratorSrc;
	bool _doneFlag;
public:
	Iterator_SkipFalse(Iterator* pIteratorSrc);
protected:
	// Destructor
	virtual ~Iterator_SkipFalse() = default;
public:
	Iterator& GetIteratorSrc() { return *_pIteratorSrc; }
	const Iterator& GetIteratorSrc() const { return *_pIteratorSrc; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return (GetIteratorSrc().GetFlags() & Flag::Finite) | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Permutation
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Permutation : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Permutation");
private:
	RefPtr<ValueOwner> _pValueOwner;
	NumList<size_t> _indices;
	bool _doneFlag;
public:
	Iterator_Permutation(ValueOwner* pValueOwner) :
		_pValueOwner(pValueOwner), _doneFlag(false) {
		_indices.FillSeq(GetValueOwner().size());
	}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetValueOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_PartialPermutation
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_PartialPermutation : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_PartialPermutation");
private:
	RefPtr<ValueOwner> _pValueOwner;
	size_t _nExtract;
	bool _doneFlag;
	NumList<size_t> _indices;
public:
	Iterator_PartialPermutation(ValueOwner* pValueOwner, size_t nExtract) :
		_pValueOwner(pValueOwner), _nExtract(nExtract), _doneFlag(false) {
		_indices.FillSeq(GetValueOwner().size());
	}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetValueOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Combination
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Combination : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Combination");
private:
	RefPtr<ValueOwner> _pValueOwner;
	size_t _nExtract;
	bool _doneFlag;
	NumList<size_t> _indices;
public:
	Iterator_Combination(ValueOwner* pValueOwner, size_t nExtract) :
		_pValueOwner(pValueOwner), _nExtract(nExtract), _doneFlag(false) {
		_indices.FillSeq(GetValueOwner().size());
	}
public:
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetValueOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_Symbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Symbol : public Iterator {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Iterator_Symbol");
private:
	SymbolList _symbolList;
	size_t _idx;
public:
	Iterator_Symbol() : _idx(0) {}
	Iterator_Symbol(SymbolList symbolList) : _symbolList(symbolList), _idx(0) {}
public:
	SymbolList& GetSymbolList() { return _symbolList; }
	const SymbolList& GetSymbolList() const { return _symbolList; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
	virtual size_t GetLength() const override { return GetSymbolList().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
