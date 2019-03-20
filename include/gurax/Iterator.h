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
class GURAX_DLLDECLARE Iterator : public Referable {
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
	virtual ~Iterator() = default;
public:
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Iterator& iterator) const { return this == &iterator; }
	bool IsEqualTo(const Iterator& iterator) const { return IsIdentical(iterator); }
	bool IsLessThan(const Iterator& iterator) const { return this < &iterator; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	virtual Value* NextValue() = 0;
	virtual String ToString(const StringStyle& ss) const;
};

}

#endif
