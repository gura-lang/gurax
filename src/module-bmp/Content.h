//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_BMP_CONTENT_H
#define GURAX_MODULE_BMP_CONTENT_H
#include <gurax.h>
#include "ImageExtension.h"

Gurax_BeginModuleScope(bmp)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
protected:
	BitmapFileHeader _bfh;
	BitmapInfoHeader _bih;
	RefPtr<Memory> _pMemory;
public:
	// Constructor
	Content() : _bfh{0}, _bih{0} {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	const BitmapFileHeader& GetBitmapFileHeader() const { return _bfh; }
	const BitmapInfoHeader& GetBitmapInfoHeader() const { return _bih; }
	const Memory* GetMemory() const { return _pMemory.get(); }
public:
	bool Read(Stream& stream);
	bool Write(Stream& stream) const;
	bool ReadHeader(Stream& stream);
	bool WriteHeader(Stream& stream) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(bmp)

#endif
