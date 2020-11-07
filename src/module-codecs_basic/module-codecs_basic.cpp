//==============================================================================
// module-codecs_basic.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs_basic)

//------------------------------------------------------------------------------
// Entries
//------------------------------------------------------------------------------
Gurax_ModuleValidate()
{
	return Version::CheckCoreVersion(GURAX_VERSION, nullptr);
}

Gurax_ModulePrepare()
{
	// Registration of CodecFactory
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf-8"));
	CodecFactory::Register(new CodecFactory_Generic<Codec_Dumb>("utf_8"));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs_basic)
