//==============================================================================
// Reader.h
//==============================================================================
#ifndef GURAX_MODULE_CSV_READER_H
#define GURAX_MODULE_CSV_READER_H
#include <gurax.h>

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Reader : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Reader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("csv.Reader");
public:
	enum class Stat { LineTop, FieldTop, Field, Quoted, QuotedEnd };
private:
	RefPtr<Stream> _pStream;
	String _field;
public:
	// Constructor
	Reader(Stream* pStream);
	// Copy constructor/operator
	Reader(const Reader& src) = delete;
	Reader& operator=(const Reader& src) = delete;
	// Move constructor/operator
	Reader(Reader&& src) noexcept = delete;
	Reader& operator=(Reader&& src) noexcept = delete;
protected:
	~Reader() = default;
public:
	Stream& GetStream() { return *_pStream; }
	bool ReadLine(ValueOwner& valueOwner);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Reader& other) const { return this == &other; }
	bool IsEqualTo(const Reader& other) const { return IsIdentical(other); }
	bool IsLessThan(const Reader& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Iterator_ReadLineAsList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ReadLineAsList : public Iterator {
private:
	RefPtr<Reader> _pReader;
public:
	Iterator_ReadLineAsList(Reader* pReader) : _pReader(pReader) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//------------------------------------------------------------------------------
// Iterator_ReadLineAsTuple
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_ReadLineAsTuple : public Iterator {
private:
	RefPtr<Reader> _pReader;
public:
	Iterator_ReadLineAsTuple(Reader* pReader) : _pReader(pReader) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(csv)

#endif
