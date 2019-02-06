//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_SYMBOL_H
#define GURAX_SYMBOL_H
#include "Referable.h"
#include "String.h"

#define Gurax_DeclareSymbol(name) \
extern const Symbol* g_pSymbol_##name;

#define Gurax_DeclareSymbolMark(name) \
extern const Symbol* g_pSymbolMark_##name;

#define Gurax_RealizeSymbolAlias(name, str) \
const Symbol* g_pSymbol_##name = Symbol::Add(str);

#define Gurax_RealizeSymbol(name) Gurax_RealizeSymbolAlias(name, #name)

#define Gurax_RealizeSymbolMark(name, str) \
const Symbol* g_pSymbolMark_##name = Symbol::Add(str);

#define Gurax_Symbol(name) g_pSymbol_##name

#define Gurax_SymbolMark(name) g_pSymbolMark_##name

namespace Gurax {

class Symbol; 
class Expr;
class ExprList;

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolList : public std::vector<const Symbol*> {
public:
	static const SymbolList Empty;
public:
	// Constructor
	SymbolList() = default;
	explicit SymbolList(std::initializer_list<const Symbol*> initList) :
		std::vector<const Symbol*>(initList) {}
	// Copy constructor/operator
	SymbolList(const SymbolList& src) = default;
	SymbolList& operator=(const SymbolList& src) = default;
	// Move constructor/operator
	SymbolList(SymbolList&& src) = default;
	SymbolList& operator=(SymbolList&& src) noexcept = default;
	// Destructor
	~SymbolList() = default;
public:
	SymbolList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	template<typename T_Map> static SymbolList CollectKeys(const T_Map& map);
	bool IsEqualTo(const SymbolList& symbolList) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<typename T_Map>
SymbolList SymbolList::CollectKeys(const T_Map& map)
{
	SymbolList keys;
	keys.reserve(map.size());
	for (auto& pair : map) keys.push_back(pair.first);
	return keys;
}

//------------------------------------------------------------------------------
// Symbol
// This class is assured to be a POD (plain old data).
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Symbol {
public:
	// Algorithm operators with UniqId
	struct EqualTo_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() == pSymbol2->GetUniqId();
		}
	};
	struct LessThan_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() < pSymbol2->GetUniqId();
		}
	};
	struct GreaterThan_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() > pSymbol2->GetUniqId();
		}
	};
	struct Hash_UniqId {
		size_t operator()(const Symbol* pSymbol) const {
			return pSymbol->GetUniqId();
		}
	};
	// Algorithm operators with Name
	struct EqualTo_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return String::IsEqualTo(pSymbol1->GetName(), pSymbol2->GetName());
		}
	};
	struct LessThan_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return String::IsLessThan(pSymbol1->GetName(), pSymbol2->GetName());
		}
	};
	struct GreaterThan_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return String::IsLessThan(pSymbol2->GetName(), pSymbol1->GetName());
		}
	};
	struct Hash_Name {
		size_t operator()(const Symbol* pSymbol) const {
			return String::CalcHash(pSymbol->GetName());
		}
	};
protected:
	size_t _uniqId;
	char* _name;
	char _nameBuff[0];
public:
	static const Symbol* Empty;
public:
	// Constructor
	Symbol() = delete;
	Symbol(size_t uniqId, char* name) : _uniqId(uniqId), _name(name) {}
	// Copy constructor/operator
	Symbol(const Symbol& src) = delete;
	Symbol& operator=(const Symbol& src) = delete;
	// Move constructor/operator
	Symbol(Symbol&& src) = delete;
	Symbol& operator=(Symbol&& src) noexcept = delete;
	// Destructor
	~Symbol() = default;
public:
	void Initialize(size_t uniqId, const char* name) {
		_uniqId = uniqId;
		::strcpy(_nameBuff, name);
		_name = _nameBuff;
	}
	int GetUniqId() const { return _uniqId; }
	const char* GetName() const { return _name; }
