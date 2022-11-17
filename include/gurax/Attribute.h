//==============================================================================
// Attribute.h
//==============================================================================
#ifndef GURAX_ATTRIBUTE_H
#define GURAX_ATTRIBUTE_H
#include "MemoryPool.h"
#include "Referable.h"
#include "DottedSymbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Attribute
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Attribute : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Attribute);
private:
	SymbolList _symbolList;
	SymbolList _symbolListOpt;
	SymbolSet _symbolSet;
	SymbolSet _symbolSetOpt;
public:
	static const Attribute* Empty;
public:
	static void Bootup();
public:
	// Constructor
	Attribute() {}
	// Copy constructor/operator
	Attribute(const Attribute& src) = delete;
	Attribute& operator=(const Attribute& src) = delete;
	// Move constructor/operator
	Attribute(Attribute&& src) = delete;
	Attribute& operator=(Attribute&& src) noexcept = delete;
protected:
	~Attribute() = default;
public:
	const SymbolList& GetSymbols() const { return _symbolList; }
	const SymbolList& GetSymbolsOpt() const { return _symbolListOpt; }
	const SymbolSet& GetSymbolSet() const { return _symbolSet; }
	const SymbolSet& GetSymbolSetOpt() const { return _symbolSetOpt; }
	void AddAttribute(const Attribute& attr);
	void AddSymbol(const Symbol* pSymbol);
	void AddSymbolOpt(const Symbol* pSymbol) {
		_symbolListOpt.push_back(pSymbol);
		_symbolSetOpt.GetSet().insert(pSymbol);
	}
	void AddSymbols(const SymbolList& symbolList) {
		for (const Symbol* pSymbol : symbolList) AddSymbol(pSymbol);
	}
	void AddSymbolsOpt(const SymbolList& symbolList) {
		for (const Symbol* pSymbol : symbolList) AddSymbolOpt(pSymbol);
	}
	bool IsEmpty() const { return GetSymbols().empty() && GetSymbolsOpt().empty(); }
	bool IsSet(const Symbol* pSymbol) const { return GetSymbolSet().IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) const { return GetSymbolSetOpt().IsSet(pSymbol); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Attribute& attr) const { return this == &attr; }
	bool IsEqualTo(const Attribute& attr) const { return IsIdentical(attr); }
	bool IsLessThan(const Attribute& attr) const { return this < &attr; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
