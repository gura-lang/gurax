//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_SYMBOL_H
#define GURAX_SYMBOL_H
#include "ListBase.h"
#include "Referable.h"
#include "String.h"
#include "StringStyle.h"
#include "ListBase.h"

#define Gurax_DeclareSymbol(name) \
extern GURAX_DLLDECLARE const Symbol* g_pSymbol_##name;

#define Gurax_DeclareSymbolMark(name) \
extern GURAX_DLLDECLARE const Symbol* g_pSymbolMark_##name;

#define Gurax_RealizeSymbolAlias(name, str) \
const Symbol* g_pSymbol_##name = Symbol::Add(str);

#define Gurax_RealizeSymbolMark(name, str) \
const Symbol* g_pSymbolMark_##name = Symbol::Add(str);

#define Gurax_RealizeSymbol(name) Gurax_RealizeSymbolAlias(name, #name)

#define Gurax_Symbol(name) g_pSymbol_##name

#define Gurax_SymbolMark(name) g_pSymbolMark_##name

namespace Gurax {

class Symbol; 
class Expr;
class ExprList;
class ExprLink;

//------------------------------------------------------------------------------
// SymbolList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolList : public ListBase<const Symbol*> {
public:
	static const SymbolList Empty;
public:
	// Constructor
	SymbolList() = default;
	explicit SymbolList(std::initializer_list<const Symbol*> initList) :
		ListBase(initList) {}
	SymbolList(const_iterator ppSymbolBegin, const_iterator ppSymbolEnd) :
		ListBase(ppSymbolBegin, ppSymbolEnd) {}
	// Copy constructor/operator
	SymbolList(const SymbolList& src) = default;
	SymbolList& operator=(const SymbolList& src) = default;
	// Move constructor/operator
	SymbolList(SymbolList&& src) = default;
	SymbolList& operator=(SymbolList&& src) noexcept = default;
	// Destructor
	~SymbolList() = default;
public:
	static SymbolList* CreateFromExprList(const ExprList& exprList) {
		std::unique_ptr<SymbolList> pSymbolList(new SymbolList());
		return pSymbolList->AddFromExprList(exprList)? pSymbolList.release() : nullptr;
	}
	static SymbolList* CreateFromExprLink(const ExprLink& exprLink) {
		std::unique_ptr<SymbolList> pSymbolList(new SymbolList());
		return pSymbolList->AddFromExprLink(exprLink)? pSymbolList.release() : nullptr;
	}
	bool AddFromExprList(const ExprList& exprList);
	bool AddFromExprLink(const ExprLink& exprLink);
	SymbolList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	template<typename T_Map> static SymbolList CollectKeys(const T_Map& map);
	bool IsEqualTo(const SymbolList& symbolList) const;
	bool DoesExist(const Symbol* pSymbol) const { return std::find(begin(), end(), pSymbol) != end(); }
	int WhereExist(const Symbol* pSymbol) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<typename T_Map>
SymbolList SymbolList::CollectKeys(const T_Map& map)
{
	SymbolList keys;
	keys.reserve(map.GetMap().size());
	for (auto& pair : map.GetMap()) keys.push_back(pair.first);
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
	char _chEnd;
	char _nameBuff[0];
public:
	static const Symbol* Empty;
public:
	// Constructor
	Symbol() = delete;
	Symbol(size_t uniqId, char* name) : _uniqId(uniqId), _name(name), _chEnd('\0') {}
	// Copy constructor/operator
	Symbol(const Symbol& src) = delete;
	Symbol& operator=(const Symbol& src) = delete;
	// Move constructor/operator
	Symbol(Symbol&& src) = delete;
	Symbol& operator=(Symbol&& src) noexcept = delete;
	// Destructor
	~Symbol() = default;
public:
	void Initialize(size_t uniqId, const char* name, bool chEnd) {
		_uniqId = uniqId;
		::strcpy(_nameBuff, name);
		_name = _nameBuff;
		_chEnd = chEnd;
	}
	int GetUniqId() const { return _uniqId; }
	const char* GetName() const { return _name; }
	char GetEndChar() const { return _chEnd; }
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
	bool StartsWith(char ch) const { return *GetName() == ch; }
	bool EndsWith(char ch) const { return GetEndChar() == ch; }
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
class GURAX_DLLDECLARE SymbolSet {
public:
	using SetType = std::unordered_set<const Symbol*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	SetType _set;
public:
	SetType& GetSet() { return _set; }
	const SetType& GetSet() const { return _set; }
	void Set(const Symbol* pSymbol) { _set.insert(pSymbol); }
	bool IsSet(const Symbol* pSymbol) const { return _set.find(pSymbol) != _set.end(); }
};

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolPool {
public:
	using SetType = std::unordered_set<const Symbol*, Symbol::Hash_Name, Symbol::EqualTo_Name>;
private:
	SetType _set;
private:
	static SymbolPool* _pSymbolPool;
public:
	SetType& GetSet() { return _set; }
	const SetType& GetSet() const { return _set; }
	static SymbolPool& GetInstance() {
		if (!_pSymbolPool) _pSymbolPool = new SymbolPool();
		return *_pSymbolPool;
	}
};

//------------------------------------------------------------------------------
// SymbolAssoc
//------------------------------------------------------------------------------
template<typename T_Associated, T_Associated associatedInvalid>
class SymbolAssoc {
public:
	using MapToAssociated = std::unordered_map<const Symbol*, T_Associated, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	using MapToSymbol = std::unordered_map<T_Associated, const Symbol*>;
private:
	MapToAssociated _mapToAssociated;
	MapToSymbol _mapToSymbol;
public:
	void Assoc(const Symbol* pSymbol, T_Associated associated) {
		_mapToAssociated[pSymbol] = associated;
		_mapToSymbol[associated] = pSymbol;
	}
	T_Associated ToAssociated(const Symbol* pSymbol) const {
		auto pPair = _mapToAssociated.find(pSymbol);
		return (pPair == _mapToAssociated.end())? associatedInvalid : pPair->second;
	}
	const Symbol* ToSymbol(T_Associated associated) const {
		auto pPair = _mapToSymbol.find(associated);
		return (pPair == _mapToSymbol.end())? Symbol::Empty : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const {
		return _mapToAssociated.find(pSymbol) != _mapToAssociated.end();
	}
};

}

#endif