public:
	size_t CalcHash() const { return static_cast<size_t>(GetUniqId()); }
	bool IsIdentical(const Symbol* pSymbol) const { return GetUniqId() == pSymbol->GetUniqId(); }
	static bool IsIdentical(const Symbol* pSymbol1, const Symbol* pSymbol2) {
		return pSymbol1 && pSymbol2 && pSymbol1->IsIdentical(pSymbol2);
	}
	bool IsEqualTo(const Symbol* pSymbol) const { return IsIdentical(pSymbol); }
	bool IsLessThan_UniqId(const Symbol* pSymbol) const { return GetUniqId() < pSymbol->GetUniqId(); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool IsEmpty() const { return IsIdentical(Empty); }
	bool IsFlowControl() const;
	static void Bootup();
	static const Symbol* Add(const char* name);
	static const Symbol* Add(const String& name) { return Add(name.c_str()); }
	static SymbolList GetAllSymbols();
	static void PrintAllSymbols();
};

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolSet :
	public std::unordered_set<const Symbol*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId> {
public:
	void Set(const Symbol* pSymbol) { insert(pSymbol); }
	bool IsSet(const Symbol* pSymbol) { return find(pSymbol) != end(); }
};

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolPool :
	public std::unordered_set<const Symbol*, Symbol::Hash_Name, Symbol::EqualTo_Name> {
private:
	static SymbolPool* _pSymbolPool;
public:
	static SymbolPool& GetInstance() {
		if (!_pSymbolPool) _pSymbolPool = new SymbolPool();
		return *_pSymbolPool;
	}
};

//------------------------------------------------------------------------------
// SymbolAssoc
//------------------------------------------------------------------------------
template<typename T_Value, T_Value valueInvalid>
class SymbolAssoc {
public:
	using MapToValue = std::unordered_map<const Symbol*, T_Value, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	using MapToSymbol = std::unordered_map<T_Value, const Symbol*>;
private:
	MapToValue _mapToValue;
	MapToSymbol _mapToSymbol;
protected:
	static SymbolAssoc* _pInstance;
public:
	void Assoc(const Symbol* pSymbol, T_Value value) {
		_mapToValue[pSymbol] = value;
		_mapToSymbol[value] = pSymbol;
	}
	T_Value ToValue(const Symbol* pSymbol) const {
		auto pPair = _mapToValue.find(pSymbol);
		return (pPair == _mapToValue.end())? valueInvalid : pPair->second;
	}
	const Symbol* ToSymbol(T_Value value) const {
		auto pPair = _mapToSymbol.find(value);
		return (pPair == _mapToSymbol.end())? Symbol::Empty : pPair->second;
	}
};

template<typename T_Value, T_Value valueInvalid>
SymbolAssoc<T_Value, valueInvalid>* SymbolAssoc<T_Value, valueInvalid>::_pInstance = nullptr;

//------------------------------------------------------------------------------
// DottedSymbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DottedSymbol : public Referable {
private:
	SymbolList _symbolList;
public:
	static const DottedSymbol Empty;
public:
	// Referable accessor
	Gurax_DeclareReferable(DottedSymbol);
public:
	// Constructor
	DottedSymbol() = default;
	explicit DottedSymbol(const Symbol* pSymbol) {
		_symbolList.reserve(1);
		_symbolList.push_back(pSymbol); 
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2) {
		_symbolList.reserve(2);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3) {
		_symbolList.reserve(3);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2); _symbolList.push_back(pSymbol3);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3, const Symbol* pSymbol4) {
		_symbolList.reserve(4);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3,
				 const Symbol* pSymbol4, const Symbol* pSymbol5) {
		_symbolList.reserve(5);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
		_symbolList.push_back(pSymbol5);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3,
				 const Symbol* pSymbol4, const Symbol* pSymbol5, const Symbol* pSymbol6) {
		_symbolList.reserve(6);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
		_symbolList.push_back(pSymbol5); _symbolList.push_back(pSymbol6);
	}
	explicit DottedSymbol(std::initializer_list<const Symbol*> initList) : _symbolList(initList) {}
	// Copy constructor/operator
	DottedSymbol(const DottedSymbol& src) : _symbolList(src._symbolList) {}
	DottedSymbol& operator=(const DottedSymbol& src) { _symbolList = src._symbolList; return *this; }
	// Move constructor/operator
	DottedSymbol(DottedSymbol&& src) = delete;
	DottedSymbol& operator=(DottedSymbol&& src) noexcept = delete;
protected:
	// Destructor
	~DottedSymbol() = default;
public:
	const SymbolList& GetSymbolList() const { return _symbolList; }
	void Reserve(size_t n) { _symbolList.reserve(n); }
	void Append(const Symbol* pSymbol) { _symbolList.push_back(pSymbol); }
	bool AppendFromExprList(const ExprList& exprList);
	bool AppendFromString(const char* str);
	bool AppendFromExpr(const Expr* pExpr);
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
	bool IsDotted() const { return _symbolList.size() > 1; }
	bool IsEmpty() const { return _symbolList.empty(); }
	bool IsEqualTo(const DottedSymbol& dottedSymbol) const {
		return _symbolList.IsEqualTo(dottedSymbol.GetSymbolList());
	}
	DottedSymbol* Clone() const { return new DottedSymbol(*this); }
};

}

#endif
