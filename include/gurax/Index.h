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
public:
	// Constructor
	Index(Value* pValueCar, Attribute* pAttr) : _pValueCar(pValueCar), _pAttr(pAttr) {}
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
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Index& index) const { return this == &index; }
	bool IsEqualTo(const Index& index) const { return IsIdentical(index); }
	bool IsLessThan(const Index& index) const { return this < &index; }
	String ToString(const StringStyle& ss) const;
};

}

#endif

