//==============================================================================
// CommandLine.h
//==============================================================================
#ifndef GURAX_COMMANDLINE_H
#define GURAX_COMMANDLINE_H
#include "Referable.h"
#include "String.h"
#include "StringStyle.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE CommandLine {
public:
	enum class Type { Bool, String, Int, MultiString, MultiInt };
	class Opt : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Opt);
	private:
		Type _type;
		String _keyLong;
		char _keyShort;
	public:
		// Constructor
		Opt(Type type, String keyLong, char keyShort) :
			_type(type), _keyLong(std::move(keyLong)), _keyShort(keyShort) {}
		// Copy constructor/operator
		Opt(const Opt& src) = delete;
		Opt& operator=(const Opt& src) = delete;
		// Move constructor/operator
		Opt(Opt&& src) = delete;
		Opt& operator=(Opt&& src) noexcept = delete;
	protected:
		// Destructor
		~Opt() = default;
	public:
		const char* GetKeyLong() const { return _keyLong.c_str(); }
		char GetKeyShort() const { return _keyShort; }
		bool IsTypeBool() const { return _type == Type::Bool; }
		bool IsTypeString() const { return _type == Type::String || _type == Type::MultiString; }
		bool IsTypeInt() const { return _type == Type::Int || _type == Type::MultiInt; }
		bool IsMulti() const { return _type == Type::MultiString || _type == Type::MultiInt; }
		String MakeKeyArg(bool longFlag) const;
	};
	class OptList : public ListBase<Opt*> {
	};
	class OptOwner : public OptList {
	public:
		~OptOwner() { Clear(); }
		void Clear() {
			for (auto pOpt : *this) Opt::Delete(pOpt);
			clear();
		}
	};
	using OptMapByKeyLong = std::map<String, const Opt*>;
	using OptMapByKeyShort = std::map<char, const Opt*>;
	class Map : public std::map<String, StringList*> {
	public:
		~Map() { Clear(); }
		void Clear() {
			for (auto iter : *this) delete iter.second;
			clear();
		}
	};
public:
	int argc;
	const char** argv;
private:
	OptOwner _optOwner;
	OptMapByKeyLong _optMapByKeyLong;
	OptMapByKeyShort _optMapByKeyShort;
	Map _map;
	String _strErr;
public:
	// Constructor
	CommandLine();
	// Copy constructor/operator
	CommandLine(const CommandLine& src) = delete;
	CommandLine& operator=(const CommandLine& src) = delete;
	// Move constructor/operator
	CommandLine(CommandLine&& src) = delete;
	CommandLine& operator=(CommandLine&& src) noexcept = delete;
	// Destructor
	~CommandLine();
public:
	CommandLine& AddOpt(Opt* pOpt);
	CommandLine& OptBool(String keyLong) { return OptBool(std::move(keyLong), '\0'); }
	CommandLine& OptBool(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::Bool, std::move(keyLong), keyShort));
	}
	CommandLine& OptString(String keyLong) { return OptString(std::move(keyLong), '\0'); }
	CommandLine& OptString(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::String, std::move(keyLong), keyShort));
	}
	CommandLine& OptInt(String keyLong) { return OptInt(std::move(keyLong), '\0'); }
	CommandLine& OptInt(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::Int, std::move(keyLong), keyShort));
	}
	CommandLine& OptMultiString(String keyLong) { return OptMultiString(std::move(keyLong), '\0'); }
	CommandLine& OptMultiString(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::MultiString, std::move(keyLong), keyShort));
	}
	void ClearMap() { _map.Clear(); }
	bool Parse(int argc, const char* argv[]);
	bool Parse(int argc, char* argv[]) { return Parse(argc, const_cast<const char**>(argv)); }
	bool IsSpecified(const char* keyLong) const;
	bool GetBool(const char* keyLong) const;
	const char* GetString(const char* keyLong, const char* defValue) const;
	const StringList& GetStringList(const char* keyLong) const;
	Int GetInt(const char* keyLong, Int defValue) const;
	//IntList GetIntList(const char* keyLong) const;
	const char* GetError() const { return _strErr.c_str(); }
private:
	const char* _GetString(const char* keyLong) const;
};

}

#endif
