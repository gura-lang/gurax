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
	DimSizes(const ValueList& values);
public:
	static size_t CalcLength(const_iterator pDimSizeBegin, const_iterator pDimSizeEnd);
	size_t CalcLength() const { return CalcLength(begin(), end()); }
	bool DoesMatch(const DimSizes& dimSizes, size_t offset = 0) const;
	bool DoesMatchDot(const DimSizes& dimSizes, size_t offset = 0) const;
	size_t GetRowSize() const { return *(rbegin() + 1); }
	size_t GetColSize() const { return back(); }
	bool Verify(const ValueList& values) const;
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
		std::function<bool (void* pv, size_t idx, const Value& value)> IndexSetValue;
		std::function<bool (void* pv, size_t idx, Double num)> IndexSetDouble;
		std::function<Value* (const void* pv, size_t idx)> IndexGetValue;
		std::function<Double (const void* pv, size_t idx)> IndexGetDouble;
		std::function<void (const ValueList& values, void* pv, size_t offset, size_t len)> InjectFromValueList;
		std::function<bool (Iterator& iterator, void* pv, size_t offset, size_t len)> InjectFromIterator;
		std::function<void (ValueOwner& values, const void* pv, size_t offset, size_t len)> ExtractToValueOwner;
		std::function<void (void* pvDst, const void* pvSrc, size_t offset, size_t len)> 	CopyElems[ElemTypeIdMax];
		std::function<void (void* pvDst, size_t nRows, size_t nCols, const void* pvSrc)>	Transpose[ElemTypeIdMax];
		std::function<void (void* pvDst, const void* pvSrc, size_t len)> 					Neg_Array;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Add_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Add_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Add_ArrayComplex;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		And_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			And_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Sub_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Sub_NumberArray;
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Sub_ArrayNumber;
		std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>	Sub_ComplexArray;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Sub_ArrayComplex;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Mul_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Mul_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Mul_ArrayComplex;
		std::function<bool (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Div_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Div_NumberArray;
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Div_ArrayNumber;
		std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>	Div_ComplexArray;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Div_ArrayComplex;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Or_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			Or_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Xor_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			Xor_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Eq_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Eq_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Eq_ArrayComplex;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Ne_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Ne_ArrayNumber;
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Ne_ArrayComplex;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Lt_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Lt_ArrayNumber;
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Lt_NumberArray;
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Le_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Le_ArrayNumber;
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Le_NumberArray;
		std::function<void (void* pvRtn, size_t m, size_t n, const void* pvL, const void* pvR, size_t l)> Dot_ArrayArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t n)>		Cross_ArrayArray[ElemTypeIdMax];
	public:
		ElemTypeT(size_t id) : id(id), bytes(0), pSymbol(nullptr) {}
		bool IsNone() const;
		bool IsIdentical(const ElemTypeT& elemType) const { return this == &elemType; }
		void* FwdPointer(void* pv, int n) const { return reinterpret_cast<char*>(pv) + n * bytes; }
		const void* FwdPointer(const void* pv, int n) const { return FwdPointer(const_cast<void*>(pv), n); }
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
	static ElemTypeT* _pElemTypeRtnTbl[ElemTypeIdMax][ElemTypeIdMax];
	static MapSymbolToElemType _mapSymbolToElemType;
	static MapSymbolToElemType _mapAtSymbolToElemType;
public:
	// Constructor
	Array(ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes);
	// Copy constructor/operator
	Array(const Array& src);
	Array& operator=(const Array& src) = delete;
	// Move constructor/operator
	Array(Array&& src);
	Array& operator=(Array&& src) noexcept = delete;
protected:
	~Array() = default;
public:
	static void Bootup();
public:
	Array* Clone() const { return new Array(*this); }
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
	void InjectElems(const void* pvSrc, ElemTypeT& elemType, size_t offset, size_t len);
	void ExtractElems(ValueOwner& values, size_t offset, size_t len) const;
	void ExtractElemsSub(ValueOwner& values, size_t& offset, DimSizes::const_iterator pDimSize) const;
	void ExtractElems(ValueOwner& values) const;
public:
	Array* Transpose() const;
