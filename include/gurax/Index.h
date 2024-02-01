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
	RefPtr<ValueOwner> _pValueOwner;
public:
	// Constructor
	Index(Value* pValueCar, Attribute* pAttr) :
		_pValueCar(pValueCar), _pAttr(pAttr), _pValueOwner(new ValueOwner()) {}
	// Copy constructor/operator
	Index(const Index& src) = delete;
	Index& operator=(const Index& src) = delete;
	// Move constructor/operator
	Index(Index&& src) = delete;
	Index& operator=(Index&& src) noexcept = delete;
protected:
	~Index() = default;
public:
	void Reserve(size_t size) { GetValueOwner().reserve(size); }
	Value& GetValueCar() const { return *_pValueCar; }
	const Attribute& GetAttr() const { return *_pAttr; }
	ValueOwner& GetValueOwner() { return *_pValueOwner; }
	const ValueOwner& GetValueOwner() const { return *_pValueOwner; }
	void FeedValue(Value* pValue) { GetValueOwner().push_back(pValue); }
	Value* IndexGet() const { return GetValueCar().DoIndexGet(*this); }
	void IndexSet(Processor& processor, RefPtr<Value> pValue) { GetValueCar().DoIndexSet(processor, *this, pValue.release()); }
	Value* IndexOpApply(Value& value, Processor& processor, Operator& op);
	bool EachIndexGet(const Value& valueIndex, Value** ppValue) const;
	bool EachIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue) const;
public:
	static bool GetIndexNumber(const Value& valueIndex, size_t size, size_t* pIdx);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Index& index) const { return this == &index; }
	bool IsEqualTo(const Index& index) const { return IsIdentical(index); }
	bool IsLessThan(const Index& index) const { return this < &index; }
	String ToString(const StringStyle& ss) const;
};

}

#endif

