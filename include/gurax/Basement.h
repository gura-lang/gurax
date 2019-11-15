//==============================================================================
// Basement.h
//==============================================================================
#ifndef GURAX_BASEMENT_H
#define GURAX_BASEMENT_H
#include "CommandLine.h"
#include "Frame.h"
#include "Value.h"
#include "SuffixMgr.h"
#include "PathMgr.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Basement {
private:
	bool _commandDoneFlag;
	RefPtr<Frame> _pFrame;
	RefPtr<Stream> _pStreamCIn;
	RefPtr<Stream> _pStreamCOut;
	RefPtr<Stream> _pStreamCErr;
	RefPtr<SuffixMgrMap> _pSuffixMgrMap;
	PathMgrOwner _pathMgrOwner;
	String _ps1;
	String _ps2;
	StringList _pathList;
	RefPtr<Processor> _pProcessor;
	CommandLine _cmdLine;
public:
	static Basement Inst;
public:
	// Constructor
	Basement();
	// Copy constructor/operator
	Basement(const Basement& src) = delete;
	Basement& operator=(const Basement& src) = delete;
	// Move constructor/operator
	Basement(Basement&& src) = delete;
	Basement& operator=(Basement&& src) noexcept = delete;
	// Destructor
	~Basement() = default;
public:
	bool Initialize(int argc, char** argv);
	CommandLine& GetCommandLine() { return _cmdLine; }
	bool GetCommandDoneFlag() const { return _commandDoneFlag; }
	void PrepareVType();
	void PrepareValue();
	void PreparePathList();
	void PrepareFunction();
	void PrepareConsoleStream();
	bool ImportModule();
	bool ExecCommand();
	void AppendPathList(const String& str);
	void AppendPathList(const StringList& strs);
	Frame& GetFrame() { return *_pFrame; }
public:
	Stream& GetStreamCIn() { return *_pStreamCIn; }
	Stream& GetStreamCOut() { return *_pStreamCOut; }
	Stream& GetStreamCErr() { return *_pStreamCErr; }
	void SetStreamCIn(Stream* pStreamCIn) { _pStreamCIn.reset(pStreamCIn); }
	void SetStreamCOut(Stream* pStreamCOut) { _pStreamCOut.reset(pStreamCOut); }
	void SetStreamCErr(Stream* pStreamCErr) { _pStreamCErr.reset(pStreamCErr); }
public:
	SuffixMgrMap& GetSuffixMgrMap() { return *_pSuffixMgrMap; }
	const SuffixMgrMap& GetSuffixMgrMap() const { return *_pSuffixMgrMap; }
	void AssignSuffixMgr(SuffixMgr* pSuffixMgr) { GetSuffixMgrMap().Assign(pSuffixMgr); }
	const SuffixMgr* LookupSuffixMgr(SuffixMgr::Target target, const Symbol* pSymbolSuffix) const {
		return GetSuffixMgrMap().Lookup(target, pSymbolSuffix);
	}
public:
	const PathMgrList& GetPathMgrList() { return _pathMgrOwner; }
	void AssignPathMgr(PathMgr* pPathMgr) { _pathMgrOwner.push_back(pPathMgr); }
public:
	const char* GetPS1() const { return _ps1.c_str(); }
	const char* GetPS2() const { return _ps2.c_str(); }
	void SetPS1(const char* ps1) { _ps1 = ps1; }
	void SetPS2(const char* ps2) { _ps2 = ps2; }
	StringList& GetPathList() { return _pathList; }
	const StringList& GetPathList() const { return _pathList; }
	Processor& GetProcessor() { return *_pProcessor; }
};

}

#endif
