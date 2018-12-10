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
// This class is assured to be a plain old data.
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
protected:
	size_t _uniqId;
	char* _name;
	char _nameBuff[0];
private:
	static SymbolPool* _pSymbolPool;
public:
	// Default constructor
	Symbol() = delete;
	// Copy constructor/operator
	Symbol(const Symbol& src) = delete;
	Symbol& operator=(const Symbol& src) = delete;
	// Move constructor/operator
	Symbol(Symbol&& src) = delete;
	Symbol& operator=(Symbol&& src) noexcept = delete;
	// Destructor
	~Symbol() = default;
public:
	Symbol(size_t uniqId, char* name) : _uniqId(uniqId), _name(name) {}
	int GetUniqId() const { return _uniqId; }
	const char* GetName() const { return _name; }
	static void Bootup();
	static const Symbol* Add(const char* name);
};

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolSet :
	public std::set<const Symbol*, Symbol::LessThan_UniqId>, public Referable {
protected:
	~SymbolSet() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(SymbolSet);
};

//------------------------------------------------------------------------------
// SymbolPool
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolPool : public std::set<const Symbol*, Symbol::LessThan_Name> {
};

}

#endif
