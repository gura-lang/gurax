//==============================================================================
// module-codecs.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModule(codecs)

//-----------------------------------------------------------------------------
// Implementation of function
//-----------------------------------------------------------------------------
// codecs.GetEncodings()
Gurax_DeclareFunction(GetEncodings)
{
	Declare(VTYPE_List, Flag::None);
	AddHelp(
		Gurax_Symbol(en),
		"Returns a list of registered encoding names.");
}

Gurax_ImplementFunction(GetEncodings)
{
	RefPtr<ValueOwner> pValues(new ValueOwner());
	for (CodecFactory* pCodecFactory : CodecFactory::GetList()) {
		pValues->push_back(new Value_String(pCodecFactory->GetName()));
	}
	return new Value_List(pValues.release());
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
	// Assignment of function
	Assign(Gurax_CreateFunction(GetEncodings));
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(codecs)
