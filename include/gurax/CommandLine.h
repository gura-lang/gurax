//==============================================================================
// CommandLine.h
//==============================================================================
#ifndef GURAX_COMMANDLINE_H
#define GURAX_COMMANDLINE_H
#include "String.h"

namespace Gurax {

//------------------------------------------------------------------------------
// CommandLine
//------------------------------------------------------------------------------
class CommandLine {
public:
	enum class Type { Flag, Value };
	struct Info {
		const char* keyLong;
		char keyShort;
		Type type;
	};
	typedef std::map<String, Info> InfoMapByKeyLong;
	typedef std::map<char, Info> InfoMapByKeyShort;
	typedef std::map<String, StringList*> Map;
private:
	InfoMapByKeyLong _infoMapByKeyLong;
	InfoMapByKeyShort _infoMapByKeyShort;
	Map _map;
public:
	CommandLine() {}
	~CommandLine();
	CommandLine& AddInfo(const Info* infoTbl, int cntInfo);
	bool Parse(int& argc, const char* argv[], String& strErr);
	bool IsSet(const char* key);
	const char* GetString(const char* key, const char* defValue) const;
	const StringList& GetStringList(const char* key) const;
	Int GetInt(const char* key, Int defValue) const;
private:
	const char* _GetString(const char* key) const;
};

}

#endif
