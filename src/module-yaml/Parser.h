//==============================================================================
// Parser.h
//==============================================================================
#ifndef GURAX_MODULE_YAML_PARSER_H
#define GURAX_MODULE_YAML_PARSER_H
#include <gurax.h>
#include <yaml.h>

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
	using AnchorMap = std::map<String, Value*>;
	class Stocker {
	public:
		virtual void Stock(RefPtr<Value> pValue) = 0;
	};
	class StockerStack : public ListBase<Stocker*> {
	public:
		void Push(Stocker* pStocker) { push_back(pStocker); }
		void Pop() { delete back(); pop_back(); }
		Stocker* GetTop() { return back(); }
	};
	class Stocker_Stream : public Stocker {
	private:
		RefPtr<ValueOwner> _pValueOwner;
	public:
		Stocker_Stream(ValueOwner* pValueOwner) : _pValueOwner(pValueOwner) {}
		virtual void Stock(RefPtr<Value> pValue) override;
	};
	class Stocker_Mapping : public Stocker {
	private:
		RefPtr<Value_Dict> _pValueDict;
		RefPtr<Value> _pValueKey;
		bool _keyFlag;
	public:
		Stocker_Mapping(Value_Dict* pValueDict) : _pValueDict(pValueDict), _keyFlag(true) {}
		virtual void Stock(RefPtr<Value> pValue) override;
	};
	class Stocker_Sequence : public Stocker {
	private:
		RefPtr<Value_List> _pValueList;
	public:
		Stocker_Sequence(Value_List* pValueList) : _pValueList(pValueList) {}
		virtual void Stock(RefPtr<Value> pValue) override;
	};
private:
	yaml_parser_t _parser;
	RefPtr<Stream> _pStream;
	AnchorMap _anchorMap;
public:
	// Constructor
	Parser(Stream* pStream);
	// Copy constructor/operator
	Parser(const Parser& src) = delete;
	Parser& operator=(const Parser& src) = delete;
	// Move constructor/operator
	Parser(Parser&& src) noexcept = delete;
	Parser& operator=(Parser&& src) noexcept = delete;
protected:
	~Parser();
public:
	Stream& GetStream() { return *_pStream; }
	bool Parse(ValueOwner& valueOwner);
protected:
	static int ReadHandler(void* ext, char* buffer, int size, int* length);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Parser& other) const { return this == &other; }
	bool IsEqualTo(const Parser& other) const { return IsIdentical(other); }
	bool IsLessThan(const Parser& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(yaml)

#endif
