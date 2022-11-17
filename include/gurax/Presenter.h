//==============================================================================
// Presenter.h
//==============================================================================
#ifndef GURAX_PRESENTER_H
#define GURAX_PRESENTER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Presenter
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Presenter : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Presenter);
public:
	// Constructor
	Presenter() {}
	// Copy constructor/operator
	Presenter(const Presenter& src) = delete;
	Presenter& operator=(const Presenter& src) = delete;
	// Move constructor/operator
	Presenter(Presenter&& src) = delete;
	Presenter& operator=(Presenter&& src) noexcept = delete;
protected:
	~Presenter() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Presenter& other) const { return this == &other; }
	bool IsEqualTo(const Presenter& other) const { return IsIdentical(other); }
	bool IsLessThan(const Presenter& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
