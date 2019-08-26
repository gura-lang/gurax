//==============================================================================
// Iterator.h
//==============================================================================
#ifndef GURAX_ITERATOR_H
#define GURAX_ITERATOR_H
#include "Help.h"
#include "DeclCallable.h"
#include "Value.h"

namespace Gurax {

class Processor;

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Iterator);
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None				= 0;
		static const Flags Infinite			= (0 << 0);
		static const Flags Finite			= (1 << 0);
		static const Flags LenUndetermined	= (0 << 1);
		static const Flags LenDetermined	= (1 << 1);
	};
protected:
	Int _idxCur;
	Int _idxNext;
	RefPtr<Value> _pValuePeeked;
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
	template<typename T_Compare> Value* FindMinMax();
	template<typename T_Compare> Value* FindMinMax(Int* pIdxFound);
	template<typename T_Compare> Value* FindMinMax(NumList<Int>& idxFoundList);
public:
	Int GetIdxCur() const { return _idxCur; }
	Int GetIdxNext() const { return _idxNext; }
	bool IsVirgin() const { return _idxCur < 0; }
	bool IsInfinite() const { return (GetFlags() & Flag::Finite) == 0; }
	bool IsFinite() const { return (GetFlags() & Flag::Finite) != 0; }
	bool MustBeFinite() const;
	bool IsLenUndetermined() const { return (GetFlags() & Flag::LenDetermined) == 0; }
	bool IsLenDetermined() const { return (GetFlags() & Flag::LenDetermined) != 0; }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Iterator& iterator) const { return this == &iterator; }
	bool IsEqualTo(const Iterator& iterator) const { return IsIdentical(iterator); }
	bool IsLessThan(const Iterator& iterator) const { return this < &iterator; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	Value* Each(Processor& processor, const Expr_Block& exprOfBlock, DeclCallable::Flags flags);
	Value* NextValue() {
		_idxCur = _idxNext++;
		return _pValuePeeked? _pValuePeeked.release() : DoNextValue();
	}
	Value* PeekValue() {
		if (!_pValuePeeked) _pValuePeeked.reset(DoNextValue());
		return _pValuePeeked.Reference();
	}
public:
	// Virtual functions
	virtual Iterator* Clone() const;
	virtual Flags GetFlags() const = 0;
	virtual Value* DoNextValue() = 0;
	virtual size_t GetLength() const = 0;
	virtual String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// IteratorList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IteratorList : public std::vector<Iterator*> {
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

}

#endif
