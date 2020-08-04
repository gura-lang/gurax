//==============================================================================
// Array.h
//==============================================================================
#ifndef GURAX_ARRAY_H
#define GURAX_ARRAY_H
#include "Referable.h"
#include "Symbols.h"
#include "Memory.h"
#include "Number.h"
#include "Half.h"

namespace Gurax {

class Iterator;
class Value;
class ValueList;
class ValueOwner;
class Value_List;

//------------------------------------------------------------------------------
// DimSizes
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DimSizes : public NumList<size_t> {
public:
	DimSizes() {}
	DimSizes(const NumList& src) : NumList(src) {}
	DimSizes(NumList&& src) : NumList(src) {}
	DimSizes(size_t n) { reserve(1); push_back(n); }
	DimSizes(size_t m, size_t n) { reserve(2); push_back(m); push_back(n); }
	DimSizes(size_t l, size_t m, size_t n) {
		reserve(3); push_back(l); push_back(m); push_back(n);
	}
public:
	size_t GetLength() const;
	String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Array : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Array);
public:
	static const size_t ElemTypeIdMax = 13;
	class GURAX_DLLDECLARE ElemTypeT {
	public:
		size_t id;
		size_t bytes;
		const Symbol* pSymbol;
	public:
		std::function<bool (void* p, size_t idx, const Value& value)> IndexSetValue;
		std::function<bool (void* p, size_t idx, Double num)> IndexSetDouble;
		std::function<Value* (const void* p, size_t idx)> IndexGetValue;
		std::function<Double (const void* p, size_t idx)> IndexGetDouble;
		std::function<void (const ValueList& values, void* p, size_t offset, size_t len)> InjectFromValueList;
		std::function<bool (Iterator& iterator, void* p, size_t offset, size_t len)> InjectFromIterator;
		std::function<void (ValueOwner& values, const void* p, size_t offset, size_t len)> ExtractToValueOwner;
		std::function<void (void* pDst, const void* pSrc, size_t offset, size_t len)> CopyElems[ElemTypeIdMax];
		std::function<void (void* pRtn, void* pLeft, const void* pRight, size_t len)> AddElems[ElemTypeIdMax];
	public:
		ElemTypeT(size_t id) : id(id), bytes(0), pSymbol(nullptr) {}
		bool IsNone() const;
		bool IsIdentical(const ElemTypeT& elemType) const { return this == &elemType; }
	};
	struct GURAX_DLLDECLARE ElemType {
		static ElemTypeT None;
		static ElemTypeT Bool;
		static ElemTypeT Int8;
		static ElemTypeT UInt8;
		static ElemTypeT Int16;
		static ElemTypeT UInt16;
		static ElemTypeT Int32;
		static ElemTypeT UInt32;
		static ElemTypeT Int64;
		static ElemTypeT UInt64;
		static ElemTypeT Half;
		static ElemTypeT Float;
		static ElemTypeT Double;
		static ElemTypeT Complex;
	};
	enum class ElemTypePrec {
		None,
		Bool,
		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Half,
		Float,
		Double,
		Complex,
	};
	using MapSymbolToElemType = std::unordered_map<
			const Symbol*, ElemTypeT*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
protected:
	ElemTypeT& _elemType;
	RefPtr<Memory> _pMemory;
	DimSizes _dimSizes;
protected:
	static MapSymbolToElemType _mapSymbolToElemType;
	static MapSymbolToElemType _mapAtSymbolToElemType;
protected:
	// Constructor
	Array(ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes);
	// Copy constructor/operator
	Array(const Array& src) = delete;
	Array& operator=(const Array& src) = delete;
	// Move constructor/operator
	Array(Array&& src) = delete;
	Array& operator=(Array&& src) noexcept = delete;
protected:
	~Array() = default;
public:
	static void Bootup();
public:
	static Array* Create(ElemTypeT& elemType, DimSizes dimSizes);
	static Array* Create1d(ElemTypeT& elemType, size_t n) {
		return Create(elemType, DimSizes(n));
	}
	static Array* Create2d(ElemTypeT& elemType, size_t m, size_t n) {
		return Create(elemType, DimSizes(m, n));
	}
	static Array* Create3d(ElemTypeT& elemType, size_t l, size_t m, size_t n) {
		return Create(elemType, DimSizes(l, m, n));
	}
	static Array* CreateIdentity(ElemTypeT& elemType, size_t n, Double mag);
	ElemTypeT& GetElemType() const { return _elemType; }
	Memory& GetMemory() { return *_pMemory; }
	const Memory& GetMemory() const { return *_pMemory; }
	const DimSizes& GetDimSizes() const { return _dimSizes; }
	bool IsMultidemensional() const { return _dimSizes.size() > 1; }
	template<typename T> T* GetPointerC() { return _pMemory->GetPointerC<T>(); }
	template<typename T> T* GetPointerC(size_t offset) { return _pMemory->GetPointerC<T>(offset); }
	template<typename T> const T* GetPointerC() const { return _pMemory->GetPointerC<T>(); }
	template<typename T> const T* GetPointerC(size_t offset) const { return _pMemory->GetPointerC<T>(offset); }
public:
	bool IndexSetValue(size_t idx, const Value& value) {
		return _elemType.IndexSetValue(GetPointerC<void>(), idx, value);
	}
	bool IndexSetDouble(size_t idx, Double num) {
		return _elemType.IndexSetDouble(GetPointerC<void>(), idx, num);
	}
	Value* IndexGetValue(size_t idx) const {
		return _elemType.IndexGetValue(GetPointerC<void>(), idx);
	}
	Double IndexGetDouble(size_t idx) const {
		return _elemType.IndexGetDouble(GetPointerC<void>(), idx);
	}
	void InjectElems(ValueList& values, size_t offset, size_t len);
	void InjectElems(ValueList& values, size_t offset = 0);
	bool InjectElems(Iterator& iterator, size_t offset, size_t len);
	bool InjectElems(Iterator& iterator, size_t offset = 0);
	void InjectElems(const void* pSrc, ElemTypeT& elemType, size_t offset, size_t len);
	void ExtractElems(ValueOwner& values, size_t offset, size_t len) const;
	void ExtractElemsSub(ValueOwner& values, size_t& offset, DimSizes::const_iterator pDimSize) const;
	void ExtractElems(ValueOwner& values) const;
	Value_List* ToList() const;
	Array* CreateCasted(ElemTypeT& elemType) const;
public:
	static ElemTypeT& SymbolToElemType(const Symbol* pSymbol) {
		return *_mapSymbolToElemType.find(pSymbol)->second;
	}
	static ElemTypeT& AtSymbolToElemType(const Symbol* pSymbol) {
		return *_mapAtSymbolToElemType.find(pSymbol)->second;
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Array& other) const { return this == &other; }
	bool IsEqualTo(const Array& other) const { return IsIdentical(other); }
	bool IsLessThan(const Array& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
