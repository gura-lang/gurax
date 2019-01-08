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

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolList : public std::vector<const Symbol*> {
public:
	SymbolList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	template<typename T_Map> static SymbolList CollectKeys(const T_Map& map);
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
	size_t CalcHash() const { return static_cast<size_t>(GetUniqId()); }
	const char* GetName() const { return _name; }
	bool IsIdentical(const Symbol* pSymbol) const { return GetUniqId() == pSymbol->GetUniqId(); }
	static bool IsIdentical(const Symbol* pSymbol1, const Symbol *pSymbol2) {
		return pSymbol1 && pSymbol2 && (pSymbol1->GetUniqId() == pSymbol2->GetUniqId());
	}
	bool IsEqualTo(const Symbol* pSymbol) const { return IsIdentical(pSymbol); }
	bool IsLessThan(const Symbol* pSymbol) const { return ::strcmp(GetName(), pSymbol->GetName()) < 0; }
	static void Bootup();
	static const Symbol* Add(const char* name);
	static SymbolList GetList();
	static void PrintList();
};

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolSet :
	public std::unordered_set<const Symbol*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
protected:
	~SymbolSet() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(SymbolSet);
public:
	void Set(const Symbol* pSymbol) { insert(pSymbol); }
	bool DoesExist(const Symbol* pSymbol) { return find(pSymbol) != end(); }
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

}

#endif
