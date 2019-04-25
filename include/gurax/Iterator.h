//==============================================================================
// Iterator.h
//==============================================================================
#ifndef GURAX_ITERATOR_H
#define GURAX_ITERATOR_H
#include "IteratorIF.h"
#include "Referable.h"
#include "Help.h"

namespace Gurax {

class Value;

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator : public Referable, public IteratorIF {
public:
	// Referable declaration
	Gurax_DeclareReferable(Iterator);
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None				= 0;
		static const Flags Infinite			= (0 << 0);
		static const Flags Finite			= (1 << 0);
		static const Flags LenUndetermined	= (0 << 1);
		static const Flags LenDetermined	= (1 << 1);
	};
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
	bool IsInfinite() const { return (GetFlags() & Flag::Finite) == 0; }
	bool IsFinite() const { return (GetFlags() & Flag::Finite) != 0; }
	bool MustBeFinite() const;
	bool IsLenUndetermined() const { return (GetFlags() & Flag::LenDetermined) == 0; }
	bool IsLenDetermined() const { return (GetFlags() & Flag::LenDetermined) != 0; }
	void AddHelp(const Symbol* pLangCode, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(doc));
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Iterator& iterator) const { return this == &iterator; }
	bool IsEqualTo(const Iterator& iterator) const { return IsIdentical(iterator); }
	bool IsLessThan(const Iterator& iterator) const { return this < &iterator; }
	String ToString() const { return ToString(StringStyle::Empty); }
public:
	// Virtual functions
	virtual Iterator* Clone() const;
	virtual Flags GetFlags() const = 0;
	virtual size_t GetLength() const = 0;
	virtual String ToString(const StringStyle& ss) const;
};

}

#endif
