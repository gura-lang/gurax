//==============================================================================
// CommandLine.h
//==============================================================================
#ifndef GURAX_COMMANDLINE_H
#define GURAX_COMMANDLINE_H
#include "Referable.h"
#include "String.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
class CommandLine {
public:
	enum class Type { Bool, String, Int };
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
		bool IsType(Type type) const { return _type == type; }
	};
	class OptList : public std::vector<Opt*> {
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
	using Map = std::map<String, StringList*>;
private:
	OptOwner _optOwner;
	OptMapByKeyLong _optMapByKeyLong;
	OptMapByKeyShort _optMapByKeyShort;
	Map _map;
	String _strErr;
public:
	// Constructor
	CommandLine() {}
	// Copy constructor/operator
	CommandLine(const CommandLine& src) = delete;
	CommandLine& operator=(const CommandLine& src) = delete;
	// Move constructor/operator
	CommandLine(CommandLine&& src) = delete;
	CommandLine& operator=(CommandLine&& src) noexcept = delete;
	// Destructor
	~CommandLine() {
		for (auto iter : _map) delete iter.second;
	}		
public:
	CommandLine& AddOpt(Opt* pOpt);
	CommandLine& OptBool(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::Bool, std::move(keyLong), keyShort));
	}
	CommandLine& OptString(String keyLong, char keyShort) {
		return AddOpt(new Opt(Type::String, std::move(keyLong), keyShort));
	}
	bool Parse(int& argc, char* argv[]);
	bool GetBool(const char* keyLong);
	const char* GetString(const char* keyLong, const char* defValue) const;
	const StringList& GetStringList(const char* keyLong) const;
	Int GetInt(const char* keyLong, Int defValue) const;
	const char* GetError() const { return _strErr.c_str(); }
private:
	const char* _GetString(const char* keyLong) const;
};

}

#endif
