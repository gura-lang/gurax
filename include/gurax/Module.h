//==============================================================================
// Module.h
//==============================================================================
#ifndef GURAX_MODULE_H
#define GURAX_MODULE_H
#include "Referable.h"
#include "Help.h"
#include "Frame.h"

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define Gurax_BeginModuleHeader(name) \
namespace Gurax { namespace Module_##name { \
class ModuleEx : public Module { \
public: \
	using Module::Module; \
	virtual bool DoPrepare() override; \
}; \
inline Module* Create(Frame* pFrameOuter) { \
	RefPtr<Module> pModule(new ModuleEx(pFrameOuter));  \
	return pModule->Prepare(#name, '_')? pModule.release() : nullptr; \
}

#define Gurax_EndModuleHeader(name) }}

#define Gurax_BeginModuleScope(name) \
namespace Gurax { namespace Module_##name {

#define Gurax_EndModuleScope(name) }}

#define Gurax_BeginModule(name) \
namespace Gurax { namespace Module_##name {

#if defined(GURAX_MODULE_SEPARATED)
#define Gurax_EndModule(name) \
extern "C" GURAX_DLLEXPORT \
bool Gurax_ModuleValidate() \
{ \
	return Gurax::Module_##name::Validate(); \
} \
extern "C" GURAX_DLLEXPORT \
Gurax::Module* Gurax_ModuleCreate(Gurax::Frame* pFrameOuter) \
{ \
	return Gurax::Module_##name::Create(pFrameOuter); \
} \
extern "C" GURAX_DLLEXPORT \
void Gurax_ModuleTerminate(Gurax::Module& module) \
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
bool ModuleEx::DoPrepare()

#define Gurax_ModuleTerminate() \
void Terminate(Module& module)

namespace Gurax {

//------------------------------------------------------------------------------
// Module
//------------------------------------------------------------------------------
class Module : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Module);
public:
	using ModuleValidateT	= bool (*)();
	using ModuleCreateT		= Module* (*)(Frame* pFrameOuter);
	using ModuleTerminateT	= void (*)(Module& module);
protected:
	RefPtr<Frame> _pFrame;
	RefPtr<DottedSymbol> _pDottedSymbol;
	RefPtr<HelpProvider> _pHelpProvider;
	RefPtr<PropHandlerMap> _pPropHandlerMap;
	String _pathName;
public:
	// Constructor
	Module() = delete;
	Module(Frame* pFrameOuter) : Module(pFrameOuter, DottedSymbol::Empty.Reference()) {}
	Module(Frame* pFrameOuter, DottedSymbol* pDottedSymbol);
	// Copy constructor/operator
	Module(const Module& src) = delete;
	Module& operator=(const Module& src) = delete;
	// Move constructor/operator
	Module(Module&& src) = delete;
	Module& operator=(Module&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Module() = default;
public:
	void SetDottedSymbol(DottedSymbol* pDottedSymbol) { _pDottedSymbol.reset(pDottedSymbol); }
	const DottedSymbol& GetDottedSymbol() const { return *_pDottedSymbol; }
	void SetPathName(const char* pathName) { _pathName = pathName; }
	const char* GetPathName() const { return _pathName.c_str(); }
	void AddHelp(const Symbol* pLangCode, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(doc));
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	PropHandlerMap& GetPropHandlerMap() { return *_pPropHandlerMap; }
	const PropHandlerMap& GetPropHandlerMap() const { return *_pPropHandlerMap; }
	const PropHandler* LookupPropHandler(const Symbol* pSymbol) const {
		return GetPropHandlerMap().Lookup(pSymbol);
	}
	void Assign(const Symbol* pSymbol, Value* pValue) { GetFrame().Assign(pSymbol, pValue); }
	void Assign(const char* name, Value* pValue) { GetFrame().Assign(name, pValue); }
	void Assign(VType& vtype) { GetFrame().Assign(vtype); }
	void Assign(Function* pFunction) { GetFrame().Assign(pFunction); }
	void Assign(PropHandler* pPropHandler) { GetPropHandlerMap().Assign(pPropHandler); }
public:
	bool Prepare(DottedSymbol* pDottedSymbol);
	bool Prepare(const char* name, char separator);
	static Module* Import(Processor& processor, const DottedSymbol& dottedSymbol);
	static Module* ImportScript(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName);
	static Module* ImportBinary(Processor& processor, const DottedSymbol& dottedSymbol, const char* pathName);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Module& module) const { return this == &module; }
	bool IsEqualTo(const Module& module) const { return IsIdentical(module); }
	bool IsLessThan(const Module& module) const { return this < &module; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	// Virtual functions
	virtual bool DoPrepare() { return true; };
};

}

#endif
