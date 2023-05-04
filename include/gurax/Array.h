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
	DimSizes(size_t l, size_t m, size_t n) { reserve(3); push_back(l); push_back(m); push_back(n); }
	DimSizes(const ValueList& values);
public:
	static size_t CalcLength(const_iterator pDimSizeBegin, const_iterator pDimSizeEnd);
	static const DimSizes* DetermineResult(const DimSizes& dimSizesL, const DimSizes& dimSizesR,
					size_t* pnUnits, size_t* pLenUnit, size_t* pLenFwdL, size_t* pLenFwdR);
	size_t CalcLength(const_iterator pDimSize) const { return CalcLength(pDimSize, end()); }
	size_t CalcLength() const { return CalcLength(begin()); }
	size_t CalcStrides(const_iterator pDimSize) const { return CalcLength(pDimSize + 1, end()); }
	size_t CalcStrides() const { return CalcLength(begin()); }
	bool IsEqual(const DimSizes& dimSizes) const;
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
		ElemTypeT(const ElemTypeT& elemType) = delete;
		ElemTypeT(size_t id) : id(id), bytes(0), pSymbol(nullptr) {}
		bool IsNone() const;
		bool IsIdentical(const ElemTypeT& elemType) const { return this == &elemType; }
		void* FwdPointer(void* pv, int n) const { return reinterpret_cast<char*>(pv) + n * bytes; }
		const void* FwdPointer(const void* pv, int n) const { return FwdPointer(const_cast<void*>(pv), n); }
		const char* GetName() const { return pSymbol->GetName(); }
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
	struct Funcs {
		std::function<bool (void* pv, size_t idx, const Value& value)>						IndexSetValue[ElemTypeIdMax];
		std::function<bool (void* pv, size_t idx, Double num)>								IndexSetDouble[ElemTypeIdMax];
		std::function<Value* (const void* pv, size_t idx)>									IndexGetValue[ElemTypeIdMax];
		std::function<Double (const void* pv, size_t idx)>									IndexGetDouble[ElemTypeIdMax];
		std::function<void (const ValueList& values, void* pv, size_t offset, size_t len)>	InjectFromValueList[ElemTypeIdMax];
		std::function<bool (Iterator& iterator, void* pv, size_t offset, size_t len)>		InjectFromIterator[ElemTypeIdMax];
		std::function<void (ValueOwner& values, const void* pv, size_t offset, size_t len)> ExtractElems[ElemTypeIdMax];
		std::function<void (const StringStyle& ss, String& str, const void* pv, size_t offset, size_t len)> ToString[ElemTypeIdMax];
		std::function<void (void* pvDst, const void* pvSrc, size_t offset, size_t len)> 	CopyElems[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvDst, size_t nRows, size_t nCols, const void* pvSrc)>	Transpose[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvDst, const void* pvSrc, size_t len)> 					Neg_Array[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Add_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Add_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Add_ArrayComplex[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		And_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			And_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Sub_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Sub_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Sub_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>	Sub_ComplexArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Sub_ArrayComplex[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Mul_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Mul_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Mul_ArrayComplex[ElemTypeIdMax];
		std::function<bool (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Div_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Div_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Div_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>	Div_ComplexArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Div_ArrayComplex[ElemTypeIdMax];
		std::function<bool (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Pow_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Pow_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Pow_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>	Pow_ComplexArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Pow_ArrayComplex[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Or_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			Or_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Xor_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>			Xor_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Eq_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Eq_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Eq_ArrayComplex[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Ne_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Ne_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>	Ne_ArrayComplex[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Lt_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Lt_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Lt_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Le_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Le_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Le_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>		Cmp_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>			Cmp_ArrayNumber[ElemTypeIdMax];
		std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>			Cmp_NumberArray[ElemTypeIdMax];
		std::function<void (void* pvRtn, size_t m, size_t n, const void* pvL, const void* pvR, size_t l)> Dot_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
		std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t n)>		Cross_ArrayArray[ElemTypeIdMax][ElemTypeIdMax];
	};
	using MapSymbolToElemType = std::unordered_map<const Symbol*, const ElemTypeT*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
protected:
	const ElemTypeT& _elemType;
	RefPtr<Memory> _pMemory;
	DimSizes _dimSizes;
public:
	static Funcs funcs;
protected:
	static const ElemTypeT* _pElemTypeRtnForArithmTbl[ElemTypeIdMax][ElemTypeIdMax];
	static MapSymbolToElemType _mapSymbolToElemType;
	static MapSymbolToElemType _mapAtSymbolToElemType;
public:
	// Constructor
	Array(const ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes);
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
	static Array* Create(const ElemTypeT& elemType, Memory* pMemory, DimSizes dimSizes);
	static Array* Create(const ElemTypeT& elemType, DimSizes dimSizes);
	static Array* CreateScalar(const ElemTypeT& elemType, Double num);
	static Array* CreateScalar(const ElemTypeT& elemType, const Complex& num);
	static Array* Create1d(const ElemTypeT& elemType, size_t n) { return Create(elemType, DimSizes(n)); }
	static Array* Create2d(const ElemTypeT& elemType, size_t m, size_t n) { return Create(elemType, DimSizes(m, n)); }
	static Array* Create3d(const ElemTypeT& elemType, size_t l, size_t m, size_t n) { return Create(elemType, DimSizes(l, m, n)); }
	static Array* CreateIdentity(const ElemTypeT& elemType, size_t n, Double mag);
	Array* Reshape(const ValueList& values) const;
	const ElemTypeT& GetElemType() const { return _elemType; }
	bool IsElemType(const ElemTypeT& elemType) const { return _elemType.IsIdentical(elemType); }
	Memory& GetMemory() { return *_pMemory; }
	const Memory& GetMemory() const { return *_pMemory; }
	const DimSizes& GetDimSizes() const { return _dimSizes; }
	bool IsMultidemensional() const { return _dimSizes.size() > 1; }
	bool HasSameShape(const Array& array) const { return _dimSizes.IsEqual(array.GetDimSizes()); }
	template<typename T> T* GetPointerC() { return _pMemory->GetPointerC<T>(); }
	template<typename T> T* GetPointerC(size_t offset) { return _pMemory->GetPointerC<T>(offset); }
	template<typename T> const T* GetPointerC() const { return _pMemory->GetPointerC<T>(); }
	template<typename T> const T* GetPointerC(size_t offset) const { return _pMemory->GetPointerC<T>(offset); }
public:
	bool IsArray() const { return !_dimSizes.empty(); }
	bool IsScalar() const { return _dimSizes.empty(); }
	bool IsScalarNumber() const { return _dimSizes.empty() && !IsElemType(ElemType::Complex); }
	bool IsScalarComplex() const { return _dimSizes.empty() && IsElemType(ElemType::Complex); }
	Double GetScalarDouble() const { return funcs.IndexGetDouble[_elemType.id](GetPointerC<void>(), 0); }
	UInt64 GetScalarUInt64() const { return static_cast<UInt64>(funcs.IndexGetDouble[_elemType.id](GetPointerC<void>(), 0)); }
	const Complex& GetScalarComplex() const { return *GetPointerC<Complex>(); }
public:
	bool IndexSetValue(size_t idx, const Value& value) { return funcs.IndexSetValue[_elemType.id](GetPointerC<void>(), idx, value); }
	bool IndexSetDouble(size_t idx, Double num) { return funcs.IndexSetDouble[_elemType.id](GetPointerC<void>(), idx, num); }
	Value* IndexGetValue(size_t idx) const { return funcs.IndexGetValue[_elemType.id](GetPointerC<void>(), idx); }
	Double IndexGetDouble(size_t idx) const { return funcs.IndexGetDouble[_elemType.id](GetPointerC<void>(), idx); }
	void InjectElems(ValueList& values, size_t offset, size_t len);
	void InjectElems(ValueList& values, size_t offset = 0);
	bool InjectElems(Iterator& iterator, size_t offset, size_t len);
	bool InjectElems(Iterator& iterator, size_t offset = 0);
	void InjectElems(const void* pvSrc, const ElemTypeT& elemType, size_t offset, size_t len);
	void ExtractElems(ValueOwner& values, size_t offset, size_t len) const;
	void ExtractElemsSub(ValueOwner& values, size_t& offset, DimSizes::const_iterator pDimSize) const;
	void ExtractElems(ValueOwner& values) const;
	void ToString(const StringStyle& ss, String& str, size_t offset, size_t len) const;
	void ToStringSub(const StringStyle& ss, String& str, size_t& offset, DimSizes::const_iterator pDimSize) const;
	void ToString(const StringStyle& ss, String& str) const;
public:
	bool Transpose(RefPtr<Array>& pArrayRtn) const;
public:
	static bool GenericUnaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& array,
		const std::function<void (void* pvRtn, const void* pv, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, const Array& arrayR,
		const std::function<void (void* pvRtn, const void* pvL, const void* pvR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, UInt64 numR,
		const std::function<void (void* pvRtn, const void* pvL, UInt64 numR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, UInt64 numL, const Array& arrayR,
		const std::function<void (void* pvRtn, UInt64 numL, const void* pvR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, Double numR,
		const std::function<void (void* pvRtn, const void* pvL, Double numR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, Double numL, const Array& arrayR,
		const std::function<void (void* pvRtn, Double numL, const void* pvR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Array& arrayL, const Complex& numR,
		const std::function<void (void* pvRtn, const void* pvL, const Complex& numR, size_t len)>& func);
	static bool GenericBinaryOp(RefPtr<Array>& pArrayRtn, const ElemTypeT& elemTypeRtn, const Complex& numL, const Array& arrayR,
		const std::function<void (void* pvRtn, const Complex& numL, const void* pvR, size_t len)>& func);
	static bool Neg(RefPtr<Array>& pArrayRtn, const Array& array);
	static bool Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Add(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool And(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool And(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR);
	static bool Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Sub(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Sub(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Sub(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR);
	static bool Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Mul(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Div(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Div(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Div(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR);
	static bool Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Pow(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Pow(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Pow(RefPtr<Array>& pArrayRtn, const Complex& numL, const Array& arrayR);
	static bool Or(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Or(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR);
	static bool Xor(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Xor(RefPtr<Array>& pArrayRtn, const Array& arrayL, UInt64 numR);
	static bool Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Eq(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Ne(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Complex& numR);
	static bool Lt(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Lt(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Lt(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Le(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Le(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Le(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Cmp(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Cmp(RefPtr<Array>& pArrayRtn, const Array& arrayL, Double numR);
	static bool Cmp(RefPtr<Array>& pArrayRtn, Double numL, const Array& arrayR);
	static bool Dot(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
	static bool Cross(RefPtr<Array>& pArrayRtn, const Array& arrayL, const Array& arrayR);
public:
	Value_List* ToList() const;
	Value* ToValue() const;
	Array* CreateLike() const;
	Array* CreateCasted(const ElemTypeT& elemType) const;
	void* FwdPointer(void* pv, int n) const { return GetElemType().FwdPointer(pv, n); }
	const void* FwdPointer(const void* pv, int n) const { return GetElemType().FwdPointer(pv, n); }
public:
	static const ElemTypeT& SymbolToElemType(const Symbol* pSymbol);
	static const ElemTypeT& AtSymbolToElemType(const Symbol* pSymbol);
public:
	static const ElemTypeT& GetElemTypeRtnForArithm(const ElemTypeT& elemTypeL, const ElemTypeT& elemTypeR) {
		return *_pElemTypeRtnForArithmTbl[elemTypeL.id][elemTypeR.id];
	}
	static const ElemTypeT& GetElemTypeRtnForArithm(const Array& arrayL, const Array& arrayR) {
		return GetElemTypeRtnForArithm(arrayL.GetElemType(), arrayR.GetElemType());
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Array& other) const { return this == &other; }
	bool IsEqualTo(const Array& other) const { return IsIdentical(other); }
	bool IsLessThan(const Array& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#define Gurax_SetArrayFuncSingle(func, funcTmpl) do { \
	func[Array::ElemType::Bool.id]						= funcTmpl<Bool>; \
	func[Array::ElemType::Int8.id]						= funcTmpl<Int8>; \
	func[Array::ElemType::UInt8.id]						= funcTmpl<UInt8>; \
	func[Array::ElemType::Int16.id]						= funcTmpl<Int16>; \
	func[Array::ElemType::UInt16.id]					= funcTmpl<UInt16>; \
	func[Array::ElemType::Int32.id]						= funcTmpl<Int32>; \
	func[Array::ElemType::UInt32.id]					= funcTmpl<UInt32>; \
	func[Array::ElemType::Int64.id]						= funcTmpl<Int64>; \
	func[Array::ElemType::UInt64.id]					= funcTmpl<UInt64>; \
	func[Array::ElemType::Half.id]						= funcTmpl<Half>; \
	func[Array::ElemType::Float.id]						= funcTmpl<Float>; \
	func[Array::ElemType::Double.id]					= funcTmpl<Double>; \
	func[Array::ElemType::Complex.id]					= funcTmpl<Complex>; \
} while (0)

#define Gurax_SetArrayFuncDouble(func, funcTmpl) do { \
	func[Array::ElemType::Bool.id][Array::ElemType::Bool.id]		= funcTmpl<Bool, Bool>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Bool.id]		= funcTmpl<Int8, Bool>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Bool.id]		= funcTmpl<UInt8, Bool>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Bool.id]		= funcTmpl<Int16, Bool>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Bool.id]		= funcTmpl<UInt16, Bool>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Bool.id]		= funcTmpl<Int32, Bool>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Bool.id]		= funcTmpl<UInt32, Bool>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Bool.id]		= funcTmpl<Int64, Bool>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Bool.id]		= funcTmpl<UInt64, Bool>; \
	func[Array::ElemType::Half.id][Array::ElemType::Bool.id]		= funcTmpl<Half, Bool>; \
	func[Array::ElemType::Float.id][Array::ElemType::Bool.id]		= funcTmpl<Float, Bool>; \
	func[Array::ElemType::Double.id][Array::ElemType::Bool.id]		= funcTmpl<Double, Bool>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Bool.id]		= funcTmpl<Complex, Bool>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int8.id]		= funcTmpl<Bool, Int8>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int8.id]		= funcTmpl<Int8, Int8>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int8.id]		= funcTmpl<UInt8, Int8>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int8.id]		= funcTmpl<Int16, Int8>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int8.id]		= funcTmpl<UInt16, Int8>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int8.id]		= funcTmpl<Int32, Int8>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int8.id]		= funcTmpl<UInt32, Int8>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int8.id]		= funcTmpl<Int64, Int8>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int8.id]		= funcTmpl<UInt64, Int8>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int8.id]		= funcTmpl<Half, Int8>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int8.id]		= funcTmpl<Float, Int8>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int8.id]		= funcTmpl<Double, Int8>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int8.id]		= funcTmpl<Complex, Int8>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt8.id]		= funcTmpl<Bool, UInt8>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt8.id]		= funcTmpl<Int8, UInt8>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt8, UInt8>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt8.id]		= funcTmpl<Int16, UInt8>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt16, UInt8>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt8.id]		= funcTmpl<Int32, UInt8>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt32, UInt8>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt8.id]		= funcTmpl<Int64, UInt8>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt64, UInt8>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt8.id]		= funcTmpl<Half, UInt8>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt8.id]		= funcTmpl<Float, UInt8>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt8.id]		= funcTmpl<Double, UInt8>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt8.id]	= funcTmpl<Complex, UInt8>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int16.id]		= funcTmpl<Bool, Int16>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int16.id]		= funcTmpl<Int8, Int16>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int16.id]		= funcTmpl<UInt8, Int16>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int16.id]		= funcTmpl<Int16, Int16>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int16.id]		= funcTmpl<UInt16, Int16>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int16.id]		= funcTmpl<Int32, Int16>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int16.id]		= funcTmpl<UInt32, Int16>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int16.id]		= funcTmpl<Int64, Int16>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int16.id]		= funcTmpl<UInt64, Int16>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int16.id]		= funcTmpl<Half, Int16>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int16.id]		= funcTmpl<Float, Int16>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int16.id]		= funcTmpl<Double, Int16>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int16.id]	= funcTmpl<Complex, Int16>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt16.id]		= funcTmpl<Bool, UInt16>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt16.id]		= funcTmpl<Int8, UInt16>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt16.id]		= funcTmpl<UInt8, UInt16>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt16.id]		= funcTmpl<Int16, UInt16>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt16, UInt16>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt16.id]		= funcTmpl<Int32, UInt16>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt32, UInt16>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt16.id]		= funcTmpl<Int64, UInt16>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt64, UInt16>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt16.id]		= funcTmpl<Half, UInt16>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt16.id]		= funcTmpl<Float, UInt16>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt16.id]	= funcTmpl<Double, UInt16>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt16.id]	= funcTmpl<Complex, UInt16>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int32.id]		= funcTmpl<Bool, Int32>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int32.id]		= funcTmpl<Int8, Int32>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int32.id]		= funcTmpl<UInt8, Int32>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int32.id]		= funcTmpl<Int16, Int32>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int32.id]		= funcTmpl<UInt16, Int32>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, Int32>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int32.id]		= funcTmpl<UInt32, Int32>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int32.id]		= funcTmpl<Int64, Int32>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int32.id]		= funcTmpl<UInt64, Int32>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int32.id]		= funcTmpl<Half, Int32>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int32.id]		= funcTmpl<Float, Int32>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int32.id]		= funcTmpl<Double, Int32>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int32.id]	= funcTmpl<Complex, Int32>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt32.id]		= funcTmpl<Bool, UInt32>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt32.id]		= funcTmpl<Int8, UInt32>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt8, UInt32>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt32.id]		= funcTmpl<Int16, UInt32>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt16, UInt32>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt32.id]		= funcTmpl<Int32, UInt32>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt32, UInt32>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt32.id]		= funcTmpl<Int64, UInt32>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt64, UInt32>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt32.id]		= funcTmpl<Half, UInt32>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt32.id]		= funcTmpl<Float, UInt32>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt32.id]	= funcTmpl<Double, UInt32>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt32.id]	= funcTmpl<Complex, UInt32>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int64.id]		= funcTmpl<Bool, Int64>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int64.id]		= funcTmpl<Int8, Int64>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int64.id]		= funcTmpl<UInt8, Int64>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int64.id]		= funcTmpl<Int16, Int64>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int64.id]		= funcTmpl<UInt16, Int64>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int64.id]		= funcTmpl<Int32, Int64>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int64.id]		= funcTmpl<UInt32, Int64>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Int64>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int64.id]		= funcTmpl<UInt64, Int64>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int64.id]		= funcTmpl<Half, Int64>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int64.id]		= funcTmpl<Float, Int64>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int64.id]		= funcTmpl<Double, Int64>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int64.id]	= funcTmpl<Complex, Int64>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt64.id]		= funcTmpl<Bool, UInt64>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt64.id]		= funcTmpl<Int8, UInt64>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt8, UInt64>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt64.id]		= funcTmpl<Int16, UInt64>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt16, UInt64>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt64.id]		= funcTmpl<Int32, UInt64>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt32, UInt64>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt64.id]		= funcTmpl<Int64, UInt64>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt64, UInt64>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt64.id]		= funcTmpl<Half, UInt64>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt64.id]		= funcTmpl<Float, UInt64>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt64.id]	= funcTmpl<Double, UInt64>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt64.id]	= funcTmpl<Complex, UInt64>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Half.id]		= funcTmpl<Bool, Half>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Half.id]		= funcTmpl<Int8, Half>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Half.id]		= funcTmpl<UInt8, Half>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Half.id]		= funcTmpl<Int16, Half>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Half.id]		= funcTmpl<UInt16, Half>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Half.id]		= funcTmpl<Int32, Half>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Half.id]		= funcTmpl<UInt32, Half>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Half.id]		= funcTmpl<Int64, Half>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Half.id]		= funcTmpl<UInt64, Half>; \
	func[Array::ElemType::Half.id][Array::ElemType::Half.id]		= funcTmpl<Half, Half>; \
	func[Array::ElemType::Float.id][Array::ElemType::Half.id]		= funcTmpl<Float, Half>; \
	func[Array::ElemType::Double.id][Array::ElemType::Half.id]		= funcTmpl<Double, Half>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Half.id]		= funcTmpl<Complex, Half>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Float.id]		= funcTmpl<Bool, Float>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Float.id]		= funcTmpl<Int8, Float>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Float.id]		= funcTmpl<UInt8, Float>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Float.id]		= funcTmpl<Int16, Float>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Float.id]		= funcTmpl<UInt16, Float>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Float.id]		= funcTmpl<Int32, Float>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Float.id]		= funcTmpl<UInt32, Float>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Float.id]		= funcTmpl<Int64, Float>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Float.id]		= funcTmpl<UInt64, Float>; \
	func[Array::ElemType::Half.id][Array::ElemType::Float.id]		= funcTmpl<Half, Float>; \
	func[Array::ElemType::Float.id][Array::ElemType::Float.id]		= funcTmpl<Float, Float>; \
	func[Array::ElemType::Double.id][Array::ElemType::Float.id]		= funcTmpl<Double, Float>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Float.id]	= funcTmpl<Complex, Float>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Double.id]		= funcTmpl<Bool, Double>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Double.id]		= funcTmpl<Int8, Double>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Double.id]		= funcTmpl<UInt8, Double>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Double.id]		= funcTmpl<Int16, Double>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Double.id]	= funcTmpl<UInt16, Double>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Double.id]		= funcTmpl<Int32, Double>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Double.id]	= funcTmpl<UInt32, Double>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Double.id]		= funcTmpl<Int64, Double>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Double.id]	= funcTmpl<UInt64, Double>; \
	func[Array::ElemType::Half.id][Array::ElemType::Double.id]		= funcTmpl<Half, Double>; \
	func[Array::ElemType::Float.id][Array::ElemType::Double.id]		= funcTmpl<Float, Double>; \
	func[Array::ElemType::Double.id][Array::ElemType::Double.id]	= funcTmpl<Double, Double>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Double.id]	= funcTmpl<Complex, Double>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Complex.id]		= funcTmpl<Bool, Complex>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Complex.id]		= funcTmpl<Int8, Complex>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Complex.id]	= funcTmpl<UInt8, Complex>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Complex.id]	= funcTmpl<Int16, Complex>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Complex.id]	= funcTmpl<UInt16, Complex>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Complex.id]	= funcTmpl<Int32, Complex>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Complex.id]	= funcTmpl<UInt32, Complex>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Complex.id]	= funcTmpl<Int64, Complex>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Complex.id]	= funcTmpl<UInt64, Complex>; \
	func[Array::ElemType::Half.id][Array::ElemType::Complex.id]		= funcTmpl<Half, Complex>; \
	func[Array::ElemType::Float.id][Array::ElemType::Complex.id]	= funcTmpl<Float, Complex>; \
	func[Array::ElemType::Double.id][Array::ElemType::Complex.id]	= funcTmpl<Double, Complex>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Complex>; \
} while (0)