public:
	static Array* GenericOp(const Array& array,
		const std::function<void (void* pvRtn, const void* pv, size_t len)>& func);
	static Array* GenericOp(const Array& arrayL, const Array& arrayR,
		const std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>& func);
	static Array* GenericOp(const Array& arrayL, UInt64 numR,
		const std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>& func);
	static Array* GenericOp(UInt64 numL, const Array& arrayR,
		const std::function<void (void* pvRtn, UInt64 numL, const void* pvR, size_t len)>& func);
	static Array* GenericOp(const Array& arrayL, Double numR,
		const std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>& func);
	static Array* GenericOp(Double numL, const Array& arrayR,
		const std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>& func);
	static Array* GenericOp(const Array& arrayL, const Complex& numR,
		const std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>& func);
	static Array* GenericOp(const Complex& numL, const Array& arrayR,
		const std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>& func);
	static Array* Neg(const Array& array);
	static Array* Add(const Array& arrayL, const Array& arrayR);
	static Array* Add(const Array& arrayL, Double numR);
	static Array* Add(const Array& arrayL, const Complex& numR);
	static Array* And(const Array& arrayL, const Array& arrayR);
	static Array* And(const Array& arrayL, UInt64 numR);
	static Array* Sub(const Array& arrayL, const Array& arrayR);
	static Array* Sub(const Array& arrayL, Double numR);
	static Array* Sub(Double numL, const Array& arrayR);
	static Array* Sub(const Array& arrayL, const Complex& numR);
	static Array* Sub(const Complex& numL, const Array& arrayR);
	static Array* Mul(const Array& arrayL, const Array& arrayR);
	static Array* Mul(const Array& arrayL, Double numR);
	static Array* Mul(const Array& arrayL, const Complex& numR);
	static Array* Div(const Array& arrayL, const Array& arrayR);
	static Array* Div(const Array& arrayL, Double numR);
	static Array* Div(Double numL, const Array& arrayR);
	static Array* Div(const Array& arrayL, const Complex& numR);
	static Array* Div(const Complex& numL, const Array& arrayR);
	static Array* Or(const Array& arrayL, const Array& arrayR);
	static Array* Or(const Array& arrayL, UInt64 numR);
	static Array* Xor(const Array& arrayL, const Array& arrayR);
	static Array* Xor(const Array& arrayL, UInt64 numR);
	static Array* Eq(const Array& arrayL, const Array& arrayR);
	static Array* Eq(const Array& arrayL, Double numR);
	static Array* Eq(const Array& arrayL, const Complex& numR);
	static Array* Ne(const Array& arrayL, const Array& arrayR);
	static Array* Ne(const Array& arrayL, Double numR);
	static Array* Ne(const Array& arrayL, const Complex& numR);
	static Array* Lt(const Array& arrayL, const Array& arrayR);
	static Array* Lt(const Array& arrayL, Double numR);
	static Array* Lt(Double numL, const Array& arrayR);
	static Array* Le(const Array& arrayL, const Array& arrayR);
	static Array* Le(const Array& arrayL, Double numR);
	static Array* Le(Double numL, const Array& arrayR);
	static Array* Dot(const Array& arrayL, const Array& arrayR);
	static Array* Cross(const Array& arrayL, const Array& arrayR);
public:
	Value_List* ToList() const;
	Array* CreateCasted(ElemTypeT& elemType) const;
	void* FwdPointer(void* pv, int n) const { return GetElemType().FwdPointer(pv, n); }
	const void* FwdPointer(const void* pv, int n) const { return GetElemType().FwdPointer(pv, n); }
public:
	static ElemTypeT& SymbolToElemType(const Symbol* pSymbol) {
		return *_mapSymbolToElemType.find(pSymbol)->second;
	}
	static ElemTypeT& AtSymbolToElemType(const Symbol* pSymbol) {
		return *_mapAtSymbolToElemType.find(pSymbol)->second;
	}
public:
	static ElemTypeT& GetElemTypeRtn(ElemTypeT& elemTypeL, ElemTypeT& elemTypeR) {
		return *_pElemTypeRtnTbl[elemTypeL.id][elemTypeR.id];
	}
	static ElemTypeT& GetElemTypeRtn(const Array& arrayL, const Array& arrayR) {
		return GetElemTypeRtn(arrayL.GetElemType(), arrayR.GetElemType());
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
