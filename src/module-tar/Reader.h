//==============================================================================
// Reader.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_READER_H
#define GURAX_MODULE_TAR_READER_H
#include <gurax.h>
#include "PathExtension.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Reader : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Reader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("tar.Reader");
private:
	RefPtr<Stream> _pStreamSrc;
public:
	// Constructor
	Reader(Stream* pStreamSrc) : _pStreamSrc(pStreamSrc) {}
	// Copy constructor/operator
	Reader(const Reader& src) = delete;
	Reader& operator=(const Reader& src) = delete;
	// Move constructor/operator
	Reader(Reader&& src) noexcept = delete;
	Reader& operator=(Reader&& src) noexcept = delete;
protected:
	~Reader() = default;
public:
	void Close() {}
	Stream& GetStreamSrc() { return *_pStreamSrc; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Reader& other) const { return this == &other; }
	bool IsEqualTo(const Reader& other) const { return IsIdentical(other); }
	bool IsLessThan(const Reader& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Iterator_Entry
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_Entry : public Iterator {
private:
	bool _doneFlag;
	size_t _offsetNext;
	RefPtr<Reader> _pReader;
	bool _skipDirFlag;
public:
	Iterator_Entry(Reader* pReader, bool skipDirFlag);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(tar)

#endif
