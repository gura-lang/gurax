//==============================================================================
// Array.h
//==============================================================================
#ifndef GURAX_ARRAY_H
#define GURAX_ARRAY_H
#include "Memory.h"

namespace Gurax {

class ValueOwner;

//------------------------------------------------------------------------------
// Array
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Array : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Array);
public:
	class GURAX_DLLDECLARE ElemTypeT {
	public:
		const Symbol* pSymbol;
		size_t bytes;
		std::function<void (void* p, size_t idx, const Value& value)> IndexSet;
		std::function<Value* (const void* p, size_t idx)> IndexGet;
		std::function<void (const void* p, const ValueList& values)> InjectElems;
		std::function<void (const void* p, size_t nElems, ValueOwner& values)> ExtractElems;
	public:
		ElemTypeT(size_t bytes) : bytes(bytes) {}
		bool IsNone() const;
		bool IsIdentical(const ElemTypeT& elemType) const { return this == &elemType; }
	};
	struct ElemType {
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
	class SymbolAssoc_ElemType : public SymbolAssoc<ElemTypeT*, &ElemType::None> {
	public:
		SymbolAssoc_ElemType() {
			Assoc(Gurax_Symbol(bool_),		&ElemType::Bool);
			Assoc(Gurax_Symbol(int8),		&ElemType::Int8);
			Assoc(Gurax_Symbol(uint8),		&ElemType::UInt8);
			Assoc(Gurax_Symbol(int16),		&ElemType::Int16);
			Assoc(Gurax_Symbol(uint16),		&ElemType::UInt16);
			Assoc(Gurax_Symbol(int32),		&ElemType::Int32);
			Assoc(Gurax_Symbol(uint32),		&ElemType::UInt32);
			Assoc(Gurax_Symbol(int64),		&ElemType::Int64);
			Assoc(Gurax_Symbol(uint64),		&ElemType::UInt64);
			Assoc(Gurax_Symbol(half),		&ElemType::Half);
			Assoc(Gurax_Symbol(float_),		&ElemType::Float);
			Assoc(Gurax_Symbol(double_),	&ElemType::Double);
			Assoc(Gurax_Symbol(complex),	&ElemType::Complex);
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
	ElemTypeT& _elemType;
	size_t _nElems;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	Array(ElemTypeT& elemType, size_t nElems, Memory* pMemory);
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
	ElemTypeT& GetElemType() { return _elemType; }
	Memory& GetMemory() { return *_pMemory; }
	const Memory& GetMemory() const { return *_pMemory; }
	template<typename T> T* GetPointerC() { return _pMemory->GetPointerC<T>(); }
	template<typename T> const T* GetPointerC() const { return _pMemory->GetPointerC<T>(); }
	size_t CountElems() const { return _nElems; }
	void ExtractElems(ValueOwner& values) const;
public:
	static ElemTypeT& SymbolToElemType(const Symbol* pSymbol) {
		return *SymbolAssoc_ElemType::GetInstance().ToAssociated(pSymbol);
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
