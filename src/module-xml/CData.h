//==============================================================================
// CData.h
//==============================================================================
#ifndef GURAX_MODULE_XML_CDATA_H
#define GURAX_MODULE_XML_CDATA_H
#include <gurax.h>
#include "Node.h"
#include "Text.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// CData
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CData : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(CData);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.CData");
private:
	RefPtr<Text> _pText;
public:
	// Constructor
	CData() : Node(Type::CData) {}
	// Copy constructor/operator
	CData(const CData& src) = delete;
	CData& operator=(const CData& src) = delete;
	// Move constructor/operator
	CData(CData&& src) noexcept = delete;
	CData& operator=(CData&& src) noexcept = delete;
protected:
	~CData() = default;
public:
	void SetText(Text* pText) { _pText.reset(pText); }
	const Text& GetText() const { return _pText? *_pText : Text::Empty; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const CData& other) const { return this == &other; }
	bool IsEqualTo(const CData& other) const { return IsIdentical(other); }
	bool IsLessThan(const CData& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// CDataStack
//------------------------------------------------------------------------------
class CDataStack : public ListBase<CData*> {
};

Gurax_EndModuleScope(xml)

#endif
