//==============================================================================
// Index.h
//==============================================================================
#ifndef GURAX_INDEX_H
#define GURAX_INDEX_H

namespace Gurax {

//------------------------------------------------------------------------------
// Index
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Index : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Index);
private:
	RefPtr<Value> _pValueCar;
	RefPtr<Attribute> _pAttr;
	RefPtr<ValueTypedOwner> _pValueTypedOwner;
public:
	// Constructor
	Index(Value* pValueCar, Attribute* pAttr) :
		_pValueCar(pValueCar), _pAttr(pAttr), _pValueTypedOwner(new ValueTypedOwner()) {}
	// Copy constructor/operator
	Index(const Index& src) = delete;
	Index& operator=(const Index& src) = delete;
	// Move constructor/operator
	Index(Index&& src) = delete;
	Index& operator=(Index&& src) noexcept = delete;
protected:
	~Index() = default;
public:
	Value& GetValueCar() { return *_pValueCar; }
	const Value& GetValueCar() const { return *_pValueCar; }
	const Attribute& GetAttr() const { return *_pAttr; }
	ValueTypedOwner& GetValueTypedOwner() { return *_pValueTypedOwner; }
	const ValueTypedOwner& GetValueTypedOwner() const { return *_pValueTypedOwner; }
	const ValueOwner& GetValueOwner() const { return GetValueTypedOwner().GetValueOwner(); }
	void FeedValue(Value* pValue) { GetValueTypedOwner().Add(pValue); }
	Value* IndexGet() const { return GetValueCar().DoIndexGet(*this); }
	void IndexSet(Value* pValue) { GetValueCar().DoIndexSet(*this, pValue); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Index& index) const { return this == &index; }
	bool IsEqualTo(const Index& index) const { return IsIdentical(index); }
	bool IsLessThan(const Index& index) const { return this < &index; }
	String ToString(const StringStyle& ss) const;
};

}

#endif

