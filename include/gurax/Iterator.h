//==============================================================================
// Iterator.h
//==============================================================================
#ifndef GURAX_ITERATOR_H
#define GURAX_ITERATOR_H
#include "Help.h"
#include "DeclCallable.h"
#include "Value.h"

namespace Gurax {

class Binary;
class Processor;
class ValueOwner;

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Iterator);
public:
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None				= 0;
		static const Flags Infinite			= (0 << 0);
		static const Flags Finite			= (1 << 0);
		static const Flags LenUndetermined	= (0 << 1);
		static const Flags LenDetermined	= (1 << 1);
		static const Flags Rewindable		= (1 << 2);
		static const Flags Unrewindable		= (0 << 2);
	};
protected:
	Int _idxCur;
	Int _idxNext;
	RefPtr<Value> _pValuePeeked;
public:
	static RefPtr<Iterator> Empty;
public:
	// Constructor
	Iterator() : _idxCur(-1), _idxNext(0) {}
	// Copy constructor/operator
	Iterator(const Iterator& src) = delete;
	Iterator& operator=(const Iterator& src) = delete;
	// Move constructor/operator
	Iterator(Iterator&& src) = delete;
	Iterator& operator=(Iterator&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Iterator() = default;
public:
	static void Bootup();
public:
	template<typename T_Compare> Value* FindMinMax();
	template<typename T_Compare> Value* FindMinMax(Int* pIdxFound);
	template<typename T_Compare> Value* FindMinMax(NumList<Int>& idxFoundList);
public:
	Flags GetFlags(Flags flags) const { return GetFlags() & flags; }
	Int GetIdxCur() const { return _idxCur; }
	Int GetIdxNext() const { return _idxNext; }
	bool IsVirgin() const { return _idxCur < 0; }
	bool IsInfinite() const { return GetFlags(Flag::Finite) == 0; }
	bool IsFinite() const { return GetFlags(Flag::Finite) != 0; }
	bool MustBeFinite() const;
	bool IsLenUndetermined() const { return GetFlags(Flag::LenDetermined) == 0; }
	bool IsLenDetermined() const { return GetFlags(Flag::LenDetermined) != 0; }
	bool IsRewindable() const { return GetFlags(Flag::Rewindable) != 0; }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Iterator& iterator) const { return this == &iterator; }
	bool IsEqualTo(const Iterator& iterator) const { return IsIdentical(iterator); }
	bool IsLessThan(const Iterator& iterator) const { return this < &iterator; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	Value* And();
	bool Contains(const Value& value);
	size_t Count(const Value& value);
	size_t CountFalse();
	size_t CountTrue();
	size_t CountIf(Processor& processor, const Function& function);
	Value* Each(Processor& processor, const Expr_Block& exprOfBlock, DeclCallable::Flags flags);
	void Join(String& str, const char* sep, const StringStyle& ss = StringStyle::Empty);
	bool Joinb(Binary& buff);
	Value* Mean(Processor& processor);
	Value* Or();
	Value* Prod(Processor& processor);
	Value* Std(Processor& processor);
	Value* Sum(Processor& processor);
	Value* Sum(Processor& processor, size_t* pCnt);
	Value* Var(Processor& processor);
	ValueOwner* Tail(size_t n);
public:
	Value* NextValue() {
		_idxCur = _idxNext++;
		return _pValuePeeked? _pValuePeeked.release() : DoNextValue();
	}
	Value* PeekValue() {
		if (!_pValuePeeked) _pValuePeeked.reset(DoNextValue());
		return _pValuePeeked.Reference();
	}
	bool Skip(size_t n) {
		for (size_t i = 0; i < n; i++) {
			RefPtr<Value> pValue(NextValue());
			if (!pValue) return false;
		}
		return true;
	}
	void Rewind() {
		_idxCur = -1, _idxNext = 0;
		_pValuePeeked.reset();
		DoRewind();
	}
public:
	// Virtual functions
	virtual Flags GetFlags() const = 0;
	virtual Value* DoNextValue() = 0;
	virtual size_t GetLength() const = 0;
	virtual void DoRewind() {}
	virtual String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// IteratorList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorList : public ListBase<Iterator*> {
public:
	void Rewind();
};

//------------------------------------------------------------------------------
// IteratorOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorOwner : public IteratorList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(IteratorOwner);
protected:
	~IteratorOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// IteratorDeque
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorDeque : public std::deque<Iterator*> {
};

//------------------------------------------------------------------------------
// IteratorDequeOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorDequeOwner : public IteratorDeque {
public:
	~IteratorDequeOwner() { Clear(); }
	void Clear();
};

}

#endif
