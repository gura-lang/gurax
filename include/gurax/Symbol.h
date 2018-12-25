//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_SYMBOL_H
#define GURAX_SYMBOL_H
#include "Referable.h"
#include "String.h"

#define Gurax_DeclareSymbol(name) \
extern const Symbol* g_pSymbol_##name;

#define Gurax_RealizeSymbolAlias(name, nameStr) \
const Symbol* g_pSymbol_##name = Symbol::Add(nameStr);

#define Gurax_RealizeSymbol(name) Gurax_RealizeSymbolAlias(name, #name)

#define Gurax_Symbol(name) g_pSymbol_##name

namespace Gurax {

class Symbol; 

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolList : public std::vector<const Symbol*> {
public:
	void Sort(SortOrder sortOrder = SortOrder::Ascend);
};

//------------------------------------------------------------------------------
// Symbol
// This class is assured to be a POD (plain old data).
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Symbol {
public:
	struct LessThan_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() < pSymbol2->GetUniqId();
		}
	};
	struct LessThan_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return ::strcmp(pSymbol1->GetName(), pSymbol2->GetName()) < 0;
		}
	};
	struct GreaterThan_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() > pSymbol2->GetUniqId();
		}
	};
	struct GreaterThan_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return ::strcmp(pSymbol1->GetName(), pSymbol2->GetName()) > 0;
		}
	};
	struct EqualTo_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return pSymbol1->GetUniqId() == pSymbol2->GetUniqId();
		}
	};
	struct EqualTo_Name {
		size_t operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) const {
			return ::strcmp(pSymbol1->GetName(), pSymbol2->GetName()) == 0;
		}
	};
	struct Hash_UniqId {
		size_t operator()(const Symbol* pSymbol) const {
			return pSymbol->GetUniqId();
		}
	};
	struct Hash_Name {
		size_t operator()(const Symbol* pSymbol) const {
			return std::hash<std::string>()(pSymbol->GetName());
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
	const char* GetName() const { return _name; }
	bool IsIdentical(const Symbol* pSymbol) const { return GetUniqId() == pSymbol->GetUniqId(); }
	static bool IsIdentical(const Symbol* pSymbol1, const Symbol *pSymbol2) {
		return pSymbol1 && pSymbol2 && (pSymbol1->GetUniqId() == pSymbol2->GetUniqId());
	}
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

}

#endif
