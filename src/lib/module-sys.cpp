//==============================================================================
// module-sys.cpp
//==============================================================================
#include "stdafx.h"

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define Gurax_BeginModuleHeader(name) \
namespace Gurax { namespace Module_##name { \
class ModuleEx : public Module { \
public: \
	using Module::Module; \
	virtual void DoPrepare(); \
}; \
Module* Create(Frame& frameOuter); \

#define Gurax_EndModuleHeader(name) }}

#define Gurax_BeginModule(name) \
namespace Gurax { namespace Module_##name { \
Module* Create(Frame& frameOuter) \
{ \
	RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol()); \
	pDottedSymbol->AppendFromString(#name, '_'); \
	RefPtr<Module> pModule(new ModuleEx(pDottedSymbol.release(), frameOuter.Reference())); \
	pModule->Prepare(); \
	return pModule.release(); \
}

#define Gurax_BeginModuleScope(name) \
namespace Gurax { namespace Module_##name {

#define Gurax_EndModuleScope(name) }}

#if defined(GURAX_MODULE_SEPARATED)
#define Gurax_EndModule(name) \
extern "C" GURAX_DLLEXPORT \
bool GuraxModuleValidate() \
{ \
	return Gurax::Module_##name::Validate(); \
} \
extern "C" GURAX_DLLEXPORT \
Gurax::Module* GuraxModuleCreate(Gurax::Frame& frame) \
{ \
	return Gurax::Module_##name::Create(frame); \
} \
extern "C" GURAX_DLLEXPORT \
void GuraxModuleTerminate(Gurax::Module& module) \
{ \
	Gurax::Module_##name::Terminate(module); \
} \
}}
#else // GURAX_MODULE_INTEGRATED
#define Gurax_EndModule(name) }}
#endif

#define Gurax_ModuleValidate() \
bool Validate()

#define Gurax_ModulePrepare() \
void ModuleEx::DoPrepare()

#define Gurax_ModuleTerminate() \
void Terminate(Module& module)

Gurax_BeginModuleHeader(sys)
Gurax_EndModuleHeader(sys)

Gurax_BeginModule(sys)

Gurax_ModuleValidate()
{
	return true;
}

Gurax_ModulePrepare()
{
}

Gurax_ModuleTerminate()
{
}

Gurax_EndModule(sys)
