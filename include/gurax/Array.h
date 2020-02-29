//==============================================================================
// Array.h
//==============================================================================
#ifndef GURAX_ARRAY_H
#define GURAX_ARRAY_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Array : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Array);
public:
	enum class ElemType {
		None,	Bool,
		Int8,	UInt8,	Int16,	UInt16,
		Int32,	UInt32,	Int64,	UInt64,
		Half,	Float,	Double,	Complex,
	};
	class SymbolAssoc_ElemType : public SymbolAssoc<ElemType, ElemType::None> {
	public:
		SymbolAssoc_ElemType() {
			Assoc(Gurax_Symbol(bool_),		ElemType::Bool);
			Assoc(Gurax_Symbol(int8),		ElemType::Int8);
			Assoc(Gurax_Symbol(uint8),		ElemType::UInt8);
			Assoc(Gurax_Symbol(int16),		ElemType::Int16);
			Assoc(Gurax_Symbol(uint16),		ElemType::UInt16);
			Assoc(Gurax_Symbol(int32),		ElemType::Int32);
			Assoc(Gurax_Symbol(uint32),		ElemType::UInt32);
			Assoc(Gurax_Symbol(int64),		ElemType::Int64);
			Assoc(Gurax_Symbol(uint64),		ElemType::UInt64);
			Assoc(Gurax_Symbol(half),		ElemType::Half);
			Assoc(Gurax_Symbol(float_),		ElemType::Float);
			Assoc(Gurax_Symbol(double_),	ElemType::Double);
			Assoc(Gurax_Symbol(complex),	ElemType::Complex);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_ElemType());
		}
	};
	template<typename T_Elem>
	class Accessor {
	public:
		static T_Elem* GetPointer(void* p) { return reinterpret_cast<T_Elem*>(p); }
		static const T_Elem* GetPointer(const void* p) { return reinterpret_cast<const T_Elem*>(p); }
		static T_Elem& Get(void* p) { return *reinterpret_cast<T_Elem*>(p); }
		static const T_Elem& Get(const void* p) { return *reinterpret_cast<const T_Elem*>(p); }
		static void Set(void* p, const T_Elem& elem) { *reinterpret_cast<T_Elem*>(p) = elem; }
	};
protected:
	ElemType _elemType;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	Array(ElemType elemType, Memory* pMemory);
	// Copy constructor/operator
	Array(const Array& src) = delete;
	Array& operator=(const Array& src) = delete;
	// Move constructor/operator
	Array(Array&& src) = delete;
	Array& operator=(Array&& src) noexcept = delete;
protected:
	~Array() = default;
public:
	static ElemType SymbolToElemType(const Symbol* pSymbol) {
		return SymbolAssoc_ElemType::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* ElemTypeToSymbol(ElemType elemType) {
		return SymbolAssoc_ElemType::GetInstance().ToSymbol(elemType);
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
