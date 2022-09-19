//==============================================================================
// Parser.h
//==============================================================================
#ifndef GURAX_MODULE_YAML_PARSER_H
#define GURAX_MODULE_YAML_PARSER_H
#include <gurax.h>

Gurax_BeginModuleScope(yaml)

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Parser : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Parser);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("yaml.Parser");
public:
	// Constructor
	Parser() {}
	// Copy constructor/operator
	Parser(const Parser& src) = delete;
	Parser& operator=(const Parser& src) = delete;
	// Move constructor/operator
	Parser(Parser&& src) noexcept = delete;
	Parser& operator=(Parser&& src) noexcept = delete;
protected:
	~Parser() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Parser& other) const { return this == &other; }
	bool IsEqualTo(const Parser& other) const { return IsIdentical(other); }
	bool IsLessThan(const Parser& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(yaml)

#endif
