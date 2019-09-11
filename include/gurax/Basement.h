//==============================================================================
// Basement.h
//==============================================================================
#ifndef GURAX_BASEMENT_H
#define GURAX_BASEMENT_H
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
	int _argc;
	char** _argv;
	bool _debugFlag;
	bool _listingFlag;
	RefPtr<Frame> _pFrame;
	RefPtr<Stream> _pStreamCIn;
	RefPtr<Stream> _pStreamCOut;
	RefPtr<Stream> _pStreamCErr;
	RefPtr<SuffixMgrMap> _pSuffixMgrMap_Number;
	RefPtr<SuffixMgrMap> _pSuffixMgrMap_String;
	PathMgrOwner _pathMgrOwner;
	String _ps1;
	String _ps2;
	StringList _pathList;
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
	bool Initialize(int& argc, char** argv);
	int GetArgc() const { return _argc; }
	char** GetArgv() const { return _argv; }
	bool GetDebugFlag() const { return _debugFlag; }
	bool GetListingFlag() const { return _listingFlag; }
	void PrepareVType(Frame& frame);
	void PrepareValue(Frame& frame);
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
	SuffixMgrMap& GetSuffixMgrMap_Number() { return *_pSuffixMgrMap_Number; }
	SuffixMgrMap& GetSuffixMgrMap_String() { return *_pSuffixMgrMap_String; }
	const SuffixMgrMap& GetSuffixMgrMap_Number() const { return *_pSuffixMgrMap_Number; }
	const SuffixMgrMap& GetSuffixMgrMap_String() const { return *_pSuffixMgrMap_String; }
	void AssignSuffixMgr(SuffixMgr* pSuffixMgr, bool numberFlag);
	const SuffixMgr* LookupSuffixMgr(const Symbol* pSymbolSuffix, bool numberFlag) const;
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
};

}

#endif
