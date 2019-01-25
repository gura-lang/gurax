//==============================================================================
// Template.h
//==============================================================================
#ifndef GURAX_TEMPLATE_H
#define GURAX_TEMPLATE_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Template
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Template : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Template);
public:
	// Constructor
	Template() {}
	// Copy constructor/operator
	Template(const Template& src) = delete;
	Template& operator=(const Template& src) = delete;
	// Move constructor/operator
	Template(Template&& src) = delete;
	Template& operator=(Template&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Template() = default;
public:
	static void Bootup();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Template& templ) const { return this == &templ; }
	bool IsEqualTo(const Template& templ) const { return IsIdentical(templ); }
	bool IsLessThan(const Template& templ) const { return this < &templ; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(template)"; }
};

}

#endif
