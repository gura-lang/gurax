//==============================================================================
// module-curl.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(curl)

// curl.Test()
Gurax_DeclareFunction(Test)
{
	Declare(VTYPE_Nil, Flag::None);
	AddHelp(Gurax_Symbol(en), u8R"**(

)**");
}

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

Gurax_ImplementFunction(Test)
{
	/* curl easy handle */ 
	CURL *handle;
 
	/* initialization of easy handle */ 
	handle = curl_easy_init();
	if(!handle) {
		curl_global_cleanup();
		return Value::nil();
	}
 
	/* turn on wildcard matching */ 
	curl_easy_setopt(handle, CURLOPT_WILDCARDMATCH, 1L);
 
	//curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);

	/* callback is called before download of concrete file started */ 
	curl_easy_setopt(handle, CURLOPT_CHUNK_BGN_FUNCTION, OnChunkBgn);
	curl_easy_setopt(handle, CURLOPT_CHUNK_END_FUNCTION, OnChunkEnd);
 
	/* this callback will write contents into files */ 
	//curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_it);
 
	/* put transfer data into callbacks */ 
	//curl_easy_setopt(handle, CURLOPT_CHUNK_DATA, &data);
	//curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);
 
	//curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
 
	/* set an URL containing wildcard pattern (only in the last part) */ 
	curl_easy_setopt(handle, CURLOPT_URL, "ftp://speedtest.tele2.net/*");
	//curl_easy_setopt(handle, CURLOPT_URL, "http://example.com/*");
 
	/* and start transfer! */
	curl_easy_perform(handle);
 
	curl_easy_cleanup(handle);
	return Value::nil();
}

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
	Assign(Gurax_CreateFunction(Test));
	curl_global_init(CURL_GLOBAL_ALL);
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(curl)
