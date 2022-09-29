//==============================================================================
// Text.h
//==============================================================================
#ifndef GURAX_MODULE_XML_TEXT_H
#define GURAX_MODULE_XML_TEXT_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Text
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Text : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Text);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Text");
private:
	String _text;
public:
	// Constructor
	Text(String text);
	// Copy constructor/operator
	Text(const Text& src) = delete;
	Text& operator=(const Text& src) = delete;
	// Move constructor/operator
	Text(Text&& src) noexcept = delete;
	Text& operator=(Text&& src) noexcept = delete;
protected:
	~Text() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Text& other) const { return this == &other; }
	bool IsEqualTo(const Text& other) const { return IsIdentical(other); }
	bool IsLessThan(const Text& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
