//==============================================================================
// Solid.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_STL_SOLID_H
#define GURAX_MODULE_MODEL_STL_SOLID_H
#include <gurax.h>
#include "Face.h"

Gurax_BeginModuleScope(model_stl)

//------------------------------------------------------------------------------
// Solid
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Solid : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Solid);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.stl.Solid");
public:
	enum class Stat {
		facet, normal, normal_coords, outer, loop, vertex, vertex_coords, endloop, endfacet,
	};
	enum TokenId { None, EOL, EndOfFile, Field, };
	class Tokenizer {
	public:
		enum Stat { LineTop, Field, SkipWhite, FileEnd, };
	private:
		Stat _stat;
		size_t _iChar;
		char _field[128];
		TokenId _tokenIdPending;
	public:
		Tokenizer() : _stat(Stat::LineTop), _iChar(0), _tokenIdPending(TokenId::None) {}
		TokenId Tokenize(Stream& stream);
		inline const char* GetField() const { return _field; }
	};
private:
	RefPtr<Stream> _pStream;
	bool _binaryFlag;
	size_t _nFace;			// for binary
	String _text;			// header for binary / solid name for text
	Stat _stat;				// for text
	Tokenizer _tokenizer;	// for text
public:
	// Constructor
	Solid(Stream* pStream);
	// Copy constructor/operator
	Solid(const Solid& src) = delete;
	Solid& operator=(const Solid& src) = delete;
	// Move constructor/operator
	Solid(Solid&& src) noexcept = delete;
	Solid& operator=(Solid&& src) noexcept = delete;
protected:
	~Solid() = default;
public:
	bool Prepare();
	Stream& GetStream() { return *_pStream; }
	const char* GetName() const { return _text.c_str(); }
	Iterator* EachFace();
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Solid& other) const { return this == &other; }
	bool IsEqualTo(const Solid& other) const { return IsIdentical(other); }
	bool IsLessThan(const Solid& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Iterator_EachFace
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Iterator_EachFace : public Iterator {
private:
	RefPtr<Solid> _pSolid;
public:
	Iterator_EachFace(Solid* pSolid) : _pSolid(pSolid) {}
public:
	Solid& GetSolid() { return *_pSolid; }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override;
	virtual size_t GetLength() const override;
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(model_stl)

#endif