#define Gurax_SetArrayFuncArithm(func, funcTmpl) do { \
	func[Array::ElemType::Bool.id][Array::ElemType::Bool.id]		= funcTmpl<Bool, Bool, Bool>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Bool.id]		= funcTmpl<Int8, Int8, Bool>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Bool.id]		= funcTmpl<UInt8, UInt8, Bool>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Bool.id]		= funcTmpl<Int16, Int16, Bool>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Bool.id]		= funcTmpl<UInt16, UInt16, Bool>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Bool.id]		= funcTmpl<Int32, Int32, Bool>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Bool.id]		= funcTmpl<UInt32, UInt32, Bool>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Bool.id]		= funcTmpl<Int64, Int64, Bool>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Bool.id]		= funcTmpl<UInt64, UInt64, Bool>; \
	func[Array::ElemType::Half.id][Array::ElemType::Bool.id]		= funcTmpl<Half, Half, Bool>; \
	func[Array::ElemType::Float.id][Array::ElemType::Bool.id]		= funcTmpl<Float, Float, Bool>; \
	func[Array::ElemType::Double.id][Array::ElemType::Bool.id]		= funcTmpl<Double, Double, Bool>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Bool.id]		= funcTmpl<Complex, Complex, Bool>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int8.id]		= funcTmpl<Int8, Bool, Int8>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int8.id]		= funcTmpl<Int8, Int8, Int8>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int8.id]		= funcTmpl<UInt8, UInt8, Int8>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int8.id]		= funcTmpl<Int16, Int16, Int8>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int8.id]		= funcTmpl<UInt16, UInt16, Int8>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int8.id]		= funcTmpl<Int32, Int32, Int8>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int8.id]		= funcTmpl<UInt32, UInt32, Int8>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int8.id]		= funcTmpl<Int64, Int64, Int8>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int8.id]		= funcTmpl<UInt64, UInt64, Int8>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int8.id]		= funcTmpl<Half, Half, Int8>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int8.id]		= funcTmpl<Float, Float, Int8>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int8.id]		= funcTmpl<Double, Double, Int8>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int8.id]		= funcTmpl<Complex, Complex, Int8>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt8, Bool, UInt8>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt8, Int8, UInt8>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt8, UInt8, UInt8>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt8.id]		= funcTmpl<Int16, Int16, UInt8>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt16, UInt16, UInt8>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt8.id]		= funcTmpl<Int32, Int32, UInt8>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt32, UInt32, UInt8>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt8.id]		= funcTmpl<Int64, Int64, UInt8>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt8.id]		= funcTmpl<UInt64, UInt64, UInt8>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt8.id]		= funcTmpl<Half, Half, UInt8>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt8.id]		= funcTmpl<Float, Float, UInt8>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt8.id]		= funcTmpl<Double, Double, UInt8>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt8.id]	= funcTmpl<Complex, Complex, UInt8>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int16.id]		= funcTmpl<Int16, Bool, Int16>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int16.id]		= funcTmpl<Int16, Int8, Int16>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int16.id]		= funcTmpl<Int16, UInt8, Int16>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int16.id]		= funcTmpl<Int16, Int16, Int16>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int16.id]		= funcTmpl<UInt16, UInt16, Int16>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int16.id]		= funcTmpl<Int32, Int32, Int16>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int16.id]		= funcTmpl<UInt32, UInt32, Int16>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int16.id]		= funcTmpl<Int64, Int64, Int16>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int16.id]		= funcTmpl<UInt64, UInt64, Int16>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int16.id]		= funcTmpl<Half, Half, Int16>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int16.id]		= funcTmpl<Float, Float, Int16>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int16.id]		= funcTmpl<Double, Double, Int16>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int16.id]	= funcTmpl<Complex, Complex, Int16>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt16.id]		= funcTmpl<UInt16, Bool, UInt16>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt16.id]		= funcTmpl<UInt16, Int8, UInt16>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt16.id]		= funcTmpl<UInt16, UInt8, UInt16>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt16.id]		= funcTmpl<UInt16, Int16, UInt16>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt16, UInt16, UInt16>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt16.id]		= funcTmpl<Int32, Int32, UInt16>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt32, UInt32, UInt16>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt16.id]		= funcTmpl<Int64, Int64, UInt16>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt16.id]	= funcTmpl<UInt64, UInt64, UInt16>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt16.id]		= funcTmpl<Half, Half, UInt16>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt16.id]		= funcTmpl<Float, Float, UInt16>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt16.id]	= funcTmpl<Double, Double, UInt16>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt16.id]	= funcTmpl<Complex, Complex, UInt16>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, Bool, Int32>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, Int8, Int32>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, UInt8, Int32>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, Int16, Int32>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, UInt16, Int32>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int32.id]		= funcTmpl<Int32, Int32, Int32>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int32.id]		= funcTmpl<UInt32, UInt32, Int32>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int32.id]		= funcTmpl<Int64, Int64, Int32>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int32.id]		= funcTmpl<UInt64, UInt64, Int32>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int32.id]		= funcTmpl<Half, Half, Int32>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int32.id]		= funcTmpl<Float, Float, Int32>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int32.id]		= funcTmpl<Double, Double, Int32>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int32.id]	= funcTmpl<Complex, Complex, Int32>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt32, Bool, UInt32>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt32, Int8, UInt32>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt32, UInt8, UInt32>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt32, Int16, UInt32>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt32, UInt16, UInt32>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt32.id]		= funcTmpl<UInt32, Int32, UInt32>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt32, UInt32, UInt32>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt32.id]		= funcTmpl<Int64, Int64, UInt32>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt32.id]	= funcTmpl<UInt64, UInt64, UInt32>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt32.id]		= funcTmpl<Half, Half, UInt32>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt32.id]		= funcTmpl<Float, Float, UInt32>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt32.id]	= funcTmpl<Double, Double, UInt32>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt32.id]	= funcTmpl<Complex, Complex, UInt32>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Bool, Int64>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Int8, Int64>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, UInt8, Int64>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Int16, Int64>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, UInt16, Int64>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Int32, Int64>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, UInt32, Int64>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Int64.id]		= funcTmpl<Int64, Int64, Int64>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Int64.id]		= funcTmpl<UInt64, UInt64, Int64>; \
	func[Array::ElemType::Half.id][Array::ElemType::Int64.id]		= funcTmpl<Half, Half, Int64>; \
	func[Array::ElemType::Float.id][Array::ElemType::Int64.id]		= funcTmpl<Float, Float, Int64>; \
	func[Array::ElemType::Double.id][Array::ElemType::Int64.id]		= funcTmpl<Double, Double, Int64>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Int64.id]	= funcTmpl<Complex, Complex, Int64>; \
	func[Array::ElemType::Bool.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, Bool, UInt64>; \
	func[Array::ElemType::Int8.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, Int8, UInt64>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, UInt8, UInt64>; \
	func[Array::ElemType::Int16.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, Int16, UInt64>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt64, UInt16, UInt64>; \
	func[Array::ElemType::Int32.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, Int32, UInt64>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt64, UInt32, UInt64>; \
	func[Array::ElemType::Int64.id][Array::ElemType::UInt64.id]		= funcTmpl<UInt64, Int64, UInt64>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::UInt64.id]	= funcTmpl<UInt64, UInt64, UInt64>; \
	func[Array::ElemType::Half.id][Array::ElemType::UInt64.id]		= funcTmpl<Half, Half, UInt64>; \
	func[Array::ElemType::Float.id][Array::ElemType::UInt64.id]		= funcTmpl<Float, Float, UInt64>; \
	func[Array::ElemType::Double.id][Array::ElemType::UInt64.id]	= funcTmpl<Double, Double, UInt64>; \
	func[Array::ElemType::Complex.id][Array::ElemType::UInt64.id]	= funcTmpl<Complex, Complex, UInt64>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Half.id]		= funcTmpl<Half, Bool, Half>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Half.id]		= funcTmpl<Half, Int8, Half>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Half.id]		= funcTmpl<Half, UInt8, Half>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Half.id]		= funcTmpl<Half, Int16, Half>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Half.id]		= funcTmpl<Half, UInt16, Half>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Half.id]		= funcTmpl<Half, Int32, Half>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Half.id]		= funcTmpl<Half, UInt32, Half>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Half.id]		= funcTmpl<Half, Int64, Half>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Half.id]		= funcTmpl<Half, UInt64, Half>; \
	func[Array::ElemType::Half.id][Array::ElemType::Half.id]		= funcTmpl<Half, Half, Half>; \
	func[Array::ElemType::Float.id][Array::ElemType::Half.id]		= funcTmpl<Float, Float, Half>; \
	func[Array::ElemType::Double.id][Array::ElemType::Half.id]		= funcTmpl<Double, Double, Half>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Half.id]		= funcTmpl<Complex, Complex, Half>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Float.id]		= funcTmpl<Float, Bool, Float>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Float.id]		= funcTmpl<Float, Int8, Float>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Float.id]		= funcTmpl<Float, UInt8, Float>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Float.id]		= funcTmpl<Float, Int16, Float>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Float.id]		= funcTmpl<Float, UInt16, Float>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Float.id]		= funcTmpl<Float, Int32, Float>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Float.id]		= funcTmpl<Float, UInt32, Float>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Float.id]		= funcTmpl<Float, Int64, Float>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Float.id]		= funcTmpl<Float, UInt64, Float>; \
	func[Array::ElemType::Half.id][Array::ElemType::Float.id]		= funcTmpl<Float, Half, Float>; \
	func[Array::ElemType::Float.id][Array::ElemType::Float.id]		= funcTmpl<Float, Float, Float>; \
	func[Array::ElemType::Double.id][Array::ElemType::Float.id]		= funcTmpl<Double, Double, Float>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Float.id]	= funcTmpl<Complex, Complex, Float>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Double.id]		= funcTmpl<Double, Bool, Double>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Double.id]		= funcTmpl<Double, Int8, Double>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Double.id]		= funcTmpl<Double, UInt8, Double>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Double.id]		= funcTmpl<Double, Int16, Double>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Double.id]	= funcTmpl<Double, UInt16, Double>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Double.id]		= funcTmpl<Double, Int32, Double>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Double.id]	= funcTmpl<Double, UInt32, Double>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Double.id]		= funcTmpl<Double, Int64, Double>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Double.id]	= funcTmpl<Double, UInt64, Double>; \
	func[Array::ElemType::Half.id][Array::ElemType::Double.id]		= funcTmpl<Double, Half, Double>; \
	func[Array::ElemType::Float.id][Array::ElemType::Double.id]		= funcTmpl<Double, Float, Double>; \
	func[Array::ElemType::Double.id][Array::ElemType::Double.id]	= funcTmpl<Double, Double, Double>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Double.id]	= funcTmpl<Complex, Complex, Double>; \
	func[Array::ElemType::Bool.id][Array::ElemType::Complex.id]		= funcTmpl<Complex, Bool, Complex>; \
	func[Array::ElemType::Int8.id][Array::ElemType::Complex.id]		= funcTmpl<Complex, Int8, Complex>; \
	func[Array::ElemType::UInt8.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, UInt8, Complex>; \
	func[Array::ElemType::Int16.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Int16, Complex>; \
	func[Array::ElemType::UInt16.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, UInt16, Complex>; \
	func[Array::ElemType::Int32.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Int32, Complex>; \
	func[Array::ElemType::UInt32.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, UInt32, Complex>; \
	func[Array::ElemType::Int64.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Int64, Complex>; \
	func[Array::ElemType::UInt64.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, UInt64, Complex>; \
	func[Array::ElemType::Half.id][Array::ElemType::Complex.id]		= funcTmpl<Complex, Half, Complex>; \
	func[Array::ElemType::Float.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Float, Complex>; \
	func[Array::ElemType::Double.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Double, Complex>; \
	func[Array::ElemType::Complex.id][Array::ElemType::Complex.id]	= funcTmpl<Complex, Complex, Complex>; \
} while (0)

#endif
