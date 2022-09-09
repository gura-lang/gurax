//==============================================================================
// Writer.h
//==============================================================================
#ifndef GURAX_MODULE_CSV_WRITER_H
#define GURAX_MODULE_CSV_WRITER_H
#include <gurax.h>

Gurax_BeginModuleScope(csv)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Writer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Writer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("csv.Writer");
private:
	String _str;
	RefPtr<Stream> _pStream;
private:
	static String _format;
public:
	// Constructor
	Writer(Stream* pStream) : _pStream(pStream) {}
	// Copy constructor/operator
	Writer(const Writer& src) = delete;
	Writer& operator=(const Writer& src) = delete;
	// Move constructor/operator
	Writer(Writer&& src) noexcept = delete;
	Writer& operator=(Writer&& src) noexcept = delete;
protected:
	~Writer() = default;
public:
	bool PutValue(String& str, const Value& value);
	bool PutValues(const ValueList& valList);
	Stream& GetStream() { return *_pStream; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Writer& other) const { return this == &other; }
	bool IsEqualTo(const Writer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Writer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(csv)

#endif
