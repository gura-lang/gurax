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
	enum class Type { Flag, Value };
	class Info : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(Info);
	private:
		String _keyLong;
		char _keyShort;
		Type _type;
	public:
		// Constructor
		Info(String keyLong, char keyShort, Type type) :
			_keyLong(std::move(keyLong)), _keyShort(keyShort), _type(type) {}
		// Copy constructor/operator
		Info(const Info& src) = delete;
		Info& operator=(const Info& src) = delete;
		// Move constructor/operator
		Info(Info&& src) = delete;
		Info& operator=(Info&& src) noexcept = delete;
	protected:
		// Destructor
		~Info() = default;
	public:
		const char* GetKeyLong() const { return _keyLong.c_str(); }
		char GetKeyShort() const { return _keyShort; }
		Type GetType() const { return _type; }
	};
	class InfoList : public std::vector<Info*> {
	};
	class InfoOwner : public InfoList {
	public:
		~InfoOwner() { Clear(); }
		void Clear() {
			for (auto pInfo : *this) Info::Delete(pInfo);
			clear();
		}
	};
	using InfoMapByKeyLong = std::map<String, const Info*>;
	using InfoMapByKeyShort = std::map<char, const Info*>;
	using Map = std::map<String, StringList*>;
private:
	InfoOwner _infoOwner;
	InfoMapByKeyLong _infoMapByKeyLong;
	InfoMapByKeyShort _infoMapByKeyShort;
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
	void AddInfo(Info* pInfo);
	void AddInfo(String keyLong, char keyShort, Type type) {
		AddInfo(new Info(std::move(keyLong), keyShort, type));
	}
	bool Parse(int& argc, char* argv[]);
	bool IsSet(const char* keyLong);
	const char* GetString(const char* keyLong, const char* defValue) const;
	const StringList& GetStringList(const char* keyLong) const;
	Int GetInt(const char* keyLong, Int defValue) const;
	const char* GetError() const { return _strErr.c_str(); }
private:
	const char* _GetString(const char* keyLong) const;
};

}

#endif
