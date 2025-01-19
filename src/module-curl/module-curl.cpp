//==============================================================================
// module-curl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(curl)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Initialize tables
	Info::Bootup();
	Opt::Bootup();
	// Assignment of VTYPE
	Assign(VTYPE_CURL);
	Assign(VTYPE_CURLU);
	Assign(VTYPE_curl_mime);
	Assign(VTYPE_curl_mimepart);
	Assign(VTYPE_curl_slist);
	Assign(VTYPE_Info);
	Assign(VTYPE_Opt);
	// Assignment of const
	AssignConsts(GetFrame());
	// Assignment of function
	AssignFunctions(GetFrame());
	// Assignment of path manager
	PathMgr::Assign(new PathMgrEx());
	// Initialize Curl
	::curl_global_init(CURL_GLOBAL_ALL);
	return true;
}

Gurax_ModuleTerminate()
{
}

#if 0
static long OnChunkBgn(curl_fileinfo* finfo, void* data, int remains)
{
	::printf("%-40s  %10zd %d\n", finfo->filename, finfo->size, finfo->filetype);
	/*
	CURLFILETYPE_DIRECTORY:
	CURLFILETYPE_FILE:
	*/
	return CURL_CHUNK_BGN_FUNC_SKIP;
}

static long OnChunkEnd(void* data)
{
	return CURL_CHUNK_END_FUNC_OK;
}
#endif

Gurax_EndModule(curl)
