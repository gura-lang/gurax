//==============================================================================
// Iterator.h
//==============================================================================
#ifndef GURAX_ITERATOR_H
#define GURAX_ITERATOR_H
#include "Referable.h"
#include "Help.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
class Iterator : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Iterator);
protected:
	RefPtr<HelpProvider> _pHelpProvider;
public:
	// Constructor
	Iterator() : _pHelpProvider(new HelpProvider()) {}
	// Copy constructor/operator
	Iterator(const Iterator& src) = delete;
	Iterator& operator=(const Iterator& src) = delete;
	// Move constructor/operator
	Iterator(Iterator&& src) = delete;
	Iterator& operator=(Iterator&& src) noexcept = delete;
protected:
	// Destructor
	~Iterator() = default;
public:
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Iterator* pIterator) const { return this == pIterator; }
	bool IsEqualTo(const Iterator* pIterator) const { return IsIdentical(pIterator); }
	bool IsLessThan(const Iterator* pIterator) const { return this < pIterator; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(iterator)"; }
};

}

#endif
