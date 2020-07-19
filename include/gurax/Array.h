//==============================================================================
// Array.h
//==============================================================================
#ifndef GURAX_ARRAY_H
#define GURAX_ARRAY_H
#include "Referable.h"
#include "Symbols.h"
#include "Memory.h"
#include "Number.h"

namespace Gurax {

class Iterator;
class Value;
class ValueList;
class ValueOwner;
class Value_List;

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
		std::function<void (void* p, size_t idx, const Value& value)> IndexSet;
		std::function<Value* (const void* p, size_t idx)> IndexGet;
		std::function<void (const ValueList& values, void* p, size_t offset, size_t len)> InjectFromValueList;
		std::function<bool (Iterator& iterator, void* p, size_t offset, size_t len)> InjectFromIterator;
		std::function<void (ValueOwner& values, const void* p, size_t offset, size_t len)> ExtractToValueOwner;
		std::function<void (void* pDst, const void* pSrc, size_t offset, size_t len)> CopyElems[ElemTypeIdMax];
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
	using MapSymbolToElemType = std::unordered_map<
			const Symbol*, ElemTypeT*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	class GURAX_DLLDECLARE DimSizes : public NumList<size_t> {
	public:
		using NumList::NumList;
	public:
		DimSizes(const NumList& src) : NumList(src) {}
		DimSizes(NumList&& src) : NumList(src) {}
	public:
		size_t GetLength() const;
		String ToString(const StringStyle& ss) const;
	};
protected:
	ElemTypeT& _elemType;
	RefPtr<Memory> _pMemory;
	DimSizes _dimSizes;
protected:
	static MapSymbolToElemType _mapSymbolToElemType;
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
	ElemTypeT& GetElemType() const { return _elemType; }
	Memory& GetMemory() { return *_pMemory; }
	const Memory& GetMemory() const { return *_pMemory; }
	const DimSizes& GetDimSizes() const { return _dimSizes; }
	template<typename T> T* GetPointerC() { return _pMemory->GetPointerC<T>(); }
	template<typename T> T* GetPointerC(size_t offset) { return _pMemory->GetPointerC<T>(offset); }
	template<typename T> const T* GetPointerC() const { return _pMemory->GetPointerC<T>(); }
	template<typename T> const T* GetPointerC(size_t offset) const { return _pMemory->GetPointerC<T>(offset); }
public:
	void IndexSet(size_t idx, const Value& value) {
		_elemType.IndexSet(GetPointerC<void>(), idx, value);
	}
	Value* IndexGet(size_t idx) const {
		return _elemType.IndexGet(GetPointerC<void>(), idx);
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
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Array& other) const { return this == &other; }
	bool IsEqualTo(const Array& other) const { return IsIdentical(other); }
	bool IsLessThan(const Array& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
