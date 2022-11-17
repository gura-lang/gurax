//==============================================================================
// VType_Attribute.h
//==============================================================================
#ifndef GURAX_VTYPE_ATTRIBUTE_H
#define GURAX_VTYPE_ATTRIBUTE_H
#include "VType_Object.h"
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Attribute : public VType {
public:
	class GURAX_DLLDECLARE Iterator_Each : public Iterator {
	public:
		// Uses MemoryPool allocator
		Gurax_MemoryPoolAllocator("Iterator_Each");
	private:
		RefPtr<Attribute> _pAttr;
		const SymbolList& _symbolList;
		size_t _idx;
	public:
		Iterator_Each(Attribute* pAttr, const SymbolList& symbolList) :
						_pAttr(pAttr), _symbolList(symbolList), _idx(0) {}
	public:
		const SymbolList& GetSymbolList() const { return _symbolList; }
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override { return Flag::Finite | Flag::LenDetermined; }
		virtual size_t GetLength() const override { return GetSymbolList().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Attribute VTYPE_Attribute;

//------------------------------------------------------------------------------
// Value_Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Attribute : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Attribute);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Attribute");
protected:
	RefPtr<Attribute> _pAttr;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Attribute() = delete;
	explicit Value_Attribute(Attribute* pAttr, VType& vtype = VTYPE_Attribute) :
		Value_Object(vtype), _pAttr(pAttr) {}
	// Copy constructor/operator
	Value_Attribute(const Value_Attribute& src) : Value_Object(src), _pAttr(src._pAttr->Reference()) {}
	Value_Attribute& operator=(const Value_Attribute& src) = delete;
	// Move constructor/operator
	Value_Attribute(Value_Attribute&& src) = delete;
	Value_Attribute& operator=(Value_Attribute&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Attribute() = default;
public:
	Attribute& GetAttr() { return *_pAttr; }
	const Attribute& GetAttr() const { return *_pAttr; }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetAttr().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetAttr().IsEqualTo(dynamic_cast<const Value_Attribute&>(value).GetAttr());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetAttr().IsLessThan(dynamic_cast<const Value_Attribute&>(value).GetAttr()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
