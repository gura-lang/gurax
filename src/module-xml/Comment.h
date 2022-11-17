//==============================================================================
// Comment.h
//==============================================================================
#ifndef GURAX_MODULE_XML_COMMENT_H
#define GURAX_MODULE_XML_COMMENT_H
#include <gurax.h>
#include "Node.h"

Gurax_BeginModuleScope(xml)

//------------------------------------------------------------------------------
// Comment
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Comment : public Node {
public:
	// Referable declaration
	Gurax_DeclareReferable(Comment);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("xml.Comment");
private:
	String _data;
public:
	// Constructor
	Comment(String data);
	// Copy constructor/operator
	Comment(const Comment& src) = delete;
	Comment& operator=(const Comment& src) = delete;
	// Move constructor/operator
	Comment(Comment&& src) noexcept = delete;
	Comment& operator=(Comment&& src) noexcept = delete;
protected:
	~Comment() = default;
public:
	const char* GetData() const { return _data.c_str(); }
	String Textize() const;
	virtual bool CheckTypeMask(UInt32 typeMask, const char* tagName) const {
		return typeMask & TypeMask::Comment;
	}
	virtual Value* CreateValue() const override;
	virtual bool Compose(Stream& stream) const override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Comment& other) const { return this == &other; }
	bool IsEqualTo(const Comment& other) const { return IsIdentical(other); }
	bool IsLessThan(const Comment& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(xml)

#endif
