//==============================================================================
// DirectoryDummy.h
//==============================================================================
#ifndef GURAX_DIRECTORYDUMMY_H
#define GURAX_DIRECTORYDUMMY_H
#include "Directory.h"
#include "Stat.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// DirectoryDummy
//-----------------------------------------------------------------------------
class DirectoryDummy : public Directory {
public:
	class CoreEx : public Core {
	public:
		Gurax_DeclareReferable(CoreEx);
	private:
		RefPtr<StatDummy> _pStatDummy;
	public:
		CoreEx(String pathName, String name, char sep, bool caseFlag) :
			Core(Type::Folder, name, sep, caseFlag, new CoreOwner()),
			_pStatDummy(new StatDummy(pathName)) {}
		StatDummy* GetStatDummy() { return _pStatDummy.get(); }
	public:
		virtual Directory* GenerateDirectory() override { return new DirectoryDummy(Reference()); }
	};
private:
	size_t _idxChild;
public:
	DirectoryDummy(CoreEx* pCoreEx) : Directory(pCoreEx), _idxChild(0) {}
public:
	CoreEx& GetCoreEx() { return dynamic_cast<CoreEx&>(*_pCore); }
protected:
	virtual void DoRewindChild() override;
	virtual Directory* DoNextChild() override;
	virtual Value_Stat* DoCreateStatValue() override;
};

}

#endif
