//==============================================================================
// Writer.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// Writer
//------------------------------------------------------------------------------
Writer::Writer(Stream* pStream) : _pStream(pStream)
{
}

bool Writer::Add(const char* fileName, Stream& stream)
{
	return false;
}

String Writer::ToString(const StringStyle& ss) const
{
	return String().Format("tar.Writer");
}

Gurax_EndModuleScope(tar)
