//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define Gurax_BeginModuleHeader(name) \
namespace Gurax { namespace ModuleNS_##name {

#define Gurax_EndModuleHeader(name) \
GURAX_DLLEXPORT bool Entry(Frame& frame); \
GURAX_DLLEXPORT Module *Import(Frame& frameOuter); \
}}

#define Gurax_BeginModuleBody(name) \
namespace Gurax { namespace ModuleNS_##name {

#define Gurax_EndModuleBody(name) \
GURAX_DLLEXPORT Module* Import(Frame& frameOuter) \
{ \
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol()); \
	pDottedSymbol->AppendFromString(#name, '_'); \
	RefPtr<Module> pModule(new Module(pDottedSymbol.release(), frameOuter.Reference())); \
	if (!Entry(pModule->GetFrame())) return nullptr; \
	return pModule.release(); \
} \
}}

#define Gurax_BeginModuleScope(name) \
namespace Gurax { namespace ModuleNS_##name {

#define Gurax_EndModuleScope(name) \
}}

#if defined(GURAX_MODULE_SEPARATED)
#define Gurax_RegisterModule(name) \
extern "C" GURAX_DLLEXPORT \
bool GuraxModuleValidate() \
{ \
	return Gurax::ModuleNS_##name::Validate(); \
} \
extern "C" GURAX_DLLEXPORT \
bool GuraxModuleEntry(Gurax::Frame& frame) \
{ \
	return Gurax::ModuleNS_##name::Entry(frame); \
} \
extern "C" GURAX_DLLEXPORT \
void GuraxModuleTerminate(Gurax::Module& module) \
{ \
	Gurax::ModuleNS_##name::Terminate(module); \
}
#else // GURAX_MODULE_INTEGRATED
#define Gurax_RegisterModule(name)
#endif

#define Gurax_ModuleValidate() \
GURAX_DLLEXPORT bool Validate()

#define Gurax_ModuleEntry() \
GURAX_DLLEXPORT bool Entry(Frame& frame)

#define Gurax_ModuleTerminate() \
GURAX_DLLEXPORT void Terminate(Module& module)

Gurax_BeginModuleBody(sys)

Gurax_ModuleEntry()
{
	return true;
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModuleBody(sys)
