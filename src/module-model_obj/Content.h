//==============================================================================
// Content.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_CONTENT_H
#define GURAX_MODULE_MODEL_OBJ_CONTENT_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

//------------------------------------------------------------------------------
// Content
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Content : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Content);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("model.obj.Content");
public:
	enum class TokenId { None, EndOfLine, EndOfFile, Field, };
	class Tokenizer {
	public:
		enum class Stat { LineTop, SkipToNextLine, Field, SkipWhite, FileEnd, };
	private:
		Stat _stat;
		size_t _iLine;
		size_t _iChar;
		char _field[128];
		TokenId _tokenIdPending;
	public:
		Tokenizer() : _stat(Stat::LineTop), _iLine(0), _iChar(0), _tokenIdPending(TokenId::None) {}
		TokenId Tokenize(Stream& stream);
		inline const char* GetField() const { return _field; }
		inline size_t GetLineNo() const { return _iLine + 1; }
	};
public:
	// Constructor
	Content() {}
	// Copy constructor/operator
	Content(const Content& src) = delete;
	Content& operator=(const Content& src) = delete;
	// Move constructor/operator
	Content(Content&& src) noexcept = delete;
	Content& operator=(Content&& src) noexcept = delete;
protected:
	~Content() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Content& other) const { return this == &other; }
	bool IsEqualTo(const Content& other) const { return IsIdentical(other); }
	bool IsLessThan(const Content& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(model_obj)

#endif
