//==============================================================================
// Iterators.h
//==============================================================================
#ifndef GURAX_ITERATORS_H
#define GURAX_ITERATORS_H
#include "Iterator.h"

namespace Gurax {

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
		return Flag::Infinite | Flag::LenUndetermined;
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
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _num; }
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
	const Operator* _pOperator;
	const OpEntry* _pOpEntry;
	RefPtr<Value> _pValue;
	const VType* _pVTypePrev;
	Flags _flags;
	size_t _len;
public:
	Iterator_UnaryOpImpMap(Processor* pProcessor, const Operator* pOperator, Value* pValue);
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
	const Operator* _pOperator;
	const OpEntry* _pOpEntry;
	RefPtr<Value> _pValueL;
	RefPtr<Value> _pValueR;
	const VType* _pVTypePrevL;
	const VType* _pVTypePrevR;
	Flags _flags;
	size_t _len;
public:
	Iterator_BinaryOpImpMap(Processor* pProcessor, const Operator* pOperator, Value* pValueL, Value* pValueR);
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
class GURAX_DLLDECLARE Iterator_FunctionImpMap : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFunction;
	RefPtr<Argument> _pArgument;
	Flags _flags;
	size_t _len;
public:
	Iterator_FunctionImpMap(Processor* pProcessor, Function* pFunction, Argument* pArgument);
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
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return (_idxEnd - _idxBegin) / _idxStep; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_MemberMapToIter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_MemberMapToIter : public Iterator {
private:
	RefPtr<Iterator> _pIteratorTarget;
	const Symbol* _pSymbol;
	RefPtr<Attribute> _pAttr;
public:
	Iterator_MemberMapToIter(Iterator* pIteratorTarget, const Symbol* pSymbol, Attribute* pAttr) :
		_pIteratorTarget(pIteratorTarget), _pSymbol(pSymbol), _pAttr(pAttr) {}
public:
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
// Iterator_Evaluator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Evaluator : public Iterator {
private:
	RefPtr<Processor> _pProcessor;
	RefPtr<Iterator> _pIterator;
	RefPtr<Argument> _pArgument;
public:
	Iterator_Evaluator(Processor* pProcessor, Iterator* pIterator, Argument* pArgument) :
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

}

#endif
