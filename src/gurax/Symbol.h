//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_SYMBOL_H
#define GURAX_SYMBOL_H
#include "Referable.h"
#include "String.h"

namespace Gurax {

class SymbolPool;
	
//------------------------------------------------------------------------------
// Symbol
// This class is assured to be a POD (plain old data).
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Symbol {
public:
	struct LessThan_UniqId {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) {
			return pSymbol1->GetUniqId() < pSymbol2->GetUniqId();
		}
	};
	struct LessThan_Name {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) {
			return ::strcmp(pSymbol1->GetName(), pSymbol2->GetName()) < 0;
		}
	};
	struct Hash_UniqId {
		size_t operator()(const Symbol* pSymbol) {
			return pSymbol->GetUniqId();
		}
	};
	struct Hash_Name {
		size_t operator()(const Symbol* pSymbol) {
			return std::hash<std::string>()(pSymbol->GetName());
		}
	};
protected:
	size_t _uniqId;
	char* _name;
	char _nameBuff[0];
private:
	static SymbolPool* _pSymbolPool;
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
	int GetUniqId() const { return _uniqId; }
	const char* GetName() const { return _name; }
	static void Bootup();
	static const Symbol* Add(const char* name);
};

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolSet :
	public std::unordered_set<const Symbol*, Symbol::Hash_UniqId>, public Referable {
protected:
	~SymbolSet() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(SymbolSet);
};

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolPool :
	public std::unordered_set<const Symbol*, Symbol::Hash_Name> {
};

}

#endif
