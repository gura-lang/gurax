//==============================================================================
// Info.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_INFO_H
#define GURAX_MODULE_BMP_INFO_H
#include <gurax.h>

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Info
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Info : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Info);
public:
	// Constructor
	Info() {}
	// Copy constructor/operator
	Info(const Info& src) = delete;
	Info& operator=(const Info& src) = delete;
	// Move constructor/operator
	Info(Info&& src) = delete;
	Info& operator=(Info&& src) noexcept = delete;
protected:
	~Info() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Info& other) const { return this == &other; }
	bool IsEqualTo(const Info& other) const { return IsIdentical(other); }
	bool IsLessThan(const Info& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(bmp)

#endif
