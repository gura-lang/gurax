//==============================================================================
// unittest.h
//==============================================================================
#ifndef UNITTEST_H
#define UNITTEST_H

#include <gurax.h>
#include "SampleRecord.h"

#define Gurax_TesterEntry(testerName) \
class Tester_##testerName : public Tester { \
public: \
	Tester_##testerName() : Tester(#testerName) {} \
	virtual void Entry(int argc, char* argv[]) const; \
} tester_##testerName; \
void Tester_##testerName::Entry(int argc, char* argv[]) const \

namespace Gurax {

class Tester;

class TesterList : public ListBase<Tester*> {
};

class Tester {
private:
	String _name;
	static TesterList _testerList;
public:
	Tester(String name) : _name(std::move(name)) { _testerList.push_back(this); }
	const char* GetName() const { return _name.c_str(); }
	virtual void Entry(int argc, char* argv[]) const = 0;
public:	
	static const TesterList& GetTesterList() { return _testerList; }
};

int Main(int argc, char* argv[]);
void PrintTitle(const char* title);

}

#endif
