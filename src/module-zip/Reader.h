//==============================================================================
// Reader.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_READER_H
#define GURAX_MODULE_ZIP_READER_H
#include <gurax.h>
#include "PathExtension.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Reader : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Reader);
private:
	RefPtr<Stream> _pStreamSrc;
	StatExOwner _statExOwner;
public:
	// Constructor
	Reader(Stream* pStreamSrc) : _pStreamSrc(pStreamSrc) {}
	// Copy constructor/operator
	Reader(const Reader& src) = delete;
	Reader& operator=(const Reader& src) = delete;
	// Move constructor/operator
	Reader(Reader&& src) = delete;
	Reader& operator=(Reader&& src) noexcept = delete;
protected:
	~Reader() = default;
public:
	Stream& GetStreamSrc() { return *_pStreamSrc; }
	StatExOwner& GetStatExOwner() { return _statExOwner; }
	bool ReadCentralDirectory();
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
	RefPtr<Reader> _pReader;
	size_t _idx;
	bool _skipDirFlag;
public:
	Iterator_Entry(Reader* pReader, bool skipDirFlag) :
		_pReader(pReader), _idx(0), _skipDirFlag(skipDirFlag) {}
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenDetermined;
	}
	virtual size_t GetLength() const override { return _pReader->GetStatExOwner().size(); }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(zip)

#endif
